/*
 * ADC_private.h
 *
 *  Created on: Aug 13, 2023
 *      Author: alibo
 */

#ifndef MCAL_ADC_ADC_PRIVATE_H_
#define MCAL_ADC_ADC_PRIVATE_H_


#define ADMUX_REG                  *((volatile  u8*) 0x27 )
#define ADCSRA_REG                 *((volatile  u8*) 0x26 )
#define ADCH_REG                   *((volatile  u8*) 0x25 )
#define ADCL_REG                   *((volatile  u8*) 0x24 )

#define ADC_RESULT_REG             *(( volatile u16*)0x24)

#define SFIOR_REG                  *((volatile  u8*) 0x50 )



#define ADC_ADEN_BIT    7
#define ADC_ADSC_BIT    6

#define ADC_ADIE_BIT    3
#define ADC_ADIF_BIT    4

#endif /* MCAL_ADC_ADC_PRIVATE_H_ */
