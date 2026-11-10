#include <stdio.h>
#include "button.h"
#include "color.h"
#include "esp_adc/adc_oneshot.h"
#include "hal/adc_types.h"
#include "macros.h"
#include "esp_log.h"
#include "photoresistor.h"
#include "potentiometer.h"
#include "rgb_light.h"
#include "freertos/FreeRTOS.h"

static adc_oneshot_unit_handle_t s_adc_handle;
static p_button s_calibration_min_button;
static p_button s_calibration_max_button;
static p_photoresistor s_photoresistor;
static p_potentiometer s_potentiometer;
static p_rgb_light s_light;

static float s_calibration_min = 0.0f;
static float s_calibration_max = 1.0f;

void handle_calibration_min_press(p_button b) {
    s_calibration_min = photoresistor_get_light_level(s_photoresistor);
}

void handle_calibration_max_press(p_button b) {
    s_calibration_max = photoresistor_get_light_level(s_photoresistor);
}

void initialize(void) {
    gpio_install_isr_service(ESP_INTR_FLAG_EDGE);

    adc_oneshot_unit_init_cfg_t adc_unit_cfg = {
        .unit_id = ADC_UNIT
    };
    adc_oneshot_new_unit(&adc_unit_cfg, &s_adc_handle);

    s_calibration_min_button = button_init(CALIBRATION_MIN_BUTTON_PIN);
    s_calibration_max_button = button_init(CALIBRATION_MAX_BUTTON_PIN);
    button_add_handler(s_calibration_min_button, handle_calibration_min_press);
    button_add_handler(s_calibration_max_button, handle_calibration_max_press);

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
    float room_brightness = photoresistor_get_light_level(s_photoresistor);
    float color_warmness = potentiometer_get_value(s_potentiometer);
    float color_brightness = 1 - INV_LERP(s_calibration_min, s_calibration_max, room_brightness);
    color_brightness = CLAMP(color_brightness, 0.0f, 1.0f);
    color light_color = color_lerp(COOL_COLOR, WARM_COLOR, color_warmness);
    light_color = color_mult(light_color, color_brightness);
    rgb_light_set_color(s_light, light_color);
}

void app_main(void) {
    initialize();
    set_and_read_initial_values();
    vTaskDelay(pdMS_TO_TICKS(1000));
    while (true) {
        update();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
