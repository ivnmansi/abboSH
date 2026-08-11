#include "jobs.h"
#include "pipeline.h"
 
#define INIT_FILE ".abbosh"

int main(){
  char** args;
  char* prompt;

  JobList* jobList = initJobList(NULL);

  execFile(INIT_FILE, jobList);

  while(1){
    reapChildrenPoll(jobList);
    prompt = getPrompt();
    printf("%s", prompt);
    free(prompt);
    args = readLine();
    execLine(args, jobList);
    freeArgs(args);
  }

  freeJobList(jobList);

  return 0;
}

