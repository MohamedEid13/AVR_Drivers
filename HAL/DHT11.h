


#ifndef DHT11_H_
#define DHT11_H_

/****** PIN Configuration ***************/
#define DHT11_PIN PINC0
#define DHT11_PORT PC
#define PIN_NUM    0
/*************************************/

typedef struct
{
	u8 Humidity_Integral;
	u8 Humidity_Decimal;
	u8 Temperature_Integral;
	u8 Temperature_Decimal;
}DHT11_Data;


/***********Functions************/

void DHT11_Init(void);
Error_t DHT11_ReadData(DHT11_Data* data);




#endif /* DHT11_H_ */