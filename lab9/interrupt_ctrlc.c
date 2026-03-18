#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Interrupt Service Routine (ISR) for handling SIGINT
void interrupt_handler(int signum) {
    printf("\nInterrupt Received: SIGINT (Ctrl+C)\n");
    printf("Interrupt handled by ISR\n");
}

int main() {
    // Register the interrupt handler for SIGINT
    signal(SIGINT, interrupt_handler);

    printf("Running... Press Ctrl+C to simulate an interrupt.\n");

    // Infinite loop to keep the program running
    while (1) {
        printf(".");
        fflush(stdout);  // Print dot continuously to simulate ongoing work
        sleep(1);
    }

    return 0;
}
