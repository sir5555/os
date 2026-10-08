#slip 20] 

#Q1]

#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, req[50], i, j, total = 0;
    char direction;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter request string: ");
    for (i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter starting head position: ");
    scanf("%d", &head);

    printf("Direction (R/L): ");
    scanf(" %c", &direction);

    /* Sort requests */
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (req[i] > req[j]) {
                int temp = req[i];
                req[i] = req[j];
                req[j] = temp;
            }

    printf("Service order: ");

    if (direction == 'R' || direction == 'r') {
        for (i = 0; i < n; i++)
            if (req[i] >= head) {
                printf("%d ", req[i]);
                total += abs(head - req[i]);
                head = req[i];
            }
        for (i = n - 1; i >= 0; i--)
            if (req[i] < head) {
                printf("%d ", req[i]);
                total += abs(head - req[i]);
                head = req[i];
            }
    } else {
        for (i = n - 1; i >= 0; i--)
            if (req[i] <= head) {
                printf("%d ", req[i]);
                total += abs(head - req[i]);
                head = req[i];
            }
        for (i = 0; i < n; i++)
            if (req[i] > head) {
                printf("%d ", req[i]);
                total += abs(head - req[i]);
                head = req[i];
            }
    }

    printf("\nTotal head movement: %d\n", total);
    return 0;
}

/*
OUTPUT

Enter number of requests: 2
Enter request string: 3
4
Enter starting head position: 5
Direction (R/L): 3
Service order: 4 3 4 
Total head movement: 3

*/

#Q2]

#include <stdio.h>

int main() {
    int pages[] = {3,5,7,2,5,1,2,3,1,3,5,3,1,6,2};
    int n = 15, frames[10], counter[10];
    int f, i, j, time = 0, faults = 0;

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for (i = 0; i < f; i++) {
        frames[i] = -1;
        counter[i] = 0;
    }

    for (i = 0; i < n; i++) {
        int found = 0;

        for (j = 0; j < f; j++)
            if (frames[j] == pages[i]) {
                found = 1;
                counter[j] = ++time;
                break;
            }

        if (!found) {
            int replace = 0;
            for (j = 0; j < f; j++)
                if (frames[j] == -1) {
                    replace = j;
                    break;
                }

            if (j == f)
                for (j = 1; j < f; j++)
                    if (counter[j] < counter[replace])
                        replace = j;

            frames[replace] = pages[i];
            counter[replace] = ++time;
            faults++;
        }

        printf("Page %d: ", pages[i]);
        for (j = 0; j < f; j++)
            if (frames[j] != -1) printf("%d ", frames[j]);
        if (!found) printf("(Fault)");
        printf("\n");
    }

    printf("Total page faults: %d\n", faults);
    return 0;
}


/*
OUTPUT:-

Enter number of frames: 4
Page 3: 3 (Fault)
Page 5: 3 5 (Fault)
Page 7: 3 5 7 (Fault)
Page 2: 3 5 7 2 (Fault)
Page 5: 3 5 7 2 
Page 1: 1 5 7 2 (Fault)
Page 2: 1 5 7 2 
Page 3: 1 5 3 2 (Fault)
Page 1: 1 5 3 2 
Page 3: 1 5 3 2 
Page 5: 1 5 3 2 
Page 3: 1 5 3 2 
Page 1: 1 5 3 2 
Page 6: 1 5 3 6 (Fault)
Page 2: 1 2 3 6 (Fault)
Total page faults: 8

*/