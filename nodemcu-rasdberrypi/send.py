from requests_toolbelt import MultipartEncoder
import requests
import sys

URL = "http://bn3monkey.koreacentral.cloudapp.com:81/upload/"
filename = sys.argv[1]
m = MultipartEncoder(
	{
		'title' : filename,
		'file' : (filename, open(filename, 'r'), 'text/plane')
	}
)

r = requests.post(URL, data=m, headers = {'Content-Type' : m.content_type})
