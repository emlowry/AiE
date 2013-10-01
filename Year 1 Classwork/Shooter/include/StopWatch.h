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
	unsigned long GetTicks() const;
	double GetMilliseconds() const;	// total elapsed milliseconds
	double GetSeconds() const;		// total elapsed seconds
	double GetMinutes() const;		// total elapsed minutes
	double GetHours() const;		// total elapsed hours
	bool IsRunning() const;
	void Print( char* a_pcBuffer, unsigned int a_uiBufferSize) const;
	static void Print( char* a_pcBuffer,
					   unsigned int a_uiBufferSize,
					   unsigned long a_ulTicks );
	void Start();
	void Stop();

private:

	// Time: hours:minutes:seconds.milliseconds, or "Time: %d:%02d:%02d.%03d"
	static const char* const TIME_FORMAT;

	bool m_bRunning;
	unsigned long m_ulStartTime;
	unsigned long m_ulTicksBeforeLastStop;

};

#endif	// _STOP_WATCH_H_
