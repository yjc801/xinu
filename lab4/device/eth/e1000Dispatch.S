/* e1000Dispatch.S - e1000Dispatch */

#include <icu.s>
		.text
		.globl	e1000Dispatch
		.globl	e1000Interrupt
e1000Dispatch:
		pushal
		pushfl
		cli
		movb	$EOI,%al	# clear the interrupt
		outb	%al,$OCW1_2
		movb	$EOI,%al
		outb	%al,$OCW2_2

		call	e1000Interrupt

		popfl
		popal
		iret
