/**
 * @file app_main.hpp
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief アプリメインヘッダー
 * @version 0.1
 * @date 2025-06-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef APP_MAIN_HPP
#define APP_MAIN_HPP

#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include "pico/version.h"
#include "pico/time.h"
#include "pico/stdlib.h"
#include "hardware/clocks.h"

#define OB_BLUE_LED_FADE_MS       30
#define OB_BLUE_LED_BITFADE_MS    50
#define LED_LOOP_CNT              8

void app_main_init(void);
void app_main(void);

#endif // APP_MAIN_HPP