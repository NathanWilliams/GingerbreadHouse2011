#include "groups.h"
#include <stdbool.h>

class Animation
{
  public:
    Animation(Group g) : group(g) {};
    virtual void step(uint8_t delta) = 0;
    void set_speed(uint8_t speed);
  protected:
    Group group;
    uint8_t speed;
};


class Chaser : public Animation
{
  public:
    Chaser(Group g) :Animation(g), current_led(0){};
    void set_start(uint8_t start);
    void step(uint8_t delta);
  private:
    uint8_t current_led;
};

class Twinkle : public Animation
{
  public:
    Twinkle(Group g) : Animation(g), even(false){};
    void step(uint8_t delta);
  private:
    bool even;
};

class Fill : public Animation
{
  public:
    Fill(Group g) : Animation(g), current_led(0){};
    void step(uint8_t delta);
  private:
    uint8_t current_led;
};

class Drain : public Animation
{
  public:
    Drain(Group g) : Animation(g), current_led(0){};
    void step(uint8_t delta);
  private:
    uint8_t current_led;
};
