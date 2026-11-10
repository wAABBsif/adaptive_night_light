#include <stdio.h>
#include "hal/adc_types.h"
#include "macros.h"
#include "esp_log.h"
#include "photoresistor.h"
#include "rgb_light.h"
#include "freertos/FreeRTOS.h"

static p_photoresistor s_photoresistor;
static p_rgb_light s_light;

void initialize(void) {
    s_photoresistor = photoresistor_init(PHOTORESISTOR_PIN, ADC_UNIT_1, ADC_CHANNEL_6, true);
    s_light = rgb_light_init(LIGHT_R_PIN, LIGHT_G_PIN, LIGHT_B_PIN,
            LIGHT_R_CHANNEL, LIGHT_G_CHANNEL, LIGHT_B_CHANNEL);
}

void set_and_read_initial_values(void) {
    ESP_LOGI(TAG, "Photoresistor level is: %f", photoresistor_get_light_level(s_photoresistor));
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
