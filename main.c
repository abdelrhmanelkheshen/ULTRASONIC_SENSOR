/*
 * main.c
 *
 *  Created on: Jun 29, 2023
 *      Author: Abdelrhman Hesham
 */


#include <avr/io.h>
#include "../HAL/LCD/lcd.h"
#include "../HAL/ULTRASONIC/ultrasonic.h"


void DisplayDistance(uint8 value);

int main(void)
{
	SREG |= (1<<7); /*Enable Interrupts*/

	LCD_init(); /*Initialize LCD*/

	Ultrasonic_init(); /*Initialize Ultra sonic*/

	LCD_displayString("Distance=    cm");
	uint16 distance=0;
	while(1)
	{
		distance=Ultrasonic_readDistance();
		DisplayDistance(distance);
	}
}

void DisplayDistance(uint8 value)
{
	LCD_moveCursor(0,10);
		if(value >= 100)
		{
			LCD_intgerToString(value);
		}
		else
		{
			LCD_intgerToString(value);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
		}

}
