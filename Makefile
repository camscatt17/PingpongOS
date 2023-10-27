tafera_parteA:
	gcc -c -g ppos-core-aux.c
	gcc -Wall pingpong-scheduler-srtf.c ppos-core-aux.o libppos_static.a -o tarefa_parteA -lrt -g
	./tarefa_parteA

tafera_teste_contab:
	gcc -Wall pingpong-contab-prio.c ppos-core-aux.c libppos_static.a -o tafera_teste_contab -lrt
	./tafera_teste_contab

clean:
	rm tafera_teste_contab tarefa_parteA