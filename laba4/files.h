
#ifndef LABA4_FILES_H
#define LABA4_FILES_H

#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define AM_OF_CREATED_PROC 8
void initAllFiles(char *scriptName);
void waitForPid(char *scriptName, char *pathToFile);
void writePid(char *scriptName, char *pathToFile, int pid);
int getPidFromFile(char *scriptName, char *pathToFile);

#endif //LABA4_FILES_H
