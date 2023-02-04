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

#if defined(FEATURE_129_ZVECTOR_FACILITY)
/*-------------------------------------------------------------------*/
/* E706 VL    - Vector Load                                    [VRX] */
/*-------------------------------------------------------------------*/
DEF_INST(vector_load)
{
    int     v1, m3;
    VADR    effective_addr2;        /* Effective address         */

    VRX(inst, regs, v1, effective_addr2, m3);
    regs->GR_G(8) = 0x33333333;

}
/*-------------------------------------------------------------------*/
/* E70E VST   - Vector Store                                   [VRX] */
/*-------------------------------------------------------------------*/
DEF_INST(vector_store)
{
    int     v1, m3;
    VADR    effective_addr2;        /* Effective address         */

    VRX(inst, regs, v1, effective_addr2, m3);
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
