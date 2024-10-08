/**
 * @copyright
 * @brief arm64 register
 * @author 2226958871@qq.com
 */
#ifndef __INCLUDE_REG_OFFSET_H__

#define __INCLUDE_REG_OFFSET_H__

// HCR
#define HCR_RW (1 << 31)
// SCTLR
#define SCTLR_EE_LITTLE_ENDIAN (0 << 25)
#define SCTLR_EOE_LITTLE_ENDIAN (0 << 24)
#define SCTLR_MMU_DISABLED (0 << 0)
#define SCTLR_VALUE_MMU_DISABLE (SCTLR_EE_LITTLE_ENDIAN | SCTLR_EOE_LITTLE_ENDIAN | SCTLR_MMU_DISABLED)
// SPSR
#define SPSR_DAIF_DISABLED (7 << 6)

#define SPSR_EL0t (0  << 0)
#define SPSR_EL1t (4  << 0)
#define SPSR_EL1h (5  << 0)
#define SPSR_EL2t (8  << 0)
#define SPSR_EL2h (9  << 0)
#define SPSR_EL3t (12 << 0)
#define SPSR_EL3h (13 << 0)

#define SPSR_EL1h (SPSR_DAIF_DISABLED | SPSR_EL1h)
#define SPSR_EL2h (SPSR_DAIF_DISABLED | SPSR_EL2h)

#endif // !__INCLUDE_REG_OFFSET_H__