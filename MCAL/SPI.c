
#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "SPI.h"

static void (*SPI_Fptr)(void)= NULLPTR;  //Pointer to Function

void SPI_Init(SPI_Mode_type Mode)
{
	switch(Mode)
	{
		case MASTER: SET_BIT(SPCR,MSTR);break;
		case SALVE : CLEAR_BIT(SPCR,MSTR);break;
		default:  /*Do Nothing */ break;
	}
	
	/*clock speed: system frequency divided by 16*/
	SET_BIT(SPCR,SPR0);
	CLEAR_BIT(SPCR,SPR1);

	//SPI Enable
	SET_BIT(SPCR,SPE);
}


u8 SPI_SendReceive(u8 data)
{
	 SPDR=data;
	 while(!READ_BIT(SPCR,SPIF));
	 return SPDR;
}


void SPI_SendNoBlock(u8 data)
{
	SPDR=data;
	
}

u8 SPI_ReceiveNoBlock(void)
{
	return SPDR;
}


u8 SPI_ReceivePerodic(u8 *pdata)
{
	if(READ_BIT(SPCR,SPIF))
	{
		*pdata=SPDR;
		return 1;
	}
	return 0;
		
}


void SPI_InterruptEnable(void)
{
	// Enable SPI interrupt 
	SET_BIT(SPCR,SPIE);
}


void SPI_InterruptDisable(void)
{
	// Disable SPI interrupt
	CLEAR_BIT(SPCR,SPIE);
}

void SPI_SetCallBack(void(*LocalFptr)(void))
{
	SPI_Fptr=LocalFptr;
	
}

ISR(SPI_STC_vect)
{
	if (SPI_Fptr!=NULLPTR)
	{
		SPI_Fptr();
	}
}


void SPI_SendByte(u8 data)
{
	// Send data to the SPI data register
	SPDR=data;
	// Wait until SPI data transfer is completed (interrupt flag is set)
	while(!READ_BIT(SPCR,SPIE));
}


u8 SPI_ReceiveByte(void)
{
	// Wait until SPI data transfer is completed (interrupt flag is set)
	while(!READ_BIT(SPCR,SPIF));
	return SPDR;
}

void SPI_SendString(u8 *str)
{
	u8 i=0;
	for(i=0;str[i];i++)
	{
		SPI_SendByte(str[i]);
	}
}

void SPI_ReceiveString(u8 *str)
{
	u8 i=0;
	str[i]=SPI_ReceiveByte();
	while(str[i]!='\0')
	{
		i++;
		str[i]=SPI_ReceiveByte();
	}
	str[i]='\0';
}