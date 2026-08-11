#ifndef JOBS_H
#define JOBS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "colors.h"


typedef struct Job {
    pid_t pid;
    char* command;
    int running;
    int exit_code;
    struct Job* next;
    int remaining;
} Job;

typedef struct JobList {
    Job* head;
    int count;
} JobList;

JobList* initJobList(JobList* jobList);

int addJob(JobList* jobList, pid_t pid, const char* command, int remaining);

int removeJob(JobList* jobList, pid_t pid);

int freeJobList(JobList* jobList);

int reapChildrenPoll(JobList* jobList);

Job* findJobByPid(JobList* jobList, pid_t pid);

#endif