#include <stdio.h>
#include <stdlib.h>

#define NUM_INTERRUPTS 5  // Define a small number of interrupt vectors

// Define types for interrupt handlers (ISRs)
typedef void (*interrupt_handler_t)(void);

// Example interrupt handlers
void handler_0() { printf("Handling interrupt 0 (Timer)\n"); }
void handler_1() { printf("Handling interrupt 1 (Keyboard)\n"); }
void handler_2() { printf("Handling interrupt 2 (Disk)\n"); }
void handler_3() { printf("Handling interrupt 3 (Network)\n"); }
void handler_4() { printf("Handling interrupt 4 (Custom)\n"); }

// Simulated interrupt vector table
interrupt_handler_t interrupt_vector[NUM_INTERRUPTS];

// Function to initialize the interrupt vector table
void initialize_interrupt_vector() {
    interrupt_vector[0] = handler_0;
    interrupt_vector[1] = handler_1;
    interrupt_vector[2] = handler_2;
    interrupt_vector[3] = handler_3;
    interrupt_vector[4] = handler_4;
}

// Function to simulate triggering an interrupt
void trigger_interrupt(int interrupt_number) {
    if (interrupt_number < 0 || interrupt_number >= NUM_INTERRUPTS) {
        printf("Invalid interrupt number: %d\n", interrupt_number);
        return;
    }
    printf("Interrupt %d triggered: ", interrupt_number);
    interrupt_vector[interrupt_number]();  // Call the corresponding handler
}

int main() {
    initialize_interrupt_vector();

    // Simulate some interrupts
    trigger_interrupt(0);  // Simulate timer interrupt
    trigger_interrupt(1);  // Simulate keyboard interrupt
    trigger_interrupt(3);  // Simulate network interrupt
    trigger_interrupt(4);  // Simulate custom interrupt
    trigger_interrupt(5);  // Simulate an invalid interrupt

    return 0;
}
