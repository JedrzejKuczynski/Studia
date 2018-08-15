from django.contrib.auth import authenticate, login, logout
from django.contrib.auth.decorators import login_required
from django.http import HttpResponse
from django.shortcuts import redirect, render
from django.contrib.auth.models import User

import random
from .forms import UserLoginForm, UserSignupForm

# Create your views here.

def home(request):
	context={}
	return render(request, "myapp/my_home.html", context)

def contact(request):
	context = {}
	return render(request, "myapp/contact.html", context)

def about(request):
	lucky_number = random.randint(1, 10)
	unlucky_number = random.randint(1, 10)
	tvseries = [
    {'title': 'Game of Thrones', 'seasons': 7, 'genre': 'fantasy', 'year': 2011, 'ongoing': True},
    {'title': 'Breaking Bad', 'seasons': 5, 'genre': 'drama', 'year': 2008, 'ongoing': False},
    {'title': 'Sons of Anarchy', 'seasons': 7, 'genre': 'crime drama', 'year': 2008, 'ongoing': False},
    {'title': 'The Big Bang Theory', 'seasons': 10, 'genre': 'comedy', 'year': 2007, 'ongoing': True},
    {'title': 'Silicon Valley', 'seasons': 4, 'genre': 'comedy', 'year': 2014, 'ongoing': True},
    {'title': 'The Walking Dead', 'seasons': 7, 'genre': 'horror', 'year': 2010, 'ongoing': True},
	]
	context = {
		"lucky_number":lucky_number,
		"unlucky_number":unlucky_number,
		"tvseries": tvseries
	}
	return render(request, "myapp/about.html", context)

def login_view(request):
	if request.method == "POST":
		form = UserLoginForm(request.POST)
		if form.is_valid():
			username = form.cleaned_data["username"]
			password = form.cleaned_data["password"]
			user = authenticate(username=username, password=password)
			if user is not None:
				login(request, user)
				return redirect("myapp:home")
	else:
		form = UserLoginForm()
	context = {"form": form}
	return render(request, "myapp/login.html", context)

@login_required(login_url="myapp:home")
def logout_view(request):
	logout(request)
	return HttpResponse("<p>You've been successfully log out.</p> <a href='/'>Home Page</a>")
	#return redirect("myapp:home")

def signup(request):
	if request.method == "POST":
		form = UserSignupForm(request.POST)
		if form.is_valid():
			username = form.cleaned_data["username"]
			password = form.cleaned_data["password"]
			email = form.cleaned_data["email"]
			User.objects.create_user(username=username, password=password, email=email)
			return redirect("myapp:login")
	else:
		form = UserSignupForm()
	context = {"form": form}
	return render(request, "myapp/signup.html", context)