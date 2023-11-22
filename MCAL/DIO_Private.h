#include "StdTypes.h"
#include "DIO_Interface.h"

#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

static void DIO_InitPin(DIO_Pin_types pin,DIO_PinStatus_t status);
const extern DIO_PinStatus_t  PinsStatusArray[TOTAL_PINS];


#endif /* DIO_PRIVATE_H_ */