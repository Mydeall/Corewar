#!/bin/bash


if [[ $# -eq 1 ]]
	then
		OFF_EXT="_off"
		./asm_off "$1.s"
		mv "$1.cor" "$1$OFF_EXT.cor"
		./asm "$1.s"
		diff "$1.cor" "$1$OFF_EXT.cor"
fi
