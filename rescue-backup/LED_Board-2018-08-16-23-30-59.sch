EESchema Schematic File Version 2
LIBS:LED_Board-rescue
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:LED_Board-cache
EELAYER 25 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ATMEGA328P-A-RESCUE-LED_Board IC?
U 1 1 5B69AF43
P 3350 6200
F 0 "IC?" H 2500 7450 50  0000 L BNN
F 1 "ATMEGA328P-A" H 3850 4800 50  0000 L BNN
F 2 "TQFP32" H 3500 6600 50  0000 C CIN
F 3 "" H 3450 6200 50  0000 C CNN
	1    3350 6200
	1    0    0    -1  
$EndComp
$Comp
L FT232RL U?
U 1 1 5B73C6FC
P 5650 5750
F 0 "U?" H 5650 6500 60  0000 C CNN
F 1 "FT232RL" H 6150 4800 60  0000 C CNN
F 2 "" H 5650 5750 60  0000 C CNN
F 3 "" H 5650 5750 60  0000 C CNN
	1    5650 5750
	1    0    0    -1  
$EndComp
$Comp
L WS2813 LED?
U 1 1 5B73C996
P 7400 5300
F 0 "LED?" H 7400 5600 60  0000 C CNN
F 1 "WS2813" H 7600 5000 60  0000 C CNN
F 2 "" H 7400 5300 60  0000 C CNN
F 3 "" H 7400 5300 60  0000 C CNN
	1    7400 5300
	1    0    0    -1  
$EndComp
$Comp
L USB_OTG P?
U 1 1 5B73CB4E
P 1200 4850
F 0 "P?" H 1525 4725 50  0000 C CNN
F 1 "USB_OTG" V 900 4850 50  0000 C CNN
F 2 "" V 1150 4750 50  0000 C CNN
F 3 "" V 1150 4750 50  0000 C CNN
	1    1200 4850
	0    -1   1    0   
$EndComp
$Comp
L Q_PMOS_GDS Q?
U 1 1 5B750B6C
P 3000 1750
F 0 "Q?" H 3300 1800 50  0000 R CNN
F 1 "Q_PMOS_GDS" H 3650 1700 50  0001 R CNN
F 2 "" H 3200 1850 50  0000 C CNN
F 3 "" H 3000 1750 50  0000 C CNN
	1    3000 1750
	0    1    -1   0   
$EndComp
$Comp
L R R?
U 1 1 5B750D5E
P 2350 1900
F 0 "R?" V 2430 1900 50  0000 C CNN
F 1 "R" V 2350 1900 50  0000 C CNN
F 2 "" V 2280 1900 50  0000 C CNN
F 3 "" H 2350 1900 50  0000 C CNN
	1    2350 1900
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 5B750DF9
P 2350 2300
F 0 "R?" V 2430 2300 50  0000 C CNN
F 1 "R" V 2350 2300 50  0000 C CNN
F 2 "" V 2280 2300 50  0000 C CNN
F 3 "" H 2350 2300 50  0000 C CNN
	1    2350 2300
	1    0    0    -1  
$EndComp
$Comp
L ZENER D?
U 1 1 5B750E2B
P 2350 2750
F 0 "D?" H 2350 2850 50  0000 C CNN
F 1 "ZENER" H 2350 2650 50  0001 C CNN
F 2 "" H 2350 2750 50  0000 C CNN
F 3 "" H 2350 2750 50  0000 C CNN
	1    2350 2750
	0    1    1    0   
$EndComp
$Comp
L Q_PNP_BCE Q?
U 1 1 5B751042
P 2600 2100
F 0 "Q?" H 2900 2150 50  0000 R CNN
F 1 "Q_PNP_BCE" H 3200 2050 50  0001 R CNN
F 2 "" H 2800 2200 50  0000 C CNN
F 3 "" H 2600 2100 50  0000 C CNN
	1    2600 2100
	1    0    0    1   
$EndComp
$Comp
L R R?
U 1 1 5B7510DA
P 3000 2600
F 0 "R?" V 3080 2600 50  0000 C CNN
F 1 "R" V 3000 2600 50  0000 C CNN
F 2 "" V 2930 2600 50  0000 C CNN
F 3 "" H 3000 2600 50  0000 C CNN
	1    3000 2600
	1    0    0    -1  
$EndComp
$Comp
L Q_PMOS_GDS Q?
U 1 1 5B7513D7
P 3550 1750
F 0 "Q?" H 3850 1800 50  0000 R CNN
F 1 "Q_PMOS_GDS" H 4200 1700 50  0001 R CNN
F 2 "" H 3750 1850 50  0000 C CNN
F 3 "" H 3550 1750 50  0000 C CNN
	1    3550 1750
	0    -1   -1   0   
$EndComp
$Comp
L Q_PMOS_GDS Q?
U 1 1 5B75142C
P 4250 1750
F 0 "Q?" H 4550 1800 50  0000 R CNN
F 1 "Q_PMOS_GDS" H 4900 1700 50  0001 R CNN
F 2 "" H 4450 1850 50  0000 C CNN
F 3 "" H 4250 1750 50  0000 C CNN
	1    4250 1750
	0    1    -1   0   
$EndComp
$Comp
L R R?
U 1 1 5B7514BA
P 3900 1900
F 0 "R?" V 3980 1900 50  0000 C CNN
F 1 "R" V 3900 1900 50  0000 C CNN
F 2 "" V 3830 1900 50  0000 C CNN
F 3 "" H 3900 1900 50  0000 C CNN
	1    3900 1900
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 5B7515E4
P 4250 2400
F 0 "R?" V 4330 2400 50  0000 C CNN
F 1 "R" V 4250 2400 50  0000 C CNN
F 2 "" V 4180 2400 50  0000 C CNN
F 3 "" H 4250 2400 50  0000 C CNN
	1    4250 2400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5B751C72
P 2350 3050
F 0 "#PWR?" H 2350 2800 50  0001 C CNN
F 1 "GND" H 2350 2900 50  0000 C CNN
F 2 "" H 2350 3050 50  0000 C CNN
F 3 "" H 2350 3050 50  0000 C CNN
	1    2350 3050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5B751DAA
P 3000 3050
F 0 "#PWR?" H 3000 2800 50  0001 C CNN
F 1 "GND" H 3000 2900 50  0000 C CNN
F 2 "" H 3000 3050 50  0000 C CNN
F 3 "" H 3000 3050 50  0000 C CNN
	1    3000 3050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5B751DDF
P 4250 3050
F 0 "#PWR?" H 4250 2800 50  0001 C CNN
F 1 "GND" H 4250 2900 50  0000 C CNN
F 2 "" H 4250 3050 50  0000 C CNN
F 3 "" H 4250 3050 50  0000 C CNN
	1    4250 3050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5B751E48
P 3550 3050
F 0 "#PWR?" H 3550 2800 50  0001 C CNN
F 1 "GND" H 3550 2900 50  0000 C CNN
F 2 "" H 3550 3050 50  0000 C CNN
F 3 "" H 3550 3050 50  0000 C CNN
	1    3550 3050
	1    0    0    -1  
$EndComp
$Comp
L BARREL_JACK J?
U 1 1 5B752729
P 1400 1750
F 0 "J?" H 1400 2000 50  0000 C CNN
F 1 "BARREL_JACK" H 1400 1550 50  0001 C CNN
F 2 "" H 1400 1750 50  0000 C CNN
F 3 "" H 1400 1750 50  0000 C CNN
	1    1400 1750
	1    0    0    -1  
$EndComp
$Comp
L F_Small F?
U 1 1 5B7527AE
P 2000 1650
F 0 "F?" H 1960 1710 50  0000 L CNN
F 1 "F_Small" H 1880 1590 50  0001 L CNN
F 2 "" H 2000 1650 50  0000 C CNN
F 3 "" H 2000 1650 50  0000 C CNN
	1    2000 1650
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW?
U 1 1 5B753010
P 4250 2800
F 0 "SW?" H 4400 2910 50  0000 C CNN
F 1 "SW_PUSH" H 4250 2720 50  0001 C CNN
F 2 "" H 4250 2800 50  0000 C CNN
F 3 "" H 4250 2800 50  0000 C CNN
	1    4250 2800
	0    -1   -1   0   
$EndComp
$Comp
L Q_NPN_BCE Q?
U 1 1 5B753EBF
P 4750 2600
F 0 "Q?" H 5050 2650 50  0000 R CNN
F 1 "Q_NPN_BCE" H 5350 2550 50  0001 R CNN
F 2 "" H 4950 2700 50  0000 C CNN
F 3 "" H 4750 2600 50  0000 C CNN
	1    4750 2600
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5B7542FA
P 4650 3050
F 0 "#PWR?" H 4650 2800 50  0001 C CNN
F 1 "GND" H 4650 2900 50  0000 C CNN
F 2 "" H 4650 3050 50  0000 C CNN
F 3 "" H 4650 3050 50  0000 C CNN
	1    4650 3050
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 5B754AB7
P 5050 2850
F 0 "R?" V 5130 2850 50  0000 C CNN
F 1 "R" V 5050 2850 50  0000 C CNN
F 2 "" V 4980 2850 50  0000 C CNN
F 3 "" H 5050 2850 50  0000 C CNN
	1    5050 2850
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 5B754B5C
P 5300 2600
F 0 "R?" V 5380 2600 50  0000 C CNN
F 1 "R" V 5300 2600 50  0000 C CNN
F 2 "" V 5230 2600 50  0000 C CNN
F 3 "" H 5300 2600 50  0000 C CNN
	1    5300 2600
	0    1    1    0   
$EndComp
Wire Wire Line
	2350 1750 2350 1650
Wire Wire Line
	2100 1650 2800 1650
Wire Wire Line
	2700 1900 2700 1650
Connection ~ 2700 1650
Wire Wire Line
	2350 2050 2350 2150
Wire Wire Line
	2400 2100 2350 2100
Connection ~ 2350 2100
Wire Wire Line
	3000 1950 3000 2450
Wire Wire Line
	2700 2300 2700 2400
Wire Wire Line
	2700 2400 3000 2400
Connection ~ 3000 2400
Wire Wire Line
	2350 2450 2350 2550
Wire Wire Line
	3200 1650 3350 1650
Wire Wire Line
	3750 1650 4050 1650
Wire Wire Line
	3900 1750 3900 1650
Connection ~ 3900 1650
Wire Wire Line
	4250 1950 4250 2250
Wire Wire Line
	3900 2050 3900 2150
Wire Wire Line
	3900 2150 4250 2150
Connection ~ 4250 2150
Wire Wire Line
	3000 2750 3000 3050
Wire Wire Line
	3550 1950 3550 3050
Wire Wire Line
	2350 2950 2350 3050
Wire Wire Line
	4650 2800 4650 3050
Wire Wire Line
	4250 2950 4250 3050
Wire Wire Line
	4950 2600 5150 2600
Wire Wire Line
	5050 2700 5050 2600
Connection ~ 5050 2600
$Comp
L GND #PWR?
U 1 1 5B754F9D
P 5050 3050
F 0 "#PWR?" H 5050 2800 50  0001 C CNN
F 1 "GND" H 5050 2900 50  0000 C CNN
F 2 "" H 5050 3050 50  0000 C CNN
F 3 "" H 5050 3050 50  0000 C CNN
	1    5050 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 2550 4250 2650
Wire Wire Line
	4650 2400 4650 2250
Wire Wire Line
	4650 2250 4450 2250
Wire Wire Line
	4450 2250 4450 2600
Wire Wire Line
	4450 2600 4250 2600
Connection ~ 4250 2600
Wire Wire Line
	5050 3000 5050 3050
Wire Wire Line
	1700 1650 1900 1650
Connection ~ 2350 1650
$Comp
L GND #PWR?
U 1 1 5B757500
P 1900 1950
F 0 "#PWR?" H 1900 1700 50  0001 C CNN
F 1 "GND" H 1900 1800 50  0000 C CNN
F 2 "" H 1900 1950 50  0000 C CNN
F 3 "" H 1900 1950 50  0000 C CNN
	1    1900 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 1750 1900 1750
Wire Wire Line
	1900 1750 1900 1950
Wire Wire Line
	1700 1850 1900 1850
Connection ~ 1900 1850
$EndSCHEMATC