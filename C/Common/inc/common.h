#ifndef COMMON_H
#define COMMON_H
#include "types.h"


#define ON 0
#define OFF 1

#define SETBIT(reg,bit)     ((*(volatile uint32_t *))reg |= (1u << bit))
#define CLEARBIT(reg,bit)   ((*(volatile uint32_t *))reg &= ~(1u << bit))

#endif