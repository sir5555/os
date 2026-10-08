#SLIP 2
#Q1
#include <stdio.h>
#include <string.h>

int main()
{
    int b[50]={0}, next[50], n, i, j;
    int start[20], f=0, len, ch, k, p;
    char name[20], fname[20][20];

    printf("Enter number of blocks: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
        next[i]=-1;

    while(1)
    {
        printf("\n1.Show Bit Vector");
        printf("\n2.Create New File");
        printf("\n3.Show Directory");
        printf("\n4.Delete File");
        printf("\n5.Exit");
        printf("\nEnter choice: ");
        scanf("%d",&ch);

        if(ch==1)
        {
            for(i=0;i<n;i++)
                printf("%d ",b[i]);
        }

        else if(ch==2)
        {
            printf("Enter file name: ");
            scanf("%s",name);
            printf("Enter number of blocks: ");
            scanf("%d",&len);

            k=0;
            for(i=0;i<n;i++)
                if(b[i]==0) k++;

            if(len>k || len<=0)
                printf("Space not available");
            else
            {
                start[f]=-1;
                p=-1;

                for(i=0;i<n && len>0;i++)
                {
                    if(b[i]==0)
                    {
                        b[i]=1;

                        if(start[f]==-1)
                            start[f]=i;
                        else
                            next[p]=i;

                        p=i;
                        len--;
                    }
                }

                next[p]=-1;
                strcpy(fname[f],name);
                f++;
                printf("File allocated");
            }
        }

        else if(ch==3)
        {
            for(k=0;k<f;k++)
            {
                printf("\n%s: ",fname[k]);
                i=start[k];

                while(i!=-1)
                {
                    printf("%d ",i);
                    i=next[i];
                }
            }
        }

        else if(ch==4)
        {
            printf("Enter file name: ");
            scanf("%s",name);

            for(k=0;k<f;k++)
                if(strcmp(fname[k],name)==0)
                    break;

            if(k==f)
                printf("File not found");
            else
            {
                i=start[k];

                while(i!=-1)
                {
                    j=next[i];
                    b[i]=0;
                    next[i]=-1;
                    i=j;
                }

                for(i=k;i<f-1;i++)
                {
                    strcpy(fname[i],fname[i+1]);
                    start[i]=start[i+1];
                }

                f--;
                printf("File deleted");
            }
        }

        else if(ch==5) break;
    }
    return 0;
}

#q2
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, r, head;
    int request[100];
    int i, movement = 0;

    printf("Enter total number of disk blocks: ");
    scanf("%d", &n);

    printf("Enter number of disk requests: ");
    scanf("%d", &r);

    printf("Enter disk request string:\n");

    for(i = 0; i < r; i++)
        scanf("%d", &request[i]);

    printf("Enter current head position: ");
    scanf("%d", &head);

    printf("\nOrder of service:\n");
    printf("%d", head);

    for(i = 0; i < r; i++)
    {
        movement = movement + abs(head - request[i]);
        head = request[i];

        printf(" -> %d", head);
    }

    printf("\n\nTotal Head Movement = %d\n", movement);

    return 0;
}
