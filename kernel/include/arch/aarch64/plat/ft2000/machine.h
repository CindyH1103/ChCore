/*
 * Copyright (c) 2023 Institute of Parallel And Distributed Systems (IPADS), Shanghai Jiao Tong University (SJTU)
 * Licensed under the Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *     http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
 * PURPOSE.
 * See the Mulan PSL v2 for more details.
 */

#ifndef ARCH_AARCH64_PLAT_FT2000_MACHINE_H
#define ARCH_AARCH64_PLAT_FT2000_MACHINE_H

#include <common/vars.h>

#ifdef CHCORE_SUBPLAT_D2000V
#define PLAT_CPU_NUM		8
#else
#define PLAT_CPU_NUM		4
#endif
#define PLAT_PROCESSOR_NUM	1
#define PLAT_CORE_NUM		1
#define PLAT_FT2000

#define CONSOLE_BAUDRATE	115200
#define CONSOLE_UART_CLK_IN_HZ	48000000
#define UARTDR			0x000
#define UARTFR			0x018
#define UARTFR_TXFF		(1 << 5)

#define FT_UART0_BASE	0x28000000
#define FT_UART1_BASE	0x28001000
#define FT_UART2_BASE	0x28002000
#define FT_UART3_BASE	0x28003000
#define FT_UART_REG_SIZE	0x1000

#define SIZE_64K	0x10000
#define SIZE_128K	0x20000

#ifdef CHCORE_SUBPLAT_D2000V
#define GIC_BASE (KBASE + 0x29A00000UL)
#else
#define GIC_BASE (KBASE + 0x29900000UL)
#endif

#define GICD_BASE GIC_BASE
#ifdef CHCORE_SUBPLAT_D2000V
#define GICR_BASE (GIC_BASE + 0x100000)
#else
#define GICR_BASE (GIC_BASE + 0x80000)
#endif
/* The size of GICR registers is 128k per core */
#define GICR_PER_CPU_BASE(CPUID) (GICR_BASE + SIZE_128K * CPUID)
#define GICC_BASE (GIC_BASE + 0x300000)
#define GICH_BASE (GIC_BASE + 0x310000)
#define GICV_BASE (GIC_BASE + 0x320000)
#define GICD_SIZE 0x20000
#define GICC_SIZE 0x10000
#define GICH_SIZE 0x10000
#define GICV_SIZE 0x10000

/*
 * Offsets of GICH Registers.
 *
 * Use offset instead of absolute address
 * because we need to use `ldr w5, [x2, GICH_HCR]`
 * style assembly to save and restore these registers,
 * where x2 is the base address of GICH register block.
 *
 * TODO: Accessing GICD and GICC registers should also
 * be in this fashion too.
 */
#define GICH_HCR	0x0
#define GICH_VTR	0x4
#define GICH_VMCR	0x8
#define GICH_MISR	0x10
#define GICH_EISR0	0x20
#define GICH_EISR1	0x24
#define GICH_ELRSR0	0x30
#define GICH_ELRSR1	0x34
#define GICH_APR	0xf0
#define GICH_LR0	0x100

/* GICD Registers */
#define GICD_CTLR	(GICD_BASE+0x000)
#define GICD_TYPER	(GICD_BASE+0x004)
#define GICD_IIDR	(GICD_BASE+0x008)
#define GICD_IGROUPR	(GICD_BASE+0x080)
#define GICD_ISENABLER	(GICD_BASE+0x100)
#define GICD_ICENABLER	(GICD_BASE+0x180)
#define GICD_ISENABLER_OFFSET (0x100)
#define GICD_ICENABLER_OFFSET (0x180)
#define GICD_ICPENDR	(GICD_BASE+0x280)
#define GICD_ISACTIVER	(GICD_BASE+0x300)
#define GICD_ICACTIVER	(GICD_BASE+0x380)
#define GICD_IPRIORITYR	(GICD_BASE+0x400)
#define GICD_ITARGETSR	(GICD_BASE+0x800)
#define GICD_ICFGR	(GICD_BASE+0xC00)
#define GICD_IGRPMODR	(GICD_BASE+0xD00)
#define GICD_SGIR	(GICD_BASE+0xF00)
#define GICD_SGIR_CLRPEND	(GICD_BASE+0xF10)
#define GICD_SGIR_SETPEND	(GICD_BASE+0xF20)
#define GICD_IROUTER		(GICD_BASE+0x6000)

#define GICD_ENABLE			0x1
#define GICD_DISABLE			0x0
#define GICD_INT_ACTLOW_LVLTRIG		0x0
#define GICD_INT_EN_CLR_X32		0xffffffff
#define GICD_INT_EN_SET_SGI		0x0000ffff
#define GICD_INT_EN_CLR_PPI		0xffff0000
#define GICD_INT_DEF_PRI		0xa0
#define GICD_INT_DEF_PRI_X4		((GICD_INT_DEF_PRI << 24) |\
					(GICD_INT_DEF_PRI << 16) |\
					(GICD_INT_DEF_PRI << 8) |\
					GICD_INT_DEF_PRI)

#define GICD_CTLR_RWP			(1U << 31)
#define GICD_CTLR_DS			(1U << 6)
#define GICD_CTLR_ARE_NS		(1U << 5)
#define GICD_CTLR_ENABLE_G1_NS		(1U << 1)
#define GICD_CTLR_ENABLE_G0		(1U << 0)

#define GICD_TYPER_RSS			(1U << 26)
#define GICD_TYPER_LPIS			(1U << 17)
#define GICD_TYPER_MBIS			(1U << 16)

/* GICD Register bits */
#define GICD_CTL_ENABLE 0x1
#define GICD_TYPE_LINES 0x01F
#define GICD_TYPE_CPUS_SHIFT 5
#define GICD_TYPE_CPUS 0x0E0
#define GICD_TYPE_SEC 0x400

/* GICD_SGIR defination */
#define GICD_SGIR_SGIINTID_SHIFT	0
#define GICD_SGIR_CPULIST_SHIFT		16
#define GICD_SGIR_LISTFILTER_SHIFT	24
#define GICD_SGIR_VAL(listfilter, cpulist, sgi)		\
	(((listfilter) << GICD_SGIR_LISTFILTER_SHIFT) |	\
	 ((cpulist) << GICD_SGIR_CPULIST_SHIFT) |	\
	 ((sgi) << GICD_SGIR_SGIINTID_SHIFT))

#define GIC_INTID_PPI			16
#define GIC_INTID_SPI			32
#define GIC_INTID_SPI_UART6		(GIC_INTID_SPI + 79)
#define GIC_INTID_PPI_EL1_PHYS_TIMER	(GIC_INTID_PPI + 14)
#define GIC_INTID_PPI_EL1_VIRT_TIMER	(GIC_INTID_PPI + 11)
#define GIC_INTID_PPI_NS_EL2_PHYS_TIMER	(GIC_INTID_PPI + 10)
#define GIC_INTID_PPI_EL3_PHYS_TIMER	(GIC_INTID_PPI + 13)

#define GICD_TYPER_ID_BITS(typer)	((((typer) >> 19) & 0x1f) + 1)
#define GICD_TYPER_NUM_LPIS(typer)	((((typer) >> 11) & 0x1f) + 1)
#define GICD_TYPER_IRQS(typer)		(((((typer) & 0x1f) + 1) << 5) - 1)

/* GICR Registers */
/* Redistributor - RD_BASE */
#define GICR_CTLR_OFFSET		0x00000000U
#define GICR_IIDR_OFFSET		0x00000004U
#define GICR_TYPER_OFFSET		0x00000008U
#define GICR_STATUSR_OFFSET		0x00000010U
#define GICR_WAKER_OFFSET		0x00000014U
#define GICR_MPAMIDR_OFFSET		0x00000018U
#define GICR_PARTIDR_OFFSET		0x0000001CU
#define GICR_SETLPIR_OFFSET		0x00000040U
#define GICR_CLRLPIR_OFFSET		0x00000048U
#define GICR_PROPBASER_OFFSET		0x00000070U
#define GICR_PENDBASER_OFFSET		0x00000078U

#define GICR_WAKER(CPUID)		(GICR_PER_CPU_BASE(CPUID) + GICR_WAKER_OFFSET)
#define GICR_WAKER_ProcessorSleep	(1U << 1)
#define GICR_WAKER_ChildrenAsleep	(1U << 2)
#define GICR_IGROUPR0(CPUID)		(GICR_PER_CPU_BASE(CPUID) + SIZE_64K + 0x080)

/* Redistributor - SGI_BASE */
#define GICR_SGI_BASE_OFFSET		0x10000U
#define GICR_IGROUPR0_OFFSET		0x00000080U
#define GICR_IGROUPR_E_OFFSET		0x00000084U
#define GICR_ISENABLER0_OFFSET		0x00000100U
#define GICR_ISENABLER_E_OFFSET		0x00000104U
#define GICR_ICENABLER0_OFFSET		0x00000180U
#define GICR_ICENABLER_E_OFFSET		0x00000184U
#define GICR_ISPENDR0_OFFSET		0x00000200U
#define GICR_ISPENDR_E_OFFSET		0x00000204U
#define GICR_ICPENDR0_OFFSET		0x00000280U
#define GICR_ICPENDR_E_OFFSET		0x00000284U
#define GICR_ISACTIVER0_OFFSET		0x00000300U
#define GICR_ISACTIVER_E_OFFSET		0x00000304U
#define GICR_ICACTIVER0_OFFSET		0x00000380U
#define GICR_ICACTIVER_E_OFFSET		0x00000384U
#define GICR_IPRIORITYR_OFFSET		0x00000400U
#define GICR_IPRIORITYR_E_OFFSET	0x00000420U
#define GICR_ICFGR0_OFFSET		0x00000C00U
#define GICR_ICFGR1_OFFSET		0x00000C04U
#define GICR_ICFGR_E_OFFSET		0x00000C08U
#define GICR_IGRPMODR0_OFFSET		0x00000D00U
#define GICR_IGRPMODR_E_OFFSET		0x00000D04U
#define GICR_NSACR_OFFSET		0x00000E00U

/* Default priority value. */
#define DEFAULT_PMR_VALUE	0xF0

#define GICD_ICACTIVER_DEFAULT_MASK	0xffffffff
#define GICD_ICENABLER_DEFAULT_MASK	0xffffffff
#define GICD_ICPENDR_DEFAULT_MASK	0xffffffff
#define GICD_IGROUPR_DEFAULT_MASK	0xffffffff
#define GICD_IGRPMODR_DEFAULT_MASK	0xffffffff

#define GICR_ICACTIVER0_DEFAULT_MASK	0xffffffff
#define GICR_ICENABLER0_DEFAULT_MASK	0xffff0000
#define GICR_ISENABLER0_DEFAULT_MASK	0x0000ffff
#define GICR_IGROUPR0_DEFAULT_MASK	0xffffffff

#endif /* ARCH_AARCH64_PLAT_FT2000_MACHINE_H */