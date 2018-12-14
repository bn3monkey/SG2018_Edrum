from requests_toolbelt import MultipartEncoder
import requests, json
import sys
from urllib import urlopen

def download_meta(url, page_num, song_num) :
	result = {}
	
	URL = url + "?page=" + str(page_num)
	s = requests.Session()
	r = s.get(URL)

	if r.status_code == 404:
		print("there is no page number in server list")
		result['flag'] = False
		return result

	r_dic = r.json()
	metas = r_dic['results']
	if song_num < len(metas) :
		meta = metas[song_num]
		result['server_id'] = meta['server_id']
		result['name'] = str(meta['name'])
		result['artist'] = str(meta['artist'])
		result['date'] = str(meta['date'])
		result['ID'] = str(meta['ID'])

	else :
		result['server_id'] = 0
		result['name'] = ""
		result['artist'] = ""
		result['date'] = ""
		result['ID'] = ""

	result['flag'] = True
	#print(result)
	return result

def download(url, path, server_id):
	result = {}

	URL = url + str(server_id)
	result['flag'] = False

	#print(URL)
	#print(path)
	#print(server_id)

	s = requests.Session()
	r = s.get(URL)
	print(r)

	if r.status_code == 404 :
		print("there is no server id in server list")
		return result
	
	r_dic = r.json()
	#print(r_dic)

	link = r_dic['song']
	mem = urlopen(link)
	data = mem.read()

	url_list = link.split('/')
	f_idx = len(url_list) - 1
	filename_list = url_list[f_idx].split('_')
	#print(filename_list)


	filename = filename_list[0] + "_" + filename_list[1] + "_" + filename_list[2] + ".sdd"
	#print(filename)
	with open(path + filename, mode="w") as f:
		f.write(data)
		result['flag'] = True

	result['server_id'] = r_dic['server_id']
	result['name'] = str(r_dic['name'])
	result['artist'] = str(r_dic['artist'])
	result['date'] = str(r_dic['date'])
	result['ID'] = str(r_dic['ID'])
	#print(result)
	
	return result

def upload(url, song_name, song_artist, creator_ID, f_name):
	URL = url
	result = {}
	result['flag'] = False

	#print(song_name)
	#print(song_artist)
	#print(creator_ID)
	#print(f_name)
	m = MultipartEncoder(
		{
			'name' : song_name,
			'artist' : song_artist,
			'ID' : creator_ID,
			'song' : (f_name, open(f_name, 'rb'), 'text/plane')
		}
	)

	r = requests.post(URL, data=m, headers = {'Content-Type' : m.content_type})
	
	#print(r.status_code)
	#print(r.text)

	if(r.status_code == 201):
		result['flag'] = True
		r_dic = r.json()
		result['server_id'] = r_dic["server_id"]

	return result

def upload_cancel(url, server_id):
	URL = url + str(server_id)
	s = requests.Session()
	r = s.delete(URL)
	#print(r)

	if r.status_code == 404 :
		print("there is no server id in server list")
		return False

	return True

def getAllpage(url, page_size) :
	
	URL = url
	s = requests.Session()
	r = s.get(URL)
	r_dic = r.json()
	
	size = r_dic["count"]
	quotient = size / page_size
	remain = size - (quotient * page_size)
	if remain :
		return quotient +1
	else :
		return quotient
