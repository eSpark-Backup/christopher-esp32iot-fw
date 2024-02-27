#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "sdkconfig.h"
#include "nvs_flash.h"
#include "fauxmoESP.h"
#include "esp_netif.h"
#include "led_strip.h"
#include "driver/rmt.h"
#include "esp_system.h"             //power modes for ESP
#include "driver/gpio.h"            //referencing internal LED
#include "esp_http_server.h"
#include "protocol_examples_common.h"

#define RMT_TX_CHANNEL RMT_CHANNEL_0
#define CONFIG_EXAMPLE_RMT_TX_GPIO 18
#define CONFIG_EXAMPLE_STRIP_LED_NUMBER 10
led_strip_t *strip;
static const char *TAG = "ESP ALEXA";

fauxmoESP fauxmo;
    
void alexa()
{
	const char *func_TAG = "alexa:";

    ESP_LOGI(TAG,"%s ALEXA LOOP STARTED!", func_TAG);
    fauxmo.createServer(true);
    fauxmo.setPort(80);
    fauxmo.enable(true);

    // You can add more devices
    fauxmo.addDevice("RGB Light");

    fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value)
    {
	    const char *func_TAG = "onSetState:";

        if(device_id == 0)
        {
            ESP_LOGI(TAG,"[DEVICE_STATE] Device #%d (%s) state: %s value: %d", device_id, device_name, state ? "ON" : "OFF", value);
            if(state == true)
            {
                for (int j = 0; j < CONFIG_EXAMPLE_STRIP_LED_NUMBER; ++j) 
                {
                    // Write RGB values to strip driver
                    ESP_ERROR_CHECK(strip->set_pixel(strip, j, value, value, value));
                }
                // Flush RGB values to LEDs
                ESP_ERROR_CHECK(strip->refresh(strip, 100));
            }

            else
            {
                for (int j = 0; j < CONFIG_EXAMPLE_STRIP_LED_NUMBER; ++j) 
                {
                    // Write RGB values to strip driver
                    ESP_ERROR_CHECK(strip->set_pixel(strip, j, value, value, value));
                }
                // Flush RGB values to LEDs
                ESP_ERROR_CHECK(strip->refresh(strip, 100));
            }
        }
    });

    while(1)
    {
        fauxmo.handle();
        static unsigned long last = esp_timer_get_time()/1000ULL;
        if ((esp_timer_get_time()/1000ULL) - last > 5000)
        {
            last = esp_timer_get_time()/1000ULL;
            ESP_LOGI(TAG,"[HEAP MEMORY] Free heap: %d bytes\n", esp_get_free_heap_size());
        }
        vTaskDelay(50);
    }
}

extern "C" {void app_main();}

void app_main(void)
{
    static httpd_handle_t server = NULL;
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(example_connect());

    strip = led_strip_init(0,CONFIG_EXAMPLE_RMT_TX_GPIO,CONFIG_EXAMPLE_STRIP_LED_NUMBER);
    alexa();
}
/*void hslToRgb(float h, float s, float l, int *r, int *g, int *b) {
            float c, x, m;
            int hi;
            
            // Normalize hue to the range [0, 360)
            h = fmod(h, 360.0);
            if (h < 0) {
                h += 360.0;
            }

            // Normalize saturation and lightness to the range [0, 1]
            s /= 100.0;
            l /= 100.0;

            c = (1 - fabs(2 * l - 1)) * s;
            x = c * (1 - fabs(fmod(h / 60.0, 2) - 1));
            m = l - c / 2.0;

            if (h >= 0 && h < 60) {
                *r = (c + m) * 255;
                *g = (x + m) * 255;
                *b = m * 255;
            } else if (h >= 60 && h < 120) {
                *r = (x + m) * 255;
                *g = (c + m) * 255;
                *b = m * 255;
            } else if (h >= 120 && h < 180) {
                *r = m * 255;
                *g = (c + m) * 255;
                *b = (x + m) * 255;
            } else if (h >= 180 && h < 240) {
                *r = m * 255;
                *g = (x + m) * 255;
                *b = (c + m) * 255;
            } else if (h >= 240 && h < 300) {
                *r = (x + m) * 255;
                *g = m * 255;
                *b = (c + m) * 255;
            } else {
                *r = (c + m) * 255;
                *g = m * 255;
                *b = (x + m) * 255;
            }
        }*/