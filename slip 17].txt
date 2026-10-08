#slip 17] 

#Q1]

#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, at[20], bt[20], wt[20], tat[20], done[20] = {0};
    int time = 0, completed = 0, totalWT = 0, totalTAT = 0;

    printf("Number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Arrival time and first CPU burst for P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
    }

    printf("\nNext CPU bursts (random):\n");
    for (int i = 0; i < n; i++) {
        int next = rand() % 10 + 1;
        bt[i] += next;
        printf("P%d: %d\n", i + 1, next);
    }

    printf("\nGantt chart:\n");
    while (completed < n) {
        int selected = -1;

        for (int i = 0; i < n; i++) {
            if (!done[i] && at[i] <= time &&
                (selected == -1 || bt[i] < bt[selected])) {
                selected = i;
            }
        }

        if (selected == -1) {
            time++;
            continue;
        }

        printf("| P%d ", selected + 1);
        wt[selected] = time - at[selected];
        time += bt[selected];
        tat[selected] = time - at[selected];
        done[selected] = 1;
        completed++;
    }
    printf("|\n");

    for (int i = 0; i < n; i++) {
        totalWT += wt[i];
        totalTAT += tat[i];
        printf("P%d: Waiting=%d, Turnaround=%d\n",
               i + 1, wt[i], tat[i]);
    }

    printf("Average waiting time = %.2f\n", (float)totalWT / n);
    printf("Average turnaround time = %.2f\n", (float)totalTAT / n);

    return 0;
}


/*
OUTPUT


Number of processes: 5
Arrival time and first CPU burst for P1: 1
0
Arrival time and first CPU burst for P2: 3 2
Arrival time and first CPU burst for P3: 4 3
Arrival time and first CPU burst for P4: 5 4
Arrival time and first CPU burst for P5: 6 5

Next CPU bursts (random):
P1: 4
P2: 7
P3: 8
P4: 6
P5: 4

Gantt chart:
| P1 | P2 | P5 | P4 | P3 |
P1: Waiting=0, Turnaround=4
P2: Waiting=2, Turnaround=11
P3: Waiting=29, Turnaround=40
P4: Waiting=18, Turnaround=28
P5: Waiting=8, Turnaround=17
Average waiting time = 11.40
Average turnaround time = 20.00

*/

#Q2]


#include <stdio.h>
#include <string.h>

int main() {
    int n, used[100] = {0}, start[20], length[20], files = 0;
    char name[20][20];
    int choice;

    printf("Number of disk blocks: ");
    scanf("%d", &n);

    /* Randomly mark some blocks allocated */
    for (int i = 0; i < n; i++)
        used[i] = (i * 7 + 3) % 5 == 0;

    do {
        printf("\n1.Show Bit Vector  2.Create File  3.Show Directory");
        printf("\n4.Delete File      5.Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            for (int i = 0; i < n; i++) printf("%d ", used[i]);
            printf("\n");
        } else if (choice == 2) {
            int len, found = 0;
            printf("File name and size: ");
            scanf("%s %d", name[files], &len);

            for (int i = 0; i <= n - len; i++) {
                int free = 1;
                for (int j = i; j < i + len; j++)
                    if (used[j]) free = 0;

                if (free) {
                    start[files] = i;
                    length[files] = len;
                    for (int j = i; j < i + len; j++) used[j] = 1;
                    files++;
                    found = 1;
                    printf("File created.\n");
                    break;
                }
            }
            if (!found) printf("No contiguous free space available.\n");
        } else if (choice == 3) {
            printf("File\tStart\tLength\n");
            for (int i = 0; i < files; i++)
                if (length[i] > 0)
                    printf("%s\t%d\t%d\n", name[i], start[i], length[i]);
        } else if (choice == 4) {
            char file[20];
            printf("File name to delete: ");
            scanf("%s", file);

            for (int i = 0; i < files; i++) {
                if (length[i] > 0 && strcmp(name[i], file) == 0) {
                    for (int j = start[i]; j < start[i] + length[i]; j++)
                        used[j] = 0;
                    length[i] = 0;
                    printf("File deleted.\n");
                    break;
                }
            }
        }
    } while (choice != 5);

    return 0;
}

/*
OUTPUT:-

Number of disk blocks: 10

1.Show Bit Vector  2.Create File  3.Show Directory
4.Delete File      5.Exit
Choice: 1
0 1 0 0 0 0 1 0 0 0 

1.Show Bit Vector  2.Create File  3.Show Directory
4.Delete File      5.Exit
Choice: 2
File name and size: RT 3
File created.

1.Show Bit Vector  2.Create File  3.Show Directory
4.Delete File      5.Exit
Choice: 3
File    Start   Length
RT      2       3

1.Show Bit Vector  2.Create File  3.Show Directory
4.Delete File      5.Exit
Choice: 5
*/