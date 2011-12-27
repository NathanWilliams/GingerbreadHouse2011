
#include "animations.h"
#include "groups.h"
#include "hal.h"

#define length8(x) sizeof(x)/sizeof(uint8_t) 

//LED group definitions
uint8_t tree_leds[] = {1,2,3}; //Fake numbers!
Group tree(tree_leds, length8(tree_leds));

uint8_t roof_left_leds[] = {4,5,6}; //Fake numbers
Group roof_left(roof_left_leds, length8(roof_left_leds));

uint8_t roof_right_leds[] = {7,8,9};
Group roof_right(roof_right_leds, length8(roof_right_leds));

//Animations

//simple_animation will have 3 animations running at once
#define SIMPLE_SIZE 3
Animation *simple_animation[SIMPLE_SIZE]; //An array of "Animation" pointers

enum animation_state
{
  SIMPLE,
  ANIM2,
  ETC
};

animation_state current_animation;

void create_animations();
uint8_t hack_led;
void FrameCallback()
{
  
  set_led(hack_led,true);
  digitalWrite(13,HIGH);
  hack_led++;
  if(hack_led >= 42)
  {
    hack_led = 0;
    clear_display();
  }
}

void setup()
{
  hack_led=0;
  //Serial.begin(9600);
  led_setup(&FrameCallback, 15);
  current_animation = SIMPLE;
  pinMode(13,OUTPUT);
  uint8_t i=0;
  for(i=0;i<42;i++)
  {
    set_led(i,true);
  }
  start_timer(); //This is the refresh timer, a new name would probably be a good idea!
}


void loop()
{
  /*uint8_t i=0;
  for(i=0;i<42;i++)
  {
    set_led(i,true);
    delay(100);
  }
  delay(500);
  clear_display();*/
}

void create_animations()
{
  simple_animation[0] = new Twinkle(tree);
  
  Chaser *tmp = new Chaser(roof_left);
  tmp->set_start(0);
  simple_animation[1] = tmp;
  
  tmp = new Chaser(roof_right);
  tmp->set_start(0);
  simple_animation[2] = tmp;
  
}



void step_animations(Animation *a[], uint8_t size, uint8_t delta)
{
  clear_display();
  uint8_t i;
  for(i=0;i<size;++i)
  {
    a[i]->step(delta);
  }
}

//I want this called by another timer
//So updates are decoupled from display refreshing.
void do_animations(uint8_t delta) //delta = time eleapsed since the last animation step
{
  switch(current_animation)
  {
    case SIMPLE:
      step_animations(simple_animation,SIMPLE_SIZE, delta);
      break;
    case ANIM2:
      break;
    case ETC:
      break;
  }
}






