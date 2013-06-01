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

/* ========================================================================= */
/* LOCAL DEFINES =========================================================== */
/* ========================================================================= */
#define READ_TASK_EVENT 0
#define LOG_TASK_EVENT 1
#define DELAY_50HZ 20

#define TOGGLE_PBLED(x) (devLedPORT ^= (1 << x))
#define TOGGLE_PDLED(x) (devSwitchPORT ^= (1 << x))

#define DEBUG

/* ========================================================================= */
/* GLOBAL VARIABLES ======================================================== */
/* ========================================================================= */
Tuint16 analogValue = 0x00;
Tuint16 digitalValue = 0x00;

/* ========================================================================= */
/* FUNCTION PROTOTYPES ===================================================== */
/* ========================================================================= */
static Tword GetAnalogSensorReading(void);
static Tword GetDigitalSensorReading(void); 
static void InitalizeAnalogSensor(void); 
static void InitalizeDigitalSensor(void); 

// This function runs when the OS is first initialized
void appBoot(void)
{ 
    devLedDRR    = 0xFF;
    devSwitchDRR = 0xFF;
    InitalizeAnalogSensor();
}

/* ========================================================================= */
/* HELPER FUNCTIONS ======================================================== */
/* ========================================================================= */

Tuint16 GetAnalogSensorReading( void )
{
    return ADC;
}

Tuint16 GetDigitalSensorReading( void )
{
    return 0;
}

void InitalizeAnalogSensor( void )
{
    // AREF = AVcc, Pin ADC0
    ADMUX = (1 << REFS0);
    // ADC Enable, Free-Running and prescaler of 128
    ADCSRA = (1 << ADEN) | (1 << ADPS2) |  (1 << ADPS1) | (1 << ADPS0)
    | (1 << ADATE);
    // Start Conversion
    ADCSRA |= (1 << ADSC);
}

void InitalizeDigitalSensor( void )
{
    
}

/* ========================================================================= */
/* TASKS =================================================================== */
/* ========================================================================= */
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
		taskDelayFromNow(DELAY_50HZ);
	} 
}
#endif

/*
*******************************************************************************
*                               READ TASK
*
* Description : This task is responsible for getting sensor values and calc-
                ulating the average that will be saved in memory.
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
    	//GetSensorData();
        
    	if (taskMutexRequestOnName(AnalogSample, defLockDoNotBlock))
        {
            analogValue = GetAnalogSensorReading();
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

/*
*******************************************************************************
*                               LOG TASK
*
* Description : The log task is responsible for writing the calculated sensor
                values to the EEPROM. This task is running at 10 Hz.
*
* Arguments   : none
*
* Returns     : none
*
*******************************************************************************
*/
#if (preTaskDefined(LogTask))

void appLoop_LogTask(void)
{	
	Tword analogCalc = 0x00;
	Tword digitalCalc = 0x00;
	
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
            valueOut = ~(analogCalc >> 8);
            portFSWriteByte(address++, valueOut);
            while(!portFSWriteReady());
            valueOut = ~(analogCalc);
            portFSWriteByte(address++, valueOut);
            
            taskMutexRequestOnName(DigitalSample, 1);
            digitalCalc = digitalValue;
            taskMutexReleaseOnName(DigitalSample);
            
            while(!portFSWriteReady());
            valueOut = ~(digitalCalc >> 8);
            portFSWriteByte(address++, valueOut);
            while(!portFSWriteReady());
            valueOut = ~(digitalCalc);
            portFSWriteByte(address++, valueOut);
        }
	}
}
#endif


