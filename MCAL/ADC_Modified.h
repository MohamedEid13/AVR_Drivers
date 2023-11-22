

#ifndef ADC_MODIFIED_H_
#define ADC_MODIFIED_H_



typedef enum{
	VREF_AREF,
	VREF_VCC,
	VREF_256
	
}ADC_VoltRef_type;

typedef enum{
	ADC_SCALER_2=1,
	ADC_SCALER_4,
	ADC_SCALER_8,
	ADC_SCALER_16,
	ADC_SCALER_32,
	ADC_SCALER_64,
	ADC_SCALER_128
	
}ADC_Prescaler_type;

typedef enum
{
	FREE_RUNNING=0,
	ANALOG_COMPARATOR,
	EXT_INTERRUPT0,
	TIMER0_COMP,
	TIMER0_OFV,
	TIMER1_COMP_B,
	TIMER1_OVF,
	TIMER1_IC,	
}ADC_AutoTriggered_type;

typedef enum{
	CH_0,
	CH_1,
	CH_2,
	CH_3,
	CH_4,
	CH_5,
	CH_6,
	CH_7
}ADC_Channel_type;



/**************************API'S********************/
void ADC_Init(ADC_VoltRef_type vref,ADC_Prescaler_type scaler);
void ADC_StartConversion(void);
void ADC_ChannelSellect(ADC_Channel_type channel);
u16 ADC_Read(void);
u16 ADC_Mapping(u16 x1,u16 x2 ,u16 y1,u16 y2,u16 ADC_Reading);
u16 ADC_Percentage (u16 value);
u16 ADC_ReadVolt(ADC_Channel_type ch);
u16 ADC_GetReadNoBlock(void);
void ADC_SetCallBack(void(*CallbackFunction)(void));
void ADC_EnableInterrupt(void);

void ADC_Auto_Triggered_Init(ADC_AutoTriggered_type TriggerMode,ADC_Channel_type CH,u16* Copy_pu16Result);

#endif /* ADC_MODIFIED_H_ */