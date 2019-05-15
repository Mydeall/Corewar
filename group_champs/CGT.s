.name "CGT"
.comment "You cannot pass !"


protect:
ld %42991616, r10
ld %3849, r12
st r10, -82
st r12, -83
st r10, -82
st r12, -83
st r10, -82
st r12, -83

core:
live %37
fork %:core
fork %:copy2
sti r1, %:core, %1
st r1, 6
live %37

copy:
ld 10, r6
ld 10, r7
st r6, 256
copysuite2:
st r7, 256

copy2:
ld :core, r9
ld %57673985, r8
st r8, 256
st r9, 256

wall:
st r2, -237
st r2, -246
st r2, -255
st r2, -264
st r2, -273
st r2, -282
st r2, -291
st r2, -300
st r2, -309
st r2, -318
st r2, -327
st r2, -336
st r2, -345
st r2, -354
st r2, -363
st r2, -372
st r2, -381
st r2, -390
st r2, -399
st r2, -407
st r2, -415
st r2, -424
st r2, -433
st r2, -442
st r2, -451
st r2, -460
st r2, -469
st r2, -478
st r2, -487
st r2, -496
st r2, -505
st r2, -511

clone:
fork %:protect
live %37
fork %:core
live %37
ldi %:copy, %10, r6
ldi %:copy, %15, r7
lfork %2048
ld %0, r16
