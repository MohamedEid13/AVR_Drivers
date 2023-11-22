#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "Kaypad_Interface.h"
#include "Converter.h"

static u16 Convert_BinToDec(u16 bin)
{
	u16 dec=0,rem=0,i=0;
	while(bin!=0)
	{
		rem=bin%10;
		bin=bin/10;
		dec=dec+rem*(1<<i);
		i++;
	}
	return dec;
}

static u16 Convert_HextoDec(u8* hex)
{
	u16 dec=0;
	u8 i=0;
	while(hex[i]!='\0')
	{
		if(hex[i]>='0' && hex[i]<='9')
		{
			dec=dec*16+hex[i]-'0';
		}
		else if(hex[i]>='A' && hex[i]<='F')
		{
			dec=dec*16+hex[i]-'A'+10;
		}
		else if(hex[i]>='a' && hex[i]<='f')
		{
			dec=dec*16+hex[i]-'a'+10;
		}
		i++;
	}
	return dec;
}



void Converter_Init(void)
{
	DIO_Init();
	LCD_Init();
	KEYPAD_Init();	LCD_WriteString("Converted By");
	LCD_SetCursor(1,0);
	LCD_WriteString("Mohamed Eid");
}


static u8 k=0,flag=0,flag1=0,Mode=55,count_D=0,count_H=0,count_B=0;
static u16 num=0,Bin2Dec=0,Hex2Dec=0;

void Converter_Start()
{
	k=KEYPAD_GetKey();
	if (k!=NO_KEY)
	{
		if (((k>='0' && k<='9')|(k>='A' && k<='Z')) && flag==2)
		{
			if (Mode==HEX_BIN || Mode==HEX_DEC)
			{
				if(flag1==0)
				{
					LCD_SetCursor(0,2);
					LCD_WriteString("            ");
					LCD_SetCursor(0,2);
					LCD_WriteString("0X");
					flag1=1;
					
				}
				
				LCD_WriteChar(k);
				if(k>='0' && k<='9')
				{
					Hex2Dec=Hex2Dec*16+k-'0';
				}
				else if(k>='A' && k<='F')
				{
					Hex2Dec=Hex2Dec*16+k-'A'+10;
				}
				
				
			}
			else{
				if(flag1==0)
				{
					LCD_SetCursor(0,2);
					LCD_WriteString("            ");
					LCD_SetCursor(0,2);
					flag1=1;
					
				}
				num=num*10+(k-'0');
				LCD_WriteChar(k);
			}
		}
		else
		{
			if(k=='1' && flag!=2)
			{
				LCD_Clear();
				LCD_SetCursor(0,0);
				LCD_WriteString("Convert Dec to");
				LCD_SetCursor(1,0);
				LCD_WriteString("1.D  2.B  3.H");
				flag+=1;
				count_D++;
				if(count_D==2)
				{
					Mode=DEC_DEC;
					LCD_Clear();
					LCD_WriteString("Same Value");
				}
				else if(count_D==1 && count_B==1)
				{
					Mode=BIN_DEC;
					LCD_Clear();
					LCD_SetCursor(0,0);
					LCD_WriteString("B:");
					LCD_SetCursor(1,0);
					LCD_WriteString("D:");
					
					
				}
				else if(count_D==1 && count_H==1)
				{
					Mode=HEX_DEC;
					LCD_Clear();
					LCD_SetCursor(0,0);
					LCD_WriteString("H:");
					LCD_SetCursor(1,0);
					LCD_WriteString("D:");
				}
			}
			else if(k=='2' && flag!=2)
			{
				LCD_Clear();
				LCD_SetCursor(0,0);
				LCD_WriteString("Convert Bin to");
				LCD_SetCursor(1,0);
				LCD_WriteString("1.D  2.B  3.H");
				flag+=1;
				count_B++;
				if(count_B==2)
				{
					Mode=BIN_BIN;
					LCD_Clear();
					LCD_WriteString("Same Value");
				}
				else if(count_B==1 && count_D==1)
				{
					Mode=DEC_BIN;
					LCD_Clear();
					LCD_SetCursor(0,0);
					LCD_WriteString("D:");
					LCD_SetCursor(1,0);
					LCD_WriteString("B:");
				}
				else if(count_B==1 && count_H==1)
				{
					Mode=HEX_BIN;
					LCD_Clear();
					LCD_SetCursor(0,0);
					LCD_WriteString("H:");
					LCD_SetCursor(1,0);
					LCD_WriteString("B:");
				}
			}
			else if(k=='3' && flag!=2)
			{
				LCD_Clear();
				LCD_SetCursor(0,0);
				LCD_WriteString("Convert Hex to");
				LCD_SetCursor(1,0);
				LCD_WriteString("1.D  2.B  3.H");
				flag+=1;
				count_H++;
				if(count_H==2)
				{
					Mode=HEX_HEX;
					LCD_Clear();
					LCD_WriteString("Same Value");
				}
				else if(count_H==1 && count_D==1)
				{
					Mode=DEC_HEX;
					LCD_Clear();
					LCD_SetCursor(0,0);
					LCD_WriteString("D:");
					LCD_SetCursor(1,0);
					LCD_WriteString("H:");
				}
				else if(count_H==1 && count_B==1)
				{
					Mode=BIN_HEX;
					LCD_Clear();
					LCD_SetCursor(0,0);
					LCD_WriteString("B:");
					LCD_SetCursor(1,0);
					LCD_WriteString("H:");
				}
			}
		}
		if(k=='=')
		{
			switch (Mode)
			{
				case HEX_HEX:
				LCD_Clear();
				LCD_WriteString("Same Value");
				break;
				case DEC_DEC:
				LCD_Clear();
				LCD_WriteString("Same Value");
				break;
				case BIN_BIN:
				LCD_Clear();
				LCD_WriteString("Value is the same");
				break;
				case DEC_HEX:
				LCD_SetCursor(1,2);
				LCD_WriteString("          ");
				LCD_SetCursor(1,2);
				LCD_WriteHex(num);
				flag1=0;
				num=0;
				break;
				case DEC_BIN:
				LCD_SetCursor(1,2);
				LCD_WriteString("          ");
				LCD_SetCursor(1,2);
				LCD_WriteBinary(num);
				flag1=0;
				num=0;
				break;
				case BIN_DEC:
				LCD_SetCursor(1,2);
				LCD_WriteString("          ");
				LCD_SetCursor(1,2);
				Bin2Dec=Convert_BinToDec(num);
				LCD_WriteNumber(Bin2Dec);
				flag1=0;
				num=0;
				Bin2Dec=0;
				break;
				case BIN_HEX:
				LCD_SetCursor(1,2);
				LCD_WriteString("          ");
				LCD_SetCursor(1,2);
				Bin2Dec=Convert_BinToDec(num);
				LCD_WriteHex(Bin2Dec);
				flag1=0;
				num=0;
				Bin2Dec=0;
				break;
				case HEX_DEC:
				LCD_SetCursor(1,2);
				LCD_WriteString("          ");
				LCD_SetCursor(1,2);
				LCD_WriteNumber(Hex2Dec);
				flag1=0;
				num=0;
				Hex2Dec=0;
				break;
				case HEX_BIN:
				LCD_SetCursor(1,2);
				LCD_WriteString("          ");
				LCD_SetCursor(1,2);
				LCD_WriteBinary(Hex2Dec);
				flag1=0;
				num=0;
				Hex2Dec=0;
				break;
				
			}
			
		}
		if(k=='c')
		{
			LCD_Clear();
			LCD_SetCursor(0,0);
			LCD_WriteString("Convert From ");
			LCD_SetCursor(1,0);
			LCD_WriteString("1.D  2.B  3.H");
			flag=0;
			flag1=0;
			num=0;
			Mode=55;
			count_B=0;
			count_D=0;
			count_H=0;
		}
	}
	
}