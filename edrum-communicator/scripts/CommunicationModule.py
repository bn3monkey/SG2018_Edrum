from requests_toolbelt import MultipartEncoder
import requests, json
import sys
from urllib import urlopen

def downloadFile(server_id):
	URL = "http://106.10.34.243/songs/"
	flag = False

	s = requests.Session()
	r = s.get(URL)
	r_dic = r.json()

	for find_song in r_dic:
		if find_song['server_id'] == server_id:
			d_link = find_song['song']
			mem = urlopen(d_link)
			data = mem.read()
			real_d = data.decode('euc-kr')

			url_list = d_link.split('/')
			f_idx = len(url_list) - 1

			with open(url_list[f_idx],mode="w") as f:
				f.write(real_d)
				flag = True

	return flag

def upload(url, song_name, song_artist, creator_ID, f_name):
	URL = url
	
	print(song_name)
	print(song_artist)
	print(creator_ID)
	print(f_name)
	m = MultipartEncoder(
		{
			'name' : song_name,
			'artist' : song_artist,
			'ID' : creator_ID,
			'song' : (f_name, open(f_name, 'rb'), 'text/plane')
		}
	)

	r = requests.post(URL, data=m, headers = {'Content-Type' : m.content_type})

	print(r.status_code)
	print(r.text)

	if(r.status_code == 201):
		print('return true')
		return True
	else:
		return False