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

extern "C"
{
    void app_main();
}

string chesult;

void solveChem(const char ga[])
{
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
}

void app_main(void)
{
    perfmon_start();
    esp_task_wdt_init(2000, false);
    esp_task_wdt_add(xTaskGetIdleTaskHandleForCPU(0));
    while (1)
    {
        for (int k = 0; k < 1000; k++)
        {
            solveChem(fuck1);
        }
        ESP_LOGI(TAG, "%s", chesult.c_str());
        esp_task_wdt_reset();
    }
}
