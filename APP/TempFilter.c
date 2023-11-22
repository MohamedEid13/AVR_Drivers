#include "StdTypes.h"
#include "Sensor.h"

static u16 tempFiltered;
static u16 tempUnFiltered;

void TEMPFilter_Init(void)
{
	tempUnFiltered=LM35_TempRead();
	tempFiltered=tempUnFiltered;
	
}
void TEMPFilter_Runnble(void)
{
	static u8 i;
	static u16 arr[10];
	u32 tempSum=0;
	arr[i]=LM35_TempRead();
	i++;
	if(i=10)
	{
		i=0;
	}
	for(u8 j=0;j<10;j++)
	{
		tempSum+=arr[j];
	}
	tempFiltered=tempSum/10;
	
}
u16 TEMPFilter_Getter(void)
{
	return tempFiltered;
}