Name: Tashya Aryan
Roll Number: 2401MC03
Set Number: Not provided

sem.c adds eight counting semaphores and uses a shared lock with sleep and wakeup to coordinate access.
main.c initializes the lock at boot, and defs.h declares the semaphore functions for the kernel.
syscall.h and syscall.c register the system calls, and sysproc.c reads their arguments.
user.h and usys.S expose the calls to user programs, and Makefile builds sem.c and installs synctest.
synctest.c passes a permit between three children to print A B C five times, then the parent waits and prints Done.
Makefile also detects the i686-elf toolchain and suppresses three warnings in stock xv6 files for modern GCC.
