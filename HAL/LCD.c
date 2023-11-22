#include "StdTypes.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "LCD_Cfg.h"

#if LCD_MODE==_8_BIT
static void WriteIns(u8 Ins)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePort(LCD_PORT,Ins); // SET 5*7 & 2 line LCD
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

static void WriteData(u8 Data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePort(LCD_PORT,Data); 
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	WriteIns(SETFUNCTION);// SET 5*7 & 2 line LCD
	WriteIns(DISPLAY_ON_OFF_CONTROL); //0x0e , 0x0f
	WriteIns(DISPLAY_CLEAR); // Clear Display
	_delay_ms(1);
	WriteIns(ENTRY_MODE_SET); // Increment DDRAM ,No Shift
}
#elif LCD_MODE ==_4_BIT
static void WriteIns(u8 ins)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePin(D7,READ_BIT(ins,7));
	DIO_WritePin(D6,READ_BIT(ins,6));
	DIO_WritePin(D5,READ_BIT(ins,5));
	DIO_WritePin(D4,READ_BIT(ins,4));
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	DIO_WritePin(D7,READ_BIT(ins,3));
	DIO_WritePin(D6,READ_BIT(ins,2));
	DIO_WritePin(D5,READ_BIT(ins,1));
	DIO_WritePin(D4,READ_BIT(ins,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

static void WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePin(D7,READ_BIT(data,7));
	DIO_WritePin(D6,READ_BIT(data,6));
	DIO_WritePin(D5,READ_BIT(data,5));
	DIO_WritePin(D4,READ_BIT(data,4));

	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	DIO_WritePin(D7,READ_BIT(data,3));
	DIO_WritePin(D6,READ_BIT(data,2));
	DIO_WritePin(D5,READ_BIT(data,1));
	DIO_WritePin(D4,READ_BIT(data,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	_delay_ms(50);
	WriteIns(0x02);
	WriteIns(0x28);//5*7 2 lines
	WriteIns(DISPLAY_ON_OFF_CONTROL); //0x0e , 0x0f
	WriteIns(DISPLAY_CLEAR); // Clear Display
	_delay_ms(1);
	WriteIns(ENTRY_MODE_SET); // Increment DDRAM ,No Shift
}
#endif

void LCD_WriteChar(u8 ch)
{
	WriteData(ch);
}

void LCD_WriteString(const char *str)
{
	u8 i=0;
	for(i=0;str[i];i++){
		LCD_WriteChar(str[i]);
	}
}

void LCD_SetCursor(u8 line, u8 cell )
{
	if (line==0)
	{
		WriteIns(0x80|cell);
	}
	else if (line==1)
	{
		WriteIns(0xC0|cell);
	}
	else if(line==2)
	{
		WriteIns(0x94|cell);
	}
	else if(line==3)
	{
		WriteIns(0xD4+cell);
	}
}

void LCD_Clear(void)
{
	WriteIns(DISPLAY_CLEAR);
	_delay_ms(1);
}

void LCD_WriteNumber(s32 num)
{
	u8 str[10],i=0,j=0;
	if(num==0){
		LCD_WriteChar('0');
		return;
	}
	if(num<0){
		num=num*(-1);
		LCD_WriteChar('-');
	}
	while(num)
	{
		str[i]=num%10 +'0';
		i++;
		num=num/10;
		
	}
	for(j=i;j>0;j--)
	{
		LCD_WriteChar(str[j-1]);
	}
}

void LCD_WriteBinary(u8 num)
{
	s8 i;
	for(i=7;i>=0;i--)
	{
		LCD_WriteChar(READ_BIT(num,i)+'0');
	}
}


void LCD_ClearLoc(u8 line ,u8 cell,u8 num)
{
	u8 i=0;
	LCD_SetCursor(line,cell);
	for (i=0;i<num;i++)
	{
		LCD_WriteChar(' ');
	}
}


void LCD_WriteNumber_4D(u16 num)
{
	LCD_WriteChar(((num%10000)/1000)+'0');
	LCD_WriteChar(((num%1000)/100)+'0');
	LCD_WriteChar(((num%100)/10)+'0');
	LCD_WriteChar(((num%10)/1)+'0');
}


void LCD_CustomChar(u8 loc,u8*pattern)
{
	WriteIns(0x40|(loc*8));
	for(u8 i=0;i<8;i++)
	{
		WriteData(pattern[i]);
	}
	WriteIns(0x80);
}



void LCD_WriteHex(u8 value)
{
	u8 low, high;
	LCD_WriteString("0x");
	high=value>>4 ;
	low=value & 0x0f;
	
	if(high<10)
	{
		LCD_WriteChar(high+'0');
	}
	else{LCD_WriteChar(high-10+'A');}
		
	if(low<10)
	{
		LCD_WriteChar(low+'0');
	}
	else{LCD_WriteChar(low-10+'A');}
}

void LCD_ClearLine(u8 line)
{
	// Set the cursor to the beginning of the second line
	LCD_SetCursor(line, 0);
	
	// Write spaces to clear the second line
	for (int i = 0; i < 16; i++) {
		LCD_WriteChar(' ');
	}
}


