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
	: m_bPaused( true ),
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
unsigned long StopWatch::GetTicks()
{
	if( m_bPaused )
	{
		return m_ulTicksBeforeLastStop;
	}
	
	return clock() - m_ulStartTime + m_ulTicksBeforeLastStop;
}

// Get the total elapsed milliseconds this watch has been running
double StopWatch::GetMilliseconds()
{
	return (double)GetTicks() / CLOCKS_PER_SEC;
}

// Get the total elapsed seconds this watch has been running
double StopWatch::GetSeconds()
{
	return (double)GetTicks() / (CLOCKS_PER_SEC * 1000);
}

// Get the total elapsed minutes this watch has been running
double StopWatch::GetMinutes()
{
	return (double)GetTicks() / (CLOCKS_PER_SEC * 60000);
}

// Get the total elapsed hours this watch has been running
double StopWatch::GetHours()
{
	return (double)GetTicks() / (CLOCKS_PER_SEC * 3600000);
}

// Print the time to a buffer in hours:minutes:seconds.milliseconds format
void StopWatch::PrintTime( char* a_pcBuffer, unsigned int a_uiBufferSize
{
	unsigned int uiMS =
		(unsigned int)( (unsigned long)GetMilliseconds() % 1000 );
	unsigned int uiS = (unsigned int)( (unsigned long)GetSeconds() % 60 );
	unsigned int uiM = (unsigned int)( (unsigned long)GetMinutes() % 60 );
	unsigned long ulH = (unsigned long)GetHours();
	sprintf_s( a_pcBuffer, a_uiBufferSize, TIME_FORMAT, ulH, uiM, uiS, uiMS);
}

// Unpause the stopwatch
void StopWatch::Start()
{
	if( m_bPaused)
	{
		m_ulStartTime = clock();
	}
	m_bPaused = false;
}

// Pause the stopwatch
void StopWatch::Stop()
{
	if( !m_bPaused )
	{
		m_ulTicksBeforeLastStop += clock() - m_ulStartTime;
	}
	m_bPaused = true;
}
