/**
 * @file multi_core_cpu.hpp
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief マルチコアCPU関連のヘッダー
 * @version 0.1
 * @date 2025-06-19
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef MULTI_CORE_CPU_HPP
#define MULTI_CORE_CPU_HPP

#include <stdint.h>

#define CPU_FIFO_DATA_INIT_MSG    0xFFFFFFFF

void multi_core_cpu_tx_data(uint32_t data);
void multi_core_cpu_rx_data(uint32_t *p_data);
void cpu_core_0_init(void);
void cpu_core_1_init(void);

#endif // MULTI_CORE_CPU_HPP