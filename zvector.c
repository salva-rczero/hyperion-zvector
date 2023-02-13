/* ZVECTOR.C    (C) Copyright Jan Jaeger, 1999-2012                  */
/*              (C) Copyright Roger Bowler, 1999-2012                */
/*              z/Arch Vector Operations                             */
/*                                                                   */
/*   Released under "The Q Public License Version 1"                 */
/*   (http://www.hercules-390.org/herclic.html) as modifications to  */
/*   Hercules.                                                       */

/* Interpretive Execution - (C) Copyright Jan Jaeger, 1999-2012      */
/* z/Architecture support - (C) Copyright Jan Jaeger, 1999-2012      */

#include "hstdinc.h"
#define _HENGINE_DLL_

#include "hercules.h"
#include "opcode.h"
#include "inline.h"

#if defined(FEATURE_129_ZVECTOR_FACILITY)
/*-------------------------------------------------------------------*/
/* E700 VLEB  - Vector Load Element (8)                        [VRX] */
/*-------------------------------------------------------------------*/
DEF_INST(vector_load_element_8)
{
    int     v1, m3, x2, b2;
    VADR    effective_addr2;        /* Effective address         */

    VRX(inst, regs, v1, x2, b2, effective_addr2, m3);

    ZVECTOR_CHECK(regs);
    PER_ZEROADDR_XCHECK2(regs, x2, b2);

    ARCH_DEP(vfetchc) (&regs->vr[v1].B[m3], 0, effective_addr2, b2, regs);

}
/*-------------------------------------------------------------------*/
/* E701 VLEH  - Vector Load Element (16)                       [VRX] */
/*-------------------------------------------------------------------*/
DEF_INST(vector_load_element_16)
{
    int     v1, m3, x2, b2;
    VADR    effective_addr2;        /* Effective address         */

    VRX(inst, regs, v1, x2, b2, effective_addr2, m3);

    ZVECTOR_CHECK(regs);
    PER_ZEROADDR_XCHECK2(regs, x2, b2);
    if (m3 > 7)                    /* M3 > 7 => Specficitcation excp */
        ARCH_DEP(program_interrupt) (regs, PGM_SPECIFICATION_EXCEPTION);

    ARCH_DEP(vfetchc) (&regs->vr[v1].B[m3*2], 1, effective_addr2, b2, regs);
}
/*-------------------------------------------------------------------*/
/* E702 VLEG  - Vector Load Element (64)                       [VRX] */
/*-------------------------------------------------------------------*/
DEF_INST(vector_load_element_64)
{
    int     v1, m3, x2, b2;
    VADR    effective_addr2;        /* Effective address         */

    VRX(inst, regs, v1, x2, b2, effective_addr2, m3);

    ZVECTOR_CHECK(regs);
    PER_ZEROADDR_XCHECK2(regs, x2, b2);
    if (m3 > 1)                    /* M3 > 1 => Specficitcation excp */
        ARCH_DEP(program_interrupt) (regs, PGM_SPECIFICATION_EXCEPTION);

    ARCH_DEP(vfetchc) (&regs->vr[v1].B[m3*8], 7, effective_addr2, b2, regs);
}
/*-------------------------------------------------------------------*/
/* E703 VLEF  - Vector Load Element (32)                       [VRX] */
/*-------------------------------------------------------------------*/
DEF_INST(vector_load_element_32)
{
    int     v1, m3, x2, b2;
    VADR    effective_addr2;        /* Effective address         */

    VRX(inst, regs, v1, x2, b2, effective_addr2, m3);

    ZVECTOR_CHECK(regs);
    PER_ZEROADDR_XCHECK2(regs, x2, b2);
    if (m3 > 3)                    /* M3 > 3 => Specification excp */
        ARCH_DEP(program_interrupt) (regs, PGM_SPECIFICATION_EXCEPTION);

    ARCH_DEP(vfetchc) (&regs->vr[v1].B[m3 * 4], 3, effective_addr2, b2, regs);
}
/*-------------------------------------------------------------------*/
/* E704 VLLEZ  - Vector Load Logical Element and Zero          [VRX] */
/*-------------------------------------------------------------------*/
DEF_INST(vector_load_logical_element_and_zero)
{
	int     v1, m3, x2, b2, pos, len;
	VADR    effective_addr2;        /* Effective address         */

	VRX(inst, regs, v1, x2, b2, effective_addr2, m3);

	ZVECTOR_CHECK(regs);
	PER_ZEROADDR_XCHECK2(regs, x2, b2);
	if (m3 > 3 && m3 != 6) /* M3 > 3 | <> 6 => Specification excp */
		ARCH_DEP(program_interrupt) (regs, PGM_SPECIFICATION_EXCEPTION);

	len = ((1 << m3) & 0x0f | ((1 << m3) >> 4)) - 1;
	pos = 7 - len + ((m3 >> 2) << 3);
	regs->vr[v1].D.H.D = 0x00;
	regs->vr[v1].D.L.D = 0x00;
	ARCH_DEP(vfetchc) (&regs->vr[v1].B[pos], len, effective_addr2, b2, regs);
}
/*-------------------------------------------------------------------*/
/* E705 VLREP  - Vector Load and Replicate                     [VRX] */
/*-------------------------------------------------------------------*/
DEF_INST(vector_load_and_replicate)
{
    int     v1, m3, x2, b2, len;
    VADR    effective_addr2;        /* Effective address         */

    VRX(inst, regs, v1, x2, b2, effective_addr2, m3);

    ZVECTOR_CHECK(regs);
    PER_ZEROADDR_XCHECK2(regs, x2, b2);
    if (m3 > 3)                    /* M3 > 3 => Specification excp */
        ARCH_DEP(program_interrupt) (regs, PGM_SPECIFICATION_EXCEPTION);
    len = (1 << m3);
    ARCH_DEP(vfetchc) (&regs->vr[v1].B[0], len-1, effective_addr2, b2, regs);
    for (int i = len; i < 16; i++)
        regs->vr[v1].B[i] = regs->vr[v1].B[i - len];
}
/*-------------------------------------------------------------------*/
/* E706 VL    - Vector Load                                    [VRX] */
/*-------------------------------------------------------------------*/
DEF_INST(vector_load)
{
    int     v1, m3, x2, b2;
    VADR    effective_addr2;        /* Effective address         */

    VRX(inst, regs, v1, x2, b2, effective_addr2, m3);

    ZVECTOR_CHECK(regs);
    PER_ZEROADDR_XCHECK2(regs, x2, b2);

    ARCH_DEP(vfetchc) (&regs->vr[v1], sizeof(VR) - 1, effective_addr2, b2, regs);

}
/*-------------------------------------------------------------------*/
/* E707 VLBB  - Vector Load to Block Boundary                  [VRX] */
/*-------------------------------------------------------------------*/
DEF_INST(vector_load_to_block_boundary)
{
    int     v1, m3, x2, b2;
    VADR    effective_addr2;        /* Effective address         */

    VRX(inst, regs, v1, x2, b2, effective_addr2, m3);

    ZVECTOR_CHECK(regs);
    PER_ZEROADDR_XCHECK2(regs, x2, b2);
    if (m3 > 6)                    /* M3 > 6 => Specficitcation excp */
        ARCH_DEP(program_interrupt) (regs, PGM_SPECIFICATION_EXCEPTION);

    int boundary = 64 << m3; /* 0: 64 Byte, 1: 128 Byte, 2: 256 Byte, 3: 512 Byte,
                                4: 1K - byte, 5: 2K - Byte, 6: 4K - Byte */
    VADR nextbound = (effective_addr2 + boundary) & !boundary;
    int length = min(sizeof(VR), nextbound - effective_addr2);
        
    ARCH_DEP(vfetchc) (&regs->vr[v1], length-1, effective_addr2, b2, regs);
}
/*-------------------------------------------------------------------*/
/* E708 VSTEB  - Vector Store Element (8)                      [VRX] */
/*-------------------------------------------------------------------*/
DEF_INST(vector_store_element_8)
{
    int     v1, m3, x2, b2;
    VADR    effective_addr2;        /* Effective address         */

    VRX(inst, regs, v1, x2, b2, effective_addr2, m3);
    ZVECTOR_CHECK(regs);
    PER_ZEROADDR_XCHECK2(regs, x2, b2);

    ARCH_DEP(vstorec) (&regs->vr[v1].B[m3], 0, effective_addr2, b2, regs);
}
/*-------------------------------------------------------------------*/
/* E709 VSTEH  - Vector Store Element (16)                     [VRX] */
/*-------------------------------------------------------------------*/
DEF_INST(vector_store_element_16)
{
    int     v1, m3, x2, b2;
    VADR    effective_addr2;        /* Effective address         */

    VRX(inst, regs, v1, x2, b2, effective_addr2, m3);
    ZVECTOR_CHECK(regs);
    PER_ZEROADDR_XCHECK2(regs, x2, b2);
    if (m3 > 7)                    /* M3 > 7 => Specficitcation excp */
        ARCH_DEP(program_interrupt) (regs, PGM_SPECIFICATION_EXCEPTION);

    ARCH_DEP(vstorec) (&regs->vr[v1].B[m3*2], 1, effective_addr2, b2, regs);
}
/*-------------------------------------------------------------------*/
/* E70A VSTEG  - Vector Store Element (64)                     [VRX] */
/*-------------------------------------------------------------------*/
DEF_INST(vector_store_element_64)
{
    int     v1, m3, x2, b2;
    VADR    effective_addr2;        /* Effective address         */

    VRX(inst, regs, v1, x2, b2, effective_addr2, m3);
    ZVECTOR_CHECK(regs);
    PER_ZEROADDR_XCHECK2(regs, x2, b2);
    if (m3 > 1)                    /* M3 > 1 => Specficitcation excp */
        ARCH_DEP(program_interrupt) (regs, PGM_SPECIFICATION_EXCEPTION);

    ARCH_DEP(vstorec) (&regs->vr[v1].B[m3 * 8], 7, effective_addr2, b2, regs);
}
/*-------------------------------------------------------------------*/
/* E70B VSTEF  - Vector Store Element (32)                     [VRX] */
/*-------------------------------------------------------------------*/
DEF_INST(vector_store_element_32)
{
    int     v1, m3, x2, b2;
    VADR    effective_addr2;        /* Effective address         */

    VRX(inst, regs, v1, x2, b2, effective_addr2, m3);
    ZVECTOR_CHECK(regs);
    PER_ZEROADDR_XCHECK2(regs, x2, b2);
    if (m3 > 3)                    /* M3 > 3 => Specficitcation excp */
        ARCH_DEP(program_interrupt) (regs, PGM_SPECIFICATION_EXCEPTION);

    ARCH_DEP(vstorec) (&regs->vr[v1].B[m3 * 4], 3, effective_addr2, b2, regs);
}
/*-------------------------------------------------------------------*/
/* E70E VST   - Vector Store                                   [VRX] */
/*-------------------------------------------------------------------*/
DEF_INST(vector_store)
{
    int     v1, m3, x2, b2;
    VADR    effective_addr2;        /* Effective address         */

    VRX(inst, regs, v1, x2, b2, effective_addr2, m3);
    ZVECTOR_CHECK(regs);
    PER_ZEROADDR_XCHECK2(regs, x2, b2);

    ARCH_DEP(vstorec) (&regs->vr[v1], sizeof(VR) - 1, effective_addr2, b2, regs);
}
/*-------------------------------------------------------------------*/
/* E727 LCBB  - Load Count to Block Boundary                   [RXE] */
/*-------------------------------------------------------------------*/
DEF_INST(load_count_to_block_boundary)
{
    int     r1, x2, b2, m3;
    VADR    effective_addr2;        /* Effective address         */

    RXE_M3(inst, regs, r1, x2, b2, effective_addr2, m3);

    ZVECTOR_CHECK(regs);
    PER_ZEROADDR_XCHECK2(regs, x2, b2);
    if (m3 > 6)                    /* M3 > 6 => Specficitcation excp */
        ARCH_DEP(program_interrupt) (regs, PGM_SPECIFICATION_EXCEPTION);

    int boundary = 64 << m3; /* 0: 64 Byte, 1: 128 Byte, 2: 256 Byte, 3: 512 Byte,
                                4: 1K - byte, 5: 2K - Byte, 6: 4K - Byte */
    VADR nextbound = (effective_addr2 + boundary) & !boundary;
    int length = min(sizeof(VR), nextbound - effective_addr2);

    regs->GR_L(r1) = length;
    regs->psw.cc = (length == 16) ? 0 : 3;

}
/*-------------------------------------------------------------------*/
/* E736 VLM   - Vector Load Multiple                         [VRS_A] */
/*-------------------------------------------------------------------*/
DEF_INST(vector_load_multiple)
{
    int     v1, v3, b2, m4;
    VADR    effective_addr2;        /* Effective address         */

    VRS_A(inst, regs, v1, v3, b2, effective_addr2, m4);
    ZVECTOR_CHECK(regs);
    PER_ZEROADDR_XCHECK(regs, b2);
    int len = (1 + v3 - v1) * sizeof(VR);
    if (len < 0 || len > 16 * sizeof(VR))
        ARCH_DEP(program_interrupt) (regs, PGM_SPECIFICATION_EXCEPTION);

    ARCH_DEP(vfetchc) (&regs->vr[v1], len - 1, effective_addr2, b2, regs);
}
/*-------------------------------------------------------------------*/
/* E73E VSTM  - Vector Store Multiple                        [VRS_A] */
/*-------------------------------------------------------------------*/
DEF_INST(vector_store_multiple)
{
    int     v1, v3, b2, m4;
    VADR    effective_addr2;        /* Effective address         */

    VRS_A(inst, regs, v1, v3, b2, effective_addr2, m4);
    ZVECTOR_CHECK(regs);
    PER_ZEROADDR_XCHECK(regs, b2);
    int len = (1 + v3 - v1) * sizeof(VR);
    if (len < 0 || len > 16 * sizeof(VR))
        ARCH_DEP(program_interrupt) (regs, PGM_SPECIFICATION_EXCEPTION);
    
    ARCH_DEP(vstorec) (&regs->vr[v1], len - 1, effective_addr2, b2, regs);
}
/*-------------------------------------------------------------------*/
/* E744 VGBM   - Vector Generate Byte Mask                   [VRI_A] */
/*-------------------------------------------------------------------*/
DEF_INST(vector_generate_byte_mask)
{
    int     v1, i2, m3;
    
    VRI_A(inst, regs, v1, i2, m3);
    ZVECTOR_CHECK(regs);
    
    for (int i = 0; i < 16; i++)
    {
        regs->vr[v1].B[i] = (i2 & (0x1 << (15 - i))) ? 0xff : 0x00;
    }
}
/*-------------------------------------------------------------------*/
/* E768 VN   - Vector AND                                    [VRR_C] */
/*-------------------------------------------------------------------*/
DEF_INST(vector_AND)
{
    int     v1, v2, v3, m4, m5, m6;

    VRR_C(inst, regs, v1, v2, v3, m4, m5, m6);
    regs->vr[v1].D.H.D = regs->vr[v2].D.H.D & regs->vr[v3].D.H.D;
    regs->vr[v1].D.L.D = regs->vr[v2].D.L.D & regs->vr[v3].D.L.D;
    ZVECTOR_CHECK(regs);

}
#endif /* defined(FEATURE_129_ZVECTOR_FACILITY) */

#if !defined(_GEN_ARCH)

#if defined(_ARCH_NUM_1)
#define  _GEN_ARCH _ARCH_NUM_1
#include "zvector.c"
#endif

#if defined(_ARCH_NUM_2)
#undef   _GEN_ARCH
#define  _GEN_ARCH _ARCH_NUM_2
#include "zvector.c"
#endif

#endif /*!defined(_GEN_ARCH)*/
