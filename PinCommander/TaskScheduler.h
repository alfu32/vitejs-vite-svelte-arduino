#ifndef TASK_SCHEDULER_H_
#define TASK_SCHEDULER_H_
#include <Arduino.h>

#define TIMING_ONCE 0xFFFFFFFF
#define TIMING_FASTEST 0x1

typedef struct Task{
  Task(char* name, int timing,void (*run)() ) : name(name), timing(timing),run(run) {}
  char* name;
  unsigned long lastRunMicros=0;
  unsigned long timing=0;
  void (*run)();
} Task;

class TaskScheduler{
  public:
  TaskScheduler(unsigned int initialSize);
  TaskScheduler* schedule(Task* task);
  TaskScheduler* run();
  private:
  Task** tasks;
  unsigned int last=0;
  unsigned int size=0;
};

#endif