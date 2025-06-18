/**
 * @file app_main.cpp
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief アプリメイン
 * @version 0.1
 * @date 2025-06-18
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "app_main.hpp"
#include "pcb_def.hpp"
#include "multi_core_cpu.hpp"
#include <Arduino.h>

/**
 * @brief アプリ初期化
 *
 */
void app_main_init(void)
{
    // NOP
}

/**
 * @brief アプリメイン Core 0
 *
 */
void app_main_core_0(void)
{
    uint32_t dmmy = 0xFFFFFFFF;

    Serial.printf("[Core0] App Main\r\n");
    multi_core_cpu_tx_data(dmmy);
    btn_polling();
    delay(1000);
}

/**
 * @brief アプリメイン Core 1
 *
 */
void app_main_core_1(void)
{
    uint32_t fifo_data = 0;

    Serial.printf("[Core1] App Main\r\n");
    multi_core_cpu_rx_data(&fifo_data);
    delay(2000);
}