from requests_toolbelt import MultipartEncoder
import requests
import sys

URL = "http://bn3monkey.koreacentral.cloudapp.azure.com:81/upload/"
filename = sys.argv[1]
m = MultipartEncoder(
	{
		'title' : filename,
		'file' : (filename, open(filename, 'rb'), 'text/plane')
	}
)

r = requests.post(URL, data=m, headers = {'Content-Type' : m.content_type})

print(r.request)
print(r.status_code)
print(r.json)
print(r.text)
