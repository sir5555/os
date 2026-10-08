#slip 16] 

#Q1]

#include <stdio.h>

int main(void) {
    int pages[] = {3, 5, 7, 2, 5, 1, 2, 3, 1, 3, 5, 3, 1, 6, 2};
    int n = sizeof(pages) / sizeof(pages[0]);
    int frame[10], lastUsed[10], frames, faults = 0, time = 0;

    printf("Number of frames: ");
    scanf("%d", &frames);

    for (int i = 0; i < frames; i++)
        frame[i] = -1, lastUsed[i] = 0;

    printf("\nPage\tFrames\t\tResult\n");

    for (int i = 0; i < n; i++) {
        int pos = -1;

        for (int j = 0; j < frames; j++)
            if (frame[j] == pages[i]) pos = j;

        if (pos == -1) {                 // Page fault
            faults++;
            pos = 0;

            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) { pos = j; break; }
                if (lastUsed[j] < lastUsed[pos]) pos = j;
            }
            frame[pos] = pages[i];
        }

        lastUsed[pos] = ++time;

        printf("%d\t", pages[i]);
        for (int j = 0; j < frames; j++)
            if (frame[j] == -1) printf("- ");
            else printf("%d ", frame[j]);

        printf("\t%s\n", pos >= 0 ? (faults && frame[pos] == pages[i] ? "" : "") : "");
        /* Fault count is printed at the end. */
    }

    printf("\nTotal page faults = %d\n", faults);
    return 0;
}

/*
OUTPUT

Number of frames: 4

Page    Frames          Result
3       3 - - - 
5       3 5 - - 
7       3 5 7 - 
2       3 5 7 2 
5       3 5 7 2 
1       1 5 7 2 
2       1 5 7 2 
3       1 5 3 2 
1       1 5 3 2 
3       1 5 3 2 
5       1 5 3 2 
3       1 5 3 2 
1       1 5 3 2 
6       1 5 3 6 
2       1 2 3 6 

Total page faults = 8

*/

#Q2]

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    char line[200], *args[20];

    while (1) {
        printf("$ ");
        if (!fgets(line, sizeof(line), stdin)) break;

        int n = 0;
        char *token = strtok(line, " \t\n");
        while (token && n < 19) {
            args[n++] = token;
            token = strtok(NULL, " \t\n");
        }
        args[n] = NULL;

        if (n == 0) continue;
        if (strcmp(args[0], "exit") == 0) break;

        if (strcmp(args[0], "count") == 0 && n == 3) {
            FILE *file = fopen(args[2], "r");
            if (!file) { perror("File"); continue; }

            int ch, chars = 0, words = 0, lines = 0, inWord = 0;
            while ((ch = fgetc(file)) != EOF) {
                chars++;
                if (ch == '\n') lines++;
                if (isspace(ch)) inWord = 0;
                else if (!inWord) { words++; inWord = 1; }
            }
            fclose(file);

            if (strcmp(args[1], "c") == 0) printf("Characters: %d\n", chars);
            else if (strcmp(args[1], "w") == 0) printf("Words: %d\n", words);
            else if (strcmp(args[1], "l") == 0) printf("Lines: %d\n", lines);
            else printf("Use: count c|w|l filename\n");
        } else {
            pid_t pid = fork();
            if (pid == 0) {
                execvp(args[0], args);
                perror("Command");
                exit(1);
            }
            wait(NULL);
        }
    }
    return 0;
}



/*
OUTPUT:-

$ count c main.c
Characters: 1564
$ 


*/