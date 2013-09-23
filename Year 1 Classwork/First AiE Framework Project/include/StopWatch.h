/******************************************************************************
 * File:               StopWatch.h
 * Author:             Elizabeth Lowry
 * Date Created:       September 23, 2013
 * Description:        Definitions for the class that tracks elapsed time.
 * Last Modified:      September 23, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _STOP_WATCH_H_
#define _STOP_WATCH_H_

// Class handling a timer that tracks elapsed time (excluding time paused)
class StopWatch
{
public:

	StopWatch();

	void Clear();
	unsigned long GetTicks();
	double GetMilliseconds();	// total elapsed milliseconds
	double GetSeconds();		// total elapsed seconds
	double GetMinutes();		// total elapsed minutes
	double GetHours();			// total elapsed hours
	void PrintTime( char* a_pcBuffer, unsigned int a_uiBufferSize);
	void Start();
	void Stop();

private:

	// hours:minutes:seconds.milliseconds, or "%d:%02d:%02d.%03d" to be precise
	static const char* const TIME_FORMAT;

	bool m_bPaused;
	unsigned long m_ulStartTime;
	unsigned long m_ulTicksBeforeLastStop;

};

#endif	// _STOP_WATCH_H_
