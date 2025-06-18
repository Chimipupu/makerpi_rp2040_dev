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
#include <Arduino.h>

/**
 * @brief アプリ初期化
 *
 */
void app_main_init(void)
{
    // 基板初期化
    pcb_init();

    led_sequential_blink(LED_LOOP_CNT);
}

/**
 * @brief アプリメイン
 *
 */
void app_main(void)
{
    led_bit_blink(LED_LOOP_CNT);
}