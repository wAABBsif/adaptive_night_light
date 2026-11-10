#pragma once
#include "driver/gpio.h"
#include "soc/gpio_num.h"
#include <stdint.h>

struct button;
typedef struct button *p_button;

typedef void (*button_handler)(p_button b);

p_button button_init(gpio_num_t pin);
void button_add_handler(p_button b, button_handler handler);
bool button_debounce_check(p_button b);
