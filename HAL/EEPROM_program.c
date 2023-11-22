/*****************************************************************/
/*****************************************************************/
/********************		Author: Amgad Samir		**************/
/********************		Layer: HAL				**************/
/********************		SWC: EEPROM				**************/
/********************		Version: 1.00			**************/
/********************		Date: 13-10-2020		**************/
/*****************************************************************/
/*****************************************************************/

#include "StdTypes.h"
#include "Utils.h"
#include "TWI_interface.h"

#include "EEPROM_interface.h"
#include "EEPROM_config.h"
#include "EEPROM_private.h"

void EEPROM_voidSendDataByte(u16 Copy_u16LocationAddress, u8 Copy_u8DataByte)
{
	u8 Local_u8AddressPacket;

	Local_u8AddressPacket = EEPROM_FIXED_ADDRESS | (A2_CONNECTION <<2) | (u8)(Copy_u16LocationAddress >>8);


	TWI_SendStartCondition();

	TWI_SendSlaveAddressWithWrite(Local_u8AddressPacket);

	TWI_MasterWriteDataByte((u8)Copy_u16LocationAddress);

	TWI_MasterWriteDataByte(Copy_u8DataByte);

	TWI_SendStopCondition();

	_delay_ms(10);
}

u8 EEPROM_u8ReadDataByte(u16 Copy_u16LocationAddress)
{
	u8 Local_u8AddressPacket, Local_u8Data;

	Local_u8AddressPacket = EEPROM_FIXED_ADDRESS | (A2_CONNECTION <<2) | (u8)(Copy_u16LocationAddress >>8);
	TWI_SendStartCondition();

	TWI_SendSlaveAddressWithWrite(Local_u8AddressPacket);

	TWI_MasterWriteDataByte((u8)Copy_u16LocationAddress);

	TWI_SendRepeatedStart();

	TWI_SendSlaveAddressWithRead(Local_u8AddressPacket);
	
	TWI_MasterReadDataByte(&Local_u8Data);

	TWI_SendStopCondition();

	return Local_u8Data;
}
