#!/usr/bin/python

flag = r'ASIS{a9ab115c488a311896dac4e8bc20a6d7}'
hflag = flag.encode('hex')
print hflag
iflag = int(hflag[2:], 16)
print iflag

def FAN(n, m):
    i = 0
    z = []
    s = 0
    while n > 0:
    	if n % 2 != 0:
    		z.append(2 - (n % 4))
    	else:
    		z.append(0)
    	n = (n - z[i])/2
    	i = i + 1
    z = z[::-1]
    l = len(z)
    for i in range(0, l):
        s += z[i] * m ** (l - 1 - i)
    return s

i = 0
r = ''
# iflag=1833536569465012315229
while i < len(str(iflag)): #i<22
    d = str(iflag)[i:i+2] #d='18'
    nf = FAN(int(d), 3)
    r += str(nf)
    i += 2

print r 