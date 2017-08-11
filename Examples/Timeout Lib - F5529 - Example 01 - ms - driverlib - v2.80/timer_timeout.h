/*******************************************************************************
 * Timer Timeout library for MSP43x V01 - timer_timeout.h
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

#ifndef _TIMER_TIMEOUT_H_
#define _TIMER_TIMEOUT_H_

#include    <stdint.h>
#include    <msp430.h>
#include    "driverlib.h"
#include    "timer_timeout_setup.h"

/* Set timer compare value */
uint32_t setCompareValue(uint32_t timerFreq, uint32_t timerCLK);

/* Initilize the Timer library */
void delayInit(void);

/* Delay Functions, argument in milisecs and microsecs */
void delayMs(uint32_t delayInMs);
void delayUs(uint32_t delayInUs);

/*
 * Timeout functions
 */

/* Return a Timeout seed used by the timeoutCheck functions */
uint32_t timeoutInit(void);

/* Check if timeouted a initilized seed */
//uint32_t timeoutCheck_ms(uint32_t delayInMs, uint32_t seed);
uint_fast8_t timeoutCheck_ms(uint32_t delayInMs, uint32_t seed);
//uint32_t timeoutCheck_us(uint32_t delayInUs, uint32_t seed);
uint_fast8_t timeoutCheck_us(uint32_t delayInUs, uint32_t seed);

/* Get the system time */
uint32_t getTime_ms(void);
uint32_t getTime_us(void);

#endif //_TIMER_H_
