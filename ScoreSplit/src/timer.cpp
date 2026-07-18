#include "timer.h"

void tick_all_timers(Timer timers[], int size)
{
	for (int i = 0; i< size; i++)
	{
		timers[i].tick_timer();
	}
}