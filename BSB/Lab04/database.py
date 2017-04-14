from Bio import Entrez, SeqIO

Entrez.email = "jk.kuczynski@gmail.com"
phrase = input("Co chcesz wyszukac? ")
database = input("W ktorej bazie chcesz to znalezc? ")
handle = Entrez.esearch(db = database, term = phrase, retmax = 25)
records = Entrez.read(handle)
handle = Entrez.efetch(db = database, id = ','.join((records["IdList"])[0:5]), rettype = "fasta", retmode = "text")
records = SeqIO.to_dict(SeqIO.parse(handle, "fasta"))
print(records)
handle.close()