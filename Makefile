tafera1_scheduler:
	gcc -Wall pingpong-scheduler_TESTE.c ppos-core-aux.c libppos_static.a -o teste_tarefa1_scheduler -lrt
	./teste_tarefa1_scheduler