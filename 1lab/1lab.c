#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void print() {printf("atexit() for pid %d\n",getpid());}

int atexit(void (*function)(void));

int main() {
pid_t pid;
int rv;

switch(pid=fork()) {
    case -1: perror("fork");
        /* ОШИБОЧКА ВЫШЛА */
        exit(1); /* ПОКА РОДИТЕЛИ */
    case 0:
        printf(" CHILD: Цей  процесс-дитина!\n");
        printf(" CHILD: Мiй PID -- %d\n", getpid());
        printf(" CHILD: PID мого батька -- %d\n", getppid());
        printf(" CHILD: Введiть мiй код повернення (як можно меньше):");
        scanf("%d",&rv);
        printf(" CHILD: Вихiд!\n");
        atexit(print);
        break;
    default:
        printf("PARENT: Цей процесс-батько!\n");
        printf("PARENT: Мiй PID -- %d\n", getpid());
        printf("PARENT: PID моэй дитины %d\n",pid);
        printf("PARENT: Я чекаю, поки дитина не викликаэ exit()...\n");
        wait(0);
        printf("PARENT: Код повернення дитины:%d\n", WEXITSTATUS(rv));
        printf("PARENT: Вихiд!\n");
        atexit(print);
        exit(rv);
        break;
    }
    atexit(print);
}