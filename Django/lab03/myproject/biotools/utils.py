def count_words(sequence, word_size):
	d = {}

	for i in range(len(sequence) - word_size + 1):
		word = sequence[i:i+word_size]
		if word not in d:
			d[word] = 0
		d[word] += 1

	total = sum(d.values())

	for word, cnt in d.items():
		d[word] = [cnt, cnt/total]

	return(d)

def reverse(sequence):
	return (sequence[::-1])

def complementary(sequence):
	d = {
		"A": "T",
		"T": "A",
		"G": "C",
		"C": "G",
	}

	return ("".join(d[char] for char in sequence))

def revcomp(sequence):
	return reverse(complementary(sequence))