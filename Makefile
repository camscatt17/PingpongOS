tafera_parteA:
	gcc -Wall pingpong-scheduler-srtf.c ppos-core-aux.c libppos_static.a -o tarefa_parteA -lrt
	./tarefa_parteA

clean:
	rm teste_tarefa1_scheduler_teste_professor teste_tarefa1_scheduler