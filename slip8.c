#SLIP 8
#Q1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int n, bit[100], choice, i, index, blocks, b;
    char name[20];

    printf("Enter number of blocks: ");
    scanf("%d", &n);

    srand(time(0));

    /* Randomly allocate blocks */
    for(i = 0; i < n; i++)
        bit[i] = rand() % 2;

    while(1)
    {
        printf("\n\n1. Show Bit Vector");
        printf("\n2. Create New File");
        printf("\n3. Show Directory");
        printf("\n4. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("\nBit Vector:\n");
                for(i = 0; i < n; i++)
                    printf("%d ", bit[i]);
                break;

            case 2:
                printf("\nEnter file name: ");
                scanf("%s", name);

                printf("Enter index block: ");
                scanf("%d", &index);

                printf("Enter number of blocks: ");
                scanf("%d", &blocks);

                if(bit[index] == 1)
                {
                    printf("Index block is already allocated!");
                    break;
                }

                bit[index] = 1;

                printf("Enter block numbers:\n");

                for(i = 0; i < blocks; i++)
                {
                    scanf("%d", &b);

                    if(bit[b] == 0)
                        bit[b] = 1;
                    else
                        printf("Block %d already allocated!\n", b);
                }

                printf("File created successfully!");
                break;

            case 3:
                printf("\nDirectory:");
                printf("\nFile Name: %s", name);
                printf("\nIndex Block: %d", index);
                printf("\nNumber of Blocks: %d", blocks);
                break;

            case 4:
                exit(0);

            default:
                printf("\nInvalid choice!");
        }
    }

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
