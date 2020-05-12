
#include "files.h"

void initAllFiles(char *scriptName) {
    char pidFile[1];
    for (int i = 1; i <= AM_OF_CREATED_PROC; i++) {
        sprintf(pidFile, "%d", i);
        int res = remove(pidFile);
        if ((res != 0) && (errno != ENOENT)) {
            fprintf(stderr, "%d: %s: %s: %s\n", getpid(), scriptName, strerror(errno), pidFile);
            exit(EXIT_FAILURE);
        }
    }
}

void waitForPid(char *scriptName, char *pathToFile) {
    struct stat fileData;
    while (stat(pathToFile, &fileData) == -1) {
        //fprintf(stdout, "%s: %lo\n", pathToFile, fileData.st_size);
    }
}

void writePid(char *scriptName, char *pathToFile, int pid) {
    FILE *file = fopen(pathToFile, "w");
    if (file == NULL) {
        fprintf(stderr, "%d: %s: %s: %s\n", getpid(), scriptName, strerror(errno), pathToFile);
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%d", pid);
    int res = fclose(file);
    if (res != 0) {
        fprintf(stderr, "%d: %s: %s: %s\n", getpid(), scriptName, strerror(errno), pathToFile);
        return;
    }
}

int getPidFromFile(char *scriptName, char *pathToFile) {
    int pid;
    FILE *file = fopen(pathToFile, "r");
    if (file == NULL) {
        fprintf(stderr, "get %d: %s: %s: %s\n", getpid(), scriptName, strerror(errno), pathToFile);
        return -1;
    }
    fscanf(file, "%d", &pid);
    int res = fclose(file);
    if (res != 0) {
        fprintf(stderr, "%d: %s: %s: %s\n", getpid(), scriptName, strerror(errno), pathToFile);
        return -1;
    }
    return pid;
}