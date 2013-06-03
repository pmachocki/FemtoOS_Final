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
#include "i2cmaster.h"


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
static void WriteMemoryHeader();
static void increment_ptr(Tuint16 *ptr);
static void sma_calc(ProcessDataStruct *dataIn, const Tuint16 newValue);

/**
 * This function runs when the OS is first initialized
 */
void appBoot(void)
{ 
    devLedDRR    = 0xFF;
    devSwitchDRR = 0xFF;
    InitalizeAnalogSensor();
    InitalizeDigitalSensor();
}

/* ========================================================================= */
/* HELPER FUNCTIONS ======================================================== */
/* ========================================================================= */

/**
 * This function returns the ADC value of the accelerometer.
 */
Tword GetAnalogSensorReading( void )
{
    return ADC;
}

/**
 * This function returns the value of one axis of the magnetometer.
 */
Tword GetDigitalSensorReading( void )
{
    uint8_t temp[SENSOR_RBYTES];
    
    if (i2c_start(SENSOR_ADDR + I2C_WRITE))
        TOGGLE_ERRORLED;
    i2c_write(SENSOR_REG);
    i2c_stop();

    if (i2c_start(SENSOR_ADDR + I2C_READ))
        TOGGLE_ERRORLED;
    temp[X_MSB] = i2c_readAck();
    temp[X_LSB] = i2c_readAck();
    temp[Z_MSB] = i2c_readAck();
    temp[Z_LSB] = i2c_readAck();
    temp[Y_MSB] = i2c_readAck();
    temp[Y_LSB] = i2c_readNak();
    i2c_stop();
    
    return temp[Y_MSB] << 8 | temp[Y_LSB];
}

/**
 * This function initializes our uC for the ADC used to read our accelerometer.
 */
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

/**
 * This function initializes our i2c magnetometer.
 */
void InitalizeDigitalSensor( void )
{
    if (i2c_start(SENSOR_ADDR + I2C_WRITE))
        TOGGLE_ERRORLED;
    i2c_write(SENSOR_MODE_REG);            // Select Mode Register
    i2c_write(SENSOR_RUN_MODE);            // Continuous Measurement Mode
    i2c_stop();
}

/**
 * This writes the header to the EEPROM
 */
void WriteMemoryHeader()
{
    Taddress address = 0;
    Tchar header[HEADER_LEN] = {HEADER1, HEADER2, HEADER3, HEADER4, HEADER5, 
                                HEADER6, HEADER7, HEADER8};
                                
    while(!portFSWriteReady());
    portFSWriteByte(address++, ~(header[0]));
    while(!portFSWriteReady());
    portFSWriteByte(address++, ~(header[1]));
    while(!portFSWriteReady());
    portFSWriteByte(address++, ~(header[2]));
    while(!portFSWriteReady());
    portFSWriteByte(address++, ~(header[3]));
    while(!portFSWriteReady());
    portFSWriteByte(address++, ~(header[4]));
    while(!portFSWriteReady());
    portFSWriteByte(address++, ~(header[5]));
    while(!portFSWriteReady());
    portFSWriteByte(address++, ~(header[6]));
    while(!portFSWriteReady());
    portFSWriteByte(address++, ~(header[7]));
}

static void increment_ptr(Tuint16 *ptr)
{
    if (*ptr < SAMPLE_SIZE - 1)
    (*ptr)++;
    else
    *ptr = 0;
}

static void sma_calc(ProcessDataStruct *dataIn, const Tuint16 newValue) {

    dataIn->next_input = newValue;
    dataIn->oldest_input = dataIn->ring_buf[dataIn->buf_ptr];
    dataIn->ring_buf[dataIn->buf_ptr] = dataIn->next_input;
    
    // Calculate Sum
    dataIn->next_sum = dataIn->next_sum + dataIn->ring_buf[dataIn->buf_ptr]
    - dataIn->oldest_input;
    // Get Average
    dataIn->next_avg = (dataIn->next_sum * SMA_MULTIPLIER) >> SMA_SHIFT;
    
    increment_ptr(&dataIn->buf_ptr);
}

/* ========================================================================= */
/* TASKS =================================================================== */
/* ========================================================================= */
/**
 * This is the main timing task. We are running at 50 Hz and triggering a 
 * sensor read event at 50 Hz, while triggering a write event at 10 Hz.
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
        
        if (tenHz == 250)
            tenHz = 0;
               
		taskDelayFromNow(DELAY_50HZ);
	} 
}
#endif

/**
 * This task is responsible for getting sensor values and calculating the 
 * average that will be saved in memory.
 */
#if (preTaskDefined(ReadTask))

void appLoop_ReadTask(void)
{
	while (true)
	{
    	taskWaitForEvent(READ_TASK_EVENT, 0xff);
        {
#ifdef DEBUG
           TOGGLE_PDLED(PD7);
#endif //DEBUG
           
           if (taskMutexRequestOnName(AnalogSample, defLockDoNotBlock))
           {
               analogValue = GetAnalogSensorReading();
               taskMutexReleaseOnName(AnalogSample);
           }
           
           if (taskMutexRequestOnName(DigitalSample, defLockDoNotBlock))
           {
               digitalValue = GetDigitalSensorReading();
               taskMutexReleaseOnName(DigitalSample);
           }
#ifdef DEBUG
           TOGGLE_PDLED(PD7);
#endif //DEBUG 
        }
   
	}
}
#endif

/**
 * The log task is responsible for writing the calculated sensor values to the 
 * EEPROM. This task is running at 10 Hz.
 */
#if (preTaskDefined(LogTask))

void appLoop_LogTask(void)
{	
	Tword analogCalc = 0x00;
	Tword digitalCalc = 0x00;
	
	Taddress address = (Taddress) HEADER_LEN;
	Tbyte valueOut;

    static ProcessDataStruct analogProcessData;
    static ProcessDataStruct digitalProcessData;
    
    WriteMemoryHeader();
        
	while (true)
	{
        while(address < (Taddress) MEMORY_MAX)
        {
            if (taskWaitForEvent(LOG_TASK_EVENT, 800))
            {
#ifdef DEBUG
                TOGGLE_PBLED(PB2);
#endif //DEBUG
                taskMutexRequestOnName(AnalogSample, 1);
                analogCalc = analogValue;
                taskMutexReleaseOnName(AnalogSample);
                
                taskMutexRequestOnName(DigitalSample, 1);
                digitalCalc = digitalValue;
                taskMutexReleaseOnName(DigitalSample);
                
                sma_calc(&analogProcessData, analogCalc);
                sma_calc(&digitalProcessData, digitalCalc);
                
                analogCalc = analogProcessData.next_avg;
                digitalCalc = digitalProcessData.next_avg;

                valueOut = ~(analogCalc >> 8);
                while(!portFSWriteReady());
                portFSWriteByte(address++, valueOut);
                
                valueOut = ~(analogCalc);
                while(!portFSWriteReady());
                portFSWriteByte(address++, valueOut);
                
                valueOut = ~(digitalCalc >> 8);
                while(!portFSWriteReady());
                portFSWriteByte(address++, valueOut);
                
                valueOut = ~(digitalCalc);
                while(!portFSWriteReady());
                portFSWriteByte(address++, valueOut);
                
#ifdef DEBUG
                TOGGLE_PBLED(PB2);
#endif //DEBUG
            }
        }
	}
}
#endif


