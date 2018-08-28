ulimit -c unlimited
gcc -g coredump.c -o coredump
./coredump
gdb ./coredump core
