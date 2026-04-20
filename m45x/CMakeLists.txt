# SPDX-License-Identifier: Apache-2.0

zephyr_include_directories(StdDriver/inc)
zephyr_include_directories(Devices/M451/Include)

zephyr_sources_ifdef(CONFIG_SOC_SERIES_M45X Devices/M451/system_M451Series.c)

add_subdirectory(StdDriver)
