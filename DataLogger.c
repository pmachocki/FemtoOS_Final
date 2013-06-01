/*
 * Femto OS v 0.92 - Copyright (C) 2008-2010 Ruud Vlaming
 *
 * This file is part of the Femto OS distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Please note that, due to the GPLv3 license, for application of this
 * work and/or combined work in embedded systems special obligations apply.
 * If these are not to you liking, please know the Femto OS is dual
 * licensed. A commercial license and support are available.
 * See http://www.femtoos.org/ for details.
 */

/**
 * This file is solely for demonstration purposes.
 *
 * The Hello World example is made to get you started and this is the file
 * you want to play with. Do not use other examples to that end, that will
 * be a disappointing experience (or a steep learning curve)
 *
 * Explanation on the website, point your browser at:
 * http://www.femtoos.org/code_start.html
 */

/* This this the only include needed in your code .*/
#include "femtoos_code.h"

#define READ_TASK_EVENT 0
#define CALC_TASK_EVENT 1
#define READ_AND_LOG_TASK_EVENT 2
#define CALC_AND_LOG_TASK_EVENT 3
#define LOG_TASK_EVENT 1
#define TIMER_50HZ 20000

#define TOGGLE_PBLED(x) (devLedPORT ^= (1 << x))
#define TOGGLE_PDLED(x) (devSwitchPORT ^= (1 << x))

#define DEBUG

Tuint08 analogValue = 0x00;
Tuint08 digitalValue = 0x00;

    
// This function runs when the OS is first initialized
void appBoot(void)
{ 
    devLedDRR    = 0xFF;
    devSwitchDRR = 0xFF;
}

/*
*******************************************************************************
*                               TIMER TASK
*
* Description : This is the main timing task. We are running at 50 Hz and
                triggering a sensor read event at 50 Hz, while triggering a 
                write event at 10 Hz. 
*
* Arguments   : none
*
* Returns     : none
*
*******************************************************************************
*/
#if (preTaskDefined(TimerTask))

void appLoop_TimerTask(void)
{
	Tuint08 tenHz = 0;
	
	while (true)
	{
        tenHz++;
        genFireEvent(READ_TASK_EVENT);
#ifdef DEBUG
        TOGGLE_PBLED(PB0);
#endif //DEBUG
        
        if (tenHz % 5 == 0)
        {
#ifdef DEBUG
           TOGGLE_PBLED(PB1);
#endif //DEBUG 
            genFireEvent(LOG_TASK_EVENT);
        }
		taskDelayFromNow(20);
	} 
}
#endif


/*
*******************************************************************************
*                               READ TASK
*
* Description : This is the main timing task. We are running at 50 Hz and
                triggering a sensor read event at 50 Hz, while triggering a 
                write event at 10 Hz. 
*
* Arguments   : none
*
* Returns     : none
*
*******************************************************************************
*/
#if (preTaskDefined(ReadTask))

void appLoop_ReadTask(void)
{
	while (true)
	{
    	taskWaitForEvent(READ_TASK_EVENT, 0xff);
#ifdef DEBUG
    	TOGGLE_PDLED(PD7);
#endif //DEBUG
       
    	//Get actual values here.
    	//GetSensorData(); // Writes to sensor data queue
        
    	if (taskMutexRequestOnName(AnalogSample, defLockDoNotBlock))
        {
            analogValue++;
            taskMutexReleaseOnName(AnalogSample);
        }    
        
        if (taskMutexRequestOnName(DigitalSample, defLockDoNotBlock))
        {
            digitalValue = 0;
            taskMutexReleaseOnName(DigitalSample);
        }        
	}
}

#endif

// The logging does appear to be happening here, as it seems to be done in the 
// task above, calc_and_log. Is this because we are still experimenting?
// Yes I moved the logging up in order to test queues and events using only two tasks. Once the events are fixed we can move it back down here.
#if (preTaskDefined(LogTask))

void appLoop_LogTask(void)
{	
	Tuint08 analogCalc = 0x00;
	Tuint08 digitalCalc = 0x00;
	
	Taddress address = 512;
	Tbyte valueOut;
	
	while (true)
	{
        while(address <= 1024)
        {
		    taskWaitForEvent(LOG_TASK_EVENT, 800);
            TOGGLE_PBLED(PB2);
        
            taskMutexRequestOnName(AnalogSample, 1);
            analogCalc = analogValue;
            taskMutexReleaseOnName(AnalogSample);
            
            while(!portFSWriteReady());
            valueOut = ~analogCalc;
            portFSWriteByte(address++, valueOut);
        
            taskMutexRequestOnName(DigitalSample, 1);
            digitalCalc = digitalValue;
            taskMutexReleaseOnName(DigitalSample);
            
            while(!portFSWriteReady());
            valueOut = ~digitalCalc;
            portFSWriteByte(address++, valueOut);
        }        
	}
}
#endif
