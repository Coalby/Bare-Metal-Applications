// TODO: Describe stm32f446xx information here
#pragma once

// Used inttypes.h instead of stdint.h because of portability
#include <inttypes.h>
#include <stdbool.h>

struct gpio {
    volatile uint32_t MODER, OTYPER, OSPEEDR, PUPDR, IDR, ODR, BSRR, LCKR, AFR[2];
};

struct rcc {
    volatile uint32_t CR, PLLCFGR, CFGR, CIR, AHB1RSTR, AHB2RSTR, AHB3RSTR, 
        RESERVED1, APB1RSTR, APB2RSTR, RESERVED2[2], AHB1ENR, AHB2ENR, AHB3ENR,
        RESERVED3, APB1ENR, APB2ENR, RESERVED4[2], AHB1LPENR, AHB2LPENR, AHB3LPENR,
        RESERVED5, APB1LPENR, APB2LPENR, RESERVED6[2], BDCR, CSR, RESERVED7[2], SSCGR,
        PLLI2SCFR, PLLSAICFGR, DCKCFGR, CKGATENR, DCKCFGR2;
};

#define RCC                     ((struct rcc *) 0x40023800)

enum {GPIO_MODE_INPUT, GPIO_MODE_OUTPUT, GPIO_MODE_ALT_FUNCTION, GPIO_MODE_ANALOG};

#define BIT(x)                  (1UL << (x))
#define GPIO(bank)              ((struct gpio *) (0x40020000 + 0x400 * (bank)))
#define PIN(bank, num)          ((((bank) - 'A')) << 8 | (num))
#define PINNUM(pin)            (pin & 0xFF)
#define PINBANK(pin)             (pin >> 8)

static inline void gpio_set_mode(uint16_t pin, uint8_t mode) {
    struct gpio *gpio = GPIO(PINBANK(pin));
    int pinnum = PINNUM(pin);
    gpio->MODER &= ~(3U << (2 * pinnum));
    gpio->MODER |= ((mode & 3) << (2 * pinnum));
}

static inline void gpio_write(uint16_t pin, bool val) {
    struct gpio *gpio = GPIO(PINBANK(pin));
    gpio->BSRR = (BIT(PINNUM(pin)) << (val ? 0 : 16));
}

static inline void spin(volatile uint32_t count) {
    while (count--) __asm__("nop");
}