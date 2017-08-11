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

#ifndef _TIMER_TIMEOUT_SETUP_H_
#define _TIMER_TIMEOUT_SETUP_H_

#include    <stdint.h>
#include    <msp430.h>
#include    "driverlib.h"

/* set the value of static variable */
void setTimerCompareValue(uint32_t compValue);

/* get the value of static variable */
uint32_t getTimerCompareValue(void);

/* Setup timer used to tick count */
void setupTimerHW(void);

#endif /* TIMER_TIMEOUT_SETUP_H_ */
