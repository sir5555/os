#slip 15 

#Q1]

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {                   // Child
        sleep(2);                      // Wait for parent to exit
        printf("Child: PID=%d, new parent PID=%d\n",
               getpid(), getppid());
    } else {                           // Parent
        printf("Parent: PID=%d, child PID=%d\n", getpid(), pid);
        printf("Parent exits now.\n");
    }

    return 0;
}

/*
OUTPUT

Parent: PID=1177, child PID=1181
Parent exits now.

*/

#Q2]

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20

int main(void) {
    int n, at[MAX], first[MAX], second[MAX], priority[MAX];
    int remaining[MAX], finish[MAX], done[MAX] = {0};
    int currentTime = 0, completed = 0;
    int ganttTime[10000], ganttProcess[10000], g = 0;
    double totalWT = 0, totalTAT = 0;

    srand((unsigned)time(NULL));

    printf("Number of processes (max %d): ", MAX);
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Enter a number between 1 and %d.\n", MAX);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("P%d: arrival time, first CPU burst, priority: ", i + 1);
        scanf("%d %d %d", &at[i], &first[i], &priority[i]);

        second[i] = rand() % 5 + 1;
        remaining[i] = first[i] + second[i];

        printf("Random second CPU burst for P%d = %d\n", i + 1, second[i]);
    }

    while (completed < n) {
        int p = -1;

        /* Choose the ready process with the highest priority.
           A smaller priority number means higher priority. */
        for (int i = 0; i < n; i++) {
            if (!done[i] && at[i] <= currentTime &&
                (p == -1 || priority[i] < priority[p])) {
                p = i;
            }
        }

        if (p == -1) {
            currentTime++;             /* CPU is idle */
            continue;
        }

        if (g >= 10000) {
            printf("Gantt chart limit reached.\n");
            return 1;
        }

        ganttTime[g] = currentTime;
        ganttProcess[g] = p;
        g++;

        remaining[p]--;
        currentTime++;

        if (remaining[p] == 0) {
            done[p] = 1;
            finish[p] = currentTime;
            completed++;
        }
    }

    printf("\nGantt chart:\n");
    for (int i = 0; i < g; i++)
        printf("| P%d ", ganttProcess[i] + 1);
    printf("|\n%d", ganttTime[0]);
    for (int i = 0; i < g; i++)
        printf("   %d", ganttTime[i] + 1);
    printf("\n\n");

    printf("Process  Turnaround Time  Waiting Time\n");
    for (int i = 0; i < n; i++) {
        int turnaround = finish[i] - at[i];
        int waiting = turnaround - first[i] - second[i];

        printf("P%-7d %-16d %d\n", i + 1, turnaround, waiting);
        totalTAT += turnaround;
        totalWT += waiting;
    }

    printf("\nAverage turnaround time = %.2f\n", totalTAT / n);
    printf("Average waiting time    = %.2f\n", totalWT / n);

    return 0;
}

/*
OUTPUT:-
Number of processes (max 20): 2 
P1: arrival time, first CPU burst, priority: 12 23 43
Random second CPU burst for P1 = 5
P2: arrival time, first CPU burst, priority: 10 9 3
Random second CPU burst for P2 = 4

Gantt chart:
| P2 | P2 | P2 | P2 | P2 | P2 | P2 | P2 | P2 | P2 | P2 | P2 | P2 | P1 | P1 | P1 | P1 | P1 | P1 | P1 | P1 | P1 | P1 | P1 | P1 | P1 | P1 | P1 | P1 | P1 | P1 | P1 | P1 | P1 | P1 | P1 | P1 | P1 | P1 | P1 | P1 |
10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25   26   27   28   29   30   31   32   33   34   35   36   37   38   39   40   41   42   43   44   45   46   47   48   49   50   51

Process  Turnaround Time  Waiting Time
P1       39               11
P2       13               0

Average turnaround time = 26.00
Average waiting time    = 5.50

*/