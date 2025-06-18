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

// CPU FIFO関連
#define CPU_FIFO_DATA_SIZE       4 // CPU FIFOのデータ長
#define CPU_FIFO_BUF_SIZE        8 // CPU FIFOのバッファサイズ
#define CPU_FIFO_DATA_INIT_MSG   0xFFFFFFFF
#define CPU_FIFO_DATA_NONE       0

typedef struct
{
    uint32_t tx_fifo_buf[CPU_FIFO_BUF_SIZE];
    uint32_t rx_fifo_buf[CPU_FIFO_BUF_SIZE];
} cpu_fifo_t;

void multi_core_cpu_tx_data(uint32_t data);
void multi_core_cpu_rx_data(cpu_fifo_t *p_data);
void cpu_core_0_init(void);
void cpu_core_1_init(void);

#endif // MULTI_CORE_CPU_HPP