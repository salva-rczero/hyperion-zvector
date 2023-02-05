*Testcase zvector instructions
mainsize    2
numcpu      1
sysclear
archlvl     zArch
loadcore    "$(testpath)/zvector.core"
fpr
t+
runtest     1
r           40.4096
*Done
