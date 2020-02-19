
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/can.h"

#ifdef CONFIG_IDF_TARGET_ESP32
#define CHIP_NAME "ESP32"
#endif

#ifdef CONFIG_IDF_TARGET_ESP32S2BETA
#define CHIP_NAME "ESP32-S2 Beta"
#endif

#define TX_GPIO_NUM             21
#define RX_GPIO_NUM             22

static const can_timing_config_t t_config = CAN_TIMING_CONFIG_500KBITS();
static const can_filter_config_t f_config = CAN_FILTER_CONFIG_ACCEPT_ALL();
static const can_general_config_t g_config = CAN_GENERAL_CONFIG_DEFAULT(TX_GPIO_NUM, RX_GPIO_NUM, CAN_MODE_NORMAL);

void app_main(void)
{
    printf("ESP32 CAN Demo\n");
    
    //Install and start CAN driver
    ESP_ERROR_CHECK(can_driver_install(&g_config, &t_config, &f_config));
    ESP_ERROR_CHECK(can_start());
    
    for (int i = 0; i < 10; i++) {
    	printf("Sending frame %d\n",i);
        can_message_t message;
        message.identifier = 0x555;
        message.data_length_code = 4;
        message.data[0] = 1;
        message.data[1] = 2;
        message.data[2] = 3;
        message.data[3] = 4;
        ESP_ERROR_CHECK(can_transmit(&message, portMAX_DELAY));
        
        vTaskDelay(1);
    }
    
    //Stop and uninstall CAN driver
    ESP_ERROR_CHECK(can_stop());  
    ESP_ERROR_CHECK(can_driver_uninstall());
}
