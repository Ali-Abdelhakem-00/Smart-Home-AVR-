/*
 * ADC_interface.h
 *
 *  Created on: Aug 13, 2023
 *      Author: alibo
 */

#ifndef MCAL_ADC_ADC_INTERFACE_H_
#define MCAL_ADC_ADC_INTERFACE_H_

typedef enum
{
	INTERNAL_5,AVCC = 64,INTERNAL_2_5 = 192 //0b11000000
}ADC_Voltage_Selection_t;

typedef enum
{
	DIV_BY2 = 1,DIV_BY4,DIV_BY8,DIV_BY16,DIV_BY32,DIV_BY64,DIV_BY128
}ADC_Prescaler_t;

typedef  enum
{
ADC0,ADC1,ADC2,ADC3,ADC4,ADC5,ADC6,ADC7
}ADC_Channel_t;

typedef struct
{
	ADC_Voltage_Selection_t  volt      ;
	ADC_Prescaler_t          Prescaler ;

}Channel_Config_t;


void ADC_voidInit(Channel_Config_t  *Ptr_To_Channel_Config);
u16 ADC_u16ConvertedValue(ADC_Channel_t channel_number);
ERROR_STATE_t ADC_ErrorStateConvertedValueSync(ADC_Channel_t channel_number ,  u16 *Ptr_To_ReturnedValue);

#endif /* MCAL_ADC_ADC_INTERFACE_H_ */
