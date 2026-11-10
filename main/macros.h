#pragma once
#include "driver/gpio.h"

#define TAG                         "adaptive_night_light"

#define ADC_UNIT                    ADC_UNIT_1

#define PHOTORESISTOR_PIN           GPIO_NUM_34
#define PHOTORESISTOR_ADC_CHANNEL   ADC_CHANNEL_6

#define LIGHT_R_PIN                 GPIO_NUM_25
#define LIGHT_G_PIN                 GPIO_NUM_26
#define LIGHT_B_PIN                 GPIO_NUM_27
#define LIGHT_R_CHANNEL             LEDC_CHANNEL_0
#define LIGHT_G_CHANNEL             LEDC_CHANNEL_1
#define LIGHT_B_CHANNEL             LEDC_CHANNEL_2

#define POTENTIOMETER_PIN           GPIO_NUM_32
#define POTENTIOMETER_ADC_CHANNEL   ADC_CHANNEL_4
