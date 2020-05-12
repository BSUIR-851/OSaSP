/*
 * 9. Написать программу шифрации всех файлов заданного каталога и его подкаталогов.
 * Пользователь задаёт имя каталога. Главный процесс открывает каталоги и запускает
 * для каждого файла каталога и отдельный процесс шифрации. Каждый процесс выводит
 * на экран свой pid, полный путь к файлу, общее число зашифрованных байт.
 * Шифрация по алгоритму сложения по модулю 2 бит исходного файла и файла ключа.
 * Число одновременно работающих процессов не должно превышать N (вводится пользователем).
 * Проверить работу программы для каталога /etc.
 */

#include "dynList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

typedef unsigned char byte;

typedef struct bytesList {
    unsigned long size;
    byte *elements;
} bytesList;

char *getRealPath(char *path, char *scriptName) {
    //get full path of file
    char *fullPath = realpath(path, NULL);
    if (fullPath == NULL) {
        fprintf(stderr, "%d: %s: %s: %s\n", getpid(), scriptName, strerror(errno),  path);
        exit(EXIT_FAILURE);
    }
    return fullPath;
}

long getAmOfFileInBytes(char *scriptName, FILE *file, const char *pathToFile) {

    //get the stat of file
    struct stat statBuf;
    int res = stat(pathToFile, &statBuf);
    if (res != 0) {
        fprintf(stderr, "%d: %s: %s: %s\n", getpid(), scriptName, strerror(errno), pathToFile);
        fclose(file);
        exit(EXIT_FAILURE);
    }
    long sizeFile = statBuf.st_size;
    return sizeFile;
}

bytesList* getKeyInBytes(char *scriptName, char *key) {

    //create buffer of bytes for storage bytes of key
    byte* keyInBytes;
    unsigned long sizeKeyInBytes = strlen(key) <= 8 ? 1: strlen(key)/8 + 1;
    keyInBytes = (byte*)malloc(sizeof(byte)*sizeKeyInBytes);
    if (keyInBytes == NULL) {
        fprintf(stderr, "%d: %s: %s: %s\n", getpid(), scriptName, strerror(errno), "Key");
        free(keyInBytes);
        exit(EXIT_FAILURE);
    }

    //create interim buffer for storage every 1 byte of key
    char* bufByte = (char*)malloc(8);

    //write all bytes of key in key buffer
    for (unsigned long i = 0; i < sizeKeyInBytes; i++) {
        strncpy(bufByte, (key + i*8), 8);
        *(keyInBytes + i) = strtol(bufByte, NULL, 2);
    }

    bytesList *keyList = malloc(sizeof(keyList));
    keyList->size = sizeKeyInBytes;
    keyList->elements = keyInBytes;

    //free interim memory
    free(bufByte);

    return keyList;
}

void checkAmOfProcesses(char *scriptName, int N, int *currAmOfProcesses) {
    //check if current amount of processes is equal to max amount processes
    if (*(currAmOfProcesses) == N) {
        int status = 1;
        int exitPid = wait(&status);

        while (exitPid == -1) {
            fprintf(stderr, "%d: %s: %s\n", getpid(), scriptName, strerror(errno));
            exitPid = wait(&status);
        }
        *(currAmOfProcesses) -= 1;
    }
}

long encryptingFile(char *scriptName, bytesList *keyInBytes, FILE *fileToEncrypt, char *pathToFile, char *pathToSave) {
    //get size in bytes of file to encrypt
    long fileSize = getAmOfFileInBytes(scriptName, fileToEncrypt, pathToFile);
    byte *bufForFile = (byte*)calloc(fileSize, sizeof(byte));

    //get all bytes of file to encrypt
    unsigned long res = fread(bufForFile, sizeof(byte), fileSize, fileToEncrypt);
    if ((res != fileSize) && !(feof(fileToEncrypt))) {
        fprintf(stderr, "%d: %s: %s: %s\n", getpid(), scriptName, strerror(errno), pathToFile);
        return -1;
    }

    //encrypt
    long amOfEncrypted = 0;
    for (long i = 0; i < fileSize; i++) {
        *(bufForFile + i) ^= *(keyInBytes->elements + (i % keyInBytes->size));
        //printf("%lo: %d\n", i, *(keyInBytes->elements + (i % keyInBytes->size)));
        amOfEncrypted++;
    }

    //save encrypted file
    char *fileName = basename(pathToFile);
    int size = strlen(pathToSave) + strlen("/") + strlen("ENCR_") + strlen(fileName);
    char *encryptedFilePath = (char*)malloc(size*sizeof(char) + 1);
    strcpy(encryptedFilePath, pathToSave);
    strcat(encryptedFilePath, "/");
    strcat(encryptedFilePath, "ENCR_");
    strcat(encryptedFilePath, fileName);
    FILE *cryptedFile = fopen(encryptedFilePath, "w");
    if (cryptedFile == NULL) {
        fprintf(stderr, "%d: %s: %s: %s\n", getpid(), scriptName, strerror(errno), encryptedFilePath);
        return -1;
    }
    res = fwrite(bufForFile, sizeof(byte), amOfEncrypted, cryptedFile);
    if (res != amOfEncrypted) {
        fclose(cryptedFile);
        return -1;
    }
    int resClose = fclose(cryptedFile);
    if (resClose != 0) {
        fprintf(stderr, "%d: %s: %s: %s\n", getpid(), scriptName, strerror(errno), encryptedFilePath);
        return -1;
    }
    return amOfEncrypted;
}

void bypassFiles(char *scriptName, char *path, int N, char *pathToSave, bytesList *keyInBytes, dynArr *allPids, int *currAmOfProcesses) {

    //open current directory
    DIR *dp = opendir(path);
    if (dp == NULL) {
        fprintf(stderr, "%d: %s: %s: %s\n", getpid(), scriptName, strerror(errno), path);
        return;
    }


    //read current directory
    struct dirent *d;
    while ((d = readdir(dp)) != NULL) {

        //read excepting (infinity recursion) "." and ".."
        if (!strcmp(".", d->d_name) || !strcmp("..", d->d_name)) {
            continue;
        }

        //create buffer for path of read file
        int size = strlen(path) + strlen("/") + strlen(d->d_name);
        char *buf = (char*)malloc(size*sizeof(char) + 1);
        if (buf == NULL) {
            fprintf(stderr, "%d: %s: %s\n", getpid(), scriptName, strerror(errno));
            continue;
        }

        //write full path of read file
        strcpy(buf, path);
        strcat(buf, "/");
        strcat(buf, d->d_name);

        //check: file is directory (DT_DIR) or regular file (DT_REG)
        if (d->d_type == DT_DIR) {
            //recursive enter for read the next subdirectory
            bypassFiles(scriptName, buf, N, pathToSave, keyInBytes, allPids, currAmOfProcesses);

        } else if (d->d_type == DT_REG) {
            //check current amount of processes
            checkAmOfProcesses(scriptName, N, currAmOfProcesses);

            //if less:
            pid_t pid = fork();

            if (pid == 0) {
                FILE *fileToCrypt = fopen(buf, "r");
                if (fileToCrypt == NULL) {
                    fprintf(stderr, "%d: %s: %s: %s\n", getpid(), scriptName, strerror(errno), buf);
                    exit(EXIT_FAILURE);
                }
                long resCrypt = encryptingFile(scriptName, keyInBytes, fileToCrypt, buf, pathToSave);
                if (resCrypt >= 0) {
                    fprintf(stdout, "%d: %s %lo\n", getpid(), buf, resCrypt);
                }
                int res = fclose(fileToCrypt);
                if (res != 0) {
                    fprintf(stderr, "%d: %s: %s: %s\n", getpid(), scriptName, strerror(errno), buf);
                    exit(EXIT_FAILURE);
                }
                exit(EXIT_SUCCESS);
            }
            else {
                *(currAmOfProcesses) += 1;
                pushToListEnd(allPids, pid);
                if (allPids == NULL) {
                    fprintf(stderr, "%d: %s: %s: %s\n", getpid(), scriptName, strerror(errno), buf);
                    free(buf);
                    continue;
                }
            }
        }
        //free buffer memory
        free(buf);
    }

    int res = closedir(dp);
    if (res == -1) {
        fprintf(stderr, "%d: %s: %s: %s\n", getpid(), scriptName, strerror(errno), path);
    }
    return;
}


void calcTask(char *scriptName, char *path, int N, char *pathToSave, char *pathToFileKey) {
    //open file with key
    FILE *fileKey = fopen(pathToFileKey, "r");
    if (fileKey == NULL) {
        fprintf(stderr, "%d: %s: %s: %s\n", getpid(), scriptName, strerror(errno), pathToFileKey);
        exit(EXIT_FAILURE);
    }

    long sizeKey = getAmOfFileInBytes(scriptName, fileKey, pathToFileKey);

    //memory allocation for buffer for read file
    char *buf = (char*)malloc(sizeof(char)*sizeKey);
    memset(buf, 0, sizeof(char)*sizeKey);
    if (buf == NULL) {
        fprintf(stderr, "%d: %s: %s: %s\n", getpid(), scriptName, strerror(errno), pathToFileKey);
        free(buf);
        fclose(fileKey);
        exit(EXIT_FAILURE);
    }

    //read all symbols from file with key
    size_t resRead = fread(buf, sizeof(char), sizeKey, fileKey);
    if (resRead != sizeKey) {
        fprintf(stderr, "%d: %s: %s: %s\n", getpid(), scriptName, "Error reading", pathToFileKey);
        fclose(fileKey);
        exit(EXIT_FAILURE);
    }

    //close file with key
    int res = fclose(fileKey);
    if (res != 0) {
        fprintf(stderr, "%d: %s: %s: %s\n", getpid(), scriptName, strerror(errno), pathToFileKey);
        exit(EXIT_FAILURE);
    }

    //memory allocation for key
    char *key = (char*)malloc(sizeof(char)*strlen(buf));
    memset(key, 0, sizeof(char)*strlen(buf));
    if (key == NULL) {
        fprintf(stderr, "%d: %s: %s: %s\n", getpid(), scriptName, strerror(errno), pathToFileKey);
        free(key);
        exit(EXIT_FAILURE);
    }

    //fill key buffer with 1 or 0 from file buffer
    for (int i = 0;  i < strlen(buf); i++) {
        if (*(buf + i) == '1') {
            strcat(key, "1");
        }
        else
            if (*(buf + i) == '0') {
                strcat(key, "0");
            }
    }

    //free memory for file buffer
    free(buf);

    //format key into array with bytes
    bytesList* keyInBytes  = getKeyInBytes(scriptName, key);

    //free memory for key buffer
    free(key);

    int currAmOfProcesses = 1;

    dynArr *allPids = createList();
    //int *allPids = (int*)malloc(sizeof(int));


    //bypass all files
    bypassFiles(scriptName, path, N, pathToSave, keyInBytes, allPids, &currAmOfProcesses);

    //free memory space after all processes
    int currPid;
    dynArr *inter = allPids;
    while (allPids->size >= 1) {
        currPid = popFromListBegin(inter);
        waitpid(currPid, 0, 0);
        //printf("%d\n", inter->index);
    }
}


int main(int argc, char **argv) {
    /*
     *  argv[0]: scriptName - name of script
     *  argv[1]: path - source directory for searching and encrypting files
     *  argv[2]: N - max number of concurrent processes
     *  argv[3]: pathToSave - directory for saving encrypted files (must be created before executing)
     *  argv[4]: pathToFileKey - file with key for encrypt
     */

    char *scriptName = basename(argv[0]);

    if (argc < 5) {
        fprintf(stderr, "%d: %s: %s\n", getpid(), scriptName, "Incorrect value of command line arguments (must be 5)");
        exit(EXIT_FAILURE);
    }

    char *path = getRealPath(argv[1], scriptName);
    int N = atoi(argv[2]);
    if (N <= 1) {
        fprintf(stderr, "%d: %s: %s\n", getpid(), scriptName, "Incorrect value of number of concurrent processes (must be greater than 1)");
        exit(EXIT_FAILURE);
    }
    char *pathToSave = getRealPath(argv[3], scriptName);

    char *pathToFileKey = getRealPath(argv[4], scriptName);

    calcTask(scriptName, path, N, pathToSave, pathToFileKey);
    return 0;
}
