/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Copyright (c) 2016, Sebastian Kunze <sebastian.kunze@hh.se>
    All rights reserved.
*/

#include <stdint.h>

/* Register Typedefs */
typedef const uint32_t un;
typedef const uint32_t ro;
typedef       uint32_t wo;
typedef       uint32_t rw;

/* General Purpose I/O (GPIO) */
struct __attribute__((packed)) GPIO_s {
    rw GPFSEL0;		/* GPIO Function Select 0 */
    rw GPFSEL1;		/* GPIO Function Select 1 */
    rw GPFSEL2;		/* GPIO Function Select 2 */
    rw GPFSEL3;		/* GPIO Function Select 3 */
    rw GPFSEL4;		/* GPIO Function Select 4 */
    rw GPFSEL5;		/* GPIO Function Select 5 */
    un Res0[1];
    wo GPSET0;		/* GPIO Pin Output Set 0 */
    wo GPSET1;		/* GPIO Pin Output Set 1 */
    un Res1[1];
    wo GPCLR0;		/* GPIO Pin Output Clear 0 */
    wo GPCLR1;		/* GPIO Pin Output Clear 1 */
    un Res2[1];
    ro GPLEV0;		/* GPIO Pin Level 0 */
    ro GPLEV1;		/* GPIO Pin Level 1 */
    un Res3[1];
    rw GPEDS0;		/* GPIO Pin Event Detect Status 0 */
    rw GPEDS1;		/* GPIO Pin Event Detect Status 1 */
    un Res4[1];
    rw GPREN0;		/* GPIO Pin Rising Edge Detect Enable 0 */
    rw GPREN1;		/* GPIO Pin Rising Edge Detect Enable 1 */
    un Res5[1];
    rw GPFEN0;		/* GPIO Pin Falling Edge Detect Enable 0 */
    rw GPFEN1;		/* GPIO Pin Falling Edge Detect Enable 1 */
    un Res6[1];
    rw GPHEN0;		/* GPIO Pin High Detect Enable 0 */
    rw GPHEN1;		/* GPIO Pin High Detect Enable 1 */
    un Res7[1];
    rw GPLEN0;		/* GPIO Pin Low Detect Enable 0 */
    rw GPLEN1;		/* GPIO Pin Low Detect Enable 1 */
    un Res8[1];
    rw GPAREN0;		/* GPIO Pin Async Rising Edge Detect 0 */
    rw GPAREN1;		/* GPIO Pin Async Rising Edge Detect 1 */
    un Res9[1];
    rw GPAFEN0;		/* GPIO Pin Async Falling Edge Detect 0 */
    rw GPAFEN1;		/* GPIO Pin Async Falling Edge Detect 1 */
    un Res10[1];
    rw GPPUD;		/* GPIO Pin Pull-up/down Enable */
    rw GPPUDCLK0;	/* GPIO Pin Pull-up/down Enable Clock 0 */
    rw GPPUDCLK1;	/* GPIO Pin Pull-up/down Enable Clock 1 */
};

#define GPIO     ((volatile struct GPIO_s*)0x3F200000)

/** @brief See Section 7.5 of the BCM2836 ARM Peripherals documentation, the base
    address of the controller is actually xxxxB000, but there is a 0x200 offset
    to the first addressable register for the interrupt controller, so offset the
    base to the first register */
#define RPI_INTERRUPT_CONTROLLER_BASE   ( PERIPHERAL_BASE + 0xB200UL )

/** @brief Bits in the Enable_Basic_IRQs register to enable various interrupts.
    See the BCM2835 ARM Peripherals manual, section 7.5 */
#define RPI_BASIC_ARM_TIMER_IRQ         (1 << 0)
#define RPI_BASIC_ARM_MAILBOX_IRQ       (1 << 1)
#define RPI_BASIC_ARM_DOORBELL_0_IRQ    (1 << 2)
#define RPI_BASIC_ARM_DOORBELL_1_IRQ    (1 << 3)
#define RPI_BASIC_GPU_0_HALTED_IRQ      (1 << 4)
#define RPI_BASIC_GPU_1_HALTED_IRQ      (1 << 5)
#define RPI_BASIC_ACCESS_ERROR_1_IRQ    (1 << 6)
#define RPI_BASIC_ACCESS_ERROR_0_IRQ    (1 << 7)


/** @brief The interrupt controller memory mapped register set */
typedef struct {
    volatile uint32_t IRQ_basic_pending;
    volatile uint32_t IRQ_pending_1;
    volatile uint32_t IRQ_pending_2;
    volatile uint32_t FIQ_control;
    volatile uint32_t Enable_IRQs_1;
    volatile uint32_t Enable_IRQs_2;
    volatile uint32_t Enable_Basic_IRQs;
    volatile uint32_t Disable_IRQs_1;
    volatile uint32_t Disable_IRQs_2;
    volatile uint32_t Disable_Basic_IRQs;
    } rpi_irq_controller_t;