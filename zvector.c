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
/* E706 VL    - Vector Load                                    [VRX] */
/*-------------------------------------------------------------------*/
DEF_INST(vector_load)
{
    int     v1, m3, x2, b2;
    VADR    effective_addr2;        /* Effective address         */

    VRX(inst, regs, v1, x2, b2, effective_addr2, m3);

    ZVECTOR_CHECK(regs);
    PER_ZEROADDR_XCHECK2(regs, x2, b2);

    ARCH_DEP(vfetchc) (&regs->vr[(v1)], sizeof(QWORD) - 1, effective_addr2, b2, regs);

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

    ARCH_DEP(vstorec) (&regs->vr[(v1)], sizeof(QWORD) - 1, effective_addr2, b2, regs);
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
    int len = (1 + v3 - v1) * sizeof(QWORD);
    if (len < 0 || len > 16 * sizeof(QWORD))
        ARCH_DEP(program_interrupt) (regs, PGM_SPECIFICATION_EXCEPTION);

    ARCH_DEP(vfetchc) (&regs->vr[(v1)], len - 1, effective_addr2, b2, regs);
}
/*-------------------------------------------------------------------*/
/* E73E VST   - Vector Store Multiple                        [VRS_A] */
/*-------------------------------------------------------------------*/
DEF_INST(vector_store_multiple)
{
    int     v1, v3, b2, m4;
    VADR    effective_addr2;        /* Effective address         */

    VRS_A(inst, regs, v1, v3, b2, effective_addr2, m4);
    ZVECTOR_CHECK(regs);
    PER_ZEROADDR_XCHECK(regs, b2);
    int len = (1 + v3 - v1) * sizeof(QWORD);
    if (len < 0 || len > 16 * sizeof(QWORD))
        ARCH_DEP(program_interrupt) (regs, PGM_SPECIFICATION_EXCEPTION);
    
    ARCH_DEP(vstorec) (&regs->vr[(v1)], len - 1, effective_addr2, b2, regs);
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
