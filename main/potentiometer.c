#include "potentiometer.h"
#include "hal/adc_types.h"
#include "esp_adc/adc_oneshot.h"
#include "hal/adc_types.h"

struct potentiometer {
    gpio_num_t pin;
    adc_oneshot_unit_handle_t adc_unit_handle;
    adc_channel_t adc_channel;
};

p_potentiometer potentiometer_init(gpio_num_t pin, adc_oneshot_unit_handle_t adc_unit_handle,
        adc_channel_t adc_channel)
{
    p_potentiometer result = malloc(sizeof(struct potentiometer));
    result->pin = pin;
    result->adc_unit_handle = adc_unit_handle;
    result->adc_channel = adc_channel;

    gpio_config_t input_pin = {
        .pin_bit_mask = (1ULL << pin),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_NEGEDGE
    };

    gpio_config(&input_pin);

    adc_oneshot_chan_cfg_t chan_cfg = {
        .bitwidth = ADC_BITWIDTH_12,
        .atten = ADC_ATTEN_DB_12
    };
    adc_oneshot_config_channel(adc_unit_handle, adc_channel, &chan_cfg);
    
    return result;
}

float potentiometer_get_value(p_potentiometer potentiometer) {
    int result;
    adc_oneshot_read(potentiometer->adc_unit_handle, potentiometer->adc_channel, &result);
    return result / 4096.0;
}
