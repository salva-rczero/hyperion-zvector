*Testcase zvector instructions
mainsize    2
numcpu      1
sysclear
archlvl     zArch
loadcore    "$(testpath)/zvector.core"
fpr
t+
runtest     1
*Compare
r 0000050.00000010
*Want 00010203 04050607 08090A0B 0C0D0E0F
r 0000060.00000010
*Want 00010203 04050607 08090A0B 0C0D0E0F
r 00000F0.10
*Want A0A1A2A3 A4A5A6A7 A8A9AAAB ACADAEAF
*Done

