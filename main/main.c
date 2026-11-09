#include <stdio.h>
#include "hal/adc_types.h"
#include "macros.h"
#include "esp_log.h"
#include "photoresistor.h"

static p_photoresistor s_photoresistor;

void app_main(void) {
    s_photoresistor = photoresistor_init(PHOTORESISTOR_PIN, ADC_UNIT_1, ADC_CHANNEL_6, true);
    while (1) {
        ESP_LOGI("adaptive_night_light", "%f", photoresistor_get_light_level(s_photoresistor));
    }
}
