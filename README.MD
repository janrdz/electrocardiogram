# Electrocardiogram

An electrocardiogram is a medical tool that records the electrical activity of the heart.

## Getting Started

This was my final project for the Microprocessors I course from UAGM (ELEN 442). The main objective of this project is to measure heart readings using Arduino and electrodes. These readings should be displayed on a LCD/LED/OLED screen (i.e., showing the Normal Sinus Rhythm waveform). 

### Electronics Components

- Arduino Uno R3
- Sparkfun’s AD8232 Sensor
- KMR 1.8 SPI (Or any other LCD TFT Screen)
- ECG Electrodes
- Crocodile Clips
- Cardiac Simulator (Optional)
- Light Emitting Diodes
- Jumper Cables
- Breadboard
- Buzzer
- USB Cable Type B

### Building Procedure

First, get an Arduino. On this project I used the Arduino Uno R3. Next you need a TFT based screen, as mentioned on the Electronics Components, a KMR 1.8 SPI. You need an ECG sensor, here I used the [Sparkfun’s AD8232](https://www.sparkfun.com/products/12650). You will need to buy at least on [Crocodile Clips](https://a.co/d/3fdAH9w). These will be useful to connect the electrodes to the sensor.

I recommend to set up the screen first. Here is a the [data sheet](https://forum.arduino.cc/t/graphics-library-for-cheap-kmr-1-8-spi-s6d02a1-and-ili9163-tft-displays/391450/52) of the KMR 1.8 SPI screen. You need the libraries of the screen as well. You can get them here:

[TFT_S6D02A1](https://github.com/Bodmer/TFT_S6D02A1)

[TFT_ST7735](https://github.com/Bodmer/TFT_ST7735)

Well...
