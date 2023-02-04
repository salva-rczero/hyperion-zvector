 TITLE '                                                 zVector Test'
***********************************************************************
*
*                     zVector Test
*
***********************************************************************
*
***********************************************************************
         PRINT OFF
         COPY  'satk.mac'
         PRINT ON
                                                                SPACE
***********************************************************************
*        SATK prolog stuff...
***********************************************************************
                                                                SPACE
         ARCHLVL  ZARCH=YES,MNOTE=NO
                                                                EJECT
***********************************************************************
*        Initiate the CLCL CSECT in the CODE region
*        with the location counter at 0
***********************************************************************
                                                                SPACE
*ZVECTOR  ASALOAD  REGION=CODE
                                                                SPACE
***********************************************************************
*        Create IPL (restart) PSW
***********************************************************************
                                                                SPACE
*        ASAIPL   IA=BEGIN
                                                                SPACE 2
***********************************************************************
*               The actual "zvector" program itself...
***********************************************************************
*
*  Architecture Mode:   ESA/390
*
*  Addressing Mode:     31-bit
*
*  Register Usage:      R12 - R13     Base registers
*                       R0  - R1      CLCL Operand-1
*                       R14 - R15     CLCL Operand-2
*                       R2  - R11     Work registers
*
***********************************************************************
                                                                SPACE
         USING  ZVECTOR,R12       FIRST Base Register
         USING  ZVECTOR+4096,R13  SECOND Base Register
                                                                SPACE
ZVECTOR  BALR  R12,0            Initalize FIRST base register
         BCTR  R12,0            Initalize FIRST base register
         BCTR  R12,0            Initalize FIRST base register
                                                                SPACE
         LA    R13,2048(,R12)   Initalize SECOND base register
         LA    R13,2048(,R13)   Initalize SECOND base register
                                                                EJECT
***********************************************************************
*        Begin test
***********************************************************************
         VL    V1,VSPACE0
         B     SUCCESS
***********************************************************************
*        Normal completion or Abnormal termination PSWs
***********************************************************************
SUCCESS  DWAITEND LOAD=YES          Normal completion
FAILURE  DWAIT LOAD=YES,CODE=BAD    Abnormal termination
***********************************************************************
*        Working Storage
***********************************************************************
         LTORG ,                Literals pool
VSPACE0  DC    XL255'00'                              
***********************************************************************
*        Register equates
***********************************************************************
R0       EQU   0
R1       EQU   1
R2       EQU   2
R3       EQU   3
R4       EQU   4
R5       EQU   5
R6       EQU   6
R7       EQU   7
R8       EQU   8
R9       EQU   9
R10      EQU   10
R11      EQU   11
R12      EQU   12
R13      EQU   13
R14      EQU   14
R15      EQU   15
V0       EQU   0
V1       EQU   1
V2       EQU   2
V3       EQU   3
V4       EQU   4
V5       EQU   5
V6       EQU   6
V7       EQU   7
V8       EQU   8
V9       EQU   9
V10      EQU   10
V11      EQU   11
V12      EQU   12
V13      EQU   13
V14      EQU   14
V15      EQU   15
         END
