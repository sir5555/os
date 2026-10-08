Slip 26
Q1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Process {
    int pid, at, bt1, bt2, total_bt, rem_bt, priority, ct, tat, wt;
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
        printf("Priority: ");
        scanf("%d", &p[i].priority);
        p[i].bt2 = (rand() % 10) + 1;
        p[i].total_bt = p[i].bt1 + p[i].bt2;
        p[i].rem_bt = p[i].total_bt;
        printf("-> Generated 2nd CPU Burst: %d (Total = %d)\n", p[i].bt2, p[i].total_bt);
    }

    int time = 0, completed = 0, gc_pid[1000], gc_start[1000], gc_end[1000], gc_count = 0;

    while (completed < n) {
        int idx = -1, min_prio = 99999;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rem_bt > 0) {
                if (p[i].priority < min_prio || (p[i].priority == min_prio && p[i].at < p[idx].at)) {
                    min_prio = p[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            if (gc_count > 0 && gc_pid[gc_count - 1] == p[idx].pid) {
                gc_end[gc_count - 1] = ++time;
            } else {
                gc_pid[gc_count] = p[idx].pid;
                gc_start[gc_count] = time;
                gc_end[gc_count++] = ++time;
            }
            p[idx].rem_bt--;
            if (p[idx].rem_bt == 0) {
                completed++;
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].total_bt;
            }
        } else {
            time++;
        }
    }

    printf("\n================================ GANTT CHART ================================\n |");
    for (int i = 0; i < gc_count; i++) printf(" P%d |", gc_pid[i]);
    printf("\n%d", gc_start[0]);
    for (int i = 0; i < gc_count; i++) printf("    %d", gc_end[i]);

    float tot_tat = 0, tot_wt = 0;
    printf("\n\nPID\tAT\tBT1\tBT2\tTotal\tPrio\tCT\tTAT\tWT\n-------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        tot_tat += p[i].tat; tot_wt += p[i].wt;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", 
               p[i].pid, p[i].at, p[i].bt1, p[i].bt2, p[i].total_bt, p[i].priority, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("\nAvg Turnaround Time = %.2f\nAvg Waiting Time    = %.2f\n", tot_tat / n, tot_wt / n);

    return 0;
}
Output:

Enter total number of processes: 3

--- Process P1 ---
Arrival Time: 1
1st CPU Burst: 
2
Priority (Lower number = Higher priority): 3
-> Generated 2nd CPU Burst: 4 (Total Burst = 6)

--- Process P2 ---
Arrival Time: 2
1st CPU Burst: 3
Priority (Lower number = Higher priority): 4
-> Generated 2nd CPU Burst: 8 (Total Burst = 11)

--- Process P3 ---
Arrival Time: 1
1st CPU Burst: 4
Priority (Lower number = Higher priority): 2
-> Generated 2nd CPU Burst: 1 (Total Burst = 5)

=================================================================================
                                  GANTT CHART                                    
=================================================================================
 ---------------------
|  P3  |  P1  |  P2  |
 ---------------------
1      6      12      23

=================================================================================================
PID	AT	BT1	BT2	Total BT	Priority	CT	TAT	WT
=================================================================================================
P1	1	2	4	6		3		12	11	5
P2	2	3	8	11		4		23	21	10
P3	1	4	1	5		2		6	5	0
=================================================================================================

Average Turnaround Time = 12.33
Average Waiting Time    = 5.00


Q2
#include <stdio.h>
#include <stdlib.h>

int main() {
    int def_ref[] = {3, 4, 5, 6, 3, 4, 7, 3, 4, 5, 6, 7, 2, 4, 6}, f_count, choice;
    
    printf("Enter number of memory frames: ");
    if (scanf("%d", &f_count) != 1 || f_count <= 0) { printf("Invalid!\n"); return 1; }

    int frames[f_count];
    for (int i = 0; i < f_count; i++) frames[i] = -1;

    printf("1. Default string\n2. Custom string\nChoice: ");
    scanf("%d", &choice);

    int *ref = def_ref, len = 15;
    if (choice == 2) {
        printf("Enter length: "); scanf("%d", &len);
        ref = malloc(len * sizeof(int));
        printf("Enter string: ");
        for (int i = 0; i < len; i++) scanf("%d", &ref[i]);
    }

    int faults = 0, fifo = 0;
    printf("\n--- FIFO Simulation ---\n");
    for (int i = 0; i < len; i++) {
        int page = ref[i], found = 0;
        for (int j = 0; j < f_count; j++) if (frames[j] == page) { found = 1; break; }

        if (!found) { frames[fifo] = page; fifo = (fifo + 1) % f_count; faults++; }

        printf("Page %2d -> [ ", page);
        for (int j = 0; j < f_count; j++) 
            if (frames[j] == -1) printf("- "); else printf("%d ", frames[j]);
        printf(found ? "]\n" : "] -> Page Fault\n");
    }

    printf("========================================\nTotal Page Faults = %d\n", faults);
    if (choice == 2) free(ref);
    return 0;
}
Output:

Enter number of memory frames: 3

Choose Reference String:
1. Use default string (3, 4, 5, 6, 3, 4, 7, 3, 4, 5, 6, 7, 2, 4, 6)
2. Enter custom reference string
Enter choice (1 or 2): 1

--- FIFO Page Replacement Simulation ---
Reference String: 3 4 5 6 3 4 7 3 4 5 6 7 2 4 6 

Page  3 -> [ 3 - - ] -> Page Fault
Page  4 -> [ 3 4 - ] -> Page Fault
Page  5 -> [ 3 4 5 ] -> Page Fault
Page  6 -> [ 6 4 5 ] -> Page Fault
Page  3 -> [ 6 3 5 ] -> Page Fault
Page  4 -> [ 6 3 4 ] -> Page Fault
Page  7 -> [ 7 3 4 ] -> Page Fault
Page  3 -> [ 7 3 4 ]
Page  4 -> [ 7 3 4 ]
Page  5 -> [ 7 5 4 ] -> Page Fault
Page  6 -> [ 7 5 6 ] -> Page Fault
Page  7 -> [ 7 5 6 ]
Page  2 -> [ 2 5 6 ] -> Page Fault
Page  4 -> [ 2 4 6 ] -> Page Fault
Page  6 -> [ 2 4 6 ]

========================================
Total Number of Page Faults = 11
========================================
