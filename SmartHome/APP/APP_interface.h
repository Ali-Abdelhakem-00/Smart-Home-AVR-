/*
 * APP_interface.h
 *
 *  Created on: Aug 31, 2023
 *      Author: alibo
 */

#ifndef APP_APP_INTERFACE_H_
#define APP_APP_INTERFACE_H_






ERROR_STATE_t CheckAli_sPassWord_ErrorState(u8 *ptru8_to_password);
void Ali_UserEntry(void);

ERROR_STATE_t CheckAmr_sPassWord_ErrorState(u8 *ptru8_to_password);
void Amr_UserEntry(void);

ERROR_STATE_t CheckMay_sPassWord_ErrorState(u8 *ptru8_to_password);
void May_UserEntry(void);

ERROR_STATE_t CheckAlaa_sPassWord_ErrorState(u8 *ptru8_to_password);
void Alaa_UserEntry(void);

ERROR_STATE_t CheckEmad_sPassWord_ErrorState(u8 *ptru8_to_password);
void Emad_UserEntry(void);


void Display_LedsOptions(void);
void Display_UsersOptions(void);


void _1LED_ON(void);
void _2LEDS_ON(void);
void _3LEDS_ON(void);
void LEDS_OFF(void);
#endif /* APP_APP_INTERFACE_H_ */
