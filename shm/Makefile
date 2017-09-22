OBJ1=shmread
OBJ2=shmwrite

all:$(OBJ1) $(OBJ2)

$(OBJ1):shmread.o shm_ops.o
	gcc shmread.o shm_ops.o -o $(OBJ1)

shmread.o:shmread.c shm_ops.h
	gcc -c shmread.c

shm_ops.o:shm_ops.c shm_ops.h
	gcc -c shm_ops.c

$(OBJ2):shmwrite.o shm_ops.o
	gcc shmwrite.o shm_ops.o -o $(OBJ2)

shmwrite.o:shmwrite.c shm_ops.h
	gcc -c shmwrite.c

clean:
	rm -v *.o $(OBJ1) $(OBJ2)
