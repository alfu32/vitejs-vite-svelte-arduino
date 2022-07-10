#ifndef TASK_SCHEDULER_CPP_
#define TASK_SCHEDULER_CPP_
#include "TaskScheduler.h"

TaskScheduler::TaskScheduler(unsigned int initialSize){
  this->size=initialSize;
  this->tasks=(Task**)malloc(initialSize*sizeof(Task*));//new Task[initialSize];
}

TaskScheduler* TaskScheduler::schedule(Task* task){
  tasks[this->last]=task;
  this->last++;
  return this;
}

TaskScheduler* TaskScheduler::run(){
  unsigned long currentFrame=micros();
  //Serial.printf("running %d tasks;frame %llu\n",this->last,currentFrame);
  for(unsigned int i=0;i<this->last;i++){
    Task* task=(this->tasks)[i];
    //Serial.printf("will run %d...",i);
    if(!(task)){
      //Serial.printf("ERR:no task @%d\n",i);
      continue;
    }
    if((task->lastRunMicros  + task->timing) <= currentFrame){
      if(!(task->run)){
        //Serial.printf("ERR:no runnable @%d\n",i);
        continue;
      }
      task->run();
      task->lastRunMicros=currentFrame;
      //Serial.printf("DONE:had run @%d\n",i,task->lastRunMicros  + task->timing,currentFrame);
    }else{
      //Serial.printf("SKIP:task @%d (%d>=%d)\n",i);
    }
  }
  return this;
}

#endif