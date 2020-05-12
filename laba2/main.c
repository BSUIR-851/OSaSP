/*
 * 9. Написать программу, находящую в заданном каталоге (первый аргумент командной строки)
 * и всех его подкаталогах...
 * ... все файлы заданного расширения и создающий для каждого найденного файла
 * жесткую ссылку в заданном каталоге.
 * Расширение файла и каталог для жестких ссылок задаются в качестве
 * второго и третьего аргументов командной строки.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

char *getRealPath(char *cat, char *scriptName) {
    char *dir = realpath(cat, NULL);
    if (dir == NULL) {
        perror(scriptName);
        exit(EXIT_FAILURE);
    }
    return dir;
}

char *getExt(char *fileName) {
    char *ext = strrchr(fileName, '.');
    if ((ext == NULL) || (!strcmp(ext, fileName)))
        return "";
    else
        return ext;
}

void searchFiles(char *path, char *ext, char *pathToLink, char *scriptName) {
    //printf("In %s:\n", path);
    char *localExt;
    DIR *dp = opendir(path);
    if (dp == NULL) {
        fprintf(stderr, "%s: %s: %s\n", scriptName, strerror(errno), path);
        return;
    }

    struct dirent *d;
    while (1) {
        errno = 0;
        d = readdir(dp);
        if ((d == NULL) && (errno != 0)) {
            perror(scriptName);
            continue;
        }
        if ((d == NULL) && (errno == 0)) {
            break;
        }

        if (!strcmp(".", d->d_name) || !strcmp("..", d->d_name)) {
            continue;
        }

        char *buf;
        int size = strlen(path) + strlen("/") + strlen(d->d_name);
        buf = (char*)malloc(size + 4);
        if (buf == NULL) {
            perror(scriptName);
            continue;
        }
        strcpy(buf, path);
        strcat(buf, "/");
        strcat(buf, d->d_name);

        if (d->d_type == DT_DIR) {
            searchFiles(buf, ext, pathToLink, scriptName);
            free(buf);
        } else if (d->d_type == DT_REG) {
            localExt = getExt(d->d_name);
            if (!strcmp(localExt, ext)) {

                char *newLink;
                int sizeLink = strlen(pathToLink) + strlen("/")  + strlen(d->d_name);
                newLink = (char*)malloc(sizeLink + 4);
                if (newLink == NULL) {
                    perror(scriptName);
                    free(buf);
                    continue;
                }
                strcpy(newLink, pathToLink);
                strcat(newLink, "/");
                strcat(newLink, d->d_name);

                int res = link(buf, newLink);
                if (res != 0) {
                    if (errno == EEXIST) {
                        fprintf(stderr, "%s: Link to file %s is created\n", scriptName, buf);
                    }
                    else  {
                        fprintf(stderr, "%s: %s: %s\n", scriptName, strerror(errno), buf);
                    }
                    free(buf);
                    free(newLink);
                    continue;
                }
                printf("%s\n", buf);
                free(buf);
                free(newLink);
            }
        }
    }

    int res = closedir(dp);
    if (res == -1) {
        fprintf(stderr, "%s: %s: %s\n", scriptName, strerror(errno), path);
    }
    return;
}

void calcTask(char *dir, char *ext, char *pathToLink, char *scriptName) {
    int res = mkdir(pathToLink, 0777);
    if (res != 0) {
        fprintf(stderr, "%s: %s: %s\n", scriptName, strerror(errno), pathToLink);
    }
    searchFiles(dir, ext, pathToLink, scriptName);
}

int main(int argc, char **argv) {
    char *scriptName = basename(argv[0]);
    char *path = argv[1];
    char *ext = argv[2];
    char *pathToLink = argv[3];
    //printf("%s\n", pathToLink);
    char *dir = getRealPath(path, scriptName);
    calcTask(dir, ext, pathToLink, scriptName);
    return 0;
}
