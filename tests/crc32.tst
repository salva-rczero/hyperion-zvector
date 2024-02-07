*Testcase zvector instructions
mainsize    2
numcpu      1
sysclear
archlvl     zArch
loadcore    "$(testpath)/crc32.core"
t+
runtest     1
gpr
vr
cr
fpr
r 0000300.200
*Compare
r 0001000.10
*Want 00000000 00000000 00000000 00000000
r 0001010.10
*Want 01234567 89ABCDEF 01234567 89ABCDEF
r 0001020.10
*Want 00000000 00000000 00000000 00000000
*Done

