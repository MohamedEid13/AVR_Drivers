#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "EEPROM.h"

void EEPROM_Read(u16 address ,u8 *pdata)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE))
	;
	/* Set up address register */
	EEAR = address;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from data register */
	*pdata=EEDR;
}

void EEPROM_Write(u16 address,u8 data)
{
	/* wait for completion of previous write */
	while(EECR &(1<<EEWE));
	// Set up address and data registers
	EEAR=address;
	EEDR=data;
	// write logical one to EEMWE 
	EECR|=(1<<EEMWE);
	//Start EEPROM write by setting EEWE
	EECR|=(1<<EEWE);
	
}