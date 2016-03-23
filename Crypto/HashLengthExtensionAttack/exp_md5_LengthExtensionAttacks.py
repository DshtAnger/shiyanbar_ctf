#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Author：DshtAnger
import my_md5
#reference:
#   http://www.freebuf.com/articles/web/69264.html
#problem link:
#   http://ctf4.shiyanbar.com/web/kzhan.php

samplehash="571580b26c65f306376d4f64e53cb5c7"
#将哈希值分为四段,并反转该四字节为小端序,作为64第二次循环的输入幻书
s1=0xb2801557
s2=0x06f3656c
s3=0x644f6d37
s4=0xc7b53ce5
#exp
secret = "a"*15
secret_admin = secret+'adminadmin\x80\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xc8\x00\x00\x00\x00\x00\x00\x00admin'
r = my_md5.deal_rawInputMsg(secret_admin)
inp = r[len(r)/2:]
print "getmein:"+my_md5.run_md5(s1,s2,s3,s4,inp)

'''
payload-hash=e18dfd8404515016d3aeeea2aa196909
'''