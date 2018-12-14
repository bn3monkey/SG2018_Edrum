from requests_toolbelt import MultipartEncoder
import requests, json
import sys
from urllib import urlopen

URL = "http://106.10.34.243/songs/"
for i in range(1,100) :
    url = URL + str(i)
    requests.delete(url)
