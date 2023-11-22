#include "StdTypes.h"
#include "MemMap.h"
#include "DIO_Interface.h"
#include "DHT11.h"
#include "Utils.h"

static void Request_Signal(void);

// Function to send start signal to the DHT11 sensor
static void Request_Signal(void)
{
	DIO_InitPin2(DHT11_PORT,PIN_NUM, OUTPUT);
	DIO_WritePin(DHT11_PIN, LOW);
	_delay_ms(18);
	DIO_WritePin(DHT11_PIN, HIGH);
	_delay_us(30);
	
}


void DHT11_Init(void)
{
	DIO_InitPin2(DHT11_PORT,PIN_NUM, INPULL);
}


Error_t DHT11_ReadData(DHT11_Data* data)
{
	u8 dht_data[5] = {0};
	
	// Send start signal to the DHT11 sensor
	Request_Signal();
	
	// Switch to input mode for data reception
	DIO_InitPin2(DHT11_PORT,PIN_NUM, INPULL);
	
	// Check the response signal from the sensor
	if (DIO_ReadPin(DHT11_PIN) == LOW)
	{
		_delay_us(80);
		if (DIO_ReadPin(DHT11_PIN) == HIGH)
		{
			_delay_us(80);
			
			// Data reception
			for (u8 i = 0; i < 5; i++)
			{
				for (u8 j = 0; j < 8; j++)
				{
					while (DIO_ReadPin(DHT11_PIN) == LOW);
					_delay_us(30);
					if (DIO_ReadPin(DHT11_PIN) == HIGH)
					SET_BIT(dht_data[i], (7 - j));
					while (DIO_ReadPin(DHT11_PIN) == HIGH);
				}
			}
			
			// Checksum validation
			if ((dht_data[0] + dht_data[1] + dht_data[2] + dht_data[3]) == dht_data[4])
			{
				data->Humidity_Integral = dht_data[0];
				data->Humidity_Decimal = dht_data[1];
				data->Temperature_Integral = dht_data[2];
				data->Temperature_Decimal = dht_data[3];
				
				return OK; // Data read successfully
			}
		}
	}
	
	return NOK; // Failed to read data
}
