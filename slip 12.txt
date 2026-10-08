# slip 12

# Q.1]

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int arrival[n], burst1[n], burst2[n], total[n];
    int waiting[n], turnaround[n], completion[n];
    int order[n], done[n];

    srand((unsigned)time(NULL));

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and first CPU burst for P%d: ", i + 1);
        scanf("%d %d", &arrival[i], &burst1[i]);

        burst2[i] = rand() % 10 + 1;  // Random burst from 1 to 10
        total[i] = burst1[i] + burst2[i];

        printf("Random next CPU burst for P%d: %d\n", i + 1, burst2[i]);
    }

    // Select processes in FCFS order: earliest arrival first.
    int time = 0;
    for (int position = 0; position < n; position++) {
        int selected = -1;

        for (int i = 0; i < n; i++) {
            if (!done[i] &&
                (selected == -1 || arrival[i] < arrival[selected])) {
                selected = i;
            }
        }

        if (time < arrival[selected])
            time = arrival[selected];

        order[position] = selected;
        time += total[selected];
        completion[selected] = time;
        done[selected] = 1;
    }

    double totalWaiting = 0, totalTurnaround = 0;

    printf("\nGantt chart:\n");
    printf("0");
    for (int i = 0; i < n; i++) {
        int p = order[i];
        int start = completion[p] - total[p];

        if (i == 0 && start > 0)
            printf(" -- idle -- %d", start);

        printf(" -- P%d -- %d", p + 1, completion[p]);
    }

    printf("\n\nProcess\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        turnaround[i] = completion[i] - arrival[i];
        waiting[i] = turnaround[i] - total[i];

        totalWaiting += waiting[i];
        totalTurnaround += turnaround[i];

        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n",
               i + 1, arrival[i], total[i], completion[i],
               waiting[i], turnaround[i]);
    }

    printf("\nAverage waiting time: %.2f\n", totalWaiting / n);
    printf("Average turnaround time: %.2f\n", totalTurnaround / n);

    return 0;
}

/*

# OUTPUT:-

Enter number of processes: 4
Enter arrival time and first CPU burst for P1: 0 1
Random next CPU burst for P1: 8
Enter arrival time and first CPU burst for P2: 1 3 
Random next CPU burst for P2: 5
Enter arrival time and first CPU burst for P3: 2 4
Random next CPU burst for P3: 4
Enter arrival time and first CPU burst for P4: 3 6
Random next CPU burst for P4: 4

Gantt chart:
0 -- P1 -- 9 -- P2 -- 17 -- P3 -- 25 -- P4 -- 35

Process Arrival Burst   Completion      Waiting Turnaround
P1      0       9       9               0       9
P2      1       8       17              8       16
P3      2       8       25              15      23
P4      3       10      35              22      32

Average waiting time: 11.25
Average turnaround time: 20.00

*/


#Q.2]

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void bubbleSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
}

void insertionSort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i], j = i - 1;

        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

void printArray(int a[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main(void) {
    int n, a[100], b[100];

    printf("Enter number of integers: ");
    scanf("%d", &n);

    printf("Enter the integers: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        b[i] = a[i];  // Copy for the child process
    }

    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    } else if (pid == 0) {
        insertionSort(b, n);
        printf("Child: insertion sort: ");
        printArray(b, n);
    } else {
        bubbleSort(a, n);
        printf("Parent: bubble sort: ");
        printArray(a, n);
        wait(NULL);
    }

    return 0;
}

/*
 OUTPUT 

Enter number of integers: 5
Enter the integers: 12 41 13 45 67
Parent: bubble sort: 12 13 41 45 67 
Child: insertion sort: 12 13 41 45 67
*/

