SHM_REGION_ONE:=19900604
SHM_REGION_TWO:=19900608
SHM_REGION_RESULT:=19900610

all: exe

exe:	solution.c
	gcc -Wall solution.c -o solution

write_exe:	write_shm.c
	gcc -Wall write_shm.c -o write_shm

clean:
	-rm solution write_shm 2>/dev/null

write_shm:	write_exe
	./write_shm $(SHM_REGION_ONE) $(SHM_REGION_TWO)

read_shm:	exe
	./solution $(SHM_REGION_ONE) $(SHM_REGION_TWO)

read_shm_debug:	exe
	./solution $(SHM_REGION_ONE) $(SHM_REGION_TWO) 1

clean_shm:
	ipcrm -M $(SHM_REGION_ONE)
	ipcrm -M $(SHM_REGION_TWO)
	ipcrm -M $(SHM_REGION_RESULT)
