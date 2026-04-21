COMPILER = gcc
FLAGS_COMPILER = -Wall -O2
FLAGS_LINKER = -luser32 -lgdi32 -mwindows

main.exe : main.c
	$(COMPILER) $(FLAGS_COMPILER) main.c -o main.exe $(FLAGS_LINKER)