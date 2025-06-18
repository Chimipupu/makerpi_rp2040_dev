/**
 * @file multi_core_cpu.cpp
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief マルチコアCPU関連処理
 * @version 0.1
 * @date 2025-06-19
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "multi_core_cpu.hpp"
#include "pcb_def.hpp"
#include "app_main.hpp"
#include <Arduino.h>

/**
 * @brief CPU FIFOにデータを送信
 * 
 * @param data 送信データ(uint32_t)
 */
void multi_core_cpu_tx_data(uint32_t data)
{
    bool ret;

    ret = rp2040.fifo.push_nb(data);

    // 送信成功
    if (ret != false) {
        Serial.printf("[INFO]CPU FIFO TX Data: 0x%08X\r\n", data);
    // FIFOが満杯で送信失敗
    } else {
        Serial.printf("[ERR]CPU FIFO OVF!\r\n");
    }
}

/**
 * @brief CPU FIFOからデータを受信
 * 
 * @param p_data 受信データのポインタ
 */
void multi_core_cpu_rx_data(uint32_t *p_data)
{
    bool ret;

    ret = rp2040.fifo.pop_nb(p_data);

    // 受信成功
    if (ret != false) { 
        Serial.printf("[INFO]CPU FIFO RX Data: 0x%08X\r\n", *p_data);
    // FIFOが空で受信失敗
    } else {
        Serial.printf("[ERR]CPU FIFO EMPTY!\r\n");
    }
}

/********** CPU Core 0 ***********/
/**
 * @brief CPU Core 0の初期化
 * 
 */
void cpu_core_0_init(void)
{
    uint32_t dmmy = CPU_FIFO_DATA_INIT_MSG;

    // GPIO初期化
    gpio_init();

    // UART初期化
    uart_init();

    // マルチコアCPU初期化
    multi_core_cpu_tx_data(dmmy);
}

/********** CPU Core 1 ***********/
/**
 * @brief CPU Core 1の初期化
 * 
 */
void cpu_core_1_init(void)
{
    app_main_init();
}