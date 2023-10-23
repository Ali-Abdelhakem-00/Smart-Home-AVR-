/*
 * UART_program.c
 *
 *  Created on: Aug 19, 2023
 *      Author: alibo
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include <util/delay.h>
#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"
static void (*Global_Ptr_To_FunNotification) (void) = NULL ;
void UART_SendString (u8 *Copy_Ptru8_To_String)
{
	u8 local_iterator = 0;
	if(Copy_Ptru8_To_String != NULL)
	{
		while( Copy_Ptru8_To_String[local_iterator] != '\0' )
		{
			UART_u8SendData_Sync(Copy_Ptru8_To_String[local_iterator]);
			local_iterator++;

		}
	}
}
void UART_ReceiveString(u8 *Copy_Ptru8_To_String)
{
	u8 local_iterator = 0;
	if(Copy_Ptru8_To_String != NULL)
	{
		while( Copy_Ptru8_To_String[local_iterator] != '\0' )
		{
			Copy_Ptru8_To_String[local_iterator] = UART_voidReceiveData_Sync() ;
			local_iterator++;
		}
	}
}
void UART_void_Init(UART_Config_t *Ptr_To_UART_CONFIG )
{

	switch (Ptr_To_UART_CONFIG ->TX_RX_ENABLE_DISABLE)
	{
	case RX_Only_Enable:
		SET_BIT( UCSRB_REG ,  RX_ENABLE_BIT );
		break;

	case TX_Only_Enable:
		SET_BIT( UCSRB_REG ,  TX_ENABLE_BIT );
		break;

	case TX_RX_Enable:
		SET_BIT( UCSRB_REG ,  RX_ENABLE_BIT );
		SET_BIT( UCSRB_REG ,  TX_ENABLE_BIT );
		break;
	}

	UCSRB_REG |=       ( (Ptr_To_UART_CONFIG ->Character_Size) & 0b100 );
	u8 local_variable_To_UCSRC = 0b10000000;
	// to select UCSRC

	local_variable_To_UCSRC |= ( ( (Ptr_To_UART_CONFIG ->Character_Size) & 0b011 ) << 1 );

	local_variable_To_UCSRC |= ( (Ptr_To_UART_CONFIG->USART_Mode)  << 6  );

	local_variable_To_UCSRC |= ( (Ptr_To_UART_CONFIG->Parity_Mode) << 4  );

	local_variable_To_UCSRC |= ( (Ptr_To_UART_CONFIG->Stop_Bits)   << 3  );

	local_variable_To_UCSRC |= ( (Ptr_To_UART_CONFIG->Clock_Polarity) );

	UCSRC_UBRRH_REG = local_variable_To_UCSRC ;



	u16 BAUD_PRESCALE     = (((8000000 / (Ptr_To_UART_CONFIG->BAUD_RATE * 16UL))) - 1);
	u16 BAUD_PRESCALE_u2x = (((8000000 / (Ptr_To_UART_CONFIG->BAUD_RATE * 8UL)))  - 1);

	switch(  Ptr_To_UART_CONFIG->UART_SPEED   )
	{
	case NORMAL_SPEED:
		UBRRL_REG       = (u8)   BAUD_PRESCALE        ;
		UCSRC_UBRRH_REG = (u8) ( BAUD_PRESCALE  >> 8 );
		break;

	case U2X_SPEED:
		UBRRL_REG       = (u8)   BAUD_PRESCALE_u2x        ;
		UCSRC_UBRRH_REG = (u8) ( BAUD_PRESCALE_u2x  >> 8 );
		break;
	default:
		break;
	}




}
void UART_u8SendData_Sync(u8 Copy_Data)
{
	while(  GET_BIT( UCSRA_REG , DATA_REG_EMPTY_INTERRUPT_ENABLE_BIT) == 0 );
	UDR_REG = Copy_Data ;
	_delay_ms(5);
}
u8 UART_voidReceiveData_Sync(void)
{
	while(  GET_BIT( UCSRA_REG , RX_COMPLETE_FLAG_BIT ) == 0  );
	return UDR_REG;
}

void UART_u8SendData_Async(u8 Copy_Data)
{

	UDR_REG = Copy_Data ;
	_delay_ms(5);
}

u8 UART_voidReceiveData_Async(void)
{


	return UDR_REG;
}


static u8 UART_Sending_Flag = 0;
static u8 UART_Receiving_Flag = 0;

void UART_voidCallBackFunSending ( void (*Ptr_To_Func)(void) )
{//Register Empty
	if(Ptr_To_Func != NULL  && UART_Sending_Flag ==0)
	{
		UART_Sending_Flag = 1;
		Global_Ptr_To_FunNotification = Ptr_To_Func ;
	}
	SET_BIT( UCSRB_REG ,  DATA_REG_EMPTY_INTERRUPT_ENABLE_BIT );

}

void UART_voidCallBackFunReceiving ( void (*Ptr_To_Func)(void) )
{//RX
	if(Ptr_To_Func != NULL  && UART_Receiving_Flag ==0)
	{
		UART_Receiving_Flag = 1;
		Global_Ptr_To_FunNotification = Ptr_To_Func ;
	}
	SET_BIT( UCSRB_REG ,  RX_COMPLETE_INTERRUPT_ENABLE_BIT );

}


void __vector_13(void) __attribute__((signal));
void __vector_13(void)
{//RX
	if(Global_Ptr_To_FunNotification != NULL)
	{
		Global_Ptr_To_FunNotification();
	}
	   CLR_BIT( UCSRB_REG ,  RX_COMPLETE_INTERRUPT_ENABLE_BIT );
	   UART_Receiving_Flag = 0;

}


void __vector_14(void) __attribute__((signal));
void __vector_14(void)
{//Register Empty

	if(Global_Ptr_To_FunNotification != NULL)
	{
		Global_Ptr_To_FunNotification();
	}
	CLR_BIT( UCSRB_REG ,   DATA_REG_EMPTY_INTERRUPT_ENABLE_BIT);
	UART_Sending_Flag = 0;

}

