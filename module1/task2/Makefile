all: exe

exe: solution.c
	gcc solution.c -fPIC -ldl -o solution

lib: solution.c
	gcc -shared multiplier.c -fPIC -o libShared.so

clean:
	-rm solution 2>/dev/null