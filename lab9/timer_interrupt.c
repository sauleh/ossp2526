#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

// Signal handler for the timer interrupt (SIGALRM)
void timer_handler(int signum) {
    static int count = 0;
    printf("Timer interrupt received! Count: %d\n", ++count);
}

int main() {
    struct itimerval timer;

    // Set up the signal handler for SIGALRM
    signal(SIGALRM, timer_handler);

    // Configure the timer to expire after 1 second (initial interval)
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 0;

    // Configure the timer to reset every 1 second (interval)
    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec = 0;

    // Start the timer
    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("Error setting timer");
        return 1;
    }

    // Keep the program running to allow the timer to trigger
    while (1) {
        pause();  // Wait for signals (interrupts)
    }

    return 0;
}
