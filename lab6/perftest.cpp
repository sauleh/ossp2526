

#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <cmath>
#include <pthread.h>

extern "C" char* processRequest(const char* request);

void* add_rules(void* arg)
{
    const int count = *static_cast<int*>(arg);
    char request[80];
    for (int i = 0; i < count; ++i)
    {
        unsigned int second = static_cast<unsigned int>((i >> 16) & 255);
        unsigned int third = static_cast<unsigned int>((i >> 8) & 255);
        unsigned int fourth = static_cast<unsigned int>(i & 255);
        unsigned int fourthEnd = (fourth < 255U) ? (fourth + 1U) : fourth;
        unsigned int portStart = 1000U + static_cast<unsigned int>(i % 50000);
        unsigned int portEnd = portStart + 5U;

        std::snprintf(
            request,
            sizeof(request),
            "A 10.%u.%u.%u-10.%u.%u.%u %u-%u",
            second, third, fourth,
            second, third, fourthEnd,
            portStart, portEnd
        );

        char* response = processRequest(request);
        std::free(response);
    }
    return nullptr;
}

// parameters: 
// -t <number_of_threads>
// -n <number_of_requests>
int main(int argc, char** argv)
{
    int threadCount = 1;
    int requestCount = 100000;
    for (int i = 1; i + 1 < argc; i += 2)
    {
        const char* flag = argv[i];
        const int value = std::atoi(argv[i + 1]);
        if (flag[0] == '-' && flag[1] == 't' && flag[2] == '\0')
        {
            if (value > 0)
                threadCount = value;
        }
        else if (flag[0] == '-' && flag[1] == 'n' && flag[2] == '\0')
        {
            if (value > 0)
                requestCount = value;
        }
    }

    requestCount = requestCount / threadCount;
    pthread_t workers[threadCount];
    double elapsedMs[10];

    for (int run = 0; run < 10; ++run)
    {
        const auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < threadCount; ++i)
        {
            pthread_create(
                &workers[i],
                nullptr,
                add_rules,
                &requestCount
            );
        }
        for (int i = 0; i < threadCount; ++i)
            pthread_join(workers[i], nullptr);
        const auto end = std::chrono::high_resolution_clock::now();
        elapsedMs[run] = std::chrono::duration<double, std::milli>(end - start).count();
    }

    double sum = 0.0;
    double minTime = elapsedMs[0];
    double maxTime = elapsedMs[0];
    for (double t : elapsedMs)
    {
        sum += t;
        if (t < minTime)
            minTime = t;
        if (t > maxTime)
            maxTime = t;
    }
    const double mean = sum / 10.0;

    double sqDiffSum = 0.0;
    for (double t : elapsedMs)
    {
        const double diff = t - mean;
        sqDiffSum += diff * diff;
    }
    const double stddev = std::sqrt(sqDiffSum / 10.0);

    std::printf(
        "add_rules(%d) avg %.3f ms, stddev %.3f ms, min %.3f ms, max %.3f ms\n",
        requestCount,
        mean,
        stddev,
        minTime,
        maxTime
    );
}
