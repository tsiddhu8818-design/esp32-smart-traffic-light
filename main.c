#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define CAR_RED     GPIO_NUM_25
#define CAR_YELLOW  GPIO_NUM_26
#define CAR_GREEN   GPIO_NUM_27
#define PED_RED     GPIO_NUM_32
#define PED_GREEN   GPIO_NUM_33
#define BUTTON      GPIO_NUM_4

void buzzer_on(void)
{
    ledc_timer_config_t timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_10_BIT,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = 2000,
        .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&timer);

    ledc_channel_config_t channel = {
        .gpio_num = GPIO_NUM_18,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 512,
        .hpoint = 0
    };
    ledc_channel_config(&channel);
}

void buzzer_off(void)
{
    ledc_stop(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
}

void app_main(void)
{
    gpio_config_t outputs = {
        .pin_bit_mask = (1ULL << CAR_RED) |
                        (1ULL << CAR_YELLOW) |
                        (1ULL << CAR_GREEN) |
                        (1ULL << PED_RED) |
                        (1ULL << PED_GREEN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&outputs);

    gpio_config_t input = {
        .pin_bit_mask = (1ULL << BUTTON),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&input);
    gpio_reset_pin(GPIO_NUM_18);
    gpio_set_direction(GPIO_NUM_18, GPIO_MODE_OUTPUT);

    while (1) {
        // Cars green; pedestrians red
        gpio_set_level(CAR_RED, 0);
        gpio_set_level(CAR_YELLOW, 0);
        gpio_set_level(CAR_GREEN, 1);
        gpio_set_level(PED_RED, 1);
        gpio_set_level(PED_GREEN, 0);

        int request = 0;

        // Wait 5 seconds, checking the button
        for (int i = 0; i < 50; i++) {
            if (gpio_get_level(BUTTON) == 0) {
                request = 1;
            }
            vTaskDelay(pdMS_TO_TICKS(100));
        }

        // Cars yellow; pedestrians red
        gpio_set_level(CAR_GREEN, 0);
        gpio_set_level(CAR_YELLOW, 1);
        vTaskDelay(pdMS_TO_TICKS(2000));

        // Cars red; pedestrians red during clearance
        gpio_set_level(CAR_YELLOW, 0);
        gpio_set_level(CAR_RED, 1);
        vTaskDelay(pdMS_TO_TICKS(1000));

        // If requested, allow pedestrians to cross
      if (request) {
    // Turn pedestrian red OFF and green ON
    gpio_set_level(PED_RED, 0);
    gpio_set_level(PED_GREEN, 1);

    // Start the buzzer
    buzzer_on();

    // Countdown from 5 to 1
    for (int seconds = 5; seconds >= 1; seconds--) {
        printf("Pedestrian crossing: %d seconds remaining\n", seconds);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    printf("Pedestrian crossing finished!\n");

    // Stop the buzzer
    buzzer_off();

    // Finish the crossing
    gpio_set_level(PED_GREEN, 0);
    gpio_set_level(PED_RED, 1);
       }


        // Cars green again at the next loop iteration
    }
}