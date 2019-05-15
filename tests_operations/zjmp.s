.name		"zmjp"
.comment	""

	ld %48, r2
	zjmp %-12
	ld %0, r2
	live %1
	fork %:pos
	fork %:stuck

	neg:
	zjmp %-511

	pos:
	zjmp %511

	stuck:
	zjmp %-512
	zjmp %512
