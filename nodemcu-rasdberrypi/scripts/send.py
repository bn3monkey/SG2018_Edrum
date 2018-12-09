from requests_toolbelt import MultipartEncoder
import requests
import sys

def sendFile(song_name,song_artist,creator_ID,f_name):
	URL = "http://106.10.34.243/songs/"
	#filename = sys.argv[1]

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

