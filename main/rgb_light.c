#include <stdlib.h>
#include "rgb_light.h"
#include "soc/gpio_num.h"
#include "driver/ledc.h"
#include "hal/ledc_types.h"

struct rgb_light {
    ledc_channel_t red_channel;
    ledc_channel_t green_channel;
    ledc_channel_t blue_channel;
};

p_rgb_light rgb_light_init(gpio_num_t red_pin, gpio_num_t green_pin, gpio_num_t blue_pin,
        ledc_channel_t red_channel, ledc_channel_t green_channel, ledc_channel_t blue_channel) {
    p_rgb_light result = malloc(sizeof(struct rgb_light));
    result->red_channel = red_channel;
    result->green_channel = green_channel;
    result->blue_channel = blue_channel;

    ledc_timer_config_t timer_cfg = {
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_10_BIT,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = 10000,
        .clk_cfg = LEDC_AUTO_CLK
    };

    ledc_channel_config_t red_cfg = {
        .gpio_num = red_pin,
        .channel = red_channel,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0
    };

    ledc_channel_config_t green_cfg = {
        .gpio_num = green_pin,
        .channel = green_channel,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0
    };

    ledc_channel_config_t blue_cfg = {
        .gpio_num = blue_pin,
        .channel = blue_channel,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0
    };

    ledc_timer_config(&timer_cfg);
    ledc_channel_config(&red_cfg);
    ledc_channel_config(&green_cfg);
    ledc_channel_config(&blue_cfg);

    return result;
}

void rgb_light_set_color(p_rgb_light light, color color) {
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, light->red_channel, color.r * (1 << 10));
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, light->green_channel, color.g * (1 << 10));
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, light->blue_channel, color.b * (1 << 10));

    ledc_update_duty(LEDC_HIGH_SPEED_MODE, light->red_channel);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, light->green_channel);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, light->blue_channel);
}
