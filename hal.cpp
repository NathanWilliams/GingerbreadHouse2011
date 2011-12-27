#include "hal.h"

#include <avr/interrupt.h>

#include <Arduino.h>

#define LED_COUNT 42

#define PORT PORTD
#define DDR  DDRD

#define FRAMERATE 1000.0/60.0
#define LED_RATE FRAMERATE/LED_COUNT

#define CLOCK_DIV64 TCCR0B = _BV(CS01) | _BV(CS00);
#define TIMER TCNT0
#define TIMER_CLEAR  TIMER = 0;


uint8_t LED[LED_COUNT][2];
volatile bool display[LED_COUNT];
uint8_t next_led; //used during refresh

frame_done gCallback = NULL;
uint8_t callback_rate = 0;
uint8_t current_frame = 0;

void led_setup(frame_done callback, uint8_t rate)
{
  gCallback = callback;
  callback_rate = rate;
  //This setup is explicitly for a 42 LED charlieplexed array
  next_led=0;
  uint8_t count=0;
  uint8_t pin1,pin2;
  for(pin1=0;pin1<7;pin1++)
  {
    for(pin2=pin1+1;pin2<7;pin2++)
    {
      LED[count][0] = pin1;
      LED[count][1] = pin2;
      LED[count+1][0] = pin2;
      LED[count+1][1] = pin1;
      count += 2;
    }
  }
}

void _display_led(uint8_t led_num, bool on)
{
  if(!on)
  {
    DDR=0;
    PORT=0;
    return;
  }
  uint8_t pin1 = LED[led_num][0];
  uint8_t pin2 = LED[led_num][1];
  DDR  = (1<<pin1) | (1<<pin2); //pin1 & 2 as outputs
  PORT = (1<<pin1); //pin1 high, pin2 low
}

void clear_display()
{
  uint8_t i;
  for(i=0; i<LED_COUNT;++i)
  {
    display[i]=false;
  }
}

void set_led(uint8_t led_num, bool state)
{
  display[led_num] = state;
}

/*
  I need to set up the timer to count to LED_RATE
  which is ~397us
  The UNO is clocked at 16MHz, which is 62.5ns per tick.
  At no prescaler, it would need a count of 6352 ticks.
  The 8-bit timer can only count to 255, so we either need to keep count, or put a prescaler on the clock
  If we use a 64 prescaler, then "99.25" ticks would be the time we want.
  So we would want to count to 99 ticks to get the aproximate refresh rate (per LED) that we want.
  
*/

void start_timer()
{
  CLOCK_DIV64;
  OCR0B = 99; //compare reg B = 99 ticks
  TIMSK0 = _BV(OCIE0B); //enable the compare match register
  TIMER_CLEAR; //start from zero
}

ISR(TIMER0_COMPB_vect)
{
  _display_led(next_led, display[next_led]);
  next_led++;
  if(next_led >= 42)
  {
    current_frame++;
    next_led=0;
    if(current_frame >= callback_rate)
    {
      gCallback();
      current_frame = 0;
    }
  }
   TIMER_CLEAR;
}


