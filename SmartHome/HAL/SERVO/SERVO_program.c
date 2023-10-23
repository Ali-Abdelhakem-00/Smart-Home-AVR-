/*
 * SERVO_program.c
 *
 *  Created on: Aug 16, 2023
 *      Author: alibo
 */


#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/TIMER/TIMER_interface.h"


void SERVO_voidInit(void)
{
	DIO_voidSetPinDirection(DIO_PORTD , DIO_PIN5 , DIO_OUTPUT);

	TIMER_CONFIG_T1 myTimerT1 = {.timer_mode_T1=FAST_PWM_T1_ICR1_TOP ,
			                     .control_oc_T1 = CLEAR_OC1A_OC1B_AND_SET_ATB0TTOM_FASTPWM,
			                     .clock_source_T1 = FCPU_DIVBY_8
	                             };

	Timer_voidT1Init(&myTimerT1);
}

void SERVO_u16SendAngle(u16 Copy_u16Angle)
{
	if( Copy_u16Angle >0 && Copy_u16Angle <=180)
	{
	u16 Local_OCRValue = ( (Copy_u16Angle + 45 ) * 100 ) / 9 ;
	Timer_voidSetCompareMatchValueT1A(Local_OCRValue);
	}
	else
	{
		Timer_voidSetCompareMatchValueT1A(500);
	}
}
