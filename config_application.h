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

#ifndef CONFIG_TESTHELLOWORLD_H_
#define CONFIG_TESTHELLOWORLD_H_

/* Comments are in the config default file */

/* ========================================================================= */
/* SYSTEM CONFIGURATION ==================================================== */
/* ========================================================================= */

#define  cfgSysOptimized                         cfgFalse
#define  cfgSysDebug                             cfgFalse
#define  cfgSysInline                            cfgFalse
#define  cfgSysFramePointerCounterMeasures       cfgTrue
#define  cfgSysReduceProEpilogue                 cfgBikini
#define  cfgSysRegisterCheckByte                 0xA5
#define  cfgSysStackGrowthUp                     cfgFalse
#define  cfgSysZeroPageStack                     cfgFalse
#define  cfgSysClearUnusedR1                     cfgTrue
#define  cfgSysSqueezeState                      defSysOptimized
#define  cfgSysReuseOsStack                      cfgTrue
#define  cfgSysClockDivider                      1
#define  cfgSysSubTicksPerFullTick               32
#define  cfgSysSubTickDivider                    256
#define  cfgSysGCCstartup                        cfgKeep
#define  cfgSysFsStorageSpace                    512


/* ========================================================================= */
/* INTERRUPT HANDLING ====================================================== */
/* ========================================================================= */

#define  cfgIntGlobalOnly                        cfgTrue
#define  cfgIntUserDefined                       cfgFalse
#define  cfgIntSwitchUsesOSstack                 cfgFalse
#define  cfgIntOsProtected                       cfgTrue
#define  cfgIntTickTrack                         cfgFalse
#define  cfgIntManualTicks                       cfgFalse


/* ========================================================================= */
/* QUALITY ASSURANCE ======================================================= */
/* ========================================================================= */

#define  cfgCheckSystem                          cfgTrue
#define  cfgCheckReset                           cfgTrue
#define  cfgCheckTrace                           cfgFalse
#define  cfgCheckAlwaysFatal                     cfgFalse
#define  cfgCheckWatermarks                      cfgFalse
#define  cfgCheckOsStack                         cfgTrue
#define  cfgCheckTaskStack                       cfgTrue
#define  cfgCheckIsrStack                        cfgFalse
#define  cfgCheckRegisters                       cfgTrue
#define  cfgCheckTiming                          cfgFalse
#define  cfgCheckQueuFilling                     cfgTrue
#define  cfgCheckMethodUse                       cfgFalse
#define  cfgCheckApplication                     cfgFalse


/* ========================================================================= */
/* COMMON CAPABILITIES ===================================================== */
/* ========================================================================= */

#define  cfgUseEquidistantTicks                  cfgTrue
#define  cfgUseDelay                             cfgTrue
#define  cfgUseSuspendOnDelay                    cfgFalse
#define  cfgUseSynchronization                   cfgSyncSingleSlot
#define  cfgUseHierarchicalRoundRobin            cfgFalse
#define  cfgUseNestedCriticals                   cfgFalse
#define  cfgUsePrioritizedRelease                cfgFalse
#define  cfgUsePriorityLifting                   cfgFalse
#define  cfgUseTaskWatchdog                      cfgFalse
#define  cfgUseCorrectWakeupTimes                cfgFalse
#define  cfgUseTimeout                           cfgTrue
#define  cfgUseTasknames                         cfgFalse
#define  cfgUseLowPowerSleep                     cfgFalse
#define  cfgUseLowPowerOnDelay                   cfgFalse
#define  cfgUseLowPowerDelayRelease              cfgFalse
#define  cfgUseLoadMonitor                       cfgFalse
#define  cfgUseFileSystem                        cfgTrue
#define  cfgUseFileSystemConcurrentRead          cfgTrue
#define  cfgUseFileSystemEconomyMode             cfgFalse
#define  cfgUseFileSystemMaintainFAT             cfgFalse
#define  cfgUseEvents                            cfgTrue
#define  cfgUseEventsOnVariables                 cfgFalse


/* ========================================================================= */
/* CODE PARAMETERS ========================================================= */
/* ========================================================================= */

#define  cfgNumWatchdogDiv                       0
#define  cfgNumMonitorDiv                        0
#define  cfgNumSleepPeriod                       0
#define  cfgNumSleepThreshold                    0
#define  cfgNumGlobWidth                         0
#define  cfgNumSwitchWidth                       0
#define  cfgNumTickWidth                         0


/* ========================================================================= */
/* EXTERNAL CALLS ========================================================== */
/* ========================================================================= */

#define  callAppTick00                           cfgFalse
#define  callAppTick08                           cfgFalse
#define  callAppTick16                           cfgFalse
#define  callAppTickSleep                        cfgFalse
#define  callAppEnterIdle                        cfgFalse
#define  callAppEnterSleep                       cfgFalse
#define  callAppExitSleep                        cfgFalse
#define  callAppBoot                             cfgTrue
#define  callAppInit                             cfgFalse
#define  callAppBark                             cfgFalse


/* ========================================================================= */
/* API INCLUSIONS ========================================================== */
/* ========================================================================= */

/* Standard functions ------------------------------------------------------ */
#define  includeTaskYield                        cfgFalse
#define  includeTaskDelayFromNow                 cfgTrue
#define  includeTaskDelayFromWake                cfgFalse
#define  includeGenSuspend                       cfgFalse
#define  includeTaskSuspend                      cfgFalse
#define  includeGenResume                        cfgFalse
#define  includeTaskSleep                        cfgFalse
#define  includeTaskSleepAll                     cfgFalse
#define  includeGenSetPriority                   cfgFalse
#define  includeGenGetPriority                   cfgFalse
#define  includeGenGetTickCount                  cfgFalse
#define  includeGenAddtoTickCount                cfgFalse
#define  includeGenGetLastWakeTime               cfgFalse
#define  includeTaskFeedWatchdog                 cfgFalse
#define  includeTaskKillWatchdog                 cfgFalse
#define  includeGenGetTaskname                   cfgFalse
#define  includeTaskTerminate                    cfgFalse
#define  includeGenReboot                        cfgFalse
#define  includeTaskRecreate                     cfgFalse
#define  includeTaskRestart                      cfgFalse
#define  includeGenLogTask                       cfgFalse
#define  includeGenLogOs                         cfgFalse
#define  includeGenTrace                         cfgFalse
#define  includeGenPipeInt16                     cfgFalse
#define  includeGenPassFlashString               cfgFalse

/* Event functions --------------------------------------------------------- */
#define  includeTaskWaitForEvents                cfgTrue
#define  includeIsrFireEvent                     cfgFalse
#define  includeGenFireEvent                     cfgTrue
#define  includeGenFireEventSet                  cfgFalse
#define  includeGenCountEventBlocks              cfgTrue

/* Synchronization functions ----------------------------------------------- */
#define  includeTaskWaitForTasks                 cfgTrue
#define  includeGenWaitRelease                   cfgFalse
#define  includeTaskMutex                        cfgFalse
#define  includeTaskQueu                         cfgTrue

/* Queu functions --------------------------------------------------------- */
#define  includeGenQueuWrite                     cfgTrue
#define  includeGenQueuRead                      cfgTrue
#define  includeGenQueuUnwrite                   cfgFalse
#define  includeGenQueuUnread                    cfgFalse
#define  includeGenQueuClear                     cfgTrue
#define  includeGenQueuPeek                      cfgFalse
#define  includeGenQueuReadable                  cfgFalse
#define  includeGenQueuWriteable                 cfgFalse
#define  includeGenQueuFull                      cfgFalse
#define  includeGenQueuEmpty                     cfgFalse

/* File System functions --------------------------------------------------- */
#define  includeTaskFileAccess                   cfgTrue
#define  includeTaskFileFormat                   cfgTrue
#define  includeTaskFileGetSize                  cfgFalse
#define  includeTaskFileSetSize                  cfgTrue
#define  includeTaskFileReadByte                 cfgTrue
#define  includeTaskFileWriteByte                cfgTrue
#define  includeTaskFileAppendByte               cfgTrue
#define  includeTaskFileReadPipe                 cfgFalse
#define  includeTaskFileWritePipe                cfgFalse
#define  includeTaskFileReadBuffer               cfgTrue
#define  includeTaskFileWriteBuffer              cfgTrue

/* Protection functions ---------------------------------------------------- */
#define  includeTaskProtectGlobalInterrupts      cfgFalse
#define  includeTaskProtectSwitchTasks           cfgFalse
#define  includeTaskProtectTickInterrupts        cfgFalse
#define  includeTaskProtectGlobalCritical        cfgFalse
#define  includeTaskProtectSwitchCritical        cfgTrue
#define  includeTaskProtectTickCritical          cfgFalse

/* ISR header/footer functions --------------------------------------------- */
#define  includeIsrEnter                         cfgFalse
#define  includeIsrExit                          cfgFalse
#define  includeIsrBegin                         cfgFalse
#define  includeIsrEndReturn                     cfgFalse
#define  includeIsrEndYield                      cfgFalse
#define  includeIsrStartLoad                     cfgFalse
#define  includeIsrStopLoad                      cfgFalse

/* Quality assurance functions --------------------------------------------- */
#define  includeTaskStackCheck                   cfgFalse
#define  includeIsrStackCheck                    cfgFalse


/* ========================================================================= */
/* TASK NAMES ============================================================== */
/* ========================================================================= */

#define  CN_00									 TimerTask
#define  CN_01									 ReadTask
#define  CN_02									 LogTask

/* ========================================================================= */
/* INCLUDE TASKS =========================================================== */
/* ========================================================================= */

#define  TaskInclude_TimerTask                   cfgStartRunning
#define  TaskInclude_ReadTask                    cfgStartRunning
#define  TaskInclude_LogTask                     cfgStartRunning

/* ========================================================================= */
/* TASK CAPABILITIES ======================================================= */
/* ========================================================================= */

#define  CapabilitiesOverride                    cfgCapAll


/* ========================================================================= */
/* STACK SIZES ============================================================= */
/* ========================================================================= */

#define  StackSafety                             4
#define  StackSizeOS                             24
#define  StackSizeISR                            0
#define  StackSizeShared                         0
#define  StackSizeOverride                       256


/* ========================================================================= */
/* TIMES SLICES ============================================================ */
/* ========================================================================= */

#define  TimeSliceIdleTime                       cfgSysSubTicksPerFullTick


/* ========================================================================= */
/* RUNTIME TASK NAMES ====================================================== */
/* ========================================================================= */


/* ========================================================================= */
/* TASK PRIORITIES ========================================================= */
/* ========================================================================= */

#define  PriorityOverride                        0

/* ========================================================================= */
/* REGISTER USE ============================================================ */
/* ========================================================================= */

#define  RegisterUse_TimerTask                   registersAll
#define  RegisterUse_ReadTask                    registersAll
#define  RegisterUse_LogTask                     registersAll


/* ========================================================================= */
/* REGISTER CHECK ========================================================== */
/* ========================================================================= */

#define  RegisterCheckOverride                   registersAll


/* ========================================================================= */
/* INTERRUPT SETTING ======================================================= */
/* ========================================================================= */

#define  InterruptStartOverride                  cfgGlobSet | cfgTickSet


/* ========================================================================= */
/* EVENT NAMES ============================================================= */
/* ========================================================================= */

#define  EN_00                                   Read
#define  EN_01                                   Log


/* ========================================================================= */
/* SLOT NAMES ============================================================== */
/* ========================================================================= */

#define  SN_01                                   AnalogSample
#define  SN_02                                   DigitalSample
#define  SN_03                                   AnalogAverage
#define  SN_04                                   DigitalAverage
#define  SN_05                                   AnalogSampleSync
#define  SN_06                                   ThePipe


/* ========================================================================= */
/* SLOT SIZES ============================================================== */
/* ========================================================================= */

#define  SlotSize_TimerTask                    0
#define  SlotSize_ReadTask                     1
#define  SlotSize_CalcTask                     1
#define  SlotSize_ReadAndLogTask               1
#define  SlotSize_CalcAndLogTask               1
#define  SlotSize_LogTask                      1
#define  SlotSize_Display                      1
#define  SlotSize_Speed                        1
#define  SlotSize_Sampler                      1


/* ========================================================================= */
/* SLOT USAGE ============================================================== */
/* ========================================================================= */

#define  SlotUse_AnalogSample                   cfgUseAsMutex
#define  SlotUse_DigitalSample                  cfgUseAsMutex
#define  SlotUse_AnalogAverage                  cfgUseAsQueu
#define  SlotUse_DigitalAverage                 cfgUseAsQueu
#define  SlotUse_AnalogSampleSync               cfgUseAsWait
#define  SlotUse_ThePipe                        cfgUseAsQueu


/* ========================================================================= */
/* QUEU SIZES ============================================================== */
/* ========================================================================= */

#define  QueuSize_AnalogSample                      1
#define  QueuSize_DigitalSample                     1
#define  QueuSize_AnalogAverage                     1
#define  QueuSize_DigitalAverage                    1
#define  QueuSize_ThePipe                           2


/* ========================================================================= */
/* FILE NAMES ============================================================== */
/* ========================================================================= */


/* ========================================================================= */
/* FILE SIZES ============================================================== */
/* ========================================================================= */

#define  FileSpaceStandard                       0

/* ========================================================================= */
/* LOCAL DEFINES =========================================================== */
/* ========================================================================= */
#define READ_TASK_EVENT 0
#define LOG_TASK_EVENT 1
#define DELAY_50HZ 20
#define MEMORY_MAX 1024

#define TOGGLE_PBLED(x) (devLedPORT ^= (1 << x))
#define TOGGLE_PDLED(x) (devSwitchPORT ^= (1 << x))
#define TOGGLE_ERRORLED (devSwitchPORT ^= (1 << PB6))

#define DEBUG

#define SENSOR_ADDR 0x3C //0x1E
#define X_MSB 0
#define X_LSB 1
#define Z_MSB 2
#define Z_LSB 3
#define Y_MSB 4
#define Y_LSB 5
#define SENSOR_RBYTES 6
#define SENSOR_MODE_REG 0x02
#define SENSOR_RUN_MODE 0x00
#define SENSOR_REG 0x03

#define HEADER_LEN 8
#define HEADER1 0x10
#define HEADER2 0x14
#define HEADER3 0x79
#define HEADER4 0x32
#define HEADER5 0x0A
#define HEADER6 0xFF
#define HEADER7 0x00
#define HEADER8 0x00

#define SAMPLE_SIZE 10
#define SMA_MULTIPLIER 3277
#define SMA_SHIFT 15
#define CMA_DIVISOR 32767
#define CMA_SHIFT 15
#define EMA_MULTIPLIER 1
#define EMA_SHIFT 1
#define WMA_MULTIPLIER 596
#define WMA_SHIFT 15
#define MMA_SHIFT 1

#define SMA_ALG 0
#define CMA_ALG 1
#define EMA_ALG 2
#define WMA_ALG 3
#define MMA_ALG 4

#ifndef __ASSEMBLER__
typedef struct
{
    Tuint16 ring_buf[SAMPLE_SIZE];
    Tuint16 sort_buf[SAMPLE_SIZE];
    Tuint16 next_input;	// 16-bit
    Tword next_avg;      // 32-bit
    uint32_t next_sum;
    Tuint16 oldest_input;
    Tuint16 buf_ptr;
    Tword prev_avg;
    Tuint16 sample_count;
} ProcessDataStruct;
#endif 

#endif /*CONFIG_TESTHELLOWORLD_H_*/
