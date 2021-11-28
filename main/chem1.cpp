#include "esp_log.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "chem.h"
#include <string>
#include "esp_task_wdt.h"
#include "esp32_perfmon.h"
#include "freertos/semphr.h"
#include "soc/timer_group_struct.h"
#include "driver/periph_ctrl.h"
#include "driver/timer.h"
#include "esp_timer.h"
#include "freertos/task.h"
static const char *TAG = "handle";
using namespace std;

const char fuck1[] = "H2+Ca(CN)2+NaAlF4+FeSO4+MgSiO3+KI+H3PO4+PbCrO4+BrCl+CF2Cl2+SO2=PbBr2+CrCl3+MgCO3+KAl(OH)4+Fe(SCN)3+PI3+Na2SiO3+CaF2+H2O";
const char fuck2[] = "H2+O2=H2O";

int count = 0;

static TaskHandle_t chem1_task_h;
static TaskHandle_t chem2_task_h;

extern "C"
{
    void app_main();
}

static void chem2_task(void *pvParameters)
{
    while (1)
    {

        ChemEquation *fuck = new ChemEquation(fuck1);
        delete fuck;

        count++;
    }
}

static void monitor_task(void *pvParameters)
{
    while (1)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        ESP_LOGI(TAG, "count %d", count);
        count = 0;
    }
}

static void chem1_task(void *pvParameters)
{
    xTaskCreatePinnedToCore(chem2_task, "chem2", 4096, NULL, configMAX_PRIORITIES, &chem2_task_h, 0);
    xTaskCreatePinnedToCore(monitor_task, "monitor", 4096, NULL, configMAX_PRIORITIES, NULL, 0);
    while (1)
    {

        ChemEquation *fuck = new ChemEquation(fuck1);
        delete fuck;

        count++;
    }
}

esp_timer_handle_t fw_timer_handle = 0;

void fw_timer_cb(void *arg)
{
    ESP_LOGI(TAG, "count %d", count);
    count = 0;
}

void app_main(void)
{
    // esp_timer_create_args_t fw_timer =
    // {
    // 	.callback = &fw_timer_cb, 	//回调函数
    // 	.arg = NULL, 				//参数
    // 	.name = "timer1" 			//定时器名称
    // };
    // esp_err_t err = esp_timer_create(&fw_timer, &fw_timer_handle);
    // err = esp_timer_start_periodic(fw_timer_handle, 1000 * 1000);//1秒回调
    xTaskCreatePinnedToCore(chem1_task, "chem1", 4096, NULL, configMAX_PRIORITIES, &chem1_task_h, 1);
}
