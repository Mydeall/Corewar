.name		"sti"
.comment	""

	ld %42, r1
	ld %50, r2
	ld %100, r3
	sti r1, %5, %10
	sti r1, r2, r3
	sti r1, %0, r3
	sti r1, %0, r3
	sti r1, %0, r3
	
