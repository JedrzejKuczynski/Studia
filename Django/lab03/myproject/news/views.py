import json
import urllib.request

from django.shortcuts import render

def index(request, source="new-scientist"):
	api_key = "&apiKey=a7f17c40bb774a4ea2fb19896f4e3e60"
	url = "https://newsapi.org/v1/articles?source={0}&sortBy=top{1}".format(source, api_key)
	page = urllib.request.urlopen(url)
	string = page.read().decode()
	data = json.loads(string)
	sources = {"science": ["ars-technica", "hacker-news", "national-geographic", "new-scientist", "techradar"],
	           "news": ["bbc-news", "reuters"],
	           }
	sources = sorted(list(sources.items()))
	selected_site = source
	context = {"newsapi": data,
			   "sources": sources,
			   "selected": selected_site
	}
	return render(request, "news/index.html", context)
