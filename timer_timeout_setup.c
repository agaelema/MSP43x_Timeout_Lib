/*******************************************************************************
 * Timer Timeout library for MSP43x V01 - timer_timeout_setup.h
 *
 * Part of Timer Timeout library for MSP43x
 * - Separate file with timer configurations and Tick variable
 *
 * Author: Haroldo Luiz Moretti do Amaral - agaelema@gmail.com
 * https://www.embarcados.com.br/author/agaelema/
 * https://www.github.com/agaelema
 *
 ********************************************************************************
 * Changes:
 * - remove unused code
 *
 * v0.3 - 2017/08/10
 *******************************************************************************/

#include    "timer_timeout_setup.h"


/*******************************************************************************
 * Compare value used in timer HW to generate ticks
 * - static variable
 * - use functions to set and get value
 *******************************************************************************/
volatile static uint32_t timer_CompareValue = 0;

/* set the value of static variable */
void setTimerCompareValue(uint32_t compValue)
{
    timer_CompareValue = compValue;
}

/* get the value of static variable */
uint32_t getTimerCompareValue(void)
{
    return timer_CompareValue;
}


/*******************************************************************************
 * Setup timer used to tick count
 * - configured with Timer_A1 - cc0
 *******************************************************************************/
void setupTimerHW(void)
{
    /* Start timer in UP mode sourced by SMCLK */
    Timer_A_initUpModeParam TA_initUpParam = {0};
    TA_initUpParam.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
    TA_initUpParam.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    TA_initUpParam.timerPeriod = timer_CompareValue;
    TA_initUpParam.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;
    TA_initUpParam.captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE;
    TA_initUpParam.timerClear = TIMER_A_DO_CLEAR;
    TA_initUpParam.startTimer = false;

    Timer_A_initUpMode(TIMER_A1_BASE, &TA_initUpParam);

    /* Initiaze compare mode */
    Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE,
                                         TIMER_A_CAPTURECOMPARE_REGISTER_0
                                         );

    Timer_A_initCompareModeParam TA_initCompParam = {0};
    TA_initCompParam.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_0;
    TA_initCompParam.compareInterruptEnable = TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE;
    TA_initCompParam.compareOutputMode = TIMER_A_OUTPUTMODE_OUTBITVALUE;
    TA_initCompParam.compareValue = timer_CompareValue;
    Timer_A_initCompareMode(TIMER_A1_BASE, &TA_initCompParam);

    Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_UP_MODE);
}
