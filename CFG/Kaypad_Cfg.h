
#ifndef KAYPAD_CFG_H_
#define KAYPAD_CFG_H_

#define  FIRST_OUTPUT PINB4
#define  FIRST_INPUT  PIND2



#define  ROWS  4
#define  COLS  4
const u8 KeysArray[ROWS][COLS]={
		{'b','a','l','+'},
		{'s','z','p','-'},
		{'m','n','o','*'},
		{'c','0','=','Q'},
};




#endif /* KAYPAD_CFG_H_ */