"""seq1 = "ACGCAGTA"
seq2 = "ACGGATA" 
dotplot = [["." for i in range(len(seq2))] for j in range(len(seq1))]

for i in range(len(dotplot)):
	for j in range(len(dotplot[i])):
		if seq1[i] == seq2[j]:
			dotplot[i][j] = "X"

print("  ", end = "")
for char in seq2:
	print(char, end = " ")
print()
for i in range(len(dotplot)):
	print(seq1[i], " ".join(dotplot[i]))"""

seq1 = "ABRACADABRACADABRA"
seq2 = "ABRACADABRACADABRA"
threshold = int(input("Prosze podac wartosc graniczna: "))
window = int(input("Prosze podac rozmiar okna: "))
cross = window//2
dotplot = [["." for i in range(len(seq2))] for j in range(len(seq1))]

for i in range(len(dotplot) - window + 1):
	for j in range(len(dotplot[i]) - window + 1):
		counter = 0
		for k in range(window):
			if seq1[i+k] == seq2[j+k]:
				counter += 1
		if counter >= threshold:
			dotplot[i+cross][j+cross] = 'X'

print("  ", end = "")
for char in seq2:
	print(char, end = " ")
print()
for i in range(len(dotplot)):
	print(seq1[i], " ".join(dotplot[i]))