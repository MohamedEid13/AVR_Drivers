#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "ADC_Interface.h"
#include "Motors_Interface.h"
#include "LCD_Interface.h"

int LDR(void)
{
	
	DIO_Init();
	ADC_Init(VREF_VCC,ADC_SCALER_64);
	LCD_Init();


	
	LCD_Clear();
	LCD_SetCursor(0,0);
	DDRB=0XFF;
	u16 num=0;
	while (1)
	{
		num=ADC_Read(CH_7);
		LCD_WriteNumber(num);
		_delay_ms(500);
		LCD_Clear();
		if(num>=0 && num<150){
			PORTB=0xff;
		}
		else if (num>=150 && num<500)
		{
			PORTB=0x3f;
		}
		else if(num>=500 && num<650)
		{
			PORTB=0x0f;
		}
		else if(num>=650 && num<850)
		{
			PORTB=0x03;
		}
		else if (num>900)
		{
			PORTB=0x01;
		}
	}
}