#include "animations.h"
#include "hal.h"

#define Odd(x) (x&1)
#define Even(x) (!Odd(x))

void Animation::set_speed(uint8_t speed)
{
  this->speed = speed;
}

void Chaser::set_start(uint8_t start)
{
  current_led = start;
}

void Chaser::step(uint8_t delta)
{
  //TODO: use delta to control the speed of the animation
  current_led++;
  if(current_led > group.length)
    current_led = 0;
  set_led(group.leds[current_led],true);
}

void Twinkle::step(uint8_t delta)
{
  //A fast flasher which alternates LEDs
  //TODO: base this on the time delta
  //This should flash at a fast rate to work
  
  uint8_t i;
  for(i=0;i<group.length;++i)
  {
    if(even && Even(i))
    {
      set_led(group.leds[i],true);
    }
  }
  even = !even;
}


void Fill::step(uint8_t delta)
{
  uint8_t i;
  for(i=0;i<current_led;++i)
  {
    set_led(group.leds[i],true);
  }
  current_led++;
  if(current_led > group.length)
    current_led = 0;
}


void Drain::step(uint8_t delta)
{
  uint8_t i;
  for(i=current_led;i<group.length;++i)
  {
    set_led(group.leds[i],true);
  }
  current_led++;
  if(current_led > group.length)
    current_led = 0;
}
