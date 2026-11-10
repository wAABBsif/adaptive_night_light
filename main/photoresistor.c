#include "photoresistor.h"
#include "esp_adc/adc_oneshot.h"
#include "hal/adc_types.h"
#include <stdlib.h>

struct photoresistor {
    gpio_num_t pin;
    adc_oneshot_unit_handle_t adc_handle;
    adc_channel_t adc_channel;
    bool invert;
};

p_photoresistor photoresistor_init(gpio_num_t pin, adc_unit_t adc_unit, adc_channel_t adc_channel,
        bool invert)
{
    p_photoresistor result = malloc(sizeof(struct photoresistor));
    result->pin = pin;
    result->adc_channel = adc_channel;
    result->invert = invert;

    gpio_config_t input_pin = {
        .pin_bit_mask = (1ULL << pin),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_NEGEDGE
    };

    gpio_config(&input_pin);
    adc_oneshot_unit_init_cfg_t init_cfg = {
        .unit_id = adc_unit
    };
    adc_oneshot_new_unit(&init_cfg, &result->adc_handle);

    adc_oneshot_chan_cfg_t chan_cfg = {
        .bitwidth = ADC_BITWIDTH_12,
        .atten = ADC_ATTEN_DB_12
    };
    adc_oneshot_config_channel(result->adc_handle, adc_channel, &chan_cfg);

    return result;
}

float photoresistor_get_light_level(p_photoresistor photoresistor) {
    int result;
    adc_oneshot_read(photoresistor->adc_handle, photoresistor->adc_channel, &result);
    if (photoresistor->invert) {
        result = 4096 - result;
    }
    return result / 4096.0;
}
