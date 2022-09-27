/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Copyright (c) 2017, Sebastian Kunze <sebastian.kunze@hh.se>
    All rights reserved.
*/

/* Startup code for Raspberry Pi 3 */
#include <stdint.h>
#include <string.h>

__asm__ (
	/* declare function */
	".section .startup\n"

	".global Entry\n"
	".global _get_stack_pointer\n"
	".global _exception_table\n"
	".global _enable_interrupts\n"

	 				// From the ARM ARM (Architecture Reference Manual). Make sure you get the
	 				// ARMv5 documentation which includes the ARMv6 documentation which is the
	 				// correct processor type for the Broadcom BCM2835. The ARMv6-M manuals
	 				// available on the ARM website are for Cortex-M parts only and are very
	 				// different.

	 				// See ARM section A2.2 (Processor Modes)

	".equ    CPSR_MODE_USER,         0x10\n"
	".equ    CPSR_MODE_FIQ,          0x11\n"
	".equ    CPSR_MODE_IRQ,          0x12\n"
	".equ    CPSR_MODE_SVR,          0x13\n"
	".equ    CPSR_MODE_ABORT,        0x17\n"
	".equ    CPSR_MODE_HYPERVISOR,   0x1A\n"
	".equ    CPSR_MODE_UNDEFINED,    0x1B\n"
	".equ    CPSR_MODE_SYSTEM,       0x1F\n"
	".equ    CPSR_MODE_MASK,         0x1F\n" 				// Used to mask the Mode bit in the CPSR

	 				// See ARM section A2.5 (Program status registers)
	".equ    CPSR_IRQ_INHIBIT,       0x80\n"
	".equ    CPSR_FIQ_INHIBIT,       0x40\n"
	".equ    CPSR_THUMB,             0x20\n"

	 				// See ARM section B3.3
	 				// The value can be decoded into constituent parts, but can be gathered easily by running
	 				// cat /proc/cpuinfo when booting any of the RPi boards into Linux
	".equ    MAINID_ARMV6,           0x410FB767\n"
	".equ    MAINID_ARMV7,           0x410FC073\n"
	".equ    MAINID_ARMV8,           0x410FD034\n"

	 				// See the following: https:				//github.com/raspberrypi/tools/blob/master/armstubs/armstub7.S
	".equ    GIC_DISTB,              0xff841000\n"
	".equ    GICC_PMR,               0x4\n"
	".equ    GICD_CTRLR,             0x0\n"
	".equ    GICD_IGROUPR,           0x80\n"
	".equ    GIC_CPUB_offset,        0x1000\n"

	".equ    SCTLR_ENABLE_DATA_CACHE,        0x4\n"
	".equ	SCTLR_ENABLE_BRANCH_PREDICTION, 0x800\n"
	".equ	SCTLR_ENABLE_INSTRUCTION_CACHE, 0x1000\n"

	"#define PRESCALER_2711	0xff800008\n"
	"#define MBOX_2711	0xff8000cc\n"

	 				// At the start address we have a "jump table", specifically laid out to allow jump to an address that is stored in
	 				// memory. This table must be laid out exactly as shown (including the instruction ldr pc,)
    ".type Entry, %function\n"                    
	"Entry:\n"
	"    ldr pc, _reset_h\n"
	"    ldr pc, _undefined_instruction_vector_h\n"
	"    ldr pc, _software_interrupt_vector_h\n"
	"    ldr pc, _prefetch_abort_vector_h\n"
	"    ldr pc, _data_abort_vector_h\n"
	"    ldr pc, _unused_handler_h\n"
	"    ldr pc, _interrupt_vector_h\n"
	"    ldr pc, _fast_interrupt_vector_h\n"

	"_reset_h:                           .word   _reset_\n"
	"_undefined_instruction_vector_h:    .word   undefined_instruction_vector\n"
	"_software_interrupt_vector_h:       .word   software_interrupt_vector\n"
	"_prefetch_abort_vector_h:           .word   prefetch_abort_vector\n"
	"_data_abort_vector_h:               .word   data_abort_vector\n"
	"_unused_handler_h:                  .word   _reset_\n"
	"_interrupt_vector_h:                .word   interrupt_vector\n"
	"_fast_interrupt_vector_h:           .word   fast_interrupt_vector\n"

	"_reset_:\n"
	     				// Determine what mode the cpu has started up in. When we get to the very start of the ARM execution we can
	     				// extract the Current Program Status Register value and mask off the Mode field which is defined in the ARM
	     				// Architecture Reference Manual for ARMV6 ARMV7 and ARMV8 as M[4:0] - in other words the 5 lowest bits
	     				// Do this in a high register so as not to overwrite anything the bootloader has passed over (such as atags)
	"    mrs r12, CPSR\n"
	"    and r12, #CPSR_MODE_MASK\n"    				// Zero all bits except the CPSR_MODE_MASK bits to be left with the mode value in r11

	     				// Store the CPSR start mode in a "global variable" that is accessible to all (including the C world)
	"    ldr r11, =_cpsr_startup_mode\n"
	"    str r12, [r11]\n"

	     				// Check to see if we're BCM2385 (RPI0/1) - these processors only have one core and so we can go ahead and
	     				// continue executing the startup code. However, all other RPI models have processors which have multiple cores.
	     				// When the ARM processor starts all four processors run the same code. 'tis weird, n'est pas?
	     				// In order to get some sanity back to our world we "park" the remaining cores and just work with one core. We're
	     				// not yet at the point of requiring parallel processing.

	     				// Skip the Hypervisor mode check and core parking when RPI0/1
	"    mrc p15, 0, r11, c0, c0, 0\n"
	"    ldr r10, =#MAINID_ARMV6\n"
	"    cmp r11, r10\n"
	"    beq _setup_interrupt_table\n"

	     				// Did we start up in hypervisor mode? If we didn't go ahead an park the cpus, we can then get back to SVC mode
	     				// later on
	"    cmp r12, #CPSR_MODE_HYPERVISOR\n"
	"    bne _multicore_park\n"

	     				// We're in hypervisor mode and we need to switch back in order to allow us to continue successfully
	"    mrs r12, CPSR\n"
	"    bic r12, r12, #CPSR_MODE_MASK\n"
	"    orr r12, r12, #(CPSR_MODE_SVR | CPSR_IRQ_INHIBIT | CPSR_FIQ_INHIBIT )\n"
	"    msr SPSR_cxsf, r12\n"

	"    add lr, pc, #4\n"
	"    .word 0xE12EF30E\n"
	"    .word 0xE160006E\n"
    
	"_multicore_park:\n"
	     				// On RPI2/3 make sure all cores that are not core 0 branch off to an infinite loop to make them enter a spinlock
	     				// We will then only operate with core 0 and setup stack pointers and the like for core 0
	"    mrc p15, 0, r12, c0, c0, 5\n"
	"    ands r12, #0x3\n"
	"    bne _inf_loop\n"

	"_setup_interrupt_table:\n"

	"    mov     r0, #0x8000\n"
	"    mov     r1, #0x0000\n"
	"    ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8, r9}\n"
	"    stmia   r1!,{r2, r3, r4, r5, r6, r7, r8, r9}\n"
	"    ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8, r9}\n"
	"    stmia   r1!,{r2, r3, r4, r5, r6, r7, r8, r9}\n"

	     				// We're going to use interrupt mode, so setup the interrupt mode
	     				// stack pointer which differs to the application stack pointer:
	"    mov r0, #(CPSR_MODE_IRQ | CPSR_IRQ_INHIBIT | CPSR_FIQ_INHIBIT )\n"
	"    msr cpsr_c, r0\n"
	"    ldr sp, =0x7000\n"

	     				// Switch back to supervisor mode (our application mode) and
	     				// set the stack pointer. Remember that the stack works its way
	     				// down memory, our heap will work it's way up from after the
	     				// application.\n"
	"    mov r0, #(CPSR_MODE_SVR | CPSR_IRQ_INHIBIT | CPSR_FIQ_INHIBIT )\n"
	"    msr cpsr_c, r0\n"
	"    ldr sp, =0x8000\n"

	     				// Enable L1 Cache -------------------------------------------------------

	     				// R0 = System Control Register
	"    mrc p15,0,r0,c1,c0,0\n"

	     				// Enable caches and branch prediction
	"    orr r0,#SCTLR_ENABLE_BRANCH_PREDICTION\n"
	"    orr r0,#SCTLR_ENABLE_DATA_CACHE\n"
	"    orr r0,#SCTLR_ENABLE_INSTRUCTION_CACHE\n"

	     				// System Control Register = R0
	"    mcr p15,0,r0,c1,c0,0\n"

	     				// Enable VFP ------------------------------------------------------------

	     				// r1 = Access Control Register
	// "    MRC p15, #0, r1, c1, c0, #2\n"
	     				// enable full access for p10,11
	// "    ORR r1, r1, #(0xf << 20)\n"
	     				// Access Control Register = r1
	// "    MCR p15, #0, r1, c1, c0, #2\n"
	// "    MOV r1, #0\n"
	     				// flush prefetch buffer because of FMXR below
	// "    MCR p15, #0, r1, c7, c5, #4\n"
	     				// and CP 10 & 11 were only just enabled
	     				// Enable VFP itself
	// "    MOV r0,#0x40000000\n"
	     				// FPEXC = r0
	// "    FMXR FPEXC, r0\n"

	     				// The c-startup function which we never return from. This function will
	     				// initialise the ro data section (most things that have the const
	     				// declaration) and initialise the bss section variables to 0 (generally
	     				// known as automatics). It'll then call main, which should never return.
	"    bl SystemInit\n"

	     				// If main does return for some reason, just catch it and stay here.
	"_inf_loop:\n"
	"    b _inf_loop\n"


	 				// A 32-bit value that represents the processor mode at startup
	"_cpsr_startup_mode:  .word    0x0\n"
	"_osc:                .word    54000000\n"
	"_value:              .word    0x63fff\n"
	"_mbox:               .word    0xff8000cc\n"

	"_get_stack_pointer:\n"
	     				// Return the stack pointer value
	"    str     sp, [sp]\n"
	"    ldr     r0, [sp]\n"

	     				// Return from the function
	"    mov     pc, lr\n"

	"_enable_interrupts:\n"
	"    mrs     r0, cpsr\n"
	"    bic     r0, r0, #CPSR_IRQ_INHIBIT\n"
	"    msr     cpsr_c, r0\n"
	"    cpsie   i\n"

	"    mov     pc, lr\n"    
);

void SystemInit(void)
{
	extern char _sbss, _ebss;

	typedef void (*func)(void);
	extern func __preinit_array_start[], __preinit_array_end;
	extern func __init_array_start[], __init_array_end;
	extern func __fini_array_start[], __fini_array_end;

	extern int main();

	/* clear .bss */
	memset(&_sbss, 0, &_ebss - &_sbss);

	/* call preinit_array */
	for(int i = 0; i < &__preinit_array_end - __preinit_array_start; i++)
		__preinit_array_start[i]();

	/* call static constructors */
	for(int i = 0; i < &__init_array_end - __init_array_start; i++)
		__init_array_start[i]();

	/* call main */
	main();

	/* call static destructors */
	for(int i = &__fini_array_end - __fini_array_start - 1; i >= 0; i--)
		__fini_array_start[i]();

	/* and never return */
	while(1) {
		__asm__ volatile("CPSID I");
		__asm__ volatile("WFI");
	}
}