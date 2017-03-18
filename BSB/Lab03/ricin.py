ricin_out = open("ricin_out.txt", "w")

with open("ricin.txt", "r") as f:
	ricin_out.write("{0}\t{1}\t{2}\t{3}\n".format("UniProtID", "Start", "End", "Domain name"))
	for line in f:
		if line.startswith("ID"):
			line = line.split()
			current_id = line[1]
		elif line.startswith("FT"):
			line = line.split()
			if line[1] == "DOMAIN":
				ricin_out.write("{0}\t{1}\t{2}\t{3}\n".format(current_id, line[2], line[3], ' '.join(line[4:])))
ricin_out.close()