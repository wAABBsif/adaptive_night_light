#pragma once
#include "driver/gpio.h"

#define CLAMP(v, min, max) ((v) > (min) ? ((v) < (max) ? (v) : (max)) : (min))
#define LERP(a, b, v) (a + (b - a) * v)
#define INV_LERP(a, b, v) ((v - a) / (b - a))
#define MOVE_TO(value, dest, delta) ((value) + CLAMP(                       \
            ((dest) > (value)) ? (delta) : (-delta),                        \
            ((dest) > (value)) ? ((value) - (dest)) : ((dest) - (value)),   \
            ((dest) > (value)) ? ((dest) - (value)) : ((value) - (dest))))

#define TAG                         "adaptive_night_light"

#define ADC_UNIT                    ADC_UNIT_1

#define CALIBRATION_MIN_BUTTON_PIN  GPIO_NUM_18
#define CALIBRATION_MAX_BUTTON_PIN  GPIO_NUM_19

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

#define WARM_COLOR                  ((color){1.0, 0.0, 0.0})
#define COOL_COLOR                  ((color){0.0, 0.0, 1.0})
#define COLOR_CHANGE_RATE           (0.5f * 0.01f)
