#slip 13]
#Q1]

#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, j, time = 0;
    int at[20], bt[20], ct[20], tat[20], wt[20];
    int done[20] = {0};
    int order[20], count = 0;
    float avgWT = 0, avgTAT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter arrival time for P%d: ", i + 1);
        scanf("%d", &at[i]);

        // Generate a random CPU burst from 1 to 10
        bt[i] = rand() % 10 + 1;
        printf("Burst time for P%d = %d\n", i + 1, bt[i]);
    }

    while (count < n) {
        int shortest = -1;

        for (i = 0; i < n; i++) {
            if (!done[i] && at[i] <= time &&
                (shortest == -1 || bt[i] < bt[shortest])) {
                shortest = i;
            }
        }

        if (shortest == -1) {
            time++;             // No process has arrived yet
        } else {
            time += bt[shortest];
            ct[shortest] = time;
            tat[shortest] = ct[shortest] - at[shortest];
            wt[shortest] = tat[shortest] - bt[shortest];

            done[shortest] = 1;
            order[count++] = shortest;
        }
    }

    printf("\nGantt chart:\n");
    for (i = 0; i < n; i++)
        printf("| P%d ", order[i] + 1);
    printf("|\n");

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
        avgWT += wt[i];
        avgTAT += tat[i];
    }

    printf("\nAverage waiting time = %.2f", avgWT / n);
    printf("\nAverage turnaround time = %.2f\n", avgTAT / n);

    return 0;
}

/*
OUTPUT

Enter number of processes: 4
Enter arrival time for P1: 3
Burst time for P1 = 4
Enter arrival time for P2: 1
Burst time for P2 = 7
Enter arrival time for P3: 2
Burst time for P3 = 8

*/

#Q2]

#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, diskSize, i, j, temp;
    int request[50], order[50], total = 0;

    printf("Enter total number of disk blocks: ");
    scanf("%d", &diskSize);

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter disk requests: ");
    for (i = 0; i < n; i++)
        scanf("%d", &request[i]);

    printf("Enter starting head position: ");
    scanf("%d", &head);

    // Sort requests in increasing order
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (request[i] > request[j]) {
                temp = request[i];
                request[i] = request[j];
                request[j] = temp;
            }

    // LOOK: move left first, then reverse direction
    int k = 0;
    for (i = n - 1; i >= 0; i--)
        if (request[i] < head)
            order[k++] = request[i];

    for (i = 0; i < n; i++)
        if (request[i] >= head)
            order[k++] = request[i];

    printf("Service order: ");
    for (i = 0; i < n; i++) {
        printf("%d ", order[i]);
        total += abs(head - order[i]);
        head = order[i];
    }

    printf("\nTotal head movement = %d\n", total);
    return 0;
}

/*
OUTPUT

Enter total number of disk blocks: 4
Enter number of requests: 3
Enter disk requests: 2
4
5
Enter starting head position: 6
Service order: 5 4 2
Total head movement = 4

*/