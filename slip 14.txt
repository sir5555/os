#slip 14
#Q1]
not run coz system 
--main.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main(int argc, char *argv[]) {
    int n, key;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int a[n];
    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter item to search: ");
    scanf("%d", &key);

    qsort(a, n, sizeof(int), compare);

    char **args = malloc((n + 3) * sizeof(char *));
    args[0] = "./search";

    for (int i = 0; i < n; i++) {
        args[i + 1] = malloc(20);
        sprintf(args[i + 1], "%d", a[i]);
    }

    args[n + 1] = malloc(20);
    sprintf(args[n + 1], "%d", key);
    args[n + 2] = NULL;

    if (fork() == 0) {
        execv("./search", args);
        perror("execv");
        exit(1);
    }

    wait(NULL);
    return 0;
}

--search.c

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int n = argc - 2;
    int key = atoi(argv[argc - 1]);
    int low = 0, high = n - 1, found = 0;

    while (low <= high) {
        int mid = (low + high) / 2;
        int value = atoi(argv[mid + 1]);

        if (value == key) {
            found = 1;
            break;
        } else if (value < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (found)
        printf("%d found\n", key);
    else
        printf("%d not found\n", key);

    return 0;
}


#Q2]

#include <stdio.h>

int main() {
    int ref[] = {3, 4, 5, 6, 3, 4, 7, 3, 4, 5, 6, 7, 2, 4, 6};
    int n = 15, frames[20], f, next = 0, faults = 0;

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for (int i = 0; i < f; i++)
        frames[i] = -1;

    for (int i = 0; i < n; i++) {
        int hit = 0;

        for (int j = 0; j < f; j++)
            if (frames[j] == ref[i])
                hit = 1;

        if (!hit) {
            frames[next] = ref[i];
            next = (next + 1) % f;
            faults++;
        }

        printf("%d: ", ref[i]);
        for (int j = 0; j < f; j++) {
            if (frames[j] == -1) printf("- ");
            else printf("%d ", frames[j]);
        }
        printf("%s\n", hit ? "Hit" : "Fault");
    }

    printf("Total page faults = %d\n", faults);
    return 0;
}

/*
Enter number of frames: 5
3: 3 - - - - Fault
4: 3 4 - - - Fault
5: 3 4 5 - - Fault
6: 3 4 5 6 - Fault
3: 3 4 5 6 - Hit
4: 3 4 5 6 - Hit
7: 3 4 5 6 7 Fault
3: 3 4 5 6 7 Hit
4: 3 4 5 6 7 Hit
5: 3 4 5 6 7 Hit
6: 3 4 5 6 7 Hit
7: 3 4 5 6 7 Hit
2: 2 4 5 6 7 Fault
4: 2 4 5 6 7 Hit
6: 2 4 5 6 7 Hit
Total page faults = 6
*/