#slip 19] 

#Q1]

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n, at[20], bt[20], rem[20], pr[20], ct[20];
    int time = 0, done = 0;

    printf("Number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("P%d arrival time, first burst, priority: ", i + 1);
        scanf("%d%d%d", &at[i], &bt[i], &pr[i]);
        rem[i] = bt[i];
    }

    while (done < n) {
        int p = -1;

        for (int i = 0; i < n; i++)
            if (at[i] <= time && rem[i] > 0 &&
                (p == -1 || pr[i] < pr[p]))
                p = i;

        if (p == -1) {
            time++;
            continue;
        }

        time++;
        rem[p]--;

        if (rem[p] == 0) {
            ct[p] = time;
            done++;
        }
    }

    printf("\nProcess  Next Burst\n");
    for (int i = 0; i < n; i++)
        printf("P%d       %d\n", i + 1, rand() % 10 + 1);

    return 0;
}

/*
OUTPUT

Number of processes: 3
P1 arrival time, first burst, priority: 0 2 1
P2 arrival time, first burst, priority: 1 3 4
P3 arrival time, first burst, priority: 3 6 2

Process  Next Burst
P1       4
P2       7
P3       8

*/

#Q2]

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int main(void) {
    pid_t pid = fork();

    if (pid == 0) {
        errno = 0;
        int value = nice(-5);  // Attempt to increase priority

        if (value == -1 && errno != 0)
            perror("nice");

        printf("Child process: PID = %d\n", getpid());
    } else if (pid > 0) {
        wait(NULL);
        printf("Parent: child finished\n");
    } else {
        perror("fork");
    }

    return 0;
}

/*
OUTPUT:-

nice: Operation not permitted
Child process: PID = 5933
Parent: child finished

*/