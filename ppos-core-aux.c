#include "ppos.h"
#include "ppos-core-globals.h"
#include "ppos_disk.h"
#include <signal.h>
#include <sys/time.h>

#define UNIX_PRIORIDADE_MINIMA -20
#define UNIX_PRIORIDADE_MAXIMA 20

#define _GNU_SOURCE


// ****************************************************************************
// Coloque aqui as suas modificações, p.ex. includes, defines variáveis, 
// estruturas e funções

#define SIGNAL_ALARM 14

void setSignal();
void setTimer();
void signalHandler(int signum);
void metricsHandler(task_t *pstPreviousTask, task_t *pstNextTask);
void printTaskInfo(void);

struct sigaction action;
struct itimerval timer;

int uiTaskStartingTick = 0;



// ****************************************************************************



void before_ppos_init () {
    // put your customization here
    setSignal();
    setTimer();

#ifdef DEBUG
    printf("\ninit - BEFORE");
#endif
}

void after_ppos_init () {
    // put your customization here
#ifdef DEBUG
    printf("\ninit - AFTER");
#endif
}

void before_task_create (task_t *task ) {
    // put your customization here
#ifdef DEBUG
    printf("\ntask_create - BEFORE - [%d]", task->id);
#endif
}

void after_task_create (task_t *task ) {
    // put your customization here
    if (task != NULL) {
        task->estimated_execution_time = 99999;
        task->time = 20;
    }
    
#ifdef DEBUG
    printf("\ntask_create - AFTER - [%d]", task->id);
#endif
}

void before_task_exit () {
    // put your customization here
    if (taskExec != NULL) { 
        taskExec->remaining_execution_time = (systemTime - taskExec->remaining_execution_time);
        printTaskInfo();
    }
#ifdef DEBUG
    printf("\ntask_exit - BEFORE - [%d]", taskExec->id);
#endif
}

void after_task_exit () {
    // put your customization here
    
#ifdef DEBUG
    printf("\ntask_exit - AFTER- [%d]", taskExec->id);
#endif
}

void before_task_switch ( task_t *task ) {
    // put your customization here
    if (task != NULL) {
        task->time = 20;
        metricsHandler(taskExec, task);
    }
#ifdef DEBUG
    printf("\ntask_switch - BEFORE - [%d -> %d]", taskExec->id, task->id);
#endif
}

void after_task_switch ( task_t *task ) {
    // put your customization here
#ifdef DEBUG
    printf("\ntask_switch - AFTER - [%d -> %d]", taskExec->id, task->id);
#endif
}

void before_task_yield () {
    // put your customization hereW
#ifdef DEBUG
    printf("\ntask_yield - BEFORE - [%d]", taskExec->id);
#endif
}
void after_task_yield () {
    // put your customization here
#ifdef DEBUG
    printf("\ntask_yield - AFTER - [%d]", taskExec->id);
#endif
}


void before_task_suspend( task_t *task ) {
    // put your customization here
#ifdef DEBUG
    printf("\ntask_suspend - BEFORE - [%d]", task->id);
#endif
}

void after_task_suspend( task_t *task ) {
    // put your customization here
#ifdef DEBUG
    printf("\ntask_suspend - AFTER - [%d]", task->id);
#endif
}

void before_task_resume(task_t *task) {
    // put your customization here
#ifdef DEBUG
    printf("\ntask_resume - BEFORE - [%d]", task->id);
#endif
}

void after_task_resume(task_t *task) {
    // put your customization here
#ifdef DEBUG
    printf("\ntask_resume - AFTER - [%d]", task->id);
#endif
}

void before_task_sleep () {
    // put your customization here
#ifdef DEBUG
    printf("\ntask_sleep - BEFORE - [%d]", taskExec->id);
#endif
}

void after_task_sleep () {
    // put your customization here
#ifdef DEBUG
    printf("\ntask_sleep - AFTER - [%d]", taskExec->id);
#endif
}

int before_task_join (task_t *task) {
    // put your customization here
#ifdef DEBUG
    printf("\ntask_join - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_task_join (task_t *task) {
    // put your customization here
#ifdef DEBUG
    printf("\ntask_join - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}


int before_sem_create (semaphore_t *s, int value) {
    // put your customization here
#ifdef DEBUG
    printf("\nsem_create - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_sem_create (semaphore_t *s, int value) {
    // put your customization here
#ifdef DEBUG
    printf("\nsem_create - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_sem_down (semaphore_t *s) {
    // put your customization here
#ifdef DEBUG
    printf("\nsem_down - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_sem_down (semaphore_t *s) {
    // put your customization here
#ifdef DEBUG
    printf("\nsem_down - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_sem_up (semaphore_t *s) {
    // put your customization here
#ifdef DEBUG
    printf("\nsem_up - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_sem_up (semaphore_t *s) {
    // put your customization here
#ifdef DEBUG
    printf("\nsem_up - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_sem_destroy (semaphore_t *s) {
    // put your customization here
#ifdef DEBUG
    printf("\nsem_destroy - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_sem_destroy (semaphore_t *s) {
    // put your customization here
#ifdef DEBUG
    printf("\nsem_destroy - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_mutex_create (mutex_t *m) {
    // put your customization here
#ifdef DEBUG
    printf("\nmutex_create - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_mutex_create (mutex_t *m) {
    // put your customization here
#ifdef DEBUG
    printf("\nmutex_create - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_mutex_lock (mutex_t *m) {
    // put your customization here
#ifdef DEBUG
    printf("\nmutex_lock - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_mutex_lock (mutex_t *m) {
    // put your customization here
#ifdef DEBUG
    printf("\nmutex_lock - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_mutex_unlock (mutex_t *m) {
    // put your customization here
#ifdef DEBUG
    printf("\nmutex_unlock - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_mutex_unlock (mutex_t *m) {
    // put your customization here
#ifdef DEBUG
    printf("\nmutex_unlock - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_mutex_destroy (mutex_t *m) {
    // put your customization here
#ifdef DEBUG
    printf("\nmutex_destroy - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_mutex_destroy (mutex_t *m) {
    // put your customization here
#ifdef DEBUG
    printf("\nmutex_destroy - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_barrier_create (barrier_t *b, int N) {
    // put your customization here
#ifdef DEBUG
    printf("\nbarrier_create - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_barrier_create (barrier_t *b, int N) {
    // put your customization here
#ifdef DEBUG
    printf("\nbarrier_create - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_barrier_join (barrier_t *b) {
    // put your customization here
#ifdef DEBUG
    printf("\nbarrier_join - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_barrier_join (barrier_t *b) {
    // put your customization here
#ifdef DEBUG
    printf("\nbarrier_join - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_barrier_destroy (barrier_t *b) {
    // put your customization here
#ifdef DEBUG
    printf("\nbarrier_destroy - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_barrier_destroy (barrier_t *b) {
    // put your customization here
#ifdef DEBUG
    printf("\nbarrier_destroy - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_mqueue_create (mqueue_t *queue, int max, int size) {
    // put your customization here
#ifdef DEBUG
    printf("\nmqueue_create - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_mqueue_create (mqueue_t *queue, int max, int size) {
    // put your customization here
#ifdef DEBUG
    printf("\nmqueue_create - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_mqueue_send (mqueue_t *queue, void *msg) {
    // put your customization here
#ifdef DEBUG
    printf("\nmqueue_send - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_mqueue_send (mqueue_t *queue, void *msg) {
    // put your customization here
#ifdef DEBUG
    printf("\nmqueue_send - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_mqueue_recv (mqueue_t *queue, void *msg) {
    // put your customization here
#ifdef DEBUG
    printf("\nmqueue_recv - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_mqueue_recv (mqueue_t *queue, void *msg) {
    // put your customization here
#ifdef DEBUG
    printf("\nmqueue_recv - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_mqueue_destroy (mqueue_t *queue) {
    // put your customization here
#ifdef DEBUG
    printf("\nmqueue_destroy - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_mqueue_destroy (mqueue_t *queue) {
    // put your customization here
#ifdef DEBUG
    printf("\nmqueue_destroy - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

int before_mqueue_msgs (mqueue_t *queue) {
    // put your customization here
#ifdef DEBUG
    printf("\nmqueue_msgs - BEFORE - [%d]", taskExec->id);
#endif
    return 0;
}

int after_mqueue_msgs (mqueue_t *queue) {
    // put your customization here
#ifdef DEBUG
    printf("\nmqueue_msgs - AFTER - [%d]", taskExec->id);
#endif
    return 0;
}

void print_tcb( task_t* task ) {
    printf("\nId %d\n", &task->id);
    printf("\nAwake Time %d\n", &task->awakeTime);
    printf("\nEstimated Execution Time %d\n", &task->estimated_execution_time);
    printf("\nPrioridade Estatica %d\n", &task->prioridade_statica);
    printf("\nRemain Execution Time %d\n", &task->remaining_execution_time);
    printf("\nState %c\n", &task->state);
}

void task_setprio(task_t *task, int prio) {
    if ((UNIX_PRIORIDADE_MINIMA <= prio) && (UNIX_PRIORIDADE_MAXIMA >= prio)) {
        if (NULL != task) 
            task->prioridade_statica = prio;
        else
            taskExec->prioridade_statica = prio;
    }

    return;
}

int task_getprio(task_t *task) {
    if (task == NULL) {
        return taskExec->prioridade_statica;
    }
    return task->prioridade_statica;
}

task_t * scheduler() {
    if (readyQueue != NULL) {
        // printf("Entro na funcao scheduler\n");
        task_t* next_task = readyQueue;
        task_t* temp = readyQueue;
        int shortest_time = 99999999;
        do {
            // printf("Entro no while\n");
            if (temp->estimated_execution_time < shortest_time && temp->id != 0) {
                shortest_time = temp->estimated_execution_time;
                next_task = temp;
                // printf("Entro no if\n");
            }
            temp = temp->next;
        } while (temp != readyQueue);
        
        return next_task;
    }
    return NULL;
}

// -------------------- Colocando minhas funcoes daqui pra baixo
void setSignal() {
    action.sa_handler = signalHandler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    if (sigaction(SIGNAL_ALARM, &action, 0) < 0) {
        perror ("Erro em sigaction: ") ;
        exit (1) ;
    }
}

void setTimer() {
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 1000;

    if (setitimer(ITIMER_REAL, &timer, 0) < 0) {
        perror ("Erro em setitimer: ") ;
        exit (1) ;
    }
}

void task_set_eet (task_t *task, int et) {
    if (task == NULL) {
        taskExec->estimated_execution_time = et;

        return;
    }
    task->estimated_execution_time = et;
}


int task_get_eet(task_t *task) {
    if (task == NULL) {
        return taskExec->estimated_execution_time;
    }
    return task->estimated_execution_time;
}


int task_get_ret(task_t *task) {
    if (task == NULL) {
        return taskExec->remaining_execution_time;
    }
    return task->remaining_execution_time;
}

void signalHandler(int signum) {
    systemTime++;
    if (taskExec != NULL) {
        taskExec->remaining_execution_time++;
    }
    // se for uma tarefa de usuario (main, pang, ..., pung)
    if(taskExec != taskDisp) {
        // diminui o quantum da tarefa
        taskExec->time--;
        // se o quantum da tarefa terminou
        if(taskExec->time == 0) {
            // libera o processador para proxima tarefa
            task_yield();
        }
    }
}

void metricsHandler(task_t *pstPreviousTask, task_t *pstNextTask) {
    (pstPreviousTask->remaining_execution_time) += (systemTime - uiTaskStartingTick);

    (pstNextTask->uiActivations)++;

    uiTaskStartingTick = systemTime;
}

void printTaskInfo(void) {
    printf("Task %d exit: Execution time: %d ms Processor time: %d ms %d activations\n",
        taskExec->id,
        taskExec->remaining_execution_time,
        taskExec->estimated_execution_time,
        taskExec->uiActivations);

    return;
}