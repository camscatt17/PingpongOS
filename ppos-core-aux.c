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

#define TIMER_STARTING_SHOT_S 1
#define TIMER_PERIOD_uS 1000
#define DEFAULT_TASK_TICKS 40
#define SIGALRM 14
#define UNIX_AGING_FACTOR -1

static void tickHandler(int signum);
static void metricsHandler(task_t *pstPreviousTask, task_t *pstNextTask);
static void printTaskInfo(void);
static task_t *getHighestPrioTaks(task_t *pstFirstTask);

// estrutura que define um tratador de sinal (deve ser global ou static)
struct sigaction action;

// estrutura de inicialização to timer
struct itimerval timer;

static int uiTaskStartingTick = 0;



// ****************************************************************************



void before_ppos_init () {
    // put your customization here

    action.sa_handler = tickHandler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    if (sigaction(SIGALRM, &action, 0) < 0)
    {
        perror("Sigaction error: ");
        exit(1);
    }

    // Timer initialization
    timer.it_value.tv_sec = TIMER_STARTING_SHOT_S;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = TIMER_PERIOD_uS;

    if (setitimer(ITIMER_REAL, &timer, 0) < 0)
    {
        perror("Setitimer error: ");
        exit(1);
    }

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
        // task->remaining_execution_time = systime();

        // printf("\n\n--------------------- INICIALIZO --------------------- %d\n\n", systime());
        // print_tcb(task);
    }
    task->time = 400;
    
#ifdef DEBUG
    printf("\ntask_create - AFTER - [%d]", task->id);
#endif
}

void before_task_exit () {
    // put your customization here

    taskExec->remaining_execution_time = (systemTime - taskExec->remaining_execution_time);

    printTaskInfo();
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
    // printf("\n\n--------------------- BEFORE --------------------- ");
    // if (task != NULL) {
    //     print_tcb(task);
    // }
    task->time = 400;
    metricsHandler(taskExec, task);
#ifdef DEBUG
    printf("\ntask_switch - BEFORE - [%d -> %d]", taskExec->id, task->id);
#endif
}

void after_task_switch ( task_t *task ) {
    // put your customization here
    // printf("\n\n--------------------- AFTER --------------------- ");
    // if (task != NULL) {
    //     print_tcb(task);
    // }
#ifdef DEBUG
    printf("\ntask_switch - AFTER - [%d -> %d]", taskExec->id, task->id);
#endif
}

void before_task_yield () {
    // put your customization here
    // taskExec->time = 20;
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
        do
        {
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

// task_t *scheduler()
// {
//     task_t *pstNextTask = readyQueue;

//     if (NULL != readyQueue)
//     {
//         pstNextTask = getHighestPrioTaks(readyQueue);
//         pstNextTask->prioridade_dinamica = pstNextTask->prioridade_statica;

//         task_t *pstListRunner = readyQueue;
//         task_t *pstFirstTask = readyQueue;

//         // The tasks list is a circular list, so this is the way to run through it
//         do
//         {
//             if (pstListRunner != pstNextTask)
//             {
//                 pstListRunner->prioridade_dinamica += UNIX_AGING_FACTOR;
//             }

//             pstListRunner = pstListRunner->next;
//         } while (pstFirstTask != pstListRunner);
//     }

//     return pstNextTask;
// }

void task_set_eet (task_t *task, int et) {
    if (task == NULL) {
        taskExec->estimated_execution_time = et;

        return;
    }
    task->estimated_execution_time = et;
    // task->remaining_execution_time = et;
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

static void tickHandler(int signum)
{
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

static void metricsHandler(task_t *pstPreviousTask, task_t *pstNextTask)
{
    // printf("\n\n--------------------- ENTRO NESSA FUNCAO DOIDA ------------------------\n\n");

    (pstPreviousTask->remaining_execution_time) += (systemTime - uiTaskStartingTick);

    (pstNextTask->uiActivations)++;

    uiTaskStartingTick = systemTime;
}

static void printTaskInfo(void)
{
    // if (0 == taskExec->id)
    // {
    //     finishDiskTask();
    // }

    printf("Task %d exit: Execution time: %d ms Processor time: %d ms %d activations\n",
        taskExec->id,
        taskExec->remaining_execution_time,
        taskExec->estimated_execution_time,
        taskExec->uiActivations);

    return;
}

static task_t *getHighestPrioTaks(task_t *pstFirstTask)
{
    task_t *pstHighestTask = pstFirstTask;
    task_t *pstListRunner = pstFirstTask;

    do
    {
        if (pstListRunner->prioridade_dinamica < pstHighestTask->prioridade_dinamica)
        {
            pstHighestTask = pstListRunner;
        }

        pstListRunner = pstListRunner->next;
    } while (pstFirstTask != pstListRunner);

    return pstHighestTask;
}