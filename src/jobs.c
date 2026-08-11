#include "jobs.h"
#include <sys/wait.h>

JobList* initJobList(JobList* jobList){
    jobList = (JobList*)malloc(sizeof(JobList));
    if(jobList == NULL){
        return NULL;
    }
    jobList->head = NULL;
    jobList->count = 0;
    return jobList;
}

int freeJobList(JobList* jobList){
    Job* current = jobList->head;
    while(current != NULL){
        Job* temp = current;
        current = current->next;
        free(temp->command);
        free(temp);
    }
    free(jobList);
    return 0;
}

int addJob(JobList* jobList, pid_t pid, const char* command){
    Job* newJob = (Job*)malloc(sizeof(Job));
    if(newJob == NULL){
        return -1; // Memory allocation failed
    }

    newJob->pid = pid;
    newJob->command = strdup(command);
    newJob->running = 1;
    newJob->exit_code = -1;
    newJob->next = NULL;

    Job* current = jobList->head;
    if(current == NULL){
        jobList->head = newJob;
    }
    else {
        while(current->next != NULL){
            current = current->next;
        }
        current->next = newJob;
    }

    jobList->count++;
    return 0;
}

int removeJob(JobList* jobList, pid_t pid){
    Job* current = jobList->head;
    Job* previous = NULL;

    while(current != NULL){
        if(current->pid == pid){
            if(previous == NULL){
                jobList->head = current->next;
            }
            else {
                previous->next = current->next;
            }
            free(current->command);
            free(current);
            jobList->count--;
            return 0;
        }
        previous = current;
        current = current->next;
    }
    return -1; // Job not found
}

Job* findJobByPid(JobList* jobList, pid_t pid){
    Job* current = jobList->head;
    while(current != NULL){
        if(current->pid == pid){
            return current;
        }
        current = current->next;
    }
    return NULL; // Job not found
}

int reapChildrenPoll(JobList* jobList){
    pid_t pid;
    int status;
    int reaped = 0;

    while((pid = waitpid(-1, &status, WNOHANG)) > 0){
        Job* job = findJobByPid(jobList, pid);
        int exit_code = -1;

        if(WIFEXITED(status)){
            exit_code = WEXITSTATUS(status);
        }
        else if(WIFSIGNALED(status)){
            exit_code = WTERMSIG(status) + 128; // Convention for signal termination
        }

        if(job != NULL){
            printf(BLUE"[Process with PID %d finished with exit code %d]\n", pid, exit_code);
            job->running = 0;
            job->exit_code = exit_code;
        }
        reaped++;
    }

    if(pid == -1 && errno != ECHILD){
        return -1;
    }

    return reaped;
}

