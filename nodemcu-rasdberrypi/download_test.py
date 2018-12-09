import requests, json
from urllib import urlopen

url = "http://106.10.34.243/songs/"

s = requests.Session()
r = s.get(url)
r_dic = r.json()

for find_song in r_dic:
    if find_song['server_id'] == 2:
        d_link = find_song['song']
        mem = urlopen(d_link)
        data = mem.read()
        real_d = data.decode('euc-kr')

        url_list = d_link.split('/')
        f_idx = len(url_list) - 1
        
        with open(url_list[f_idx],mode="w") as f:
            f.write(real_d)
        