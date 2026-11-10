#include "button.h"
#include "esp_timer.h"
#include "esp_log.h"
#include <stdint.h>

#define DEBOUNCE_PERIOD 200 * 1000

struct button {
    gpio_num_t pin;
    int64_t previous_press_time;
    button_handler handler;
};

void button_isr_handler(void *arg) {
    p_button b = arg;
    if (!button_debounce_check(b)) {
        return;
    }

    b->handler(b);
}

p_button button_init(gpio_num_t pin) {
    p_button result = malloc(sizeof(struct button));

    gpio_config_t input_pin = {
        .pin_bit_mask = (1ULL << pin),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_NEGEDGE
    };

    gpio_config(&input_pin);

    result->pin = pin;
    result->previous_press_time = 0;
    result->handler = NULL;

    return result;
}

void button_add_handler(p_button b, button_handler handler) {
    b->handler = handler;
    gpio_isr_handler_add(b->pin, button_isr_handler, b);
}

bool button_debounce_check(p_button b) {
    int64_t now = esp_timer_get_time();
    if ((now - b->previous_press_time) <= DEBOUNCE_PERIOD) {
        return false;
    }

    b->previous_press_time = now;
    return true;
}

