#include <stdio.h>
#include "esp_log.h"
#include "esp_adc/adc_oneshot.h"

#define PHOTO_ADC_CHANNEL ADC_CHANNEL_6
#define POT_ADC_CHANNEL   ADC_CHANNEL_4

void app_main(void)
{
    while (1) {
        ESP_LOGI("adaptive_night_light", "Hello World!");
        (void)PHOTO_ADC_CHANNEL;
        (void)POT_ADC_CHANNEL;
    }
}
