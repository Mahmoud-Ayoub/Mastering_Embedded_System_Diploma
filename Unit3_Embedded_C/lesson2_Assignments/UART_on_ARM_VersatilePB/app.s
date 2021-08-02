
app.o:     file format elf32-littlearm


Disassembly of section .text:

00000000 <main>:
   0:	e92d4800 	push	{fp, lr}
   4:	e28db004 	add	fp, sp, #4
   8:	e59f0008 	ldr	r0, [pc, #8]	; 18 <main+0x18>
   c:	ebfffffe 	bl	0 <Uart_Send_String>
  10:	e1a00000 	nop			; (mov r0, r0)
  14:	e8bd8800 	pop	{fp, pc}
  18:	00000000 	andeq	r0, r0, r0

Disassembly of section .data:

00000000 <string_buffer>:
   0:	7261656c 	rsbvc	r6, r1, #108, 10	; 0x1b000000
   4:	6e692d6e 	cdpvs	13, 6, cr2, cr9, cr14, {3}
   8:	7065642d 	rsbvc	r6, r5, sp, lsr #8
   c:	4d3a6874 	ldcmi	8, cr6, [sl, #-464]!	; 0xfffffe30
  10:	6f6d6861 	svcvs	0x006d6861
  14:	00006475 	andeq	r6, r0, r5, ror r4
	...

Disassembly of section .comment:

00000000 <.comment>:
   0:	43434700 	movtmi	r4, #14080	; 0x3700
   4:	4728203a 			; <UNDEFINED> instruction: 0x4728203a
   8:	4120554e 			; <UNDEFINED> instruction: 0x4120554e
   c:	45206d72 	strmi	r6, [r0, #-3442]!	; 0xfffff28e
  10:	6465626d 	strbtvs	r6, [r5], #-621	; 0xfffffd93
  14:	20646564 	rsbcs	r6, r4, r4, ror #10
  18:	6c6f6f54 	stclvs	15, cr6, [pc], #-336	; fffffed0 <main+0xfffffed0>
  1c:	69616863 	stmdbvs	r1!, {r0, r1, r5, r6, fp, sp, lr}^
  20:	3031206e 	eorscc	r2, r1, lr, rrx
  24:	3230322d 	eorscc	r3, r0, #-805306366	; 0xd0000002
  28:	34712d30 	ldrbtcc	r2, [r1], #-3376	; 0xfffff2d0
  2c:	6a616d2d 	bvs	185b4e8 <main+0x185b4e8>
  30:	2029726f 	eorcs	r7, r9, pc, ror #4
  34:	322e3031 	eorcc	r3, lr, #49	; 0x31
  38:	3220312e 	eorcc	r3, r0, #-2147483637	; 0x8000000b
  3c:	31303230 	teqcc	r0, r0, lsr r2
  40:	20333031 	eorscs	r3, r3, r1, lsr r0
  44:	6c657228 	sfmvs	f7, 2, [r5], #-160	; 0xffffff60
  48:	65736165 	ldrbvs	r6, [r3, #-357]!	; 0xfffffe9b
  4c:	Address 0x0000004c is out of bounds.


Disassembly of section .ARM.attributes:

00000000 <.ARM.attributes>:
   0:	00002b41 	andeq	r2, r0, r1, asr #22
   4:	61656100 	cmnvs	r5, r0, lsl #2
   8:	01006962 	tsteq	r0, r2, ror #18
   c:	00000021 	andeq	r0, r0, r1, lsr #32
  10:	45543505 	ldrbmi	r3, [r4, #-1285]	; 0xfffffafb
  14:	0506004a 	streq	r0, [r6, #-74]	; 0xffffffb6
  18:	01090108 	tsteq	r9, r8, lsl #2
  1c:	01140412 	tsteq	r4, r2, lsl r4
  20:	03170115 	tsteq	r7, #1073741829	; 0x40000005
  24:	01190118 	tsteq	r9, r8, lsl r1
  28:	061e011a 			; <UNDEFINED> instruction: 0x061e011a
