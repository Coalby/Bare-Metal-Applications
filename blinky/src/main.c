#include <main.h>

int main(void) {

    // Sets ld2 to ON
    uint16_t ld2 =  PIN('A', 5);
    RCC->AHB1ENR |= BIT(PINBANK(ld2));
    gpio_set_mode(ld2, GPIO_MODE_OUTPUT);

    for (;;) {
        gpio_write(ld2, true);
        spin(999999);
        gpio_write(ld2, false);
        spin(999999);
    };  // Infinite Hang
    return 0;
}

// Startup Code
__attribute__((naked, noreturn)) void _reset(void) {
    extern long _sbss, _ebss, _sdata, _edata, _sidata;
    for (long *dst = &_sbss; dst < &_ebss; dst++) *dst = 0;
    for (long *dst = &_sdata, *src = &_sidata; dst < &_edata;) *dst++ = *src++;

    main();
}

extern void _estack(void);      // Defined in link.ld

__attribute__((section(".vectors"))) void (*const tab[16 + 96])(void) = {
    _estack, _reset
};