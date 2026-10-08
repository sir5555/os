#SLIP 7
#Q1
#include <stdio.h>

int main()
{
    int alloc[5][4] = {
        {2,0,0,1},
        {3,1,2,1},
        {2,1,0,3},
        {1,3,1,2},
        {1,4,3,2}
    };

    int max[5][4] = {
        {4,2,1,2},
        {5,2,5,2},
        {2,3,1,6},
        {1,4,2,4},
        {3,6,6,5}
    };

    int avail[4] = {3,3,2,1};
    int need[5][4], finish[5] = {0};
    int i,j,k, count=0, safe;

    /* Calculate Need */
    for(i=0;i<5;i++)
        for(j=0;j<4;j++)
            need[i][j] = max[i][j] - alloc[i][j];

    printf("Need Matrix:\n");
    for(i=0;i<5;i++)
    {
        for(j=0;j<4;j++)
            printf("%d ",need[i][j]);
        printf("\n");
    }

    printf("\nSafe Sequence: ");

    while(count < 5)
    {
        safe = 0;

        for(i=0;i<5;i++)
        {
            if(finish[i] == 0)
            {
                for(j=0;j<4;j++)
                    if(need[i][j] > avail[j])
                        break;

                if(j == 4)
                {
                    for(k=0;k<4;k++)
                        avail[k] += alloc[i][k];

                    printf("P%d ",i);
                    finish[i] = 1;
                    count++;
                    safe = 1;
                }
            }
        }

        if(safe == 0)
        {
            printf("\nSystem is NOT SAFE");
            return 0;
        }
    }

    printf("\nSystem is SAFE");

    return 0;
}

#Q2
#include <stdio.h>
#include<unistd.h>
void main()
{
    int pid,ret;

    pid = fork();

    if(pid == 0)
    {
        ret=nice(-5);
        printf("child gets higher cpu priority %d \n",ret);
        sleep(1);
    }
    else{
        ret=nice(4);
        printf("parent gets lower cpu priority %d \n,retnice");
        sleep(1);
    }
}
