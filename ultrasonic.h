/*
 * ultrasonic.h
 *
 *  Created on: Jun 29, 2023
 *      Author: Abdelrhman Hesham
 */

#ifndef HAL_ULTRASONIC_ULTRASONIC_H_
#define HAL_ULTRASONIC_ULTRASONIC_H_


#include <avr\io.h>
#include <util/delay.h>
#include "../../MCAL/GPIO/gpio.h"
#include "../../MCAL/ICU/icu.h"
#include "../../OLIB/common_macros.h"
#include "../../OLIB/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define TRIGGER_PORT_ID PORTB_ID
#define TRIGGER_PIN_ID  PIN5_ID


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description : Function to initialize the ICU driver
 * 	1. Initialize ICU
 * 	2. Setup ICU callback function
 * 	3. Setup the direction of trigger pin
 */
void Ultrasonic_init(void);


/*
 * Description : Function to send trigger pulse
 */
void Ultrasonic_trigger(void);

/*
 * Description : Function to read distance measured by sensor
 * 1.  send trigger pulse
 * 2.  start measuring value
 */
uint16 Ultrasonic_readDistance(void);

/*
 * Description : Function to measure pulse
 */
void Ultrasonic_edgeProcessing(void);




#endif /* HAL_ULTRASONIC_ULTRASONIC_H_ */
