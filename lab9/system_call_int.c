#include <unistd.h>

int main() {
    const char *msg = "Hello, from direct syscall!\r\n";
    int syscall_number = 1;   // SYS_write on x86_64 Linux
    int file_descriptor = 1;  // File descriptor for stdout
    int length = 27;          // Length of the message

    // Use inline assembly to call the `write` system call directly with `syscall`
    asm("syscall" 
        : // no output
        : "a"(syscall_number), "D"(file_descriptor), "S"(msg), "d"(length)
    );

    return 0;
}



// Anatomy of the asm Statement
// The asm statement syntax is as follows:

// c
// Copy code
// asm("assembly code" : output operands : input operands : clobbered registers);
// "assembly code": The assembly instructions you want to execute—in this case, "syscall".
// output operands: Specifies any registers or memory locations where the assembly code should place output values (optional).
// input operands: Lists the input values for the assembly code.
// clobbered registers: Lists any registers that are modified by the assembly code and whose values the compiler should not assume to be preserved (optional).
// Let’s break down each part of the statement used in our example.

// 1. "syscall" – The Assembly Code
// This is the actual assembly instruction we want to execute. "syscall" is the x86-64 instruction used to make system calls in Linux on 64-bit systems. It triggers a transition from user mode to kernel mode, so the CPU can execute the system call specified in rax and handle any necessary arguments passed in other registers.

// 2. : // no output
// The : following "syscall" specifies the beginning of the output operands section. In this case, we have no output operands because the syscall instruction only performs an action (a system call) and does not return a value directly through registers in this example. Therefore, this section is left empty.

// 3. : "a"(syscall_number), "D"(file_descriptor), "S"(msg), "d"(length)
// This is the input operands section, where we define the input values passed to the assembly code. Each operand specifies a register constraint, followed by the variable or value to load into that register.
// "a"(syscall_number): The "a" constraint tells the compiler to place syscall_number into the rax register. In x86-64 Linux, rax holds the system call number for the syscall instruction, and in this example, syscall_number = 1, which corresponds to the write system call.
// "D"(file_descriptor): The "D" constraint tells the compiler to place file_descriptor into the rdi register. On x86-64 Linux, the first argument to a system call goes into rdi, which is file_descriptor (set to 1 for stdout).
// "S"(msg): The "S" constraint tells the compiler to place msg into the rsi register. rsi holds the second argument to the system call, which is the pointer to the message we want to write.
// "d"(length): The "d" constraint tells the compiler to place length into the rdx register. rdx holds the third argument to the system call, which is the length of the message.

// Why These Specific Constraints?
// The "a", "D", "S", and "d" constraints map to specific registers (rax, rdi, rsi, and rdx, respectively) based on the calling conventions of the x86-64 architecture for system calls.

// rax ("a"): Holds the system call number.
// rdi ("D"): Holds the first argument.
// rsi ("S"): Holds the second argument.
// rdx ("d"): Holds the third argument.
// Using these constraints ensures the values are placed in the correct registers for the syscall instruction to execute successfully.