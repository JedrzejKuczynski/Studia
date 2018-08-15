from django import forms

class UserLoginForm(forms.Form):
	username = forms.CharField(required=True)
	password = forms.CharField(widget=forms.PasswordInput, required=True)

class UserSignupForm(forms.Form):
	username = forms.CharField(required=True)
	password = forms.CharField(widget=forms.PasswordInput, required=True)
	confirm_password = forms.CharField(widget=forms.PasswordInput, required=True)
	email = forms.EmailField(required=True)

	def clean(self):
		password = self.cleaned_data["password"]
		confirm_password = self.cleaned_data["confirm_password"]
		if password != confirm_password:
			raise forms.ValidationError("Passwords don't match each other!")