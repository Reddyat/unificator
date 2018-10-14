#include <sys/time.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "unificator_timer.h"

void unificator_timer_start(struct timeval * tv)
{
	_unificator_timer_now(tv);
}

int32_t unificator_timer_get(struct timeval * tv)
{
	struct timeval now;
	_unificator_timer_now(&now);

	if ( now.tv_sec < tv->tv_sec )
	{
		printf("Error: Clock changed during the processing or processing duration too long.");
		return -1;
	}

	time_t diff_seconds = now.tv_sec - tv->tv_sec;
	suseconds_t diff_microseconds = now.tv_usec - tv->tv_usec;

	return (diff_seconds * 1000000) + diff_microseconds;
}

void _unificator_timer_now(struct timeval * local_tv)
{
	if ( gettimeofday(local_tv, NULL) != 0 )
	{
		printf("Error : Clock error.");
		exit(EXIT_FAILURE);
	}
}