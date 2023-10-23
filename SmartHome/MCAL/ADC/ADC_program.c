/*
 * ADC_program.c
 *
 *  Created on: Aug 13, 2023
 *      Author: alibo
 */

#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_interface.h"
#include"ADC_interface.h"
#include"ADC_private.h"
#include "ADC_config.h"

ERROR_STATE_t ADC_ErrorStateConvertedValueSync(ADC_Channel_t channel_number ,  u16 *Ptr_To_u16ReturnedValue)
{
	ERROR_STATE_t Local_Error_State = STD_TYPE_OK;
	ADMUX_REG &= 0b11100000; //0xE0 clearing 5 bits of channels

	ADMUX_REG |=  (channel_number & 0x07 );//INSERT THE REQUERED CHANNEL  (& with 0b00000111) forcing user to iput from adc0 to adc7 only

	SET_BIT( ADCSRA_REG , ADC_ADSC_BIT); // START CONVERSION

	u16 local_u16TimeOutCounter = 0 ;
	while (  ( GET_BIT( ADCSRA_REG , ADC_ADIF_BIT) == 0 ) && local_u16TimeOutCounter < 30000 )// waiting for flag to be 1
	{
		local_u16TimeOutCounter++;
	}

	if(  GET_BIT( ADCSRA_REG , ADC_ADIF_BIT) == 1 && Ptr_To_u16ReturnedValue != NULL  )
	{
		SET_BIT( ADCSRA_REG , ADC_ADIF_BIT); // clear flag by writing 1
		// GET THE DIGITAL READING
#if ADC_ADJUST == ADC_ADJUST_RIGHT
		*Ptr_To_u16ReturnedValue = ( ADCL_REG | (ADCH_REG<<8) ) ;
#elif ADC_ADJUST == ADC_ADJUST_LEFT
		*Ptr_To_u16ReturnedValue = (ADCH_REG<<2);
#endif
	}
	else // TIMEOUT
	{
		Local_Error_State = STD_TYPE_NOTOK ;
	}

	return Local_Error_State;
}
void ADC_voidInit(Channel_Config_t  *Ptr_To_Channel_Config)
{

	ADMUX_REG &= 0x3F ;//  to clear REFS1 AND REFS0

	ADMUX_REG |= (Ptr_To_Channel_Config->volt);// SET voltage


	ADCSRA_REG &= 0xF80 ; //0xF8  0b11111000  to clear least 3 bits of prescaler

	ADCSRA_REG |= (Ptr_To_Channel_Config->Prescaler);// set prescaler

	// PIE
#if   ADC_MECHANISM == ADC_POLLING
	CLR_BIT( ADCSRA_REG, ADC_ADIE_BIT );
#elif ADC_MECHANISM == ADC_INTERRUPT
	SET_BIT( ADCSRA_REG, ADC_ADIE_BIT );

#endif

	// ENABLE ADC
	SET_BIT(ADCSRA_REG, ADC_ADEN_BIT);
}

u16 ADC_u16ConvertedValue(ADC_Channel_t channel_number)
{
	ADMUX_REG &= 0b11100000; //0xE0 clearing 5 bits of channels

	ADMUX_REG |=  (channel_number & 0x07 );//INSERT THE REQUERED CHANNEL  (& with 0b00000111) forcing user to iput from adc0 to adc7 only

	SET_BIT( ADCSRA_REG , ADC_ADSC_BIT); // START CONVERSION

	while ( GET_BIT( ADCSRA_REG , ADC_ADIF_BIT) == 0 ); // waiting for flag to be 1

	SET_BIT( ADCSRA_REG , ADC_ADIF_BIT); // clear flag by writing 1


	return (ADC_RESULT_REG);// GET THE DIGITAL READING

}
