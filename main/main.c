#include <stdio.h>
#include "esp_adc/adc_oneshot.h"
#include "hal/adc_types.h"
#include "macros.h"
#include "esp_log.h"
#include "photoresistor.h"
#include "potentiometer.h"
#include "rgb_light.h"
#include "freertos/FreeRTOS.h"

static adc_oneshot_unit_handle_t s_adc_handle;
static p_photoresistor s_photoresistor;
static p_potentiometer s_potentiometer;
static p_rgb_light s_light;

void initialize(void) {
    adc_oneshot_unit_init_cfg_t adc_unit_cfg = {
        .unit_id = ADC_UNIT
    };
    adc_oneshot_new_unit(&adc_unit_cfg, &s_adc_handle);
    s_photoresistor = photoresistor_init(PHOTORESISTOR_PIN, s_adc_handle,
            PHOTORESISTOR_ADC_CHANNEL, true);
    s_potentiometer = potentiometer_init(POTENTIOMETER_PIN, s_adc_handle,
            POTENTIOMETER_ADC_CHANNEL);
    s_light = rgb_light_init(LIGHT_R_PIN, LIGHT_G_PIN, LIGHT_B_PIN,
            LIGHT_R_CHANNEL, LIGHT_G_CHANNEL, LIGHT_B_CHANNEL);
}

void set_and_read_initial_values(void) {
    ESP_LOGI(TAG, "Photoresistor level is: %f", photoresistor_get_light_level(s_photoresistor));
    ESP_LOGI(TAG, "Potentiometer value is: %f", potentiometer_get_value(s_potentiometer));
    rgb_light_set_color(s_light, WHITE);
}

void update(void) {
}

void app_main(void) {
    initialize();
    set_and_read_initial_values();
    vTaskDelay(pdMS_TO_TICKS(1000));
    while (1) {
        update();
    }
}
