#pragma once

#include <time.h>

/*
	IT 266

	An API for getting millisecond time.
*/

/*	Stealing this function	*/
int timeDiff = 0;
int	curtime;
int ModTime_Milliseconds(void)
{
	static int		base;
	static char	initialized = 0;

	if (!initialized)
	{	// let base retain 16 bits of effectively random data
		base = timeGetTime() & 0xffff0000;
		initialized = 1;
	}
	curtime = timeGetTime() - base;

	return curtime;
}
int ModTime_GetTimeSinceLastCall()
{
	int diff;
	if (timeDiff == 0)
	{
		timeDiff = ModTime_Milliseconds();
		return 0;
	}
	diff = ModTime_Milliseconds() - timeDiff;
	timeDiff = ModTime_Milliseconds();
	return diff;
	
}