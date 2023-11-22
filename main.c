#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "ADC_Modified.h"
#include "Timers.h"
#include "LCD_Interface.h"
#include "EX_Interrupt.h"
#include "Kaypad_Interface.h"
#include "Servo.h"
#include "UART.h"
#include "UART_Service.h"
#include "SPI.h"
#include "TWI_interface.h"
#include "EEPROM_interface.h"
#include "Timer_Service.h"




int main()
{
	DIO_Init();
	LCD_Init();




	
	
	while(1)
	{
	
	}
	
	return 0;
}


/*
   //Servo Task With ADC
int main()
{
	DIO_Init();
	LCD_Init();
	ADC_Init(VREF_VCC,ADC_SCALER_64);
	SERVO_Init();

	ADC_ChannelSellect(CH_0);
	

	while(1)
	{
		ADC_StartConversion();
		u16 value= ADC_Read();
		u16 precent = ADC_Mapping(0,1023,750,2500,value);
		SERVO_SetAngle(precent);
		LCD_SetCursor(0,0);
		LCD_WriteNumber(precent);
		LCD_WriteString("    ");
	}
}

*/

/*
static u8 counter=0;
volatile u8 flag1=0,flag2=0;
void Ex0_func(void);
void Ex1_func(void);
int main()
{
	
	DIO_Init();
	ADC_Init(VREF_VCC,ADC_SCALER_64);
	TIMER0_Init(TIMER0_FASTPWM_MODE,TIMER0_SCALER_8);
	LCD_Init();
	
	TIMER0_OC0Mode(OC0_NON_INVERTING);
	ADC_ChannelSellect(CH_0);
	
	EXI_Init();
	EXI_Enable(EX_INT0);
	EXI_Enable(EX_INT1);
	EXI_TriggerEdge(EX_INT0,RISING_EDGE);
	EXI_TriggerEdge(EX_INT1,RISING_EDGE);
	EXI_SetCallBack(EX_INT0,Ex0_func);
	EXI_SetCallBack(EX_INT1,Ex1_func);
	sei();

	while(1)
	{
		if (flag1==1)
		{
			counter+=5;
			SetValue_OCR(counter);
			flag1=0;
		}
		else if (flag2==1)
		{
			counter-=5;
			SetValue_OCR(counter);
			flag2=0;
		}
		
		
		
		
	}
	return 0;
}

void Ex0_func(void)
{
	
	flag1=1;
}
void Ex1_func(void)
{
	
	flag2=1;
}

*/
/*
 Task 2
int main()
{
	
	DIO_Init();
	ADC_Init(VREF_VCC,ADC_SCALER_64);
	TIMER0_Init(TIMER0_FASTPWM_MODE,TIMER0_SCALER_8);
	LCD_Init();
	
	TIMER0_OC0Mode(OC0_NON_INVERTING);
	ADC_ChannelSellect(CH_0);
	

	LCD_SetCursor(0,0);
	u16 value =0;
	while(1)
	{
		ADC_StartConversion();
		value=ADC_Read();
		u16 percent =ADC_Mapping(0,1023,0,255,value);
		SetValue_OCR(percent);
		LCD_WriteNumber(percent);
		LCD_SetCursor(0,0);
		
	}
	return 0;
}
*/