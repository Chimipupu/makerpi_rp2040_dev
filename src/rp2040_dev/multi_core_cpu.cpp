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

static cpu_fifo_t s_cpu_fifo_t;

/**
 * @brief CPU FIFOにデータを送信
 * 
 * @param data 送信データ(uint32_t)
 */
void multi_core_cpu_tx_data(uint32_t data)
{
    bool ret;

    ret = rp2040.fifo.push_nb(data);

#if 1
    // 送信成功
    if (ret != false) {
        // Serial.printf("[INFO]CPU FIFO TX Data: 0x%08X\r\n", data);
    // FIFOが満杯で送信失敗
    } else {
        // Serial.printf("[ERR]CPU FIFO FULL!\r\n");
    }
#endif
}

/**
 * @brief CPU FIFOからデータを受信
 * @param p_data cpu_fifo_tのポインタ
 */
void multi_core_cpu_rx_data(cpu_fifo_t *p_data)
{
    uint8_t i;
    uint8_t fifo_data_num;
    bool ret;

    fifo_data_num = rp2040.fifo.available();

    if (fifo_data_num > 0) {
        for(i = 0; i < fifo_data_num; i++)
        {
            ret = rp2040.fifo.pop_nb(&p_data->rx_fifo_buf[i]);
#if 1
            // 受信成功
            if (ret != false) {
                Serial.printf("[INFO]CPU FIFO %d RX Data: 0x%08X\r\n", i, p_data->rx_fifo_buf[i]);
            // FIFOが空で受信失敗
            } else {
                Serial.printf("[ERR]CPU FIFO EMPTY!\r\n");
                break;
            }
#endif
        }
    }
}

/**
 * @brief CPU FIFOのデータをポーリング
 * 
 */
void cpu_fifo_rx_data_polling(void)
{
    multi_core_cpu_rx_data(&s_cpu_fifo_t);
}

/********** CPU Core 0 ***********/
/**
 * @brief CPU Core 0の初期化
 * 
 */
void cpu_core_0_init(void)
{
    uint32_t i, dmmy;

    // GPIO初期化
    gpio_init();

    // UART初期化
    uart_init();

    // マルチコアCPU初期化
    // (DEBUG)ダミーデータをCPU Core1に送信
    for(i = 0; i < CPU_FIFO_BUF_SIZE; i++) {
        dmmy = (i + 1) * 0x01010101;
        multi_core_cpu_tx_data(dmmy);
    }
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