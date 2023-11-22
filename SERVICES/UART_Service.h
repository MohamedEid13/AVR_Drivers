

#ifndef UART_SERVICE_H_
#define UART_SERVICE_H_

void UART_SendString(u8 *str);
void UART_ReceiveString(u8 *str);

void UART_SendNumber(u32 num);
u32 UART_ReceiveNumber(void);

u8 Endian_Check(void);
u32 Convert_Endian(u32 num);
u16 endian_convert16(u16 num);

void UART_SendStringCheckSum(char *str);
u8 UART_ReceiveStringCheckSum(u8 *str);

#endif /* UART_SERVICE_H_ */