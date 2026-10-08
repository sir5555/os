#slip 18] 

#Q1]

#include <stdio.h>

int main() {
    int n, at[20], bt[20], rt[20], ct[20], wt[20], tat[20];
    int time = 0, done = 0, shortest;
    float avgWT = 0, avgTAT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and first burst for P%d: ", i + 1);
        scanf("%d%d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    while (done < n) {
        shortest = -1;

        for (int i = 0; i < n; i++)
            if (at[i] <= time && rt[i] > 0 &&
                (shortest == -1 || rt[i] < rt[shortest]))
                shortest = i;

        if (shortest == -1) {
            time++;
            continue;
        }

        rt[shortest]--;  // Run for one time unit
        time++;

        if (rt[shortest] == 0) {
            ct[shortest] = time;
            done++;
        }
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        avgWT += wt[i];
        avgTAT += tat[i];
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("Average waiting time = %.2f\n", avgWT / n);
    printf("Average turnaround time = %.2f\n", avgTAT / n);
    return 0;
}

/*
OUTPUT

Enter number of processes: 5
Enter arrival time and first burst for P1: 0 1
Enter arrival time and first burst for P2: 2 3
Enter arrival time and first burst for P3: 3 4
Enter arrival time and first burst for P4: 5 6
Enter arrival time and first burst for P5: 6 7

Process AT      BT      CT      TAT     WT
P1      0       1       1       1       0
P2      2       3       5       3       0
P3      3       4       9       6       2
P4      5       6       15      10      4
P5      6       7       22      16      9
Average waiting time = 3.00
Average turnaround time = 7.20

*/

#Q2]

#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        sleep(3);
        printf("Child process: PID = %d, Parent PID = %d\n",
               getpid(), getppid());
    } else if (pid > 0) {
        printf("Parent process: PID = %d\n", getpid());
        printf("Parent terminates before child.\n");
    } else {
        perror("fork failed");
    }

    return 0;
}

/*
OUTPUT:-

Parent process: PID = 2111
Parent terminates before child.

*/