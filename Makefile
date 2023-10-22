tafera1_scheduler:
	gcc -Wall pingpong-scheduler_TESTE.c ppos-core-aux.c libppos_static.a -o teste_tarefa1_scheduler -lrt
	./teste_tarefa1_scheduler

tafera1_scheduler_teste_professor:
	gcc -Wall pingpong-scheduler_TESTE_PROFESSOR.c ppos-core-aux.c libppos_static.a -o teste_tarefa1_scheduler -lrt
	./teste_tarefa1_scheduler_teste_professor

clean:
	rm teste_tarefa1_scheduler_teste_professor teste_tarefa1_scheduler