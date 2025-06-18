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
    uint32_t i, dmmy;

    Serial.printf("[Core0] App Main\r\n");
    for(i = 0; i < CPU_FIFO_BUF_SIZE; i++) {
        dmmy = (i + 1) * 0x01010101; // ダミーデータ生成
        multi_core_cpu_tx_data(dmmy);
    }

    btn_polling();
    delay(1000);
}

/**
 * @brief アプリメイン Core 1
 *
 */
void app_main_core_1(void)
{
    cpu_fifo_t fifo_data;

    Serial.printf("[Core1] App Main\r\n");
    multi_core_cpu_rx_data(&fifo_data);
    delay(800);
}