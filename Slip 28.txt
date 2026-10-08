#Slip 28
Q1
#include <stdio.h>
#include <stdlib.h>

int main() {
    int total, n, head, dir;
    printf("Enter total blocks: ");
    if (scanf("%d", &total) != 1 || total <= 0) { printf("Invalid!\n"); return 1; }
    printf("Enter request count: ");
    if (scanf("%d", &n) != 1 || n <= 0) { printf("Invalid!\n"); return 1; }

    int req[n];
    printf("Enter %d requests:\n", n);
    for (int i = 0; i < n; i++) scanf("%d", &req[i]);
    printf("Enter head & direction (0=Left, 1=Right): ");
    scanf("%d %d", &head, &dir);

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (req[j] > req[j + 1]) { int t = req[j]; req[j] = req[j + 1]; req[j + 1] = t; }

    int pos = 0;
    while (pos < n && req[pos] < head) pos++;

    printf("\n--- SCAN Disk Scheduling ---\nSequence: ");
    int movement = (dir == 0) ? head + req[n - 1] : ((total - 1) - head) + ((total - 1) - req[0]);

    if (dir == 0) {
        for (int i = pos - 1; i >= 0; i--) printf("%d ", req[i]);
        printf("0 ");
        for (int i = pos; i < n; i++) printf("%d ", req[i]);
    } else {
        for (int i = pos; i < n; i++) printf("%d ", req[i]);
        printf("%d ", total - 1);
        for (int i = pos - 1; i >= 0; i--) printf("%d ", req[i]);
    }

    printf("\n========================================\nTotal Head Movements = %d\n", movement);
    return 0;
}

Output:
Enter total number of disk blocks: 3
Enter total number of requests: 2
Enter the 2 disk requests:
1
2
Enter current head position: 
1
Enter direction (0 for Left, 1 for Right): 0

--- SCAN Disk Scheduling Order ---
Start Head Position: 1
Sequence of serviced requests: 0 1 2 

========================================
Total number of head movements = 3
========================================

Q2
#include <stdio.h>
#include <stdlib.h>

int main() {
    int def_ref[] = {8, 5, 7, 8, 5, 7, 2, 3, 7, 3, 5, 9, 4, 6, 2}, f_count, choice;

    printf("Enter number of memory frames: ");
    if (scanf("%d", &f_count) != 1 || f_count <= 0) { printf("Invalid!\n"); return 1; }

    int frames[f_count], count[f_count], time_in[f_count];
    for (int i = 0; i < f_count; i++) { frames[i] = -1; count[i] = 0; time_in[i] = 0; }

    printf("1. Default string\n2. Custom string\nChoice: ");
    scanf("%d", &choice);

    int *ref = def_ref, len = 15;
    if (choice == 2) {
        printf("Enter length: "); scanf("%d", &len);
        ref = malloc(len * sizeof(int));
        printf("Enter string: ");
        for (int i = 0; i < len; i++) scanf("%d", &ref[i]);
    }

    int faults = 0, timer = 0;
    printf("\n--- MFU Simulation ---\n");
    for (int i = 0; i < len; i++) {
        int page = ref[i], found = 0;
        timer++;

        for (int j = 0; j < f_count; j++) {
            if (frames[j] == page) { found = 1; count[j]++; break; }
        }

        if (!found) {
            int r_idx = -1, max_f = -1, oldest = 999999;
            for (int j = 0; j < f_count; j++) {
                if (frames[j] == -1) { r_idx = j; break; }
                if (count[j] > max_f || (count[j] == max_f && time_in[j] < oldest)) {
                    max_f = count[j];
                    oldest = time_in[j];
                    r_idx = j;
                }
            }
            frames[r_idx] = page;
            count[r_idx] = 1;
            time_in[r_idx] = timer;
            faults++;
        }

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
Enter number of memory frames: 5

Choose Reference String:
1. Use default string (8, 5, 7, 8, 5, 7, 2, 3, 7, 3, 5, 9, 4, 6, 2)
2. Enter custom reference string
Enter choice (1 or 2): 1

--- MFU Page Replacement Simulation ---
Reference String: 8 5 7 8 5 7 2 3 7 3 5 9 4 6 2 

Page  8 -> [ 8 - - - - ] -> Page Fault
Page  5 -> [ 8 5 - - - ] -> Page Fault
Page  7 -> [ 8 5 7 - - ] -> Page Fault
Page  8 -> [ 8 5 7 - - ]
Page  5 -> [ 8 5 7 - - ]
Page  7 -> [ 8 5 7 - - ]
Page  2 -> [ 8 5 7 2 - ] -> Page Fault
Page  3 -> [ 8 5 7 2 3 ] -> Page Fault
Page  7 -> [ 8 5 7 2 3 ]
Page  3 -> [ 8 5 7 2 3 ]
Page  5 -> [ 8 5 7 2 3 ]
Page  9 -> [ 8 9 7 2 3 ] -> Page Fault
Page  4 -> [ 8 9 4 2 3 ] -> Page Fault
Page  6 -> [ 6 9 4 2 3 ] -> Page Fault
Page  2 -> [ 6 9 4 2 3 ]

========================================
Total Number of Page Faults = 8
========================================