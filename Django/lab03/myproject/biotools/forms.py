from django import forms

class SeqContentForm(forms.Form):
	sequence = forms.CharField(widget=forms.Textarea, min_length=5, required=True)
	word_size = forms.IntegerField(initial=1, required=True)

	def clean_sequence(self):
		sequence = self.cleaned_data['sequence']
		return sequence.upper()

	def clean(self):
		sequence = self.cleaned_data["sequence"]
		word_size = self.cleaned_data["word_size"]

		if word_size and sequence:
			if len(sequence) < word_size:
				raise forms.ValidationError("Sequence cannot be shorter than word size.")

class RevCompForm(forms.Form):
	sequence = forms.CharField(widget=forms.Textarea, required=True)
	methods_choice = [("rev", "Reverse"), ("comp", "Complementary"), ("revcomp", "Reverse Complementary")]
	methods = forms.ChoiceField(choices=methods_choice)

	def clean_sequence(self):
		sequence = self.cleaned_data['sequence']
		sequence = sequence.split("\r\n")

		if sequence[0].startswith(">"):
			sequence = sequence[1:]

		sequence = "".join(char for char in sequence if char is not "\r\n")

		return sequence.upper()