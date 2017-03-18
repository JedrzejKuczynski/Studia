from Bio import SeqIO

d = {}
out = open('out.fasta', 'w')
for seq_record in SeqIO.parse("many.fasta", "fasta"):
	d[seq_record.id] = len(seq_record.seq)
	out.write("{0}: {1}\n".format(seq_record.id, len(seq_record.seq)))

mean = sum([float(d[key]) for key in d])/len(d)
print(mean)
out.close()