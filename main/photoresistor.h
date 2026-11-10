#pragma once
#include <stdio.h>
#include "driver/gpio.h"
#include "esp_adc/adc_oneshot.h"
#include "hal/adc_types.h"
#include "soc/gpio_num.h"

struct photoresistor;
typedef struct photoresistor *p_photoresistor;

p_photoresistor photoresistor_init(gpio_num_t pin, adc_oneshot_unit_handle_t adc_unit_handle,
        adc_channel_t adc_channel, bool invert);
float photoresistor_get_light_level(p_photoresistor photoresistor);
