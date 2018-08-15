from django.shortcuts import redirect, render
from django.contrib.auth.decorators import login_required

from .forms import RevCompForm, SeqContentForm
from .utils import complementary, count_words, revcomp, reverse

@login_required(login_url="myapp:login")
def seqcontent_view(request):
	if request.method == "POST":
		form = SeqContentForm(request.POST)
		if form.is_valid():
			sequence = form.cleaned_data["sequence"]
			word_size = form.cleaned_data["word_size"]
			
			return render(request, "biotools/seqcontent.html", {"results": count_words(sequence, word_size)})
	else:
		form = SeqContentForm()

	return render(request, "biotools/seqcontent.html", {"form": form})

def revcomp_view(request):
	methods = {"comp":complementary, "rev": reverse, "revcomp": revcomp}
	if request.method == "POST":
		form = RevCompForm(request.POST)
		if form.is_valid():
			sequence = form.cleaned_data["sequence"]
			method = form.cleaned_data["methods"]
			result = methods[method](sequence)
			
			return render(request, "biotools/revcomp.html", {"results": result})
	else:
		form = RevCompForm()

	return render(request, "biotools/revcomp.html", {"form": form})