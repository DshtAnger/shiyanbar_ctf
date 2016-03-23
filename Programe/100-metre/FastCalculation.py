#coding:utf-8
import re,requests
url = r"http://ctf8.simplexue.com/jia/"
session = requests.Session()
html = session.get(url).content
pattern = re.compile(r"(?<=my_expr'>)(.*?)(?=</div)")
match = pattern.search(html).group().replace('x','*')
post = session.post(url,{'pass_key':eval(match)})
print post.content





