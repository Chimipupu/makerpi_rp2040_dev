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
    Serial.printf("[Core0] App Core0 Main\r\n");
#if 1
    // (DEBUG)ダミーデータをCPU Core1に送信
    uint32_t i, dmmy;
    for(i = 0; i < CPU_FIFO_BUF_SIZE; i++) {
        dmmy = (i + 1) * 0x01010101;
        multi_core_cpu_tx_data(dmmy);
    }
#endif
    btn_polling();
    delay(1000);
}

/**
 * @brief アプリメイン Core 1
 *
 */
void app_main_core_1(void)
{
    Serial.printf("[Core1] App Core1 Main\r\n");
    cpu_fifo_rx_data_polling();
    delay(950);
}