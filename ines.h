	
	INesMirroringHorizontal = 0
	INesMirroringVertical = 1

	;; Some common mappers
	INesMapperNone = 0
	INesMapperMMC1 = 1
	INesMapperUNROM = 2
	INesMapperCNROM = 3
	INesMapperMMC3 = 4
	INesMapperMMC5 = 5
	
.macro INesPrgSizeInKilobytes size
	.assert size > 0, error, "Size must be greater than zero"
	.assert ((size & $f) = 0), error, "Size must be a multiple of 16k"
	INesPrgSize = size / 16
.endmacro
	
.macro INesChrSizeInKilobytes size
	.assert size > 0, error, "Size must be greater than zero"
	.assert ((size & $7) = 0), error, "Size must be a multiple of 8k"
	INesChrSize = size / 8
.endmacro
	
.macro INesHeaderStart
	.pushseg
	.segment "HEADER"
.endmacro
	
.macro INesHeaderEnd
	;; iNES header identifier: "NES" + $1A. Don't use a string in case
	;; a non-standard charmap is setup
	.byte	$4e, $45, $53, $1A
	.byte	INesPrgSize	; PRG code
	.byte	INesChrSize	; CHR data
	.byte	((INesMapper & $0F) << 4) | INesMirroring
	.byte	(INesMapper & $F0)
	
	;; Filler
	.byte	$00, $00, $00, $00
	.byte	$00, $00, $00, $00
	
	.popseg
.endmacro
	
	
; Local Variables: 
; mode: asm
; End: 
