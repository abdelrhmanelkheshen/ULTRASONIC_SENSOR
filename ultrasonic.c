/*
 * ultrasonic.c
 *
 *  Created on: Jun 29, 2023
 *      Author: Abdelrhman Hesham
 */


#include "../../HAL/ULTRASONIC/ultrasonic.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

uint8 g_edgeCount = 0;
uint16 g_timeHigh = 0;



/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description : Function to initialize the ICU driver
 * 	1. Initialize ICU
 * 	2. Setup ICU callback function
 * 	3. Setup the direction of trigger pin
 */
void Ultrasonic_init(void)
{
	Icu_ConfigType ICU_Ptr={F_CPU_8,RISING};
	Icu_init(&ICU_Ptr);
	Icu_setCallBack(Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(TRIGGER_PORT_ID,TRIGGER_PIN_ID,PIN_OUTPUT);
}

/*
 * Description : Function to send trigger pulse
 */
void Ultrasonic_trigger(void)
{
	GPIO_writePin(TRIGGER_PORT_ID,TRIGGER_PIN_ID,LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(TRIGGER_PORT_ID,TRIGGER_PIN_ID,LOGIC_LOW);
}


/*
 * Description : Function to read distance measured by sensor
 * 1.  send trigger pulse
 * 2.  start measuring value
 */
uint16 Ultrasonic_readDistance(void)
{
	Ultrasonic_trigger();
	if(g_edgeCount==2)
	{
		g_edgeCount = 0;
		return (uint16)((uint32)g_timeHigh*10/588);
	}
}


/*
 * Description : Function to measure pulse
 */
void Ultrasonic_edgeProcessing(void)
{
	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		Icu_clearTimerValue();
		/* Toggle edge */
		Icu_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount == 2)
	{
		/* Store the High time value */
		g_timeHigh = Icu_getInputCaptureValue();
		/* Toggle edge edge */
		Icu_setEdgeDetectionType(RISING);
	}
}

