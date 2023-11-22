

#ifndef SPI_H_
#define SPI_H_

typedef enum {
	SALVE,
	MASTER
	}SPI_Mode_type;
	
void SPI_Init(SPI_Mode_type Mode);

u8   SPI_SendReceive(u8 data);

void SPI_SendNoBlock(u8 data);
u8   SPI_ReceiveNoBlock(void);

u8   SPI_ReceivePerodic(u8 *pdata);

void SPI_InterruptEnable(void);
void SPI_InterruptDisable(void);
void SPI_SetCallBack(void(*LocalFptr)(void));

void SPI_SendByte(u8 data);
u8   SPI_ReceiveByte(void);

void SPI_SendString(u8 *str);
void SPI_ReceiveString(u8 *str);


#endif /* SPI_H_ */