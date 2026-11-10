#pragma once
#include <stdio.h>
#include "driver/gpio.h"
#include "hal/adc_types.h"
#include "soc/gpio_num.h"

struct potentiometer;
typedef struct potentiometer *p_potentiometer;

p_potentiometer potentiometer_init();
float potentiometer_get_value(p_potentiometer potentiometer);
