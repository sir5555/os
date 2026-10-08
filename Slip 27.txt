Slip 27
Q1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int total, n, head;
    printf("Enter total blocks: ");
    if (scanf("%d", &total) != 1 || total <= 0) { printf("Invalid!\n"); return 1; }
    printf("Enter request count: ");
    if (scanf("%d", &n) != 1 || n <= 0) { printf("Invalid!\n"); return 1; }

    int req[n], visited[n] = {0};
    printf("Enter %d requests:\n", n);
    for (int i = 0; i < n; i++) scanf("%d", &req[i]);
    printf("Enter start head position: ");
    scanf("%d", &head);

    int total_movement = 0, count = 0;
    printf("\n--- SSTF Disk Scheduling ---\nStart Head: %d\nSequence: ", head);

    while (count < n) {
        int min_dist = 999999, idx = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && abs(req[i] - head) < min_dist) {
                min_dist = abs(req[i] - head);
                idx = i;
            }
        }
        visited[idx] = 1;
        total_movement += min_dist;
        head = req[idx];
        printf("%d ", head);
        count++;
    }

    printf("\n========================================\nTotal Head Movements = %d\n========================================\n", total_movement);
    return 0;
}
Output:
Enter total number of disk blocks: 4
Enter total number of requests: 2
Enter the 2 disk requests :
5
4
Enter current head position: 1

--- SSTF Disk Scheduling Order ---
Start Head Position: 1

Sequence of serviced requests: 4 5 

========================================
Total number of head movements = 4
========================================

Q2
#include <stdio.h>
#include <stdlib.h>

int main() {
    int def_ref[] = {3, 5, 7, 2, 5, 1, 2, 3, 1, 3, 5, 3, 1, 6, 2}, f_count, choice;

    printf("Enter number of memory frames: ");
    if (scanf("%d", &f_count) != 1 || f_count <= 0) { printf("Invalid!\n"); return 1; }

    int frames[f_count], counter[f_count];
    for (int i = 0; i < f_count; i++) { frames[i] = -1; counter[i] = 0; }

    printf("1. Default string\n2. Custom string\nChoice: ");
    scanf("%d", &choice);

    int *ref = def_ref, len = 15;
    if (choice == 2) {
        printf("Enter length: "); scanf("%d", &len);
        ref = malloc(len * sizeof(int));
        printf("Enter string: ");
        for (int i = 0; i < len; i++) scanf("%d", &ref[i]);
    }

    int faults = 0, time = 0;
    printf("\n--- LRU Simulation ---\n");
    for (int i = 0; i < len; i++) {
        int page = ref[i], found = 0;
        time++;
        for (int j = 0; j < f_count; j++) {
            if (frames[j] == page) { found = 1; counter[j] = time; break; }
        }

        if (!found) {
            int r_idx = 0;
            for (int j = 0; j < f_count; j++) {
                if (frames[j] == -1) { r_idx = j; break; }
                if (counter[j] < counter[r_idx]) r_idx = j;
            }
            frames[r_idx] = page;
            counter[r_idx] = time;
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

Enter number of memory frames: 4

Choose Reference String:
1. Use default string (3, 5, 7, 2, 5, 1, 2, 3, 1, 3, 5, 3, 1, 6, 2)
2. Enter custom reference string
Enter choice (1 or 2): 1

--- LRU Page Replacement Simulation (Counter Method) ---
Reference String: 3 5 7 2 5 1 2 3 1 3 5 3 1 6 2 

Page  3 -> [ 3 - - - ] -> Page Fault
Page  5 -> [ 3 5 - - ] -> Page Fault
Page  7 -> [ 3 5 7 - ] -> Page Fault
Page  2 -> [ 3 5 7 2 ] -> Page Fault
Page  5 -> [ 3 5 7 2 ]
Page  1 -> [ 1 5 7 2 ] -> Page Fault
Page  2 -> [ 1 5 7 2 ]
Page  3 -> [ 1 5 3 2 ] -> Page Fault
Page  1 -> [ 1 5 3 2 ]
Page  3 -> [ 1 5 3 2 ]
Page  5 -> [ 1 5 3 2 ]
Page  3 -> [ 1 5 3 2 ]
Page  1 -> [ 1 5 3 2 ]
Page  6 -> [ 1 5 3 6 ] -> Page Fault
Page  2 -> [ 1 2 3 6 ] -> Page Fault

========================================
Total Number of Page Faults = 8
========================================