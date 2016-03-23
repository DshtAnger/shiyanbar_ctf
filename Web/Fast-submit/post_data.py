#!/usr/bin/env python
#coding=utf-8

import requests
import base64
'''
import urllib2 
import urllib
import base64
def main():
    #urllib的post方法
    url = 'http://ctf4.shiyanbar.com/web/10.php'
    req = urllib2.Request(url)
    rsp = urllib2.urlopen(req)

    flag = rsp.info().getheader('FLAG')
    flag = base64.b64decode(flag).split(':')[1]
    print flag

    data = urllib.urlencode({'key':flag})
    req1 = urllib2.Request(url, data=data)
    rsp = urllib2.urlopen(req1).read()
    print rsp
'''

def main():
    #requests的post方法
    url = 'http://ctf4.shiyanbar.com/web/10.php'
    flag = requests.get(url).headers['FLAG']
    flag = base64.b64decode(flag)
    flag = flag.split(':')[1]
    if flag:
        r = requests.post(url, data = {'key': flag})
        print r.content #r.text


