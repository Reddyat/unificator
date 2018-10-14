#ifndef UNIFICATOR_TIMER_H
#define UNIFICATOR_TIMER_H

#include <sys/time.h>
#include <stdint.h>

/**
  * @brief Start the timer of reset it if already started.
  * @return 0 if succeed, -1 otherwise.
  */
void unificator_timer_start(struct timeval * tv);

/**
  * @brief Get the difference between the unificator_timer_start
  *       and now in microseconds.
  */
int32_t unificator_timer_get(struct timeval * tv);

/**
  * @brief Local function to set a timeval struct to now. */
void _unificator_timer_now(struct timeval * local_tv);

#endif