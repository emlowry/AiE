/******************************************************************************
 * File:               StopWatch.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       September 23, 2013
 * Description:        Implementation for functions of the StopWatch class.
 * Last Modified:      September 23, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#include "StopWatch.h"
#include <ctime>
#include <cstdio>	// for sprintf_s

// hours:minutes:seconds.milliseconds
const char* const StopWatch::TIME_FORMAT = "%d:%02d:%02d.%03d";

// Default constructor instantiates all members in initializer list
StopWatch::StopWatch()
	: m_bRunning( false ),
	  m_ulStartTime( clock() ),
	  m_ulTicksBeforeLastStop( 0 )
{
}

// Set elapsed time to 0 as of this call
void StopWatch::Clear()
{
	m_ulTicksBeforeLastStop = 0;
	m_ulStartTime = clock();
}

// Get the total ticks this watch has been running (excluding time paused)
unsigned long StopWatch::GetTicks() const
{
	if( !m_bRunning )
	{
		return m_ulTicksBeforeLastStop;
	}
	return clock() - m_ulStartTime + m_ulTicksBeforeLastStop;
}

// Get the total elapsed milliseconds this watch has been running
double StopWatch::GetMilliseconds() const
{
	return ( (double)GetTicks() * 1000 ) / CLOCKS_PER_SEC;
}

// Get the total elapsed seconds this watch has been running
double StopWatch::GetSeconds() const
{
	return (double)GetTicks() / CLOCKS_PER_SEC;
}

// Get the total elapsed minutes this watch has been running
double StopWatch::GetMinutes() const
{
	return (double)GetTicks() / ( CLOCKS_PER_SEC * 60 );
}

// Get the total elapsed hours this watch has been running
double StopWatch::GetHours() const
{
	return (double)GetTicks() / ( CLOCKS_PER_SEC * 3600 );
}

// Is the stopwatch currently stopped?
bool StopWatch::IsRunning() const
{
	return m_bRunning;
}

// Print the time to a buffer in hours:minutes:seconds.milliseconds format
void StopWatch::PrintTime( char* a_pcBuffer, unsigned int a_uiBufferSize ) const
{
	unsigned int uiMS =
		(unsigned int)( (unsigned long)GetMilliseconds() % 1000 );
	unsigned int uiS = (unsigned int)( (unsigned long)GetSeconds() % 60 );
	unsigned int uiM = (unsigned int)( (unsigned long)GetMinutes() % 60 );
	unsigned long ulH = (unsigned long)GetHours();
	sprintf_s( a_pcBuffer, a_uiBufferSize, TIME_FORMAT, ulH, uiM, uiS, uiMS );
}

// Unpause the stopwatch
void StopWatch::Start()
{
	if( !m_bRunning)
	{
		m_ulStartTime = clock();
		m_bRunning = true;
	}
}

// Pause the stopwatch
void StopWatch::Stop()
{
	if( m_bRunning )
	{
		m_ulTicksBeforeLastStop += clock() - m_ulStartTime;
		m_bRunning = false;
	}
}
