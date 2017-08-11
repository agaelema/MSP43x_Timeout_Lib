/******************************************************************************
 * Timeout Lib for MSP430 V01 - Example of use
 *
 * Author: Haroldo L. M. Amaral - agaelema@globo.com
 * Date: 2017/07/30
 ******************************************************************************/

#include    <msp430.h>
#include    "driverlib.h"
#include    "timer_timeout.h"

/*****************************************************************************
 * Define the frequency of external clock source
 *****************************************************************************/
#define EXT_XT1_CLOCK_IN    32768               // ideally 32768 Hz
#define EXT_XT2_CLOCK_IN    0                   // 4MHz, but not used

/*****************************************************************************
 * Target frequency for MCLK in kHz
 *****************************************************************************/
#define UCS_MCLK_DESIRED_FREQUENCY_IN_KHZ   16000ul

/*****************************************************************************
 * Variable to store current Clock values
 *****************************************************************************/
uint32_t ACLK_clockValue = 0;
uint32_t MCLK_clockValue = 0;
uint32_t SMCLK_clockValue = 0;

/*****************************************************************************
 * Variable to store status of Oscillator fault flags
 *****************************************************************************/
uint16_t status = 0;

/*****************************************************************************
 * MCLK/FLLRef Ratio - used to set FLL
 *****************************************************************************/
unsigned long UCS_MCLK_FLLREF_RATIO = ((UCS_MCLK_DESIRED_FREQUENCY_IN_KHZ*1000)/EXT_XT1_CLOCK_IN) + 1;


void main(void)
{
    /* Stop WDT */
    WDT_A_hold(WDT_A_BASE);

    /* Set P1.0 to output direction - LED1 */
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);        // just to debug

    /* Set P4.7 to output direction - LED2 */
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN7);        // just to debug


    /* Set VCore = 3 for 20MHz clock */
    status = PMM_setVCore(PMMCOREV_3);
    __delay_cycles(1000000); // Output high for 1 second

    /* if vcore is OK */
    if (status)
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN7);       // just to debug
    }


    /*******************************************************************************
     *                          UCS - CLOCK CONFIGURATION
     *******************************************************************************/

    //Port select XT1
    GPIO_setAsPeripheralModuleFunctionInputPin(
            GPIO_PORT_P5,
            GPIO_PIN4 + GPIO_PIN5
    );

    /* Inform the frequency of the external crystals (XT1, XT2) */
    UCS_setExternalClockSource(
            EXT_XT1_CLOCK_IN,
            EXT_XT2_CLOCK_IN
    );



    /* Set DCO FLL reference = XT1 */
    UCS_initClockSignal(
            UCS_FLLREF,
            UCS_XT1CLK_SELECT,
            UCS_CLOCK_DIVIDER_1
    );

    /* Set ACLK = XT1 */
    UCS_initClockSignal(
            UCS_ACLK,
            UCS_XT1CLK_SELECT,
            UCS_CLOCK_DIVIDER_1
    );

    /* Set MCLK = DCOCLKDIV */
    UCS_initClockSignal(
            UCS_MCLK,
            UCS_DCOCLKDIV_SELECT,
            UCS_CLOCK_DIVIDER_1
    );

    /* Set SMCLK = DCOCLKDIV */
    UCS_initClockSignal(
            UCS_SMCLK,
            UCS_DCOCLKDIV_SELECT,
            UCS_CLOCK_DIVIDER_1
    );


    /* Set Ratio and Desired MCLK Frequency  and initialize DCO */
    UCS_initFLLSettle(
            UCS_MCLK_DESIRED_FREQUENCY_IN_KHZ,
            UCS_MCLK_FLLREF_RATIO
    );


    /* Enable global oscillator fault flag */
    SFR_clearInterrupt(SFR_OSCILLATOR_FAULT_INTERRUPT);
    SFR_enableInterrupt(SFR_OSCILLATOR_FAULT_INTERRUPT);


    /*******************************************************************************
     *                      TIMER A SETUP AND TIMEOUT LIB INIT
     *******************************************************************************/
    volatile uint32_t compare_value = 0;
    /* set compare value to get tick of 100us (10kHz) */
    compare_value = setCompareValue( 10000, UCS_getSMCLK() );
    delayInit();                                            // start timeout lib

    /* Enable global interrupt */
    __bis_SR_register(GIE);


    /* Verify if the Clock settings are as expected */
    SMCLK_clockValue = UCS_getSMCLK();
    MCLK_clockValue = UCS_getMCLK();
    ACLK_clockValue = UCS_getACLK();
    __no_operation();

    uint16_t repeat_delay;
    /*
     * Blink LEDs 4 times - use delayMs()
     */
    for (repeat_delay = 0; repeat_delay < 4; repeat_delay++)
    {
        GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
        GPIO_toggleOutputOnPin(GPIO_PORT_P4, GPIO_PIN7);
        delayMs(200);
    }

    uint32_t lastexection_1 = 0;
    uint32_t lastexection_2 = 0;

    while (1)
    {
        /*
         * blink LED1 (red) every 234ms
         * - use getTime_ms
         */
        if ((getTime_ms() - lastexection_1) >= 234)
        {
            GPIO_toggleOutputOnPin(             // toggle LED1
                    GPIO_PORT_P1,
                    GPIO_PIN0
            );
            lastexection_1 = getTime_ms();      // get the current time
        }


        /*
         * blink LED2 (green) every 1000ms
         * - use getTime_ms
         */
        if (timeoutCheck_ms(1000, lastexection_2))
        {
            lastexection_2 = timeoutInit();         // get the current time

            GPIO_toggleOutputOnPin(                 // toggle LED2
                    GPIO_PORT_P4,
                    GPIO_PIN7
            );
        }

    }
}


#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=UNMI_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(UNMI_VECTOR)))
#endif
void NMI_ISR(void)
{
    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2);        // just to debug
    do
    {
        // If it still can't clear the oscillator fault flags after the timeout,
        // trap and wait here.
        status = UCS_clearAllOscFlagsWithTimeout(1000);
    }
    while(status != 0);
}
