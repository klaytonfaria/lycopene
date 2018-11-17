#include <iostream>
#include <time.h>
#include <math.h>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

const int WORK_TIME = 1;
const int BREAK_TIME = 1;
const int LONG_BREAK_TIME = 2;

const int BREAK_AFTER_CYCLES = 5;
const int LONG_BREAK_AFTER_CYCLES = 900;

const int SEC_IN_MIN = 60;
const int TOTAL_COUNT = 3;

const int cseconds_in_day = 86400;
const int cseconds_in_hour = 3600;
const int cseconds_in_minute = 60;
const int cseconds = 1;

using namespace std;

void clear()
{
  // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
  std::cout << "\x1B[2J\x1B[H";
}

time_t GetTargetTime(int duration) {
  time_t initialTime;
  struct tm *startTimeinfo;
  time_t startTime = time(&initialTime);
  startTimeinfo = localtime(&startTime);
  startTimeinfo->tm_min += duration;
  startTimeinfo->tm_sec = 0;

  return mktime(startTimeinfo);
}

time_t GetCurrentTime()
{
  time_t endtime;
  time(&endtime);

  return mktime(localtime(&endtime));
}

void Countdown(time_t targetTime)
{
  time_t currentTime = GetCurrentTime();
  long diffTime = difftime(targetTime, currentTime);
  long input_seconds = diffTime;
  int days = input_seconds / cseconds_in_day;
  int hours = (input_seconds % cseconds_in_day) / cseconds_in_hour;
  int minutes = ((input_seconds % cseconds_in_day) % cseconds_in_hour) / cseconds_in_minute;
  int seconds = (((input_seconds % cseconds_in_day) % cseconds_in_hour) % cseconds_in_minute) / cseconds;

  clear();
  printf("%02d:%02d:%02d\n", hours, minutes, seconds);
}

void StartCycle(int duration, int cycle)
{
  while (true)
  {
    Countdown(GetTargetTime(duration));
    sleep(1);
  }
}

void StartWork()
{
  int cycle = 0;
  int cycleDuration = WORK_TIME;
  int cyclecycleDurationInSeconds;

  if (cycle == TOTAL_COUNT)
  {
    cycle = 0;
    cycleDuration = LONG_BREAK_TIME;
  }
  else
  {
    if (cycle % 2 == 0)
      cycleDuration = WORK_TIME;
    else
      cycleDuration = BREAK_TIME;
  }

  cyclecycleDurationInSeconds = cycleDuration * cseconds_in_minute;

  while (true)
  {
    StartCycle(cycleDuration, cycle);
    cycle++;
    sleep(cyclecycleDurationInSeconds);
  }
}

int main()
{
  StartWork();
}