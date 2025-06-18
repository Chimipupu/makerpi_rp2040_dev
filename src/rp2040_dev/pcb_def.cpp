/**
 * @file pcb_def.cpp
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief 基板関連のアプリ
 * @version 0.1
 * @date 2025-06-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "pcb_def.hpp"
#include <Arduino.h>

static void show_single_led(uint32_t idx);
static void show_bit_led(uint32_t val);

#ifdef PCB_MAKERPI_RP2040

volatile bool g_btn0_flag = false;
volatile bool g_btn1_flag = false;

/**
 * @brief ボタン0の割り込みサービスルーチン
 * 
 */
void btn0_ISR()
{
    g_btn0_flag = true;
}

/**
 * @brief ボタン1の割り込みサービスルーチン
 * 
 */
void btn1_ISR()
{
    g_btn1_flag = true;
}

// 基板の青LEDのGPIO
const uint8_t g_ob_blue_leds[OB_LED_BIT_NUM] = {0, 1, 2, 3, 4, 5, 6, 7, 16, 17, 26, 27, 28};

// 指定したLEDだけ点灯
static void show_single_led(uint32_t idx)
{
    uint8_t i;

    for (i = 0; i < OB_LED_BIT_NUM; i++)
    {
        digitalWrite(g_ob_blue_leds[i], (i == idx) ? HIGH : LOW);
    }
}

// 13bit値をLEDに表示
static void show_bit_led(uint32_t val)
{
    uint8_t i;

    for (i = 0; i < OB_LED_BIT_NUM; i++)
    {
        digitalWrite(g_ob_blue_leds[12 - i], (val >> i) & 1);
    }
}

/**
 * @brief LEDを左右に行ったりきたり光らせる
 * 
 * @param loop_cnt 点滅回数
 */
void led_sequential_blink(uint32_t loop_cnt)
{
    uint8_t i, j;
    int8_t k;

    for (j = 0; j < loop_cnt; j++)
    {
        // 左→右
        for (k = (OB_LED_BIT_NUM - 1); k >= 0; k--)
        {
            show_single_led((uint8_t)k);
            delay(OB_LED_SEQ_MS);
        }

        // 右→左
        for (i = 0; i < OB_LED_BIT_NUM; i++)
        {
            show_single_led(i);
            delay(OB_LED_SEQ_MS);
        }
    }
}

/**
 * @brief 13bitの値をLEDに表示しながら点滅
 * 
 * @param loop_cnt 点滅回数
 */
void led_bit_blink(uint32_t loop_cnt)
{
    uint32_t val;

    // 13bitカウンタとして青LEDに表示
    for (val = 0; val <= 8191; val++)
    {
        show_bit_led(val);
        delay(OB_LED_BIT_MS);
    }
}
#endif // PCB_MAKERPI_RP2040

/**
 * @brief GPIO初期化
 * 
 */
void gpio_init(void)
{
#ifdef PCB_MAKERPI_RP2040
    uint8_t i;

    // ボタン初期化
    pinMode(OB_BTN_0, INPUT); // 基板ボタン0(GPIO20)
    pinMode(OB_BTN_1, INPUT); // 基板ボタン1(GPIO21)
    attachInterrupt(digitalPinToInterrupt(OB_BTN_0), // 割り込み
                    btn0_ISR,                        // ISR
                    FALLING);                        // Lowで割り込み
    attachInterrupt(digitalPinToInterrupt(OB_BTN_1), // 割り込み
                    btn1_ISR,                        // ISR
                    FALLING);                        // Lowで割り込み

                    // 青LED初期化
    for (i = 0; i < OB_LED_BIT_NUM; i++)
    {
        pinMode(g_ob_blue_leds[i], OUTPUT);
        digitalWrite(g_ob_blue_leds[i], LOW);
    }
#endif // PCB_MAKERPI_RP2040
}

/**
 * @brief UART初期化
 * 
 */
void uart_init(void)
{
    Serial.begin(115200);
}

/**
 * @brief ボタンのポーリング
 * 
 */
void btn_polling(void)
{
#ifdef PCB_MAKERPI_RP2040
    if (g_btn0_flag != false) {
        g_btn0_flag = false;
        led_sequential_blink(LED_LOOP_CNT);
    }

    if (g_btn1_flag != false){
        g_btn1_flag = false;
        led_bit_blink(LED_LOOP_CNT);
    }
#endif // PCB_MAKERPI_RP2040
}