/*
 * LCD_interface.h
 *
 *  Created on: Aug 5, 2023
 *      Author: alibo
 */

#ifndef HAL_LCD_LCD_INTERFACE_H_
#define HAL_LCD_LCD_INTERFACE_H_



void LCD_voidShiftRight(void);
void LCD_voidShiftLeft(void);
void LCD_voidSetposition(u8 copy_u8Row, u8 copy_u8col);
void LCD_voidInit(void);
void LCD_voidSendCommand (u8 copy_u8command);
void LCD_voidSendData    (u8 copy_u8data);
void LCD_voidDisplay_CLR(void);
void LCD_u8Display_Number(u64 Copy_Number);
void LCD_voidSendEXTRAChar(u8 copy_u8PatternLocation, u8 *p_u8ExtraChar,u8 copy_u8_row, u8 copy_u8_coulmn);
void LCD_voidSendString (u8 *copy_pu8string);

#endif /* HAL_LCD_LCD_INTERFACE_H_ */
