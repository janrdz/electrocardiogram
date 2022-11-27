# Electrocardiogram

An electrocardiogram is a medical tool that records the electrical activity of the heart.

## Getting Started

This was (still is) my final project for the Electronics I course from UAGM (ELEN 330). The main objective was to build 
an Electrocardiogram using Operational Amplifiers (specifically the Instrumentation Amplifier), but why this amplifier?

The instrumentation amplifier has all the characteristics of the operational amplifier: 
	Differential Amplification
	High input impedance
	Low output impedance
	Gain is constant over a wide band of frequencies
	Common Mode Rejection Ratio

An important characteristic of this type of amplifier is the previously mentioned [Common Mode Rejection Ratio](https://www.circuitbread.com/ee-faq/what-is-common-mode-rejection-ratio-in-op-amps), 
which rejects the interferance of common signals to both inputs and amplifies only the difference between them. 
That is what we are looking for to build an ECG.

Later on I will be uploading the: circuit schematic, source code for Arduino, mathematical analysis and so on. 

### Prerequisites

If you want to build it yourself, you will have to know a few basic concepts of circuit design and analysis such as:
- [Nodal Analysis] (https://www.tutorialspoint.com/network_theory/network_theory_nodal_analysis.htm)
- [Operational Amplifiers] (https://www.electronics-tutorials.ws/opamp/opamp_1.html)
- [Filters] (https://www.electronics-tutorials.ws/filter/filter_2.html)
- [NI Multisim] (https://www.ni.com/es-cr/support/downloads/software-products/download.multisim.html#312060)
- [Arduino](https://www.arduino.cc/en/software)

### Electronics Components
- x1 AD623 (you can use this one to simplify the Instrumentation Schematic)
- x5 OPAMS741 (x2 if you will use the AD623)
- Resistors, Capacitors, Jumper Wires, Dual Power Supply (+15V, -15V) (rating of each component will be provided later)
- Oscilloscope, Breadboard, ECG Electrode Stickers

### Building Procedure

A step by step series will be updated later.

## Acknowledgments

  - Dr. Diego Aponte Roa (my professor)
  - Ryan Rodríguez (my project partner)