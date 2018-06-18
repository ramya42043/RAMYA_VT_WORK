import pprint
def chunks(l, n):
	"""Yield successive n-sized chunks from l."""
	for i in range(0, len(l), n):
		print l[i:i + n]
      		yield tuple(l[i:i + n])



pprint.pprint(list(chunks(range(1, 10), 3)))
