#slip 11 ]

# Q.1]

#include <stdio.h>

int main()
{
    int n, i, j, ch;
    int alloc[10][3], max[10][3], need[10][3], avail[3];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Allocation matrix (A B C):\n");
    for(i=0;i<n;i++)
        for(j=0;j<3;j++)
            scanf("%d",&alloc[i][j]);

    printf("Enter Max matrix (A B C):\n");
    for(i=0;i<n;i++)
        for(j=0;j<3;j++)
            scanf("%d",&max[i][j]);

    printf("Enter Available (A B C):\n");
    for(j=0;j<3;j++)
        scanf("%d",&avail[j]);

    /* Calculate Need */
    for(i=0;i<n;i++)
        for(j=0;j<3;j++)
            need[i][j] = max[i][j] - alloc[i][j];

    do
    {
        printf("\n--- MENU ---\n");
        printf("1. Display Allocation and Max\n");
        printf("2. Display Need Matrix\n");
        printf("3. Display Available\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d",&ch);

        switch(ch)
        {
            case 1:
                printf("\nAllocation\tMax\n");
                for(i=0;i<n;i++)
                {
                    printf("P%d  ",i);
                    for(j=0;j<3;j++)
                        printf("%d ",alloc[i][j]);

                    printf("\t");
                    for(j=0;j<3;j++)
                        printf("%d ",max[i][j]);
                    printf("\n");
                }
                break;

            case 2:
                printf("\nNeed Matrix:\n");
                for(i=0;i<n;i++)
                {
                    printf("P%d  ",i);
                    for(j=0;j<3;j++)
                        printf("%d ",need[i][j]);
                    printf("\n");
                }
                break;

            case 3:
                printf("\nAvailable: ");
                for(j=0;j<3;j++)
                    printf("%d ",avail[j]);
                printf("\n");
                break;

            case 4:
                printf("Exit\n");
                break;

            default:
                printf("Invalid choice\n");
        }

    } while(ch != 4);

    return 0;
}

 
/*
 OUTPUT :-


Enter number of processes: 3
Enter Allocation matrix (A B C):
0 0 2
1 1 0
0 1 0
Enter Max matrix (A B C):
2 0 2
5 2 1
1 1 3
Enter Available (A B C):
1 1 3

--- MENU ---
1. Display Allocation and Max
2. Display Need Matrix
3. Display Available
4. Exit
Enter choice: 1

Allocation      Max
P0  0 0 2       2 0 2 
P1  1 1 0       5 2 1 
P2  0 1 0       1 1 3 

--- MENU ---
1. Display Allocation and Max
2. Display Need Matrix
3. Display Available
4. Exit
Enter choice: 2

Need Matrix:
P0  2 0 0 
P1  4 1 1 
P2  1 0 3 

--- MENU ---
1. Display Allocation and Max
2. Display Need Matrix
3. Display Available
4. Exit
Enter choice: 3

Available: 1 1 3 

--- MENU ---
1. Display Allocation and Max
2. Display Need Matrix
3. Display Available
4. Exit
Enter choice: 4
Exit 

*/



# Q.2]
#include <stdio.h>

int main() {
    int pages[] = {8, 5, 7, 8, 5, 7, 2, 3, 7, 3, 5, 9, 4, 6, 2};
    int count = 15, n, faults = 0;

    printf("Enter number of frames: ");
    scanf("%d", &n);

    int frame[n];
    for (int i = 0; i < n; i++)
        frame[i] = -1;

    for (int i = 0; i < count; i++) {
        int found = 0;

        for (int j = 0; j < n; j++)
            if (frame[j] == pages[i])
                found = 1;

        if (!found) {
            int replace = -1, farthest = -1;

            for (int j = 0; j < n; j++) {
                int k;
                for (k = i + 1; k < count; k++)
                    if (frame[j] == pages[k])
                        break;

                if (k == count) {
                    replace = j;
                    break;
                }
                if (k > farthest) {
                    farthest = k;
                    replace = j;
                }
            }

            frame[replace] = pages[i];
            faults++;
        }

        printf("%d: ", pages[i]);
        for (int j = 0; j < n; j++)
            if (frame[j] == -1) printf("- ");
            else printf("%d ", frame[j]);
        printf("%s\n", found ? "Hit" : "Fault");
    }

    printf("Total page faults = %d\n", faults);
    return 0;
}




/*
OUTPUT:- 

Enter number of frames: 5
8: 8 - - - - Fault
5: 8 5 - - - Fault
7: 8 5 7 - - Fault
8: 8 5 7 - - Hit
5: 8 5 7 - - Hit
7: 8 5 7 - - Hit
2: 2 5 7 - - Fault
3: 2 5 7 3 - Fault
7: 2 5 7 3 - Hit
3: 2 5 7 3 - Hit
5: 2 5 7 3 - Hit
9: 2 9 7 3 - Fault
4: 2 4 7 3 - Fault
6: 2 6 7 3 - Fault
2: 2 6 7 3 - Hit
Total page faults = 8

*/

