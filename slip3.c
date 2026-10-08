#SLIP 3
#Q1
#include <stdio.h>

int main()
{
    int alloc[5][4] = {
        {0,0,1,2},
        {1,0,0,0},
        {1,3,5,4},
        {0,6,3,2},
        {0,0,1,4}
    };

    int max[5][4] = {
        {0,0,1,2},
        {1,7,5,0},
        {2,3,5,6},
        {0,6,5,2},
        {0,6,5,6}
    };

    int avail[4] = {1,5,2,0};
    int need[5][4];
    int finish[5] = {0};
    int safe[5];

    int i, j, k, count = 0;
    int possible;

    /* Calculate Need */
    for(i = 0; i < 5; i++)
        for(j = 0; j < 4; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    /* Display Need */
    printf("Need Matrix:\n");

    for(i = 0; i < 5; i++)
    {
        printf("P%d: ", i);

        for(j = 0; j < 4; j++)
            printf("%d ", need[i][j]);

        printf("\n");
    }

    /* Banker's Algorithm */
    while(count < 5)
    {
        possible = 0;

        for(i = 0; i < 5; i++)
        {
            if(finish[i] == 0)
            {
                int canRun = 1;

                for(j = 0; j < 4; j++)
                {
                    if(need[i][j] > avail[j])
                    {
                        canRun = 0;
                        break;
                    }
                }

                if(canRun)
                {
                    for(k = 0; k < 4; k++)
                        avail[k] += alloc[i][k];

                    safe[count] = i;
                    finish[i] = 1;
                    count++;
                    possible = 1;
                }
            }
        }

        if(possible == 0)
            break;
    }

    if(count == 5)
    {
        printf("\nSystem is in SAFE state.\n");
        printf("Safe Sequence: ");

        for(i = 0; i < 5; i++)
            printf("P%d ", safe[i]);

        printf("\n");
    }
    else
    {
        printf("\nSystem is NOT in safe state.\n");
    }

    return 0;
}

#q2
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int blocks, n, i, j;
    int req[100], visited[100] = {0};
    int head, min, pos, total = 0;

    printf("Enter total disk blocks: ");
    scanf("%d", &blocks);

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter requests: ");
    for(i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter head position: ");
    scanf("%d", &head);

    printf("\nOrder: %d", head);

    for(i = 0; i < n; i++)
    {
        min = 9999;

        for(j = 0; j < n; j++)
        {
            if(!visited[j] && abs(head - req[j]) < min)
            {
                min = abs(head - req[j]);
                pos = j;
            }
        }

        visited[pos] = 1;
        total += min;
        head = req[pos];

        printf(" -> %d", head);
    }

    printf("\nTotal Head Movement = %d\n", total);

    return 0;
}
