#include "StdTypes.h"
#include "DIO_Interface.h"
#include "ADC_Interface.h"
#include "Sensor_Cfg.h"
#include "Sensor.h"


/* Return Temp Celeuis*10 */
u16 LM35_TempRead(void)
{
	u16 volt=ADC_ReadVolt(LM35_CH);
	u16 temp=volt; //every 10 mv equal 1 deg
	return temp;
}

u16 MPX_PressureRead(void)
{
	u16 adc,pressure;
	adc=ADC_Read(MPX4115_CH);
	pressure=(((u32)1000*(adc-55))/921)+150;
	return pressure;
}