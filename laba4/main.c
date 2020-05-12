/*
 * Table 1: Var 1
 *  0->1
 *  1->2
 *  2->(3,4)
 *  4->5
 *  3->6
 *  6->7
 *  7->8
 *
 *  Table 2: Var 5
 *  1->(2,3,4,5) SIGUSR1
 *  5->(6,7,8) SIGUSR1
 *  8->1 SIGUSR1
 */

#include "main.h"

int main(int argc, char* argv[]) {
    //get name of script
    scriptName = basename(argv[0]);

    //initialize files for pids
    initAllFiles(scriptName);

    //initialize dynamic arrays for pids, signals with 0
    gPidList = createList();
    amOfSentSignals = createList();
    amOfRecvSignals = createList();

    for (int i = 0; i < AM_OF_PROC; i++) {
        pushToListEnd(gPidList, 0);
        pushToListEnd(amOfSentSignals, 0);
        pushToListEnd(amOfRecvSignals, 0);
    }

    changeValueByIndex(gPidList, 0, getpid());

    //create process #1
    int proc1 = fork();
    if (proc1 == 0) {
        changeValueByIndex(gPidList, 1, getpid());
        process1();
    } else {
        waitpid(proc1, 0, 0);
    }

    return 0;
}

void waitForProcByIndex(int index) {
    char pidFile[1];
    sprintf(pidFile, "%d", index);
    waitForPid(scriptName, pidFile);
}

void setSigactUSR_proc1() {
    //create and set properties for signal action
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_sigaction = sigHandlerUSR_proc1;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    int res = sigaction(SIGUSR1, &sa, NULL);
    if (res != 0) {
        fprintf(stderr, "%d: %s: %s\n", getpid(), scriptName, strerror(errno));
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
}

void setSigactTERM_proc1() {
    //create and set properties for signal action
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_sigaction = sigHandlerTERM_proc1;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    int res = sigaction(SIGTERM, &sa, NULL);
    if (res != 0) {
        fprintf(stderr, "%d: %s: %s\n", getpid(), scriptName, strerror(errno));
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
}

void setSigactUSR_proc2() {
    //create and set properties for signal action
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_sigaction = sigHandlerUSR_proc2;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    int res = sigaction(SIGUSR1, &sa, NULL);
    if (res != 0) {
        fprintf(stderr, "%d: %s: %s\n", getpid(), scriptName, strerror(errno));
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
}

void setSigactTERM_proc2() {
    //create and set properties for signal action
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_sigaction = sigHandlerTERM_proc2;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    int res = sigaction(SIGTERM, &sa, NULL);
    if (res != 0) {
        fprintf(stderr, "%d: %s: %s\n", getpid(), scriptName, strerror(errno));
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
}

void setSigactUSR_proc3() {
    //create and set properties for signal action
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_sigaction = sigHandlerUSR_proc3;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    int res = sigaction(SIGUSR1, &sa, NULL);
    if (res != 0) {
        fprintf(stderr, "%d: %s: %s\n", getpid(), scriptName, strerror(errno));
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
}

void setSigactTERM_proc3() {
    //create and set properties for signal action
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_sigaction = sigHandlerTERM_proc3;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    int res = sigaction(SIGTERM, &sa, NULL);
    if (res != 0) {
        fprintf(stderr, "%d: %s: %s\n", getpid(), scriptName, strerror(errno));
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
}

void setSigactUSR_proc4() {
    //create and set properties for signal action
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_sigaction = sigHandlerUSR_proc4;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    int res = sigaction(SIGUSR1, &sa, NULL);
    if (res != 0) {
        fprintf(stderr, "%d: %s: %s\n", getpid(), scriptName, strerror(errno));
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
}

void setSigactTERM_proc4() {
    //create and set properties for signal action
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_sigaction = sigHandlerTERM_proc4;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    int res = sigaction(SIGTERM, &sa, NULL);
    if (res != 0) {
        fprintf(stderr, "%d: %s: %s\n", getpid(), scriptName, strerror(errno));
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
}

void setSigactUSR_proc5() {
    //create and set properties for signal action
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_sigaction = sigHandlerUSR_proc5;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    int res = sigaction(SIGUSR1, &sa, NULL);
    if (res != 0) {
        fprintf(stderr, "%d: %s: %s\n", getpid(), scriptName, strerror(errno));
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
}

void setSigactTERM_proc5() {
    //create and set properties for signal action
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_sigaction = sigHandlerTERM_proc5;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    int res = sigaction(SIGTERM, &sa, NULL);
    if (res != 0) {
        fprintf(stderr, "%d: %s: %s\n", getpid(), scriptName, strerror(errno));
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
}

void setSigactUSR_proc6() {
    //create and set properties for signal action
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_sigaction = sigHandlerUSR_proc6;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    int res = sigaction(SIGUSR1, &sa, NULL);
    if (res != 0) {
        fprintf(stderr, "%d: %s: %s\n", getpid(), scriptName, strerror(errno));
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
}

void setSigactTERM_proc6() {
    //create and set properties for signal action
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_sigaction = sigHandlerTERM_proc6;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    int res = sigaction(SIGTERM, &sa, NULL);
    if (res != 0) {
        fprintf(stderr, "%d: %s: %s\n", getpid(), scriptName, strerror(errno));
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
}

void setSigactUSR_proc7() {
    //create and set properties for signal action
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_sigaction = sigHandlerUSR_proc7;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    int res = sigaction(SIGUSR1, &sa, NULL);
    if (res != 0) {
        fprintf(stderr, "%d: %s: %s\n", getpid(), scriptName, strerror(errno));
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
}

void setSigactTERM_proc7() {
    //create and set properties for signal action
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_sigaction = sigHandlerTERM_proc7;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    int res = sigaction(SIGTERM, &sa, NULL);
    if (res != 0) {
        fprintf(stderr, "%d: %s: %s\n", getpid(), scriptName, strerror(errno));
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
}

void setSigactUSR_proc8() {
    //create and set properties for signal action
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_sigaction = sigHandlerUSR_proc8;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    int res = sigaction(SIGUSR1, &sa, NULL);
    if (res != 0) {
        fprintf(stderr, "%d: %s: %s\n", getpid(), scriptName, strerror(errno));
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
}

void setSigactTERM_proc8() {
    //create and set properties for signal action
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_sigaction = sigHandlerTERM_proc8;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    int res = sigaction(SIGTERM, &sa, NULL);
    if (res != 0) {
        fprintf(stderr, "%d: %s: %s\n", getpid(), scriptName, strerror(errno));
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
}

void sigHandlerUSR_proc1() {

    int procNum = getNumOfSon(getpid());
    changeValueByIndex(amOfRecvSignals, procNum, getValueByIndex(amOfRecvSignals, procNum) + 1);

    struct timeval tv;
    gettimeofday(&tv, NULL);

    fprintf(stdout, "%d %d %d получил SIGUSR1 %ld\n", procNum, getpid(), getppid(), tv.tv_usec % 1000);
    fflush(stdout);

    if (getValueByIndex(amOfRecvSignals, procNum) < MAX_AM_OF_SIG) {
        changeValueByIndex(amOfSentSignals, 1, getValueByIndex(amOfSentSignals, 1) + 1);
        sendSignalSIGUSR1(getPidFromFile(scriptName, "2"));
    }
    else {
        kill(getPidFromFile(scriptName, "2"), SIGTERM);
        waitpid(getPidFromFile(scriptName, "2"), 0, 0);
        exit(EXIT_SUCCESS);
    }

}

void sigHandlerUSR_proc2() {

    int procNum = getNumOfSon(getpid());
    changeValueByIndex(amOfRecvSignals, procNum, getValueByIndex(amOfRecvSignals, procNum) + 1);

    struct timeval tv;
    gettimeofday(&tv, NULL);

    fprintf(stdout, "%d %d %d получил SIGUSR1 %ld\n", procNum, getpid(), getppid(), tv.tv_usec % 1000);
    fflush(stdout);

}

void sigHandlerUSR_proc3() {

    int procNum = getNumOfSon(getpid());
    changeValueByIndex(amOfRecvSignals, procNum, getValueByIndex(amOfRecvSignals, procNum) + 1);

    struct timeval tv;
    gettimeofday(&tv, NULL);

    fprintf(stdout, "%d %d %d получил SIGUSR1 %ld\n", procNum, getpid(), getppid(), tv.tv_usec % 1000);
    fflush(stdout);

}

void sigHandlerUSR_proc4() {

    int procNum = getNumOfSon(getpid());
    changeValueByIndex(amOfRecvSignals, procNum, getValueByIndex(amOfRecvSignals, procNum) + 1);

    struct timeval tv;
    gettimeofday(&tv, NULL);

    fprintf(stdout, "%d %d %d получил SIGUSR1 %ld\n", procNum, getpid(), getppid(), tv.tv_usec % 1000);
    fflush(stdout);

}

void sigHandlerUSR_proc5() {

    int procNum = getNumOfSon(getpid());
    changeValueByIndex(amOfRecvSignals, procNum, getValueByIndex(amOfRecvSignals, procNum) + 1);

    struct timeval tv;
    gettimeofday(&tv, NULL);

    fprintf(stdout, "%d %d %d получил SIGUSR1 %ld\n", procNum, getpid(), getppid(), tv.tv_usec % 1000);
    fflush(stdout);

    changeValueByIndex(amOfSentSignals, 5, getValueByIndex(amOfSentSignals, 5) + 1);
    sendSignalSIGUSR1(getPidFromFile(scriptName, "6"));
}


void sigHandlerUSR_proc6() {

    int procNum = getNumOfSon(getpid());
    changeValueByIndex(amOfRecvSignals, procNum, getValueByIndex(amOfRecvSignals, procNum) + 1);

    struct timeval tv;
    gettimeofday(&tv, NULL);

    fprintf(stdout, "%d %d %d получил SIGUSR1 %ld\n", procNum, getpid(), getppid(), tv.tv_usec % 1000);
    fflush(stdout);

}

void sigHandlerUSR_proc7() {

    int procNum = getNumOfSon(getpid());
    changeValueByIndex(amOfRecvSignals, procNum, getValueByIndex(amOfRecvSignals, procNum) + 1);

    struct timeval tv;
    gettimeofday(&tv, NULL);

    fprintf(stdout, "%d %d %d получил SIGUSR1 %ld\n", procNum, getpid(), getppid(), tv.tv_usec % 1000);
    fflush(stdout);

}

void sigHandlerUSR_proc8() {

    int procNum = getNumOfSon(getpid());
    changeValueByIndex(amOfRecvSignals, procNum, getValueByIndex(amOfRecvSignals, procNum) + 1);

    struct timeval tv;
    gettimeofday(&tv, NULL);

    fprintf(stdout, "%d %d %d получил SIGUSR1 %ld\n", procNum, getpid(), getppid(), tv.tv_usec % 1000);
    fflush(stdout);

    changeValueByIndex(amOfSentSignals, 8, getValueByIndex(amOfSentSignals, 8) + 1);
    sendSignalSIGUSR1(getPidFromFile(scriptName, "1"));

}

void sigHandlerTERM_proc1() {

    int procNum = getNumOfSon(getpid());
    int amount = getValueByIndex(amOfSentSignals, procNum);

    fprintf(stdout, "%d %d %d завершил работу после %d-го сигнала SIGUSR1 и 0-го сигнала SIGUSR2\n", procNum, getpid(), getppid(), amount);
    fflush(stdout);

    changeValueByIndex(gPidList, procNum, -1);
    exit(EXIT_SUCCESS);
}

void sigHandlerTERM_proc2() {

    int procNum = getNumOfSon(getpid());
    int amount = getValueByIndex(amOfSentSignals, procNum);

    fprintf(stdout, "%d %d %d завершил работу после %d-го сигнала SIGUSR1 и 0-го сигнала SIGUSR2\n", procNum, getpid(), getppid(), amount);
    fflush(stdout);

    kill(getPidFromFile(scriptName, "3"), SIGTERM);
    kill(getPidFromFile(scriptName, "4"), SIGTERM);
    waitpid(getPidFromFile(scriptName, "3"), 0, 0);
    waitpid(getPidFromFile(scriptName, "4"), 0, 0);

    changeValueByIndex(gPidList, procNum, -1);
    exit(EXIT_SUCCESS);
}

void sigHandlerTERM_proc3() {

    int procNum = getNumOfSon(getpid());
    int amount = getValueByIndex(amOfSentSignals, procNum);

    fprintf(stdout, "%d %d %d завершил работу после %d-го сигнала SIGUSR1 и 0-го сигнала SIGUSR2\n", procNum, getpid(), getppid(), amount);
    fflush(stdout);

    kill(getPidFromFile(scriptName, "6"), SIGTERM);
    waitpid(getPidFromFile(scriptName, "6"), 0, 0);

    changeValueByIndex(gPidList, procNum, -1);
    exit(EXIT_SUCCESS);
}

void sigHandlerTERM_proc4() {

    int procNum = getNumOfSon(getpid());
    int amount = getValueByIndex(amOfSentSignals, procNum);

    fprintf(stdout, "%d %d %d завершил работу после %d-го сигнала SIGUSR1 и 0-го сигнала SIGUSR2\n", procNum, getpid(), getppid(), amount);
    fflush(stdout);

    kill(getPidFromFile(scriptName, "5"), SIGTERM);
    waitpid(getPidFromFile(scriptName, "5"), 0, 0);

    changeValueByIndex(gPidList, procNum, -1);
    exit(EXIT_SUCCESS);
}

void sigHandlerTERM_proc5() {

    int procNum = getNumOfSon(getpid());
    int amount = getValueByIndex(amOfSentSignals, procNum);

    fprintf(stdout, "%d %d %d завершил работу после %d-го сигнала SIGUSR1 и 0-го сигнала SIGUSR2\n", procNum, getpid(), getppid(), amount);
    fflush(stdout);

    changeValueByIndex(gPidList, procNum, -1);
    exit(EXIT_SUCCESS);
}

void sigHandlerTERM_proc6() {

    int procNum = getNumOfSon(getpid());
    int amount = getValueByIndex(amOfSentSignals, procNum);

    fprintf(stdout, "%d %d %d завершил работу после %d-го сигнала SIGUSR1 и 0-го сигнала SIGUSR2\n", procNum, getpid(), getppid(), amount);
    fflush(stdout);

    kill(getPidFromFile(scriptName, "7"), SIGTERM);
    waitpid(getPidFromFile(scriptName, "7"), 0, 0);

    changeValueByIndex(gPidList, procNum, -1);
    exit(EXIT_SUCCESS);
}

void sigHandlerTERM_proc7() {

    int procNum = getNumOfSon(getpid());
    int amount = getValueByIndex(amOfSentSignals, procNum);

    fprintf(stdout, "%d %d %d завершил работу после %d-го сигнала SIGUSR1 и 0-го сигнала SIGUSR2\n", procNum, getpid(), getppid(), amount);
    fflush(stdout);

    kill(getPidFromFile(scriptName, "8"), SIGTERM);
    waitpid(getPidFromFile(scriptName, "8"), 0, 0);

    changeValueByIndex(gPidList, procNum, -1);
    exit(EXIT_SUCCESS);
}

void sigHandlerTERM_proc8() {

    int procNum = getNumOfSon(getpid());
    int amount = getValueByIndex(amOfSentSignals, procNum);

    fprintf(stdout, "%d %d %d завершил работу после %d-го сигнала SIGUSR1 и 0-го сигнала SIGUSR2\n", procNum, getpid(), getppid(), amount);
    fflush(stdout);

    changeValueByIndex(gPidList, procNum, -1);
    exit(EXIT_SUCCESS);
}


void sendSignalSIGUSR1(int group) {

    int procNum = getNumOfSon(getpid());

    usleep(DELAY_OF_SIG);

    struct timeval tv;
    gettimeofday(&tv, NULL);

    fprintf(stdout, "%d %d %d послал SIGUSR1 %ld \n", procNum, getpid(), getppid(), tv.tv_usec % 1000);
    fflush(stdout);

    if (kill(-group, SIGUSR1) == -1) {
        fprintf(stderr, "%d: %s: %s\n", getpid(), scriptName, strerror(errno));
        fflush(stderr);
    }
}

int getNumOfSon(pid_t pid) {
    for (int i = 0; i < AM_OF_PROC; i++) {
        if (getValueByIndex(gPidList, i) == pid) {
            return i;
        }
    }
    return 0;
}

void process1() {
    if (getpid() == getValueByIndex(gPidList, 1)) {
        writePid(scriptName, "1", getpid());

        setSigactUSR_proc1();
        setSigactTERM_proc1();

        setpgid(getpid(), getpid());

        //create process #2
        if (fork() == 0) {
            changeValueByIndex(gPidList, 2, getpid());
            process2();

        } else {
            waitForProcByIndex(8);
            sendSignalSIGUSR1(getPidFromFile(scriptName, "2"));
            while (1) {
                pause();
            }
        }
    }
}

void process2() {
    if (getpid() == getValueByIndex(gPidList, 2)) {
        writePid(scriptName, "2", getpid());

        setSigactUSR_proc2();
        setSigactTERM_proc2();

        setpgid(getpid(), getpid());

        //create process #3
        if (fork() == 0) {
            changeValueByIndex(gPidList, 3, getpid());
            process3();

        } else {
            //process #4
            if (fork() == 0) {
                changeValueByIndex(gPidList, 4, getpid());
                process4();

            } else {
                while (1) {
                    pause();
                }
            }
        }
    }
}

void process3() {
    if (getpid() == getValueByIndex(gPidList, 3)) {
        writePid(scriptName, "3", getpid());

        setSigactUSR_proc3();
        setSigactTERM_proc3();

        waitForProcByIndex(2);
        setpgid(getpid(), getPidFromFile(scriptName, "2"));

        //create process #6
        if (fork() == 0) {
            changeValueByIndex(gPidList, 6, getpid());
            process6();

        } else {
            while (1) {
                pause();
            }
        }
    }
}

void process4() {
    if (getpid() == getValueByIndex(gPidList, 4)) {
        writePid(scriptName, "4", getpid());

        setSigactUSR_proc4();
        setSigactTERM_proc4();

        waitForProcByIndex(2);
        setpgid(getpid(), getPidFromFile(scriptName, "2"));

        //create process #5
        if (fork() == 0) {
            changeValueByIndex(gPidList, 5, getpid());
            process5();

        } else {
            while (1) {
                pause();
            }
        }
    }
}

void process5() {
    if (getpid() == getValueByIndex(gPidList, 5)) {
        writePid(scriptName, "5", getpid());

        setSigactUSR_proc5();
        setSigactTERM_proc5();

        waitForProcByIndex(2);
        setpgid(getpid(), getPidFromFile(scriptName, "2"));

        while (1) {
            pause();
        }
    }
}

void process6() {
    if (getpid() == getValueByIndex(gPidList, 6)) {
        writePid(scriptName, "6", getpid());

        setSigactUSR_proc6();
        setSigactTERM_proc6();

        setpgid(getpid(), getPidFromFile(scriptName, "6"));

        //create process #7
        if (fork() == 0) {
            changeValueByIndex(gPidList, 7, getpid());
            process7();

        } else {
            while (1) {
                pause();
            }
        }
    }
}

void process7() {
    if (getpid() == getValueByIndex(gPidList, 7)) {
        writePid(scriptName, "7", getpid());

        setSigactUSR_proc7();
        setSigactTERM_proc7();

        waitForProcByIndex(6);
        setpgid(getpid(), getPidFromFile(scriptName, "6"));

        //create process #8
        if (fork() == 0) {
            changeValueByIndex(gPidList, 8, getpid());
            process8();

        } else {
            while (1) {
                pause();
            }
        }
    }
}

void process8() {
    if (getpid() == getValueByIndex(gPidList, 8)) {

        setSigactUSR_proc8();
        setSigactTERM_proc8();

        waitForProcByIndex(6);

        outputProcessTree();
        setpgid(getpid(), getPidFromFile(scriptName, "6"));

        writePid(scriptName, "8", getpid());
        while (1) {
            pause();
        }
    }
}

void outputProcessTree() {
    char treeCmdBuf[32] = {0};
    sprintf(treeCmdBuf, "pstree -p %d", getValueByIndex(gPidList, 0));
    system(treeCmdBuf);
}