#include "StdTypes.h"
#include "Utils.h"
#include "ADC_Private_Modifed.h"
#include "ADC_Confg.h"
#include "ADC_Modified.h"
static u16* ADCResult = NULL;


/****************************Pointer to functions to be assigned to ISR*********************************/
static void (*ADC_Fptr) (void)=NULLPTR;



/******************* Function's Implementation ******************/
u16 ADC_GetReadNoBlock(void)
{
	return ADCDATA;
}


void ADC_StartConversion(void)
{
	ADCSRA_REG->ADSC=0b1;
}

void ADC_ChannelSellect(ADC_Channel_type channel)
{
	ADMUX_REG->MUX=channel;
}

u16 ADC_Read(void)
{
	while (ADCSRA_REG->ADIF==0);
	ADCSRA_REG->ADIF=0b1;
	return ADCDATA;
}

u16 ADC_ReadVolt(ADC_Channel_type ch)
{
	u16 adc=ADC_Read();
	u16 volt=(adc*(u32)5000)/1024; // get the value of volt in milli
	return volt;
}


u16 ADC_Percentage (u16 value)
{
	u16 percentage =((u32)value*100)/ADC_RESOLUTION;
	
	return percentage;
}

u16 ADC_Mapping(u16 x1,u16 x2 ,u16 y1,u16 y2,u16 ADC_Reading)
{
	u32 volt = ADC_Reading-x1;
	volt=volt*(y2-y1);
	volt=volt/(x2-x1);
	volt=volt+y1;
	return volt;
}


void ADC_Init(ADC_VoltRef_type vref,ADC_Prescaler_type scaler)
{
	/*vref*/
	ADMUX_REG->REFS=0b01;


	/* Adjust Read */
	ADMUX_REG->ADLAR=0b0; // If ADLAR is cleared (default), the result is right adjusted.



	/*clock*/
	ADCSRA_REG->ADPS=scaler;
	/* ADC Enable */
	ADCSRA_REG->ADEN=0b1;


}

void ADC_EnableInterrupt(void)
{
	ADCSRA_REG->ADIE=0b1;
}

void ADC_Auto_Triggered_Init(ADC_AutoTriggered_type TriggerMode,ADC_Channel_type CH,u16* Result)
{

	/*Initialize the global pointer to point to the result address*/
	ADCResult = Result;
	/*Set the required channel*/
	ADMUX_REG->MUX=CH;
	/*Start conversion buy OutTrigger*/
	ADCSRA_REG->ADATE=1;//enable auto triggered
	//Select Trigger_Mode Type
	SFIOR_reg->ADTS=TriggerMode;

	/*Enable ADC conversion complete interrupt*/
	ADCSRA_REG->ADIE=0b1;

}



void ADC_SetCallBack(void(*CallbackFunction)(void))
{
	/* Set the callback function */
	if(CallbackFunction != NULLPTR)
	{
		ADC_Fptr = CallbackFunction;
	}

}




void __vector_16 (void)			__attribute__((signal));
void __vector_16 (void)
{


	* ADCResult =ADCDATA  ;
	if(ADC_Fptr != NULL)
	{
		ADC_Fptr();
	}
}
