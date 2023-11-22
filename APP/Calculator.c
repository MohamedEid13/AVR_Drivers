#include "StdTypes.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "Kaypad_Interface.h"

void Calculator_Init(void)
{
	LCD_Init();
	KEYPAD_Init();
	LCD_SetCursor(0,0);
	LCD_WriteString("  Calculator");
	LCD_SetCursor(0,0);
}

/* Global Variables */


static u8 k,op='#',flag=0,flag2=0;
u32 num1=0,num2=0;
u32 result=0;

void Calculator_Calc(void)
{
		k=KEYPAD_GetKey();
		if (k!=NO_KEY)
		{
			if(k>='0' && k<='9')
			{
				if(flag==0)
				{
					LCD_SetCursor(0,0);
					LCD_Clear();
					LCD_SetCursor(0,0);
					flag=1;
					num1=0;
				}
				
				if (op=='#')
				{
					num1=num1*10+(k -'0');
					LCD_WriteChar(k);
					
				}
				else
				{
					num2=num2*10+(k-'0');
					LCD_WriteChar(k);
					
				}
			}
			else if(k=='+'||k=='/'||k=='-'||k=='*')
			{
				op=k;
				flag=1;
				LCD_WriteChar(op);
			}
			else if(k =='=')
			{
				
				if(op=='+')
				{
					result =num1+num2;
					
				}
				else if(op=='-')
				{
					result= num1-num2;
					
				}
				else if(op=='*')
				{
					result =num1*num2;
				}
				else if(op=='/')
				{
					
					result=num1/num2;
					
				}
				LCD_ClearLine(1);
				LCD_SetCursor(1,0);
				LCD_WriteString("Result :");
				LCD_WriteNumber(result);
				num1=result;
				num2=0;
				op='#';
				flag=0;
			}
			else if(k=='c')
			{
				LCD_Clear();
				LCD_SetCursor(0,0);
				num1=0;
				num2=0;
				result=0;
				op='#';
				flag=0;
			}
		}
	}
