#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "ADC_Cfg.h"
#include "ADC_Interface.h"


u8  static ADC_ReadFlag=0;

void ADC_Init(ADC_VoltRef_type vref ,ADC_Prescaler_type scaler)
{
	/*vref*/
	switch(vref)
	{
		case VREF_AREF:
		CLEAR_BIT(ADMUX,REFS1);
		CLEAR_BIT(ADMUX,REFS0);
		break;
		case VREF_VCC:
		CLEAR_BIT(ADMUX,REFS1);
		SET_BIT(ADMUX,REFS0);
		break;
		case VREF_256:
		SET_BIT(ADMUX,REFS1);
		SET_BIT(ADMUX,REFS0);
		break;
	}
	
	/* Adjust Read */
	CLEAR_BIT(ADMUX,ADLAR); // If ADLAR is cleared (default), the result is right adjusted.
	
	/*clock*/
	ADCSRA=ADCSRA&0xf8; //0b11111000
// 	if(scaler>7)
// 	{
// 		scaler=7;
// 	}
	scaler=scaler&0x07;
	ADCSRA=ADCSRA|scaler;
	/* ADC Enable */
	SET_BIT(ADCSRA,ADEN);
}

u16 ADC_Read(ADC_Channel_type channel)
{
	u16 ADC_Value=0;
	/* select channel using mux */
	ADMUX=ADMUX&0Xe0; 
	ADMUX=ADMUX|channel;
	
	/*start conversion */
	SET_BIT(ADCSRA,ADSC);
	
	/* wait until end */ 
	while(READ_BIT(ADCSRA,ADSC));
	
	/* get reading from 2 registers */
	// the result is .If ADLAR is cleared (default), the result is right adjusted.  ADCL must be read first, then ADCH
 	ADC_Value=ADCL;
	ADC_Value=ADC_Value | ((u16)(ADCH<<8)); 
	//ADC_Value=ADC;
	
	return ADC_Value;
}

u16 ADC_ReadVolt(ADC_Channel_type ch)
{
	u16 adc=ADC_Read(ch);
	u16 volt=(adc*(u32)5000)/1024; // get the value of volt in milli 
	return volt;
}

u16 ADC_Percentage (u16 value, u16 resolution)
{
	u16 percentage =((u32)value*100)/resolution;
	
	return percentage;
}




/*Polling */

void ADC_StartConversion(ADC_Channel_type channel)
{
	if(ADC_ReadFlag==0)
	{
		/* select channel using mux */
		ADMUX=ADMUX&0Xe0;
		ADMUX=ADMUX|channel;
	
		/*start conversion */
		SET_BIT(ADCSRA,ADSC);
		ADC_ReadFlag=1;
		
	}
}

u16  ADC_GetRead(void)
{
	/* wait until end */
	while(READ_BIT(ADCSRA,ADSC));
	
	return ADC;
}

u8 ADC_GetReadPeriodicCheck(u16 *pdata)
{
	/* Check if the Reading End */
	if(!READ_BIT(ADCSRA,ADSC))
	{
		*pdata=ADC;
		ADC_ReadFlag=0;
		return 1;
		
	}
	return 0;
}

u16 ADC_GetReadNoBlock(void)
{
	return ADC;
}
