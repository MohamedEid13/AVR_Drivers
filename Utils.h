
#ifndef UTILS_H_
#define UTILS_H_


#define  READ_BIT(REG,BIT)  ((REG>>BIT)&1)
#define  CLEAR_BIT(REG,BIT)  (REG=REG&(~(1<<BIT)))
#define  TOGGLE_BIT(REG,BIT)  (REG=REG^(1<<BIT))
#define  SET_BIT(REG,BIT)     (REG=REG|(1<<BIT))


#define  F_CPU 8000000
#include <util/delay.h>


#endif /* UTILS_H_ */