# Interrupts

## One: Ctrl+C Interrupt
1. Ctrl+C is an interrupt. Inspect interrupt_ctrlc.c and how it handles the Ctrl+C interrupt. Put a breakpoint in the interrupt service routine for Ctrl+C and observe its call stack. How many threads are in the process?

## Two: Simulating an Interrupt Vector Table in C
The interrupt vector is usually held in kernel space and we don't have access to it from user space. However we can simulate how it works. To simulate an interrupt vector table, we’ll create a simple array of function pointers, where each entry in the array represents an "interrupt vector." Each vector will point to a specific handler function for a different "interrupt."

- Inspect interrupt_vector_sim.c to understand how interrupt vectors work.
- Update the code to take an integer from the input (simulating an interrupt) and calling the corresponding ISR.


IRQ Number	Typical Use
IRQ0	    System timer
IRQ1	    Keyboard
IRQ3	    Serial port (COM2)
IRQ4	    Serial port (COM1)
IRQ6	    Floppy disk controller
IRQ8	    Real-time clock (RTC)
IRQ12	    Mouse
IRQ14	    Primary IDE channel
IRQ15	    Secondary IDE channel


## Observe Interrupt Information in Windows and Linux

- Linux: /etc/interrupts
Windows:
- msinfo32 ==> Hardware Resources ==> IRQs
- perfmon ==> Processor ==> Interrupt/Sec
- procexp ==> Interrupts process

Perform "I/O" heavy tasks such as copying large files or downloading and see how that effects interrupts/sec


## Make a system call using the syscall or (int 0x80) assembly instruction 
- Inspect and run the system_call_int.c function.
- Find the system call number location from linux source code
https://elixir.bootlin.com/linux/v6.11.5/source
- Find out what other system call are there
- Try to see if you can make another system call

## observe system calls made by a program
On Linux
- use "strace ls" to see the system calls made by the "ls" program
    1. Try to identify which system call "ls" is using to inquire about the files in the current folder.
    2. Try to identify the system call that "ls" is using to write the result to the terminal.
    
On Windows
- Use "procmon" from the System Internal tools available from Microsoft to observe activies related to a "notepad" process. 
    1. open procmon and add "image path" contains "notepad.exe" to its filter list.
    2. Start capturing events
    3. run notepad.exe
    4. Observe and inspect the events happening. Try to identify some of the system calls.
    5. Clear the events.
    6. Open a sample text file. Notice what new events happen and which one corresponds to the file you opened.
    7. Clear the events.
    8. Modify the file and save it.
    9. Inspect the new events and identify which system call is related to saving the file to the disk.