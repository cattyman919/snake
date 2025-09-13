#ifndef TIMER_H
#define TIMER_H

#include "raylib.h"

class Timer {
 public:
  Timer(double lifetime) : m_lifeTime(lifetime) {};

  // Remove Copy Constructor
  Timer(const Timer& other) = delete;
  Timer& operator=(const Timer& other) = delete;

  void StartTimer(double lifetime) {
    this->m_startTime = GetTime();
    this->m_lifeTime = lifetime;
  }

  bool TimerDone() { return GetElapsed() >= this->m_lifeTime; }

  double GetElapsed() { return GetTime() - this->m_startTime; }

 private:
  double m_startTime{GetTime()};
  double m_lifeTime;
};

#endif
