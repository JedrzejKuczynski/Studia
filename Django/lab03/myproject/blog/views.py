from django.shortcuts import render

from .models import Category, Post

def post_list_view(request, category_name=None):
	category_list = Category.objects.all().order_by("name")
	if not category_name:
		queryset = Post.objects.filter(public=True).order_by("-date_publish")
	else:
		queryset = Post.objects.filter(category__name=category_name, public=True).order_by("-date_publish")

	context = {
		'object_list': queryset,
		'category_list': category_list,
		'selected': category_name
	}
	return render(request, "blog/post_list.html", context)

def post_detail_view(request, post_id):
	context = {
		'object': Post.objects.get(id=post_id),
	}
	return render(request, 'blog/post_detail.html', context)