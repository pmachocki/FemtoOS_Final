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

// This function runs when the OS is first initialized
void appBoot(void)
{ 
    devLedDRR    = 0xFF;
    //devSwitchDRR = 0xFF;
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
	Tuint08 currMode = 0;
	
	while (true)
	{
        tenHz++;
        currMode = READ_TASK_EVENT;

        if (tenHz % 5 == 0)
        {
            currMode = LOG_TASK_EVENT;
        }

        //genFireEvent(currMode);
        
#ifdef DEBUG
        TOGGLE_PBLED(PB0);
#endif //DEBUG
        if (currMode)
        {
#ifdef DEBUG
            TOGGLE_PBLED(PB1);
#endif //DEBUG
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
/*
#if (preTaskDefined(ReadTask))

void appLoop_ReadTask(void)
{
	Tuint08 analogValue = 0x00;
	Tuint08 digitalValue = 0x00;
	Tuint08 success = 0x00;
		
	while (true)
	{
    	taskWaitForEvent(READ_TASK_EVENT);
#ifdef DEBUG
    	TOGGLE_PBLED(PD2);
#endif //DEBUG

    	//Get actual values here.
    	//GetSensorData(); // Writes to sensor data queue
    	
    	taskQueuWriteRequestOnName(AnalogSample, 1);
    	genQueuClearOnName(AnalogSample);
    	genQueuWriteOnName(AnalogSample, analogValue++);
    	taskQueuReleaseOnName(AnalogSample);

    	taskQueuWriteRequestOnName(DigitalSample, 1);
    	genQueuClearOnName(DigitalSample);
    	genQueuWriteOnName(DigitalSample, digitalValue++);
    	taskQueuReleaseOnName(DigitalSample);

    	//genFireEvent(LOG_TASK_EVENT);
	}
}

#endif
*/
/*

#if (preTaskDefined(CalcTask))

void appLoop_CalcTask(void)
{	
	Tuint08 analogValue = 0x00;
	Tuint08 digitalValue = 0x00;
	Tuint08 analogCalc = 0x00;
	Tuint08 digitalCalc = 0x00;
	
	while (true)
	{
		taskWaitForEvent(CALC_TASK_EVENT, 0xFFFF);
		
		if (taskQueuReadRequestOnName(AnalogSample, 1, 0xFFFF))
		{
			analogValue = genQueuReadOnName(AnalogSample);
			taskDelayFromNow(2000); //Why are we delaying here? All these can be removed
			taskQueuReleaseOnName(AnalogSample);
		}
		
		if (taskQueuReadRequestOnName(DigitalSample, 1, 0xFFFF))
		{
			digitalValue = genQueuReadOnName(DigitalSample);
			taskDelayFromNow(2000); //Why are we delaying here? All these can be removed
			taskQueuReleaseOnName(DigitalSample);
		}
		
		//Calc(); // Reads from sensor data queue, writes to averaging queue
		analogCalc = analogValue;
		digitalCalc = digitalValue;
		
		if (taskQueuWriteRequestOnName(AnalogAverage, 1, 0xFFFF))
		{
			genQueuWriteOnName(AnalogAverage, analogCalc);
			taskDelayFromNow(2000); //Why are we delaying here? All these can be removed
			taskQueuReleaseOnName(AnalogAverage);
		}
		
		if (taskQueuWriteRequestOnName(DigitalAverage, 1, 0xFFFF))
		{
			genQueuWriteOnName(DigitalAverage, digitalCalc);
			taskDelayFromNow(2000); //Why are we delaying here? All these can be removed
			taskQueuReleaseOnName(DigitalAverage);
		}
	}
}
#endif

// This function looks pretty similar to the ReadTask. 
// Is there a difference between these two tasks?
// The difference is that ultimately this line of logic will call Log whereas the logic starting with ReadTask calls the CalcTask and then stops there
// There are two lines of logic that you can follow by looking what tasks fire events and which task wait for those events. Events are not working and thats what I was hoping you could look at.
#if (preTaskDefined(ReadAndLogTask))

void appLoop_ReadAndLogTask(void)
{
	Tuint08 analogValue = 0x00;
	Tuint08 digitalValue = 0x00;
	Tuint08 success = 0x00;
	
	while (true)
	{
		taskWaitForEvent(READ_AND_LOG_TASK_EVENT, 0xFFFF);
		//GetSensorData(); // Writes to sensor data queue
		
		success = 0x00;
		while(!success) 
        {
			if (taskQueuWriteRequestOnName(AnalogSample, 1, defLockBlockInfinite))
			{
				genQueuClearOnName(AnalogSample);
				taskDelayFromNow(100);  //Why are we delaying here? All these can be removed
				genQueuWriteOnName(AnalogSample, 0x01);
				taskDelayFromNow(100);  //Why are we delaying here? All these can be removed
				taskQueuReleaseOnName(AnalogSample);
				success = 0x01;
			}
		}		
		
		if (taskQueuWriteRequestOnName(DigitalSample, 1, 0xFFFF))
		{
			genQueuWriteOnName(DigitalSample, digitalValue++);
			taskDelayFromNow(100);  //Why are we delaying here? All these can be removed
			taskQueuReleaseOnName(DigitalSample);
		}
		
		genFireEvent(CALC_AND_LOG_TASK_EVENT);
	}
}
#endif


#if (preTaskDefined(CalcAndLogTask))

void appLoop_CalcAndLogTask(void)
{
	Tuint08 analogValue = 0x00;
	Tuint08 digitalValue = 0x00;
	Tuint08 analogCalc = 0x00;
	Tuint08 digitalCalc = 0x00;
	Tuint08 success = 0x00;
	
	Taddress address = 256;
	Tbyte valueOut;
	
	while (true)
	{
		if (taskWaitForEvent(CALC_AND_LOG_TASK_EVENT, 0xFFFF)) 
        {
		    success = 0x00;
			while(!success) 
            {
				if (taskQueuReadRequestOnName(AnalogSample, 1, defLockBlockInfinite))
				{
					genQueuClearOnName(AnalogSample);
					taskDelayFromNow(100); //Why are we delaying here? All these can be removed
					analogValue = genQueuReadOnName(AnalogSample);
					taskDelayFromNow(100); //Why are we delaying here? All these can be removed
					taskQueuReleaseOnName(AnalogSample);
			
					while(!portFSWriteReady());
					valueOut = ~analogValue;
					portFSWriteByte(address++, valueOut);
				
					success = 0x01;
				}
			}		
		
			if (taskQueuReadRequestOnName(DigitalSample, 1, 0xFFFF))
			{
				digitalValue = genQueuReadOnName(DigitalSample);
				taskDelayFromNow(100);  //Why are we delaying here? All these can be removed
				taskQueuReleaseOnName(DigitalSample);
			}
		
			//Calc(); // Reads from sensor data queue, writes to averaging queue
			analogCalc = analogValue;
			digitalCalc = digitalValue;
		
			if (taskQueuWriteRequestOnName(AnalogAverage, 1, 0xFFFF))
			{
				genQueuWriteOnName(AnalogAverage, analogCalc);
				taskDelayFromNow(100); //Why are we delaying here? All these can be removed
				taskQueuReleaseOnName(AnalogAverage);
			}
		
			if (taskQueuWriteRequestOnName(DigitalAverage, 1, 0xFFFF))
			{
				genQueuWriteOnName(DigitalAverage, digitalCalc);
				taskDelayFromNow(100); //Why are we delaying here? All these can be removed
				taskQueuReleaseOnName(DigitalAverage);
			}
		
			genFireEvent(LOG_TASK_EVENT);
		}		
	}
}

#endif
*/
/*
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

	Tuint08 count = 0;
	Tuint08 uiCharCount;
	Tchar cChar;
	
	while (true)
	{
        while(address <= 1024)
        {
		    taskWaitForEvent(LOG_TASK_EVENT);
            TOGGLE_PBLED(PB2);
        
		    //Calc(); // Reads from averaging queue, writes to EEPROM
		
            taskQueuReadRequestOnName(AnalogSample, 1);
            analogCalc = genQueuReadOnName(AnalogSample);
            taskQueuReleaseOnName(AnalogSample);
        
            while(!portFSWriteReady());
            valueOut = ~analogCalc;
            portFSWriteByte(address++, valueOut);
        
            taskQueuReadRequestOnName(DigitalSample, 1);
            digitalCalc = genQueuReadOnName(DigitalSample);
            taskQueuReleaseOnName(DigitalSample);
        
            while(!portFSWriteReady());
            valueOut = ~digitalCalc;
            portFSWriteByte(address++, valueOut);
        }        
	}
}
#endif
*/