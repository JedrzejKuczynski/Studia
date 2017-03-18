nucleotides = {
	
	'A': 'T',
	'T': 'A',
	'G': 'C',
	'C': 'G',
}

def complement_dna(seq):
	return "".join(nucleotides[nucleotide] for nucleotide in seq)

# print(complement_dna("AATTGGCC"))

def seq_content(seq):
	return {'A': seq.count('A')/len(seq), 'T': seq.count('T')/len(seq), 'G': seq.count('G')/len(seq), 'C': seq.count('C')/len(seq)}

print(seq_content("ATGC"))