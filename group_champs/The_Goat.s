.name		"The Goat"
.comment	"Half man, half amazing"


		zjmp %-400
	#	fork %:back
		ld 48,r2			#5
		ld 47,r3			#5
		ld 46,r4			#5
		ld 45,r5			#5
		ld 44,r6			#5
		ld %0,r14			#7
dupli:		live %1			#5

fork:		live %1
		fork %:write
		#ld %0,r14			#5
		zjmp %40			#3

write:		st r2,120			#5
		st r3,219			#5
		st r4,218			#5
		st r5,217			#5
		st r6,216			#5
		#st r6,120			#5
		#zjmp %:fork			#5
		#zjmp %-60			#5
		fork %:dup

dup:	live %1
		fork %:fork
		fork %:write

writeb:		st r2,120			#5
		st r3,119			#5
		st r4,118			#5
		st r5,117			#5
		st r6,116			#5
		#st r6,120			#5
		#zjmp %:fork			#5
		#zjmp %-60			#5
		fork %:write

repli:	live %1
		st r2,200
		st r2,200
		ld %0,r15
	#	zjmp %-400
