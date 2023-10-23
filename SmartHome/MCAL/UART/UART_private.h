/*
 * UART_private.h
 *
 *  Created on: Aug 19, 2023
 *      Author: alibo
 */

#ifndef MCAL_UART_UART_PRIVATE_H_
#define MCAL_UART_UART_PRIVATE_H_


#define  UDR_REG              *( (volatile u8* )  (0x2C) )
#define  UCSRA_REG            *( (volatile u8* )  (0x2B) )
#define  UCSRB_REG            *( (volatile u8* )  (0x2A) )
#define  UCSRC_UBRRH_REG      *( (volatile u8* )  (0x40) )
#define  UBRRL_REG            *( (volatile u8* )  (0x29) )



#define TX_ENABLE_BIT     3
#define RX_ENABLE_BIT     4



#define RX_COMPLETE_INTERRUPT_ENABLE_BIT     7
#define TX_COMPLETE_INTERRUPT_ENABLE_BIT     6
#define DATA_REG_EMPTY_INTERRUPT_ENABLE_BIT  5

#define RX_COMPLETE_FLAG_BIT     7
#define TX_COMPLETE_FLAG_BIT     6
#define DATA_REG_EMPTY_FLAG_BIT  5

#define URSEL_BIT   7
// 1  UCSRC       0 UBRRH
#endif /* MCAL_UART_UART_PRIVATE_H_ */
