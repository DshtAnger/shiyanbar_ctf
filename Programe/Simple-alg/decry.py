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


dictionary = {}
for num in range(0,100):
    dictionary[FAN(num,3)] = num

file = open('enc.txt','r').read()
FileLen = len(file)

StartPos=0
ResNum=''
while StartPos<FileLen:
    for step in range(4,0,-1):
        SerachKey = int(file[StartPos:(StartPos+step)])
        if dictionary.has_key(SerachKey):
            ResNum += '%02d'%dictionary[SerachKey]
            StartPos += step
            break
        else:
            continue 

temp = list(ResNum)
temp[(len(ResNum)-2)]=''
ResNum=''.join(temp)

result = hex(int(ResNum)).replace('0x','').replace('L','').decode('hex')

print 'The result of decryption is : ',result








