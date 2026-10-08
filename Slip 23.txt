Slip 23
Q1
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void bubbleSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1]) { int t = a[j]; a[j] = a[j + 1]; a[j + 1] = t; }
}

void insertionSort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i], j = i - 1;
        while (j >= 0 && a[j] > key) { a[j + 1] = a[j]; j--; }
        a[j + 1] = key;
    }
}

int main() {
    int n;
    printf("Enter total number of elements (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) { printf("Invalid input size!\n"); return 1; }

    int arr[n];
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    printf("\nCreating child process using fork()...\n");
    pid_t pid = fork();

    if (pid < 0) { perror("Fork failed"); return 1; }
    else if (pid == 0) {
        printf("\n[Child Process - PID: %d] Sorting using Insertion Sort...\n", getpid());
        insertionSort(arr, n);
        printf("[Child Process] Sorted Array (Insertion Sort): ");
        for (int i = 0; i < n; i++) printf("%d ", arr[i]);
        printf("\n");
        exit(0);
    } else {
        wait(NULL);
        printf("\n[Parent Process - PID: %d] Child process finished.\n[Parent Process] Sorting using Bubble Sort...\n", getpid());
        bubbleSort(arr, n);
        printf("[Parent Process] Sorted Array (Bubble Sort): ");
        for (int i = 0; i < n; i++) printf("%d ", arr[i]);
        printf("\n");
    }
    return 0;
}

Output:

Enter total number of elements (n): 4
Enter 4 integers:
2
3 
6
2

Creating child process using fork()...

[Child Process - PID: 3094] Sorting using Insertion Sort...
[Child Process] Sorted Array (Insertion Sort): 2 2 3 6 

[Parent Process - PID: 3019] Child process finished.
[Parent Process] Sorting using Bubble Sort...
[Parent Process] Sorted Array (Bubble Sort): 2 2 3 6 


Q2
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Process {
    int pid, at, bt1, bt2, total_bt, ct, tat, wt, completed;
};

int main() {
    int n;
    printf("Enter total number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0) { printf("Invalid input!\n"); return 1; }

    struct Process p[n];
    srand(time(0));
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\n--- Process P%d ---\nArrival Time: ", p[i].pid);
        scanf("%d", &p[i].at);
        printf("1st CPU Burst: ");
        scanf("%d", &p[i].bt1);
        p[i].bt2 = (rand() % 10) + 1;
        p[i].total_bt = p[i].bt1 + p[i].bt2;
        p[i].completed = 0;
        printf("-> Generated 2nd CPU Burst: %d (Total Burst = %d)\n", p[i].bt2, p[i].total_bt);
    }

    int current_time = 0, completed_count = 0, gc_count = 0;
    int gc_pid[100], gc_start[100], gc_end[100];
    float total_tat = 0, total_wt = 0;

    while (completed_count < n) {
        int idx = -1, min_bt = 999999;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && !p[i].completed) {
                if (p[i].total_bt < min_bt || (p[i].total_bt == min_bt && p[i].at < p[idx].at)) {
                    min_bt = p[i].total_bt;
                    idx = i;
                }
            }
        }
        if (idx != -1) {
            gc_pid[gc_count] = p[idx].pid;
            gc_start[gc_count] = current_time;
            current_time += p[idx].total_bt;
            gc_end[gc_count++] = current_time;

            p[idx].ct = current_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].total_bt;
            total_tat += p[idx].tat;
            total_wt += p[idx].wt;
            p[idx].completed = 1;
            completed_count++;
        } else {
            current_time++;
        }
    }

    printf("\n=============================================\n                 GANTT CHART                 \n=============================================\n ");
    for (int i = 0; i < gc_count; i++) printf("-------");
    printf("\n|");
    for (int i = 0; i < gc_count; i++) printf("  P%d  |", gc_pid[i]);
    printf("\n ");
    for (int i = 0; i < gc_count; i++) printf("-------");
    printf("\n%d", gc_start[0]);
    for (int i = 0; i < gc_count; i++) printf("      %d", gc_end[i]);

    printf("\n\n=========================================================================================\n");
    printf("PID\tAT\tBT1\tBT2\tTotal BT\tCT\tTAT\tWT\n");
    printf("=========================================================================================\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt1, p[i].bt2, p[i].total_bt,
               p[i].ct, p[i].tat, p[i].wt);
    }
    printf("=========================================================================================\n");
    printf("\nAverage Turnaround Time = %.2f\nAverage Waiting Time    = %.2f\n", total_tat / n, total_wt / n);

    return 0;
}
Output:

Enter total number of processes: 3

--- Process P1 ---
Arrival Time: 2
1st CPU Burst: 1
-> Generated 2nd CPU Burst: 9 (Total Burst = 10)

--- Process P2 ---
Arrival Time: 3
1st CPU Burst: 2
-> Generated 2nd CPU Burst: 8 (Total Burst = 10)

--- Process P3 ---
Arrival Time: 4
1st CPU Burst: 3
-> Generated 2nd CPU Burst: 4 (Total Burst = 7)

=============================================
                 GANTT CHART                 
=============================================
 ---------------------
|  P1  |  P3  |  P2  |
 ---------------------
2      12      19      29

=========================================================================================
PID	AT	BT1	BT2	Total BT	CT	TAT	WT
=========================================================================================
P1	2	1	9	10		12	10	0
P2	3	2	8	10		29	26	16
P3	4	3	4	7		19	15	8
=========================================================================================

Average Turnaround Time = 17.00
Average Waiting Time    = 8.00
