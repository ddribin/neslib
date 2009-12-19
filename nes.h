	
	.include "ines.h"
	
.define	bit2mask(bitnum) (1 << bitnum)
.define bits2mask(bits, bitnum) (bits << bitnum)

	;; PPU Registers
	ppuctrl		:= $2000
	ppuctrl_nametable_bit = 0
	ppuctrl_nametable_addr_2000 = bits2mask(%00, ppuctrl_nametable_bit)
	ppuctrl_nametable_addr_2400 = bits2mask(%01, ppuctrl_nametable_bit)
	ppuctrl_nametable_addr_2800 = bits2mask(%10, ppuctrl_nametable_bit)
	ppuctrl_nametable_addr_2c00 = bits2mask(%11, ppuctrl_nametable_bit)
	ppuctrl_vram_inc_by_32 = bit2mask(2)
	ppuctrl_sprite_addr_1000 = bit2mask(3)
	ppuctrl_nmi_enable = bit2mask(7)
	
	ppumask		:= $2001
	ppumask_grayscale = bit2mask(0)
	ppumask_bg_left8_enable = bit2mask(1)
	ppumask_sprit_left8_enable = bit2mask(1)
	ppumask_bg_enable = bit2mask(3)
	ppumask_sprite_enable = bit2mask(4)
	
	ppustatus	:= $2002
	ppustatus_sprite_overflow = bit2mask(5)
	ppustatus_sprite_0_hit = bit2mask(6)
	ppustatus_vblank = bit2mask(7)
	
	oamaddr		:= $2003
	oamdata		:= $2004
	ppuscroll	:= $2005
	ppuaddr		:= $2006
	ppudata		:= $2007

	sq1_vol		:= $4000
	sq1_sweep	:= $4001
	sq1_lo		:= $4002
	sq1_hi		:= $4003

	sq2_vol		:= $4004
	sq2_sweep	:= $4005
	sq2_lo		:= $4006
	sq2_hi		:= $4007

	tri_linear	:= $4008
	tri_unused	:= $4009
	tri_lo		:= $400a
	tri_hi		:= $400b

	noise_vol	:= $400c
	noice_unused	:= $400d
	noise_lo	:= $400e
	noise_hi	:= $400f
	
	dmc_freq	:= $4010
	dmc_raw		:= $4011
	dmc_start	:= $4012
	dmc_len		:= $4013
	
	oamdma		:= $4014
	
	snd_chn		:= $4015
	snd_chn_sq1_len_enable = bit2mask(0)
	snd_chn_sq2_len_enable = bit2mask(1)
	snd_chn_tri_len_enable = bit2mask(2)
	snd_chn_noise_len_enabled = bit2mask(3)
	
	apuframe	:= $4017
	apuframe_mode_5_step = bit2mask(7)
	apuframe_irq_disable = bit2mask(6)

	joy1	:= $4016
	joy2	:= $4017
	
	joy_button_a		= bit2mask(7)
	joy_button_b		= bit2mask(6)
	joy_button_select	= bit2mask(5)
	joy_button_start	= bit2mask(4)
	
	joy_button_up 		= bit2mask(3)
	joy_button_down 	= bit2mask(2)
	joy_button_left 	= bit2mask(1)
	joy_button_right 	= bit2mask(0)

	;; VRAM addresses
	pattern_table_0		:= $0000
	pattern_table_1		:= $1000
	nametable_0_base	:= $2000
	attribute_0_base	:= $2c30
	nametable_1_base	:= $2400
	attribute_1_base	:= $27c0
	nametable_2_base	:= $2800
	attribute_2_base	:= $2bc0
	nametable_3_base	:= $2c00
	attribute_3_base	:= $2fc0

	palette_bg_base		:= $3f00
	palette_sprite_base	:= $3f10

	;; Some helpful values
	sprite_offscreen = $fe

	;; Common color values
	color_black 	= $0f
	color_white 	= $30
	color_blue 	= $02
	color_red 	= $06
	color_orange	= $27
	color_green 	= $29
	color_purple	= $13
	color_dark_gray	= $00
	color_light_gray = $10

	;; Some helper macros

;;; Sets ppuaddr
.macro	set_ppuaddr addr
	lda	#.hibyte(addr)
	sta	ppuaddr
	lda	#.lobyte(addr)
	sta	ppuaddr
.endmacro

.macro set_ppuscroll_xy scroll_x, scroll_y
	lda	scroll_x
	sta	ppuscroll
	lda	scroll_y
	sta	ppuscroll
.endmacro

;;; Wait for a vblank by waiting until bit 7 of PPUSTATUS goes high.
.macro	wait_vblank
	.local wait
wait:
	bit	ppustatus
	bpl	wait
.endmacro


;;; Writes $01 then $00 to joy1 port which resets latches.
.macro	joy_prepare
	lda	#$01
	sta	joy1
	lda	#$00
	sta	joy1
.endmacro

;;; Writes a null terminated string to the PPU.
.macro write_string_to_ppu string
	.local loop, done

	ldy	#$00
loop:
	lda	string, y
	beq	done		; Null terminated
	sta	ppudata
	iny
	bne	loop
done:
.endmacro
	
; Local Variables: 
; mode: asm
; End: 
