# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\Ala\Desktop\Cypress\BeoM_main.cydsn\BeoM_main.cyprj
# Date: Wed, 02 Sep 2020 22:37:52 GMT
#set_units -time ns
create_clock -name {UART_SCBCLK(FFB)} -period 708.33333333333326 -waveform {0 354.166666666667} [list [get_pins {ClockBlock/ff_div_2}]]
create_clock -name {SPIM_SCBCLK(FFB)} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/ff_div_3}]]
create_clock -name {SwClock(FFB)} -period 5000000 -waveform {0 2500000} [list [get_pins {ClockBlock/ff_div_8}] [get_pins {ClockBlock/ff_div_9}]]
create_clock -name {CyRouted1} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/dsi_in_0}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFCLK} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFCLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySYSCLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {UART_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 17 35} -nominal_period 708.33333333333326 [list]
create_generated_clock -name {SPIM_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 2 3} [list]
create_generated_clock -name {SwClock} -source [get_pins {ClockBlock/hfclk}] -edges {1 120001 240001} [list [get_pins {ClockBlock/udb_div_3}]]
create_generated_clock -name {SwClock_1} -source [get_pins {ClockBlock/hfclk}] -edges {1 4689 9377} -nominal_period 195333.33333333331 [list [get_pins {ClockBlock/udb_div_1}]]


# Component constraints for C:\Users\Ala\Desktop\Cypress\BeoM_main.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\Ala\Desktop\Cypress\BeoM_main.cydsn\BeoM_main.cyprj
# Date: Wed, 02 Sep 2020 22:37:47 GMT
