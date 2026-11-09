#include <stdio.h>
#include "macros.h"
#include "esp_log.h"
#include "esp_adc/adc_oneshot.h"

void app_main(void)
{
    while (1) {
        ESP_LOGI("adaptive_night_light", "Hello World!");
        (void)PHOTO_ADC_CHANNEL;
        (void)POT_ADC_CHANNEL;
    }
}
