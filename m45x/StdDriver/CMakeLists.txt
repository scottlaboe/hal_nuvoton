# SPDX-License-Identifier: Apache-2.0

zephyr_library_sources_ifdef(CONFIG_HAS_NUMICRO_HAL     src/sys.c)

zephyr_library_sources(src/clk.c)
zephyr_library_sources_ifdef(CONFIG_HAS_NUMICRO_GPIO    src/gpio.c)

zephyr_library_sources_ifdef(CONFIG_HAS_NUMAKER_ADC     src/eadc.c)
zephyr_library_sources_ifdef(CONFIG_HAS_NUMAKER_DAC     src/dac.c)
zephyr_library_sources_ifdef(CONFIG_HAS_NUMAKER_PWM     src/pwm.c)
zephyr_library_sources_ifdef(CONFIG_HAS_NUMAKER_FMC     src/fmc.c)
zephyr_library_sources_ifdef(CONFIG_HAS_NUMAKER_I2C     src/i2c.c)
zephyr_library_sources_ifdef(CONFIG_HAS_NUMAKER_PDMA    src/pdma.c)
zephyr_library_sources_ifdef(CONFIG_HAS_NUMAKER_SPI     src/spi.c)
zephyr_library_sources_ifdef(CONFIG_HAS_NUMAKER_TMR     src/timer.c)
zephyr_library_sources_ifdef(CONFIG_HAS_NUMAKER_UART    src/uart.c)
zephyr_library_sources_ifdef(CONFIG_HAS_NUMAKER_USBD    src/usbd.c)
