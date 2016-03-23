#coding:utf-8
file = open("x") #随便重命名什么都好，原名太长了
count = 0 
while 1:
    lines = file.readlines(100000)
    if not lines:
        break
    for line in lines:
        res = line.split('|')
        if (len(res)>2 and res[1]=='CN' and res[2]=='ipv4'):
			count+=int(res[4])
print "The amount of Ipv4 address assigned to CN is %d"%count
        