Slip 21
Q1
#include <stdio.h>
#include <stdlib.h>

int main() {
    int def_ref[] = {8, 5, 7, 8, 5, 7, 2, 3, 7, 3, 5, 9, 4, 6, 2}, f_count, choice;

    printf("Enter number of memory frames: ");
    if (scanf("%d", &f_count) != 1 || f_count <= 0) { printf("Invalid!\n"); return 1; }

    int frames[f_count], count[f_count], time_in[f_count];
    for (int i = 0; i < f_count; i++) { frames[i] = -1; count[i] = 0; time_in[i] = 0; }

    printf("1. Default string (8, 5, 7, 8, 5, 7, 2, 3, 7, 3, 5, 9, 4, 6, 2)\n2. Custom string\nChoice: ");
    scanf("%d", &choice);

    int *ref = def_ref, len = 15;
    if (choice == 2) {
        printf("Enter length: "); scanf("%d", &len);
        ref = malloc(len * sizeof(int));
        printf("Enter string: ");
        for (int i = 0; i < len; i++) scanf("%d", &ref[i]);
    }

    int faults = 0, timer = 0;
    printf("\n--- MFU Page Replacement Simulation ---\n");
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

    printf("========================================\nTotal Number of Page Faults = %d\n", faults);
    if (choice == 2) free(ref);
    return 0;
}

Q2
#include <stdio.h>
int main() {
    int ref[] = {8, 5, 7, 8, 5, 7, 2, 3, 7, 3, 5, 9, 4, 6, 2}, n = 15, frames, mem[10], freq[10], pf = 0;
    printf("Enter the number of frames (n): ");
    scanf("%d", &frames);
    for(int i = 0; i < frames; i++) mem[i] = -1, freq[i] = 0;
    printf("\n--- Page Scheduling Steps ---\n");
    for(int i = 0; i < n; i++) {
        int page = ref[i], found = 0;
        for(int j = 0; j < frames; j++) 
            if(mem[j] == page) { found = 1; freq[j]++; break; }
        if(!found) {
            int idx = -1, empty = 0;
            for(int j = 0; j < frames; j++) 
                if(mem[j] == -1) { idx = j; empty = 1; break; }
            if(!empty) {
                int max = -1;
                for(int j = 0; j < frames; j++) 
                    if(freq[j] > max) { max = freq[j]; idx = j; }
            }
            mem[idx] = page; freq[idx] = 1; pf++;
        }
        printf("Page %2d -> [ ", page);
        for(int j = 0; j < frames; j++) 
            mem[j] != -1 ? printf("%d ", mem[j]) : printf("- ");
        printf("]\n");
    }
    printf("\nTotal Number of Page Faults = %d\n", pf);
    return 0;
}