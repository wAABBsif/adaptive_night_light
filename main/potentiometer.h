#pragma once
#include <stdio.h>
#include "driver/gpio.h"
#include "esp_adc/adc_oneshot.h"
#include "hal/adc_types.h"
#include "soc/gpio_num.h"

struct potentiometer;
typedef struct potentiometer *p_potentiometer;
p_potentiometer potentiometer_init(gpio_num_t pin, adc_oneshot_unit_handle_t adc_unit_handle,
        adc_channel_t adc_channel);
float potentiometer_get_value(p_potentiometer potentiometer);
