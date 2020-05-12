
#ifndef LABA4_MAIN_H
#define LABA4_MAIN_H

#include "dynList.h"
#include "files.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/time.h>
#include <libgen.h>

#define AM_OF_PROC         9
#define DELAY_OF_SIG       100
#define MAX_AM_OF_SIG      101

char *scriptName = NULL;

dynArr *gPidList;
dynArr *amOfSentSignals, *amOfRecvSignals;

void sigHandlerUSR_proc1(),
     sigHandlerUSR_proc2(),
     sigHandlerUSR_proc3(),
     sigHandlerUSR_proc4(),
     sigHandlerUSR_proc5(),
     sigHandlerUSR_proc6(),
     sigHandlerUSR_proc7(),
     sigHandlerUSR_proc8();

void sigHandlerTERM_proc1(),
     sigHandlerTERM_proc2(),
     sigHandlerTERM_proc3(),
     sigHandlerTERM_proc4(),
     sigHandlerTERM_proc5(),
     sigHandlerTERM_proc6(),
     sigHandlerTERM_proc7(),
     sigHandlerTERM_proc8();

void setSigactUSR_proc1(),
     setSigactUSR_proc2(),
     setSigactUSR_proc3(),
     setSigactUSR_proc4(),
     setSigactUSR_proc5(),
     setSigactUSR_proc6(),
     setSigactUSR_proc7(),
     setSigactUSR_proc8();

void setSigactTERM_proc1(),
     setSigactTERM_proc2(),
     setSigactTERM_proc3(),
     setSigactTERM_proc4(),
     setSigactTERM_proc5(),
     setSigactTERM_proc6(),
     setSigactTERM_proc7(),
     setSigactTERM_proc8();

void sendSignalSIGUSR1(int group);

int getNumOfSon(pid_t pid);

void waitForAllProcesses();
void waitForProcByIndex(int index);

void process1(),
     process2(),
     process3(),
     process4(),
     process5(),
     process6(),
     process7(),
     process8();

void outputProcessTree();

#endif //LABA4_MAIN_H
