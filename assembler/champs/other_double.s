.name "alivetayin' alive"
.comment "Ha, Ha, Ha, stayiiiiin' aliiiiiiiiiive"
sti r1, %:erreur, r1			;change live by the right value
sti	r1, %:test, %1			;change live by the right value
sti	r1, %:other, %1			;change live by the right value
erreur:
test:
live %4
other: