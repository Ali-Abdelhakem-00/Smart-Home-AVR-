/*
 * APP_program.c
 *
 *  Created on: Aug 31, 2023
 *      Author: alibo
 */
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include <util/delay.h>
#include "APP_interface.h"
#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/UART/UART_interface.h"
#include "../HAL/LCD/LCD_interface.h"
#include "../HAL/SERVO/SERVO_interface.h"



u8 ALISPASS [4] = {'1','2','3','4'};
u8 AMRSPASS [4] = {'4','3','2','1'};
u8 MAYSPASS [4] = {'5','6','7','8'};
u8 ALAASPASS[4] = {'1','2','9','9'};
u8 EMADSPASS[4] = {'1','2','1','2'};
u8 Attempts    =   0  ;
u8 pass[4]     = {'0'};
u8 passcounter =   0  ;
ERROR_STATE_t  local_state;
u8 Chcek_Counter =0 ;
u8 Correct_PASS_Flag = 0 ;


ERROR_STATE_t CheckAli_sPassWord_ErrorState(u8 *ptru8_to_password)
{
	Chcek_Counter = 0 ;
	Correct_PASS_Flag = 0 ;
	while(Chcek_Counter <=3)
	{
		if(ALISPASS[Chcek_Counter] == ptru8_to_password[Chcek_Counter ])
		{
			Correct_PASS_Flag++;
		}
		Chcek_Counter++;
	}

	if(Correct_PASS_Flag == 4 )
	{
		LCD_voidSetposition(2,1);
		LCD_voidSendString((u8*)"Hello ALI");
		local_state = STD_TYPE_OK;
	}
	else
	{
		LCD_voidSetposition(2,1);
		LCD_voidSendString((u8*)"Wrong Pass");
		_delay_ms(500);
		LCD_voidDisplay_CLR();
		local_state = STD_TYPE_NOTOK;
		LCD_voidSetposition(2,1);
		LCD_voidSendString((u8*)"Try Again");
	}
	return local_state ;
}



void Ali_UserEntry(void)
{
	static ERROR_STATE_t Local_Error_State =STD_TYPE_NOTOK ;
	LCD_voidDisplay_CLR();
	LCD_voidSetposition(1,1);
	LCD_voidSendString((u8*)"Enter ALI's Pass");
	while(Attempts<3)
	{
		while(passcounter <=3 )
		{
			pass[passcounter] = UART_voidReceiveData_Sync();
			passcounter++;
		}
		passcounter = 0;
		Local_Error_State = CheckAli_sPassWord_ErrorState(pass);
		if(Local_Error_State == STD_TYPE_OK)
		{
			break;
		}
		Attempts++;
	}
	if(Attempts == 3)
	{
		LCD_voidSetposition(2,1);
		LCD_voidSendString((u8*)"No More Attempts");
		while(1)
		{
			DIO_voidSetPinValue(DIO_PORTA , DIO_PIN6 ,DIO_HIGH );//ALARM
		}
	}
	else
	{
		SERVO_u16SendAngle(90);
		_delay_ms(1500);
		SERVO_u16SendAngle(0);
	}
}

ERROR_STATE_t CheckAmr_sPassWord_ErrorState(u8 *ptru8_to_password)
{
	Chcek_Counter = 0 ;
	Correct_PASS_Flag = 0 ;
	while(Chcek_Counter <=3)
	{
		if(AMRSPASS[Chcek_Counter] == ptru8_to_password[Chcek_Counter ])
		{
			Correct_PASS_Flag++;
		}
		Chcek_Counter++;
	}

	if(Correct_PASS_Flag == 4 )
	{
		LCD_voidSetposition(2,1);
		LCD_voidSendString((u8*)"Hello AMR");
		local_state = STD_TYPE_OK;
	}
	else
	{
		LCD_voidSetposition(2,1);
		LCD_voidSendString((u8*)"Wrong Pass");
		_delay_ms(500);
		LCD_voidDisplay_CLR();
		local_state = STD_TYPE_NOTOK;
		LCD_voidSetposition(2,1);
		LCD_voidSendString((u8*)"Try Again");
	}
	return local_state ;
}
void Amr_UserEntry(void)
{


	static ERROR_STATE_t Local_Error_State =STD_TYPE_NOTOK ;
	LCD_voidDisplay_CLR();
	LCD_voidSetposition(1,1);
	LCD_voidSendString((u8*)"Enter AMR's Pass");
	while(Attempts<3)
	{
		while(passcounter <=3 )
		{
			pass[passcounter] = UART_voidReceiveData_Sync();
			passcounter++;
		}
		passcounter = 0;
		Local_Error_State = CheckAmr_sPassWord_ErrorState(pass);
		if(Local_Error_State == STD_TYPE_OK)
		{
			break;
		}
		Attempts++;
	}
	if(Attempts == 3)
	{
		LCD_voidSetposition(2,1);
		LCD_voidSendString((u8*)"No More Attempts");
		while(1)
		{
			DIO_voidSetPinValue(DIO_PORTA , DIO_PIN6 ,DIO_HIGH );//ALARM
		}
	}
	else
	{
		SERVO_u16SendAngle(90);
		_delay_ms(1500);
		SERVO_u16SendAngle(0);
	}

}

ERROR_STATE_t CheckMay_sPassWord_ErrorState(u8 *ptru8_to_password)
{
	Chcek_Counter = 0 ;
	Correct_PASS_Flag = 0 ;
	while(Chcek_Counter <=3)
	{
		if(MAYSPASS[Chcek_Counter] == ptru8_to_password[Chcek_Counter ])
		{
			Correct_PASS_Flag++;
		}
		Chcek_Counter++;
	}

	if(Correct_PASS_Flag == 4 )
	{
		LCD_voidSetposition(2,1);
		LCD_voidSendString((u8*)"Hello MAY");
		local_state = STD_TYPE_OK;
	}
	else
	{
		LCD_voidSetposition(2,1);
		LCD_voidSendString((u8*)"Wrong Pass");
		_delay_ms(500);
		LCD_voidDisplay_CLR();
		local_state = STD_TYPE_NOTOK;
		LCD_voidSetposition(2,1);
		LCD_voidSendString((u8*)"Try Again");
	}
	return local_state ;
}
void May_UserEntry(void)
{


	static ERROR_STATE_t Local_Error_State =STD_TYPE_NOTOK ;
	LCD_voidDisplay_CLR();
	LCD_voidSetposition(1,1);
	LCD_voidSendString((u8*)"Enter MAY's Pass");
	while(Attempts<3)
	{
		while(passcounter <=3 )
		{
			pass[passcounter] = UART_voidReceiveData_Sync();
			passcounter++;
		}
		passcounter = 0;
		Local_Error_State = CheckMay_sPassWord_ErrorState(pass);
		if(Local_Error_State == STD_TYPE_OK)
		{
			break;
		}
		Attempts++;
	}
	if(Attempts == 3)
	{
		LCD_voidSetposition(2,1);
		LCD_voidSendString((u8*)"No More Attempts");
		while(1)
		{
			DIO_voidSetPinValue(DIO_PORTA , DIO_PIN6 ,DIO_HIGH );//ALARM
		}
	}
	else
	{
		SERVO_u16SendAngle(90);
		_delay_ms(1500);
		SERVO_u16SendAngle(0);
	}
}

ERROR_STATE_t CheckAlaa_sPassWord_ErrorState(u8 *ptru8_to_password)
{
	Chcek_Counter = 0 ;
	Correct_PASS_Flag = 0 ;
	while(Chcek_Counter <=3)
	{
		if(ALAASPASS[Chcek_Counter] == ptru8_to_password[Chcek_Counter ])
		{
			Correct_PASS_Flag++;
		}
		Chcek_Counter++;
	}

	if(Correct_PASS_Flag == 4 )
	{
		LCD_voidSetposition(2,1);
		LCD_voidSendString((u8*)"Hello ALAA");
		local_state = STD_TYPE_OK;
	}
	else
	{
		LCD_voidSetposition(2,1);
		LCD_voidSendString((u8*)"Wrong Pass");
		_delay_ms(500);
		LCD_voidDisplay_CLR();
		local_state = STD_TYPE_NOTOK;
		LCD_voidSetposition(2,1);
		LCD_voidSendString((u8*)"Try Again");
	}
	return local_state ;
}
void Alaa_UserEntry(void)
{


	static ERROR_STATE_t Local_Error_State =STD_TYPE_NOTOK ;
	LCD_voidDisplay_CLR();
	LCD_voidSetposition(1,1);
	LCD_voidSendString((u8*)"Enter ALAA's Pass");
	while(Attempts<3)
	{
		while(passcounter <=3 )
		{
			pass[passcounter] = UART_voidReceiveData_Sync();
			passcounter++;
		}
		passcounter = 0;
		Local_Error_State = CheckAlaa_sPassWord_ErrorState(pass);
		if(Local_Error_State == STD_TYPE_OK)
		{
			break;
		}
		Attempts++;
	}
	if(Attempts == 3)
	{
		LCD_voidSetposition(2,1);
		LCD_voidSendString((u8*)"No More Attempts");
		while(1)
		{
			DIO_voidSetPinValue(DIO_PORTA , DIO_PIN6 ,DIO_HIGH );//ALARM
		}
	}
	else
	{
		SERVO_u16SendAngle(90);
		_delay_ms(1500);
		SERVO_u16SendAngle(0);
	}
}

ERROR_STATE_t CheckEmad_sPassWord_ErrorState(u8 *ptru8_to_password)
{

	Chcek_Counter = 0 ;
	Correct_PASS_Flag = 0 ;
	while(Chcek_Counter <=3)
	{
		if(EMADSPASS[Chcek_Counter] == ptru8_to_password[Chcek_Counter ])
		{
			Correct_PASS_Flag++;
		}
		Chcek_Counter++;
	}

	if(Correct_PASS_Flag == 4 )
	{
		LCD_voidSetposition(2,1);
		LCD_voidSendString((u8*)"Hello EMAD");
		local_state = STD_TYPE_OK;
	}
	else
	{
		LCD_voidSetposition(2,1);
		LCD_voidSendString((u8*)"Wrong Pass");
		_delay_ms(500);
		LCD_voidDisplay_CLR();
		local_state = STD_TYPE_NOTOK;
		LCD_voidSetposition(2,1);
		LCD_voidSendString((u8*)"Try Again");
	}
	return local_state ;
}
void Emad_UserEntry(void)
{


	static ERROR_STATE_t Local_Error_State =STD_TYPE_NOTOK ;
	LCD_voidDisplay_CLR();
	LCD_voidSetposition(1,1);
	LCD_voidSendString((u8*)"Enter EMAD's Pass");
	while(Attempts<3)
	{
		while(passcounter <=3 )
		{
			pass[passcounter] = UART_voidReceiveData_Sync();
			passcounter++;
		}
		passcounter = 0;
		Local_Error_State = CheckEmad_sPassWord_ErrorState(pass);
		if(Local_Error_State == STD_TYPE_OK)
		{
			break;
		}
		Attempts++;

	}
	if(Attempts == 3)
	{
		LCD_voidSetposition(2,1);
		LCD_voidSendString((u8*)"No More Attempts");
		while(1)
		{
			DIO_voidSetPinValue(DIO_PORTA , DIO_PIN6 ,DIO_HIGH );//ALARM
		}
	}
	else
	{
		SERVO_u16SendAngle(90);
		_delay_ms(1500);
		SERVO_u16SendAngle(0);
	}
}


void Display_LedsOptions(void)
{
	LCD_voidSetposition(1,1);
	LCD_voidSendString((u8*)"1_LED ");
	LCD_voidSetposition(1,9);
	LCD_voidSendString((u8*)"2_LEDS ");
	LCD_voidSetposition(2,1);
	LCD_voidSendString((u8*)"3_LEDS ");
	LCD_voidSetposition(2,9);
	LCD_voidSendString((u8*)"4_OFF");
}
void Display_UsersOptions(void)
{
	LCD_voidSetposition(1,1);
	LCD_voidSendString((u8*)"1_ALI");
	LCD_voidSetposition(1,6);
	LCD_voidSendString((u8*)"2_AMR");
	LCD_voidSetposition(1,11);
	LCD_voidSendString((u8*)" 3_MAY");
	LCD_voidSetposition(2,1);
	LCD_voidSendString((u8*)"4_ALAA");
	LCD_voidSetposition(2,8);
	LCD_voidSendString((u8*)"5_EMAD");
}


void _1LED_ON(void)
{
	DIO_voidSetPinValue( DIO_PORTA , DIO_PIN3 , DIO_HIGH );
	DIO_voidSetPinValue( DIO_PORTA , DIO_PIN4 , DIO_LOW );
	DIO_voidSetPinValue( DIO_PORTA , DIO_PIN5 , DIO_LOW );
}
void _2LEDS_ON(void)
{
	DIO_voidSetPinValue( DIO_PORTA , DIO_PIN3 , DIO_HIGH );
	DIO_voidSetPinValue( DIO_PORTA , DIO_PIN4 , DIO_HIGH );
	DIO_voidSetPinValue( DIO_PORTA , DIO_PIN5 , DIO_LOW );
}
void _3LEDS_ON(void)
{
	DIO_voidSetPinValue( DIO_PORTA , DIO_PIN3 , DIO_HIGH );
	DIO_voidSetPinValue( DIO_PORTA , DIO_PIN4 , DIO_HIGH );
	DIO_voidSetPinValue( DIO_PORTA , DIO_PIN5 , DIO_HIGH );
}
void LEDS_OFF(void)
{
	DIO_voidSetPinValue( DIO_PORTA , DIO_PIN3 , DIO_LOW );
	DIO_voidSetPinValue( DIO_PORTA , DIO_PIN4 , DIO_LOW );
	DIO_voidSetPinValue( DIO_PORTA , DIO_PIN5 , DIO_LOW );
}
