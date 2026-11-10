idf_component_register(SRCS
    "main.c"
    "macros.h"
    "color.h"
    "photoresistor.h" "photoresistor.c"
    "rgb_light.h" "rgb_light.c"
    INCLUDE_DIRS "."
    REQUIRES driver
    REQUIRES esp_adc
    REQUIRES esp_driver_gpio
    REQUIRES esp_driver_ledc
)
