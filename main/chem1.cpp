#include "esp_log.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "chem.h"
#include <string>
#include "esp_task_wdt.h"
#include "esp32_perfmon.h"

static const char *TAG = "handle";
using namespace std;

const char fuck1[] = "H2+Ca(CN)2+NaAlF4+FeSO4+MgSiO3+KI+H3PO4+PbCrO4+BrCl+CF2Cl2+SO2=PbBr2+CrCl3+MgCO3+KAl(OH)4+Fe(SCN)3+PI3+Na2SiO3+CaF2+H2O";
const char fuck2[] = "H2+O2=H2O";

int lock = 0;

static TaskHandle_t chem1_task_h;
static TaskHandle_t chem2_task_h;

extern "C"
{
    void app_main();
}

string chesult;

void solveChem(const char ga[])
{
    if (lock == 0)
    {
        lock = 1;
        setChem(ga);
        toMatrixBaby();
        initMatrix(baby, myRow, myColume);
        coefficientArray();
        chesult = "";
        for (int k = 0; k < myColume; k++)
        {
            chesult += to_string(coefficientNum[k]);
            chesult += "  ";
        }

        freeMatrix();
        freeChem();
        lock = 0;
    }
}

static void chem1_task(void *pvParameters)
{
    while (1)
    {
        vTaskDelay(10);

        for (int k = 0; k < 100; k++)
        {

            solveChem(fuck1);
        }

        int x = xPortGetCoreID();
        ESP_LOGI(TAG, "%s    fuck  %d", chesult.c_str(), x);
    }
}


static void chem2_task(void *pvParameters)
{
    while (1)
    {

        for (int k = 0; k < 100; k++)
        {

            solveChem(fuck1);
        }
        int x = xPortGetCoreID();
        ESP_LOGI(TAG, "%s    fuck  %d", chesult.c_str(), x);
    }

    vTaskDelay(10);
}


void app_main(void)
{
    perfmon_start();
    xTaskCreatePinnedToCore(chem1_task, "chem1", 4096, NULL, 1, &chem1_task_h, 0);
    xTaskCreatePinnedToCore(chem2_task, "chem2", 4096, NULL, 2, &chem2_task_h, 1);
}
