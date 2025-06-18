/**
 * @file makerpi_rp2040.ino
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief Arduino IDE用ファイル
 * @version 0.1
 * @date 2025-06-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "app_main.hpp"
#include "multi_core_cpu.hpp"

/********** CPU Core 0 ***********/
void setup()
{
    cpu_core_0_init();
}

void loop()
{
    app_main_core_0();
}

/********** CPU Core 1 ***********/
void setup1()
{
    cpu_core_1_init();
}

void loop1()
{
    app_main_core_1();
}