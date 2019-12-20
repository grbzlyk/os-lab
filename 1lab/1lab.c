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
        printf(" ДИТИНА: Цей  процесс-дитина!\n");
        printf(" ДИТИНА: Мiй PID -- %d\n", getpid());
        printf(" ДИТИНА: PID мого батька -- %d\n", getppid());
        printf(" ДИТИНА: Введiть мiй код повернення (як можно меньше):");
        scanf("%d",&rv);
        printf(" ДИТИНА: Вихiд!\n");
        atexit(print);
        break;
    default:
        printf("БАТЬКО: Цей процесс-батько!\n");
        printf("БАТЬКО: Мiй PID -- %d\n", getpid());
        printf("БАТЬКО: PID моэй дитины %d\n",pid);
        printf("БАТЬКО: Я чекаю, поки дитина не викликаэ exit()...\n");
        wait(0);
        printf("БАТЬКО: Код повернення дитины:%d\n", WEXITSTATUS(rv));
        printf("БАТЬКО: Вихiд!\n");
        atexit(print);
        exit(rv);
        break;
    }
    atexit(print);
}