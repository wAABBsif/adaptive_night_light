#pragma once
#include "color.h"
#include "soc/gpio_num.h"
#include "hal/ledc_types.h"

struct rgb_light;
typedef struct rgb_light *p_rgb_light;


p_rgb_light rgb_light_init(gpio_num_t red_pin, gpio_num_t green_pin, gpio_num_t blue_pin,
        ledc_channel_t red_channel, ledc_channel_t green_channel, ledc_channel_t blue_channel);
void rgb_light_set_color(p_rgb_light light, color color);
