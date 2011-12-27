#include "groups.h"

Group::Group(uint8_t *group, uint8_t length)
{
  this->length = length;
  this->leds = group;
}
