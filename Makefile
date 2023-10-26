tafera_parteA:
	gcc -Wall pingpong-scheduler-srtf.c ppos-core-aux.c libppos_static.a -o tarefa_parteA -lrt
	./tarefa_parteA

tafera_teste_contab:
	gcc -Wall pingpong-contab-prio.c ppos-core-aux.c libppos_static.a -o tafera_teste_contab -lrt
	./tafera_teste_contab

clean:
	rm teste_tarefa1_scheduler_teste_professor teste_tarefa1_scheduler