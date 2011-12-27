#include <stdbool.h>
#include <avr/io.h>

typedef void (*frame_done) ();

void led_setup(frame_done callback, uint8_t rate);
void set_led(uint8_t led_num, bool state);
void clear_display();
void start_timer();
void _display_led(uint8_t led_num, bool on);
