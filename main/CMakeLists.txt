idf_component_register(SRCS "main.c"
    "macros.h"
    "photoresistor.h" "photoresistor.c"
    INCLUDE_DIRS "."
    REQUIRES driver
    REQUIRES esp_adc
    REQUIRES esp_driver_gpio)
