#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "ADC_Interface.h"
#include "LCD_Interface.h"
#include "Kaypad_Interface.h"
#include "Sensor.h"
#include "FireSystem.h"

void FireAlarm_Init(void)
{
	DIO_Init();
	LCD_Init();
	KEYPAD_Init();
	ADC_Init(VREF_VCC,ADC_SCALER_64);
}


static u16 temp,smoke,smoke_percent=0,num=0;
static u8  flag1=0,flag2=0,flag3=0,fire_flag=0,k,flag4=0;

void FireAlarm_Runnable(void)
{
	temp=LM35_TempRead();
	if(temp<500 && fire_flag==0)
	{
		if(flag1==0)
		{
		LCD_SetCursor(0,0);
		LCD_Clear();
		LCD_SetCursor(0,0);
		flag1=1;
		flag2=0;
		}
		LCD_WriteString("Fine");
		LCD_SetCursor(1,0);
		LCD_WriteString("Temp=");
		LCD_WriteNumber(temp/10);
		LCD_WriteChar('.');
		LCD_WriteNumber(temp%10);
		LCD_WriteChar('C');
		LCD_WriteString("       ");
		DIO_WritePort(PC,LOW);
	}
	else if(temp>500)
	{
			
		smoke=ADC_Read(CH_1);
		smoke_percent=ADC_Percentage(smoke,1023);
		if(temp>500 && smoke_percent>50 && fire_flag==0)
		{
			PORTC=0x0E;
			if(flag3==0)
			{
				LCD_SetCursor(0,0);
				LCD_Clear();
				LCD_SetCursor(0,0);
				flag3=1;
			}
			LCD_WriteString("Fire");
			LCD_SetCursor(1,0);
			LCD_WriteNumber(temp/10);
			LCD_WriteChar('.');
			LCD_WriteNumber(temp%10);
			LCD_WriteChar('C');
			LCD_SetCursor(1,7);
			LCD_WriteNumber(smoke_percent);
			LCD_WriteChar('%');
			LCD_WriteString("                           ");
			fire_flag=1;
		}
		else if(smoke_percent<50 && temp>50 && fire_flag==0)
		{
		DIO_WritePin(PINC0,HIGH);
		if(flag2==0)
		{
			LCD_SetCursor(0,0);
			LCD_Clear();
			LCD_SetCursor(0,0);
			flag2=1;
			flag1=0;
		}
		LCD_WriteString("Heat");
		LCD_SetCursor(1,0);
		LCD_WriteNumber(temp/10);
		LCD_WriteChar('.');
		LCD_WriteNumber(temp%10);
		LCD_WriteChar('C');
		LCD_SetCursor(1,7);
		LCD_WriteNumber(smoke_percent);
		LCD_WriteChar('%');
		LCD_WriteString("                           ");
		}
	}
	k=KEYPAD_GetKey();
	if (k!=NO_KEY && fire_flag==1)
	{
		if(k=='c')
		{
			LCD_SetCursor(0,0);
			LCD_Clear();
			LCD_SetCursor(0,0);
			LCD_WriteString("Fire is ON");
			LCD_SetCursor(1,0);
			LCD_WriteString("Enter Stop Pass");
			flag4=0;
			num=0;
		}
		else if (k>='0' && k<='9')
		{
			if(flag4==0)
			{
				LCD_SetCursor(0,0);
				LCD_Clear();
				LCD_SetCursor(0,0);
				flag4=1;
			}
			num=num*10 +(k-'0');
			LCD_WriteChar(k);
		}
		else if(k=='=')
		{
			if(num==1182)
			{
				LCD_SetCursor(1,0);
				LCD_WriteString("Correct PassWord");
				_delay_ms(1000);
				LCD_Clear();
				LCD_SetCursor(0,0);
				LCD_WriteString("Alarm is Off");
				fire_flag=0;
				flag1=0;
				flag2=0;
				flag3=0;
				flag4=0;
				num=0;
				DIO_WritePort(PC,LOW);
	
			}
			else
			{
				LCD_SetCursor(1,0);
				LCD_WriteString("Wrong PassWord");
				_delay_ms(1000);
				LCD_Clear();
				LCD_SetCursor(0,0);
				LCD_WriteString("Fire Alrarm ON");
				LCD_SetCursor(1,0);
				LCD_WriteString("Enter Stop Pass");
				flag4=0;
				num=0;
			}
	
		}
	}
	
		
}

