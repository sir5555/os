Slip 25
Q1
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int user_delay;
    printf("Enter seconds for the child process to run: ");
    if (scanf("%d", &user_delay) != 1 || user_delay <= 0) {
        printf("Invalid input! Defaulting to 5 seconds.\n");
        user_delay = 5;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } 
    else if (pid == 0) {
        printf("\n[Child] Started. PID: %d, Parent PID: %d\n", getpid(), getppid());      
        printf("[Child] Sleeping for %d seconds to become an orphan...\n", user_delay);
        sleep(user_delay);
        printf("[Child] Awake! PID: %d, New Parent PID: %d (Orphaned! Adopted by init/systemd)\n", 
               getpid(), getppid());
    } 
    else {
        printf("\n[Parent] Started. PID: %d, Child PID: %d\n", getpid(), pid);
        printf("[Parent] Terminating immediately before child finishes...\n");
        
        // Parent exits immediately, leaving the child orphaned
        exit(0);
    }

    return 0;
}


Q2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void search_file(char opt, char *fn, char *pat) {
    FILE *fp = fopen(fn, "r");
    if (!fp) { printf("Error opening file '%s'\n", fn); return; }

    char line[512];
    int l = 1, cnt = 0;
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, pat)) {
            cnt++;
            if (opt == 'f') { printf("First at Line %d: %s", l, line); fclose(fp); return; }
            if (opt == 'a') printf("Line %d: %s", l, line);
        }
        l++;
    }
    if (opt == 'c') printf("Pattern '%s' found %d time(s)\n", pat, cnt);
    else if (!cnt) printf("Pattern '%s' not found\n", pat);
    fclose(fp);
}

int main() {
    char in[80], *args[10];

    while (1) {
        printf("$ "); fflush(stdout);
        if (!fgets(in, sizeof(in), stdin)) break;
        in[strcspn(in, "\n")] = 0;

        int i = 0;
        char *tok = strtok(in, " ");
        while (tok && i < 9) { args[i++] = tok; tok = strtok(NULL, " "); }
        args[i] = NULL;

        if (!args[0]) continue;
        if (!strcmp(args[0], "exit")) break;

        if (!strcmp(args[0], "search")) {
            if (i < 4) printf("Usage: search <f|a|c> <file> <pattern>\n");
            else search_file(args[1][0], args[2], args[3]);
        } else {
            if (!fork()) {
                execvp(args[0], args);
                printf("Command not found: %s\n", args[0]); exit(1);
            }
            wait(NULL);
        }
    }
    return 0;
}