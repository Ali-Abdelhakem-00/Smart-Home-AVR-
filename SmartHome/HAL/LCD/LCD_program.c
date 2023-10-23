/*
 * LCD_program.c
 *
 *  Created on: Aug 5, 2023
 *      Author: alibo
 */
#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATH.h"
#include"../../MCAL/DIO/DIO_interface.h"
#define F_CPU   8000000UL
#include<util/delay.h>
#include"LCD_interface.h"
#include"LCD_private.h"
#include"LCD_config.h"
void LCD_u8Display_Number(u64 Copy_Number)
{


	u64 local_Reversed_variable=1;
	if(Copy_Number==0)
	{
		LCD_voidSendData('0');
	}
	else
	{

		while( Copy_Number!=0)
		{

			local_Reversed_variable=(local_Reversed_variable*10)+(Copy_Number%10);
		Copy_Number = Copy_Number/10;

	     }
		while(local_Reversed_variable!=1)
		{
			LCD_voidSendData( (local_Reversed_variable % 10)+ 48);
			local_Reversed_variable=local_Reversed_variable/10;
		}


	}



}
void LCD_voidShiftRight(void)
{
	LCD_voidSendCommand(0b00011100);
}
void LCD_voidShiftLeft(void)
{
	LCD_voidSendCommand(0b00011000);
}
void LCD_voidSendString (u8 *copy_pu8string)
{
u8 local_iterator =0;
  while(copy_pu8string[local_iterator]!= '\0')
    {
	  LCD_voidSendData(copy_pu8string[local_iterator]);
	  local_iterator++;
	}

}

void LCD_voidSendEXTRAChar(u8 copy_u8PatternLocation, u8 *p_u8ExtraChar,u8 copy_u8_row, u8 copy_u8_coulmn)
{
	u8 Local_u8Address =0 ;
	Local_u8Address = copy_u8PatternLocation*8;
	//Go toCGRAM
	LCD_voidSendCommand(64+Local_u8Address );

	//GENERATE CHARACHTER INSIDE CGRAM
	for(u8 i =0; i<8; i++)
	{
		LCD_voidSendData(p_u8ExtraChar[i]);
	}

	//BACK TO DDRAM
	LCD_voidSetposition(copy_u8_row, copy_u8_coulmn);


	//DRAW CHAR ON DISPLAY
	LCD_voidSendData(copy_u8PatternLocation);

}
void LCD_voidSetposition(u8 copy_u8Row, u8 copy_u8Col)
{

	switch(copy_u8Row)
	{
	case 1:
	LCD_voidSendCommand(0x80+ (copy_u8Col-1 ) );
		break;

	case 2:
		LCD_voidSendCommand(0x80+64+ (copy_u8Col-1) );
		break;

	default:
		break;

	}
}
void LCD_voidInit(void)
{
	DIO_voidSetPortDirection(LCD_DATA_PORT,DIO_OUTPUT);

	DIO_voidSetPinDirection(LCD_CTR_PORT,LCD_EN_PIN,DIO_OUTPUT);
	DIO_voidSetPinDirection(LCD_CTR_PORT,LCD_RS_PIN,DIO_OUTPUT);
	DIO_voidSetPinDirection(LCD_CTR_PORT,LCD_RW_PIN,DIO_OUTPUT);
	_delay_ms(50);

	// FUNCTION SET
	LCD_voidSendCommand(0b00111000);
	_delay_ms(50);
	//display/on/off
	LCD_voidSendCommand(0b00001100);

	//display clr
	LCD_voidSendCommand(0x01);
	_delay_ms(2);

	// entry modeset
	LCD_voidSendCommand(0b00000110);

}
void LCD_voidSendCommand(u8 copy_u8command)
{
	/*RS-> low(to send command)
	 *
	 * RW -> LOW(TO WRITE)
	 *
	 * SEND COMMAND
	 *
	 *
     *
     *     ENABLE SEQUENCE
     */



	DIO_voidSetPinValue (LCD_CTR_PORT,LCD_RS_PIN,DIO_LOW);
	DIO_voidSetPinValue (LCD_CTR_PORT,LCD_RW_PIN,DIO_LOW);
	DIO_voidSetPortValue(LCD_DATA_PORT, copy_u8command);


	DIO_voidSetPinValue(LCD_CTR_PORT,LCD_EN_PIN,DIO_HIGH);
	_delay_us(1);
	DIO_voidSetPinValue(LCD_CTR_PORT,LCD_EN_PIN,DIO_LOW);
	_delay_us(1);

}
void LCD_voidSendData(u8 copy_u8data)
{
	DIO_voidSetPinValue(LCD_CTR_PORT,LCD_RS_PIN,DIO_HIGH);
	DIO_voidSetPinValue(LCD_CTR_PORT,LCD_RW_PIN,DIO_LOW);
	DIO_voidSetPortValue(LCD_DATA_PORT, copy_u8data);


	DIO_voidSetPinValue(LCD_CTR_PORT,LCD_EN_PIN,DIO_HIGH);
	_delay_us(1);
	DIO_voidSetPinValue(LCD_CTR_PORT,LCD_EN_PIN,DIO_LOW);
	_delay_us(1);
}
void LCD_voidDisplay_CLR(void)
{
	LCD_voidSendCommand(0x01);
}
