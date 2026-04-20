/*
 * Copyright (c) 2024 Nuvoton Technology Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Compatibility header to bridge M451 BSP API differences with M480 BSP
 * that the Zephyr drivers expect.
 */

#ifndef M45X_COMPAT_H_
#define M45X_COMPAT_H_

/* GPIO: M451 does not have PUSEL register (pull-up/pull-down selection).
 * Define compatibility macros. PUSEL writes go to reserved register space
 * at offset 0x30 in GPIO block - harmless on M451.
 */
#ifndef GPIO_PUSEL_DISABLE
#define GPIO_PUSEL_DISABLE  0x0UL
#define GPIO_PUSEL_PULL_UP  0x1UL
#define GPIO_PUSEL_PULL_DOWN 0x2UL
#endif

/* UART: M451 BSP uses UART_SetLine_Config (underscore), M480 uses UART_SetLineConfig */
#ifndef UART_SetLineConfig
#define UART_SetLineConfig UART_SetLine_Config
#endif

/* UART: M451 does not have SWBEIEN (single-wire bit error interrupt) */
#ifndef UART_INTEN_SWBEIEN_Msk
#define UART_INTEN_SWBEIEN_Msk 0
#endif

/* CLK: M451 BSP does not have CLK_GetModuleClockDivider or CLK_GetModuleClockSource.
 * Provide static inline implementations.
 * Module index encoding (from numaker_m45x_clock.h):
 *   [31:28] = CLKDIV mask width (unused)
 *   [27:20] = CLKDIV mask
 *   [19:18] = reserved
 *   [17:16] = CLKSEL register index (0=CLKSEL0, 1=CLKSEL1, 2=CLKSEL2, 3=CLKSEL3)
 *   [15:14] = CLKDIV register index (0=CLKDIV0, 1=CLKDIV1)
 *   [13:10] = CLKDIV bit position
 *   [9:8]   = CLKSEL mask width (in bits-1 form)
 *   [7:4]   = CLKSEL bit position
 *   [3:2]   = AHBCLK/APBCLK register index
 *   [1:0]   = AHBCLK/APBCLK bit position (partial)
 */
#ifndef CLK_GetModuleClockDivider

static inline uint32_t CLK_GetModuleClockDivider(uint32_t u32ModuleIdx)
{
    uint32_t u32DivTbl[] = {0x0, 0x4};  /* CLKDIV0, CLKDIV1 offsets */
    uint32_t u32div_sel, u32div_pos, u32div_msk;

    u32div_sel = (u32ModuleIdx >> 14) & 0x3;
    u32div_pos = (u32ModuleIdx >> 10) & 0xF;
    u32div_msk = (u32ModuleIdx >> 20) & 0xFF;

    if (u32div_msk) {
        uint32_t u32DivReg = *(volatile uint32_t *)((uint32_t)&CLK->CLKDIV0 + u32DivTbl[u32div_sel]);
        return (u32DivReg >> u32div_pos) & u32div_msk;
    }

    return 0;
}

#endif /* CLK_GetModuleClockDivider */

#ifndef CLK_GetModuleClockSource

static inline uint32_t CLK_GetModuleClockSource(uint32_t u32ModuleIdx)
{
    uint32_t u32SelTbl[] = {0x0, 0x4, 0x8, 0xC};  /* CLKSEL0-3 offsets */
    uint32_t u32sel_sel, u32sel_pos, u32sel_msk;

    u32sel_sel = (u32ModuleIdx >> 16) & 0x3;
    u32sel_pos = (u32ModuleIdx >> 4) & 0xF;
    u32sel_msk = (u32ModuleIdx >> 8) & 0x3;

    /* Convert mask width to actual mask */
    uint32_t mask = (1UL << (u32sel_msk + 1)) - 1;

    if (mask) {
        uint32_t u32SelReg = *(volatile uint32_t *)((uint32_t)&CLK->CLKSEL0 + u32SelTbl[u32sel_sel]);
        return (u32SelReg >> u32sel_pos) & mask;
    }

    return 0;
}

#endif /* CLK_GetModuleClockSource */

#endif /* M45X_COMPAT_H_ */
