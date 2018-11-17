#include <iostream>
#include <time.h>
#include <math.h>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

const int INITIAL_CYCLE = 1;
const int WORK_TIME = 2;
const int BREAK_TIME = 1;
const int LONG_BREAK_TIME = 5;

const int BREAK_AFTER_CYCLES = 5;
const int LONG_BREAK_AFTER_CYCLES = 900;

const int SEC_IN_MIN = 60;
const int TOTAL_COUNT = 3;

const int cseconds_in_day = 86400;
const int cseconds_in_hour = 3600;
const int cseconds_in_minute = 60;
const int cseconds = 1;
int total = 0;

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

int Countdown(time_t targetTime)
{
  time_t currentTime = GetCurrentTime();
  long diffTime = difftime(targetTime, currentTime);
  long input_seconds = diffTime;
  int days = input_seconds / cseconds_in_day;
  int hours = (input_seconds % cseconds_in_day) / cseconds_in_hour;
  int minutes = ((input_seconds % cseconds_in_day) % cseconds_in_hour) / cseconds_in_minute;
  int seconds = (((input_seconds % cseconds_in_day) % cseconds_in_hour) % cseconds_in_minute) / cseconds;

  clear();
  printf("%02d:%02d:%02d --%2d -- %d\n", hours, minutes, seconds, total, diffTime);
  return diffTime;
}

void StartCycle(int duration, int cycle)
{
  while (true)
  {
    if (Countdown(GetTargetTime(duration)) == 1)
      break;
    sleep(1);
  }
}

void StartWork()
{
  while (true)
  {
    int cycle = INITIAL_CYCLE;
    int cycleDuration = WORK_TIME;

    if (cycle == TOTAL_COUNT)
    {
      cycle = INITIAL_CYCLE;
      cycleDuration = LONG_BREAK_TIME;
    }
    else if (cycle % 2 == 1)
    {
      cycleDuration = BREAK_TIME;
    }
    else
    {
      cycleDuration = WORK_TIME;
    }

    StartCycle(cycleDuration, cycle);
    total++;
    cycle++;
    sleep(1);
  }
}

int main()
{
  StartWork();
}