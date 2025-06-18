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
#include <Arduino.h>

static void showSingleLED(uint8_t idx);
static void showBits(uint8_t val);
static void led_sequential_blink(uint32_t loop_cnt);

// 基板の青LEDのGPIO
const uint8_t g_ob_blue_leds[13] = {0, 1, 2, 3, 4, 5, 6, 7, 16, 17, 26, 27, 28};

// 指定したLEDだけ点灯
static void showSingleLED(uint8_t idx)
{
    uint8_t i;

    for (i = 0; i < 13; i++)
    {
        digitalWrite(g_ob_blue_leds[i], (i == idx) ? HIGH : LOW);
    }
}

// 13bit値をLEDに表示
static void showBits(uint8_t val)
{
    uint8_t i;

    for (i = 0; i < 13; i++)
    {
        digitalWrite(g_ob_blue_leds[12 - i], (val >> i) & 1);
    }
}

// LEDを左右に行ったりきたり光らせる
static void led_sequential_blink(uint32_t loop_cnt)
{
    uint8_t i, j;
    int8_t k;

    for (j = 0; j < loop_cnt; j++)
    {
        // 左→右（インデックス12→0）
        for (k = 12; k >= 0; k--)
        {
            showSingleLED((uint8_t)k);
            delay(OB_BLUE_LED_FADE_MS);
        }

        // 右→左（インデックス0→12）
        for (i = 0; i < 13; i++)
        {
            showSingleLED(i);
            delay(OB_BLUE_LED_FADE_MS);
        }
    }
}

/**
 * @brief アプリ初期化
 *
 */
void app_main_init(void)
{
    uint8_t i;

    // GPIO初期化
    for (i = 0; i < 13; i++)
    {
        pinMode(g_ob_blue_leds[i], OUTPUT);
        digitalWrite(g_ob_blue_leds[i], LOW);
    }

    led_sequential_blink(LED_LOOP_CNT);
}

/**
 * @brief アプリメイン
 *
 */
void app_main(void)
{
    uint32_t val;

    // 13bitカウンタとして青LEDに表示
    for (val = 0; val <= 8191; val++)
    {
        showBits(val);
        delay(OB_BLUE_LED_BITFADE_MS);
    }
}