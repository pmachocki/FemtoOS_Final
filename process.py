#!/usr/bin/python
from pylab import *

dArray = []
aArray = []
dOut = []
aOut = []

if (sys.argv[1] is 0):
	exit

f = open(sys.argv[1])

lists = []
for lines in f:
    line = lines[9:len(lines)-3]
    for x in range(0, len(line), 8):
        dArray.append(line[x:x+2])
        dArray.append(line[x+2:x+4])
        aArray.append(line[x+4:x+6])
        aArray.append(line[x+6:x+8])

for x in range(0, 4, 1):
    dArray.pop(0)
    aArray.pop(0)    
    
for x in range(0, len(dArray), 2):
    dValue = int(dArray.pop(0), 16) << 8
    dValue |= int(dArray.pop(0), 16)
    aValue = int(aArray.pop(0), 16) << 8
    aValue |= int(aArray.pop(0), 16)
    if dValue > 32768:
    	dValue = dValue - 65536
    if aValue > 32768:
		aValue = aValue - 65536
    dOut.append(dValue)
    aOut.append(aValue)
    #print "d:" + str(dValue) + "a:" + str(aValue)

p1, = plot(dOut,'x', label="Digital")
p2, = plot(aOut,'o', label="Analog")
ylabel("Sensor Value")
xlabel("Sample (#)")
legend(bbox_to_anchor=(1.1, 1.05))
show()
