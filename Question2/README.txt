Name: Tashya Aryan
Roll Number: 2401MC03
Set Number: Not provided

kalloc.c updates and reads the free-page count under kmem.lock once allocator locking is enabled.
vm.c walks the page table without allocating pages and combines the physical frame with the offset for a user-accessible mapping.
defs.h declares the helpers, syscall.h and syscall.c register the calls, and sysproc.c selects the calling process's page table.
user.h and usys.S expose the calls to user programs, and Makefile installs memtest in the xv6 image.
memtest.c prints page counts and translations and uses a pipe to order parent and child output before reporting the count after wait.
Makefile also detects the i686-elf toolchain and suppresses three warnings in stock xv6 files for modern GCC.
