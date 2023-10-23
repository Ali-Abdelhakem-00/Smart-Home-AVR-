/*
 * main.c
 *
 *  Created on: Aug 30, 2023
 *      Author: alibo
 */

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include <util/delay.h>
#include "APP/APP_interface.h"
#include "MCAL/DIO/DIO_interface.h"
#include "MCAL/UART/UART_interface.h"
#include "HAL/LCD/LCD_interface.h"
#include "HAL/SERVO/SERVO_interface.h"

int main(void)
{
	LCD_voidInit();
	SERVO_voidInit();
	UART_Config_t myuart = { .USART_Mode            = Asynchronous,
			.Parity_Mode          = Disabled ,
			.Stop_Bits             = one_bit,
			.Character_Size       = EIGHT_BIT,
			.Clock_Polarity       = TXD_RISING_RXD_FALLING,
			.TX_RX_ENABLE_DISABLE = RX_Only_Enable,
			.UART_SPEED           = NORMAL_SPEED,
			.BAUD_RATE            = 9600,
	};
	DIO_voidSetPinDirection(DIO_PORTD ,DIO_PIN0 , DIO_INPUT);  //RX
	UART_void_Init(&myuart);

	DIO_voidSetPinDirection(DIO_PORTA ,DIO_PIN3 , DIO_OUTPUT);//LED1
	DIO_voidSetPinDirection(DIO_PORTA ,DIO_PIN4 , DIO_OUTPUT);//LED2
	DIO_voidSetPinDirection(DIO_PORTA ,DIO_PIN5 , DIO_OUTPUT);//LED3
	DIO_voidSetPinDirection(DIO_PORTA ,DIO_PIN6 , DIO_OUTPUT);//Alarm

	u8 Local_RecivedData;

	LCD_voidSetposition(1,1);
	LCD_voidSendString((u8*)"1)Safety Door");
	LCD_voidSetposition(2,1);
	LCD_voidSendString((u8*)"2)Control Light");
	_delay_ms(1500);
	LCD_voidDisplay_CLR();

	Local_RecivedData = UART_voidReceiveData_Sync();
	if(Local_RecivedData == '1')
	{
		LCD_voidSetposition(1,1);
		LCD_voidSendString((u8*)"1)Safety Door");
		_delay_ms(1000);
		LCD_voidDisplay_CLR();

		Display_UsersOptions();

		Local_RecivedData = UART_voidReceiveData_Sync();
		if(Local_RecivedData == '1')
		{
			Ali_UserEntry();
		}
		else if(Local_RecivedData == '2')
		{
			Amr_UserEntry();
		}
		else if(Local_RecivedData == '3')
		{
			May_UserEntry();
		}
		else if(Local_RecivedData == '4')
		{
			Alaa_UserEntry();
		}
		else if(Local_RecivedData == '5')
		{
			Emad_UserEntry();
		}
	}

	else if(Local_RecivedData == '2')
	{
		LCD_voidSetposition(2,1);
		LCD_voidSendString((u8*)"2)Control Light");
		_delay_ms(1000);
		LCD_voidDisplay_CLR();

		Display_LedsOptions();
		while(1)
		{
			Local_RecivedData = UART_voidReceiveData_Sync();
			if(Local_RecivedData == '1')
			{
				_1LED_ON();
			}
			if(Local_RecivedData == '2')
			{
				_2LEDS_ON();
			}
			if(Local_RecivedData == '3')
			{
				_3LEDS_ON();
			}
			if(Local_RecivedData == '4')
			{
				LEDS_OFF();
			}
		}
	}



	return 0 ;
}
