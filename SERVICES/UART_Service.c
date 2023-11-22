
#include "StdTypes.h"
#include "UART.h"
#include "UART_Service.h"

void UART_SendString(u8 *str)
{
	u8 i=0;
	for(i=0;str[i];i++)
	{
		UART_Send(str[i]);
	}
}

void UART_ReceiveString(u8 *str)
{
	u8 i=0;
	str[i]=UART_Receive();
	for (;str[i]!=13;)
	{
		i++;
		str[i]=UART_Receive();
	}
	str[i]=0;
}

void UART_SendNumber(u32 num)
{
	UART_Send((u8)num);
	UART_Send((u8)num>>8);
	UART_Send((u8)num>>16);
	UART_Send((u8)num>>24);
	/* // Another Sol
	u8 *p=&num;
	UART_Send(p[0]);
	UART_Send(p[1]);
	UART_Send(p[2]);
	UART_Send(p[3]);
	*/
}

u32 UART_ReceiveNumber(void)
{
	u32 num;
	u8 b0=UART_Receive();
	u8 b1=UART_Receive();
	u8 b2=UART_Receive();
	u8 b3=UART_Receive();
	num=(u32)b0|((u32)b1<<8)|((u32)b2<<16)|((u32)b3<<24);
	
	/* //Another Sol 
	u8 *p=&num;
	p[0]=UART_Receive();
	p[1]=UART_Receive();
	p[2]=UART_Receive();
	p[3]=UART_Receive();
	*/
	return num;
}

u8 Endian_Check(void)
{
	u32 num=1;
	u8*p=&num;
	if(*p==1)
	{
		return 1; //Little Endian System
	}
	else
	{
		return 0; //Big Endian System 
	}
}

u32 Convert_Endian(u32 num)
{
	num=(num>>24)|(num<<24)|((num>>8)&0x0000FF00)|((num<<8)&0x00FF0000);
	
	/*
	//Another Solution
	u8 *p=&num;
	u8 temp=0;
	temp=p[0];
	p[0]=p[3];
	p[3]=temp;
	temp=p[1];
	p[1]=p[2];
	p[2]=temp;
	*/
	return num;
}




u16 endian_convert16(u16 num)
{
	num=num>>8|num<<8;
	return num;
	
}

/* Protocol for Check sum */
/* Length    data         check_sum */
/* 1 byte   0:255 byte    2 byte  */

void UART_SendStringCheckSum(char *str)
{
	u8 i;
	u16 sum=0;
	u8 len;
	for (i=0;str[i];i++)
	{
		sum=sum+str[i];
	}
	len=i;
	UART_Send(len);
	for (i=0;str[i];i++)
	{
		UART_Send(str[i]);
	}
	UART_Send((u8)sum);
	UART_Send((u8)(sum>>8));
}


u8 UART_ReceiveStringCheckSum(u8 *str)
{
	u8 len,byte0,byte1,i;
	u16 SumCalc=0,SumReceived;
	// Receive Length
	len=UART_Receive();
	for(i=0;i<len;i++)
	{
		// Receive Data
		str[i]=UART_Receive();
		SumCalc+=str[i];
	}
	// Receive check sum
	byte0=UART_Receive();
	byte1=UART_Receive();
	SumReceived=(u16)byte0|(u16)(byte1<<8);
	if(SumCalc==SumReceived)
	{
		return 1; // data is oK
	}
	else
	{
		return 0;
	}
}


/* // Interview question answer in session 57  
void UART_SendStringRunnable(void)
{
	static u8 i=0;
  if (flag==1)
  {
	  if (TXStr[i]!=0)
	  {
		  UART_SendNoBlock(TXStr[i]);
		  i++;
	  }
	  else 
	  {
		  i=0;
	  }
	  flag=0;
  }

}


UART_SendStringPeroidic(u8*str)
{
	TXStr=str;
}
*/