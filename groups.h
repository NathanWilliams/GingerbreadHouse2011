#ifndef _GROUPS
#define _GROUPS
#include <avr/io.h>

class Group
{
  public:
    Group(uint8_t *group, uint8_t length);
    
    uint8_t length;
    uint8_t *leds;
};

#endif //_GROUPS
