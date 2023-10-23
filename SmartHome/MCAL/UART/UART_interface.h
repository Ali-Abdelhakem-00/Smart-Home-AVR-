/*
 * UART_interface.h
 *
 *  Created on: Aug 19, 2023
 *      Author: alibo
 */

#ifndef MCAL_UART_UART_INTERFACE_H_
#define MCAL_UART_UART_INTERFACE_H_

typedef enum
{
	Asynchronous, Symchronous

}USART_Mode_t;

typedef enum
{
	Disabled , Reserved , Enabled_Even_Parity , Enabled_Odd_Parity
}Parity_Mode_t;


typedef enum
{
	one_bit  , two_bits
}Stop_Bit_t;


typedef enum
{
	FIVE_BIT , SIX_BIT , SEVEN_BIT , EIGHT_BIT  , RESERVED1 ,RESERVED2, RESERVED3 ,NINE_BIT
}Character_Size_t;

typedef enum
{
	TXD_RISING_RXD_FALLING ,   TXD_FALLING_RXD_RISING
}Clock_Polarity_t;

typedef enum
{
	TX_Only_Enable ,
	RX_Only_Enable ,
	TX_RX_Enable,

}TX_RX_ENABLE_DISABLE_t;

typedef enum
{
	NORMAL_SPEED , U2X_SPEED
}UART_TRANSMISSION_SPEED_t;

typedef struct
{
	USART_Mode_t               USART_Mode;
	Parity_Mode_t              Parity_Mode;
	Stop_Bit_t                 Stop_Bits;
	Character_Size_t           Character_Size;
	Clock_Polarity_t           Clock_Polarity;
	TX_RX_ENABLE_DISABLE_t     TX_RX_ENABLE_DISABLE;
	UART_TRANSMISSION_SPEED_t  UART_SPEED;
	u16                        BAUD_RATE;

}UART_Config_t;

void UART_void_Init( UART_Config_t *Ptr_To_UART_CONFIG );
void UART_u8SendData_Sync(u8 Copy_Data);
u8 UART_voidReceiveData_Sync(void);
void UART_SendString(u8 *Copy_Ptru8_To_String);
void UART_ReceiveString(u8 *Copy_Ptru8_To_String);

void UART_u8SendData_Async(u8 Copy_Data);
u8 UART_voidReceiveData_Async(void);


void UART_voidCallBackFunSending ( void (*Ptr_To_Func)(void) );

void UART_voidCallBackFunReceiving ( void (*Ptr_To_Func)(void) );

#endif /* MCAL_UART_UART_INTERFACE_H_ */
