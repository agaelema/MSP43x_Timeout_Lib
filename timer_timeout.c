/*******************************************************************************
 * Timer Timeout library for MSP43x V01 - timer_timeout.c
 *
 * - Use a timer and interrupt to tick a 32bit unsigned variable
 * - period selected by user, between 1us and 1ms
 * - enable to use timer interruption with less then 1MHz, very useful for
 *   small microcontrollers (tested at 100us - 10kHz)
 *
 * Author: Haroldo Luiz Moretti do Amaral - agaelema@gmail.com
 * https://www.embarcados.com.br/author/agaelema/
 * https://www.github.com/agaelema
 *
 * Based on idea presented by: Felipe de Andrade Neves Lavratti
 * - generic delay and timeout library
 * https://www.embarcados.com.br/biblioteca-de-timer-delay-timeout/
 *
 ********************************************************************************
 * Changes:
 * - Separate setup of timer in different file ("timer_timeout_setup")
 * - remove unused code
 *
 * v0.3 - 2017/08/10
 *******************************************************************************/

#include    "timer_timeout.h"


volatile static uint32_t timer_Tick_Acc = 0;
volatile static uint32_t timer_Constant_Uint = 1;
static const uint32_t timer_us_Freq = 1000000;            // freq of 1us = 1MHz



/*******************************************************************************
 * _HwTimerInit() - initialize timer HW used to tick increments
 *  NO ARGUMENTS
 *******************************************************************************/
static __inline void _HwTimerInit(void)
{
    /*
     * Setup a 32bits Timer or Ticker to increment each 1ms
     * allow it to overflow
     */
    setupTimerHW();
}


/*******************************************************************************
 * _HwTick() - return the number of ticks of timer times timer_constant
 *  NO ARGUMENT:
 *
 *      - the value return is related to time in us scale
 *******************************************************************************/
static __inline uint32_t _HwTick(void)
{
    /* return the 32bits Timer/Ticker value */
    return (uint32_t)(timer_Tick_Acc * timer_Constant_Uint);
}


/*******************************************************************************
 * setCompareValue - set the compare value of timer and some constants
 *  (uint32_t)timerFreq:    desired frequency of timer in Hz
 *  (uint32_t)timerCLK:     clock of timer in Hz
 *
 *      - calculate some constants to compensate the clock of used timer
 *      - enable to use timer clock lower than 1MHz (less overload to CPU
 *        due the accumulator inside the timer interrupt)
 *******************************************************************************/
uint32_t setCompareValue(uint32_t timerFreq, uint32_t timerCLK)
{
    setTimerCompareValue(timerCLK / timerFreq);
    timer_Constant_Uint = timer_us_Freq / timerFreq;

    return (uint32_t)getTimerCompareValue();
}


/*******************************************************************************
 * delayInit() - start the timer, called after "setCompareValue()"
 *  NO ARGUMENTS
 *******************************************************************************/
void delayInit()
{
    _HwTimerInit();
}


/*******************************************************************************
 * delayMs() - creates a delay in ms scale
 *  (uint32_t) delayInMs: time in ms
 *
 *      - this function will halt the CPU in a loop until the time be reached
 *******************************************************************************/
void delayMs(uint32_t delayInMs)
{
    uint32_t compval =  (delayInMs * 1000);
    uint32_t start = _HwTick();
    while( ( (uint32_t)_HwTick() - start ) < compval);  //This comparison tolerates overflow
}


/*******************************************************************************
 * delayUs() - creates a delay in us scale
 *  (uint32_t) delayInUs: time in us
 *
 *      - this function will halt the CPU in a loop until the time be reached
 *******************************************************************************/
void delayUs(uint32_t delayInUs)
{
    uint32_t compval = delayInUs;
    uint32_t start = _HwTick();
    while( ( (uint32_t)_HwTick() - start ) < compval);  //This comparison tolerates overflow
}


/*******************************************************************************
 * timeoutInit - return the number of ticks used in timeout routines
 *  NO ARGUMENTS
 *******************************************************************************/
uint32_t timeoutInit(void)
{
    return _HwTick();
}


/*******************************************************************************
 * timeoutCheck_us() - check if the time was reached
 *  NO ARGUMENTS
 *******************************************************************************/
//uint32_t timeoutCheck_us(uint32_t delayInUs, uint32_t seed)
uint_fast8_t timeoutCheck_us(uint32_t delayInUs, uint32_t seed)
{
    uint32_t compval = delayInUs;
    return ( !( (_HwTick() - seed) < compval) );    //This comparison tolerates overflow
}


/*******************************************************************************
 * timeoutCheck_ms() - check if the time was reached
 *  NO ARGUMENTS
 *******************************************************************************/
//uint32_t timeoutCheck_ms(uint32_t delayInMs, uint32_t seed)
uint_fast8_t timeoutCheck_ms(uint32_t delayInMs, uint32_t seed)
{
    uint32_t compval = delayInMs*1000;
    return ( !( (_HwTick() - seed) < compval) ); //This comparison tolerates overflow
}


/*******************************************************************************
 * getTime_us() - return the total time since the start point in us
 *  NO ARGUMENTS
 *******************************************************************************/
uint32_t getTime_us(void){
    return _HwTick();
}


/*******************************************************************************
 * getTime_ms() - return the total time since the start point in ms
 *  NO ARGUMENTS
 *******************************************************************************/
uint32_t getTime_ms(void){
    return (uint32_t)(_HwTick() / 1000);
}






/******************************************************************************
 * This is the TIMER1_A3 interrupt vector service routine.
 ******************************************************************************/
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER1_A0_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(TIMER1_A0_VECTOR)))
#endif
void TIMER1_A0_ISR(void)
{
    timer_Tick_Acc++;
}
