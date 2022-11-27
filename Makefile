objects = main.o task_loader.o coordinator.o statistician.o

main : $(objects)
	cc -o main $(objects)

main.o :
	cc -g -c main.c

task_loader.o :
	cc -g -c task_loader.c

coordinator.o :
	cc -g -c coordinator.c

statistician.o :
	cc -g -c statistician.c

.PHONY : clean
clean :
	rm -rf main $(objects)