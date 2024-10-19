
# Parkinsonian Tremor Detector Using Adafruit Circuit Playground

This project implements a tremor detection system for Parkinson's disease using the **Adafruit Circuit Playground Classic**. The system uses data from the onboard accelerometer to detect tremor intensity and classify the severity of tremors. The detected tremors are displayed visually using the onboard NeoPixels and accompanied by auditory feedback.

## Features
- **Tremor Detection**: Detects tremor intensities in the 3-6 Hz range using Fast Fourier Transform (FFT).
- **Visual and Auditory Feedback**: Depending on tremor intensity, different NeoPixel patterns and sounds are triggered.
- **Tremor Severity Classification**: Classifies tremors into various levels: Light, Slight, Medium, Severe, and Serious, with corresponding LED and sound outputs.
- **FFT Processing**: Uses the `Adafruit_ZeroFFT` library to analyze the tremor frequencies and calculate tremor intensities.
- **Data Logging**: Outputs tremor data to the serial monitor, displaying a 1-minute window of tremor averages.

## Hardware Requirements
- **Adafruit Circuit Playground Classic**
- USB cable for programming
- Computer with Arduino IDE installed

## Software Requirements
- **Arduino IDE**: To compile and upload the code.
- **Libraries**:
  - `Adafruit_CircuitPlayground`: For accessing the onboard sensors and NeoPixels.
  - `Adafruit_ZeroFFT`: For performing FFT on the accelerometer data.
  - `math.h`: For mathematical functions such as square root and power calculations.

## Setup Instructions
1. **Install Arduino IDE**:
   - Download and install the latest version of the Arduino IDE from the [official Arduino website](https://www.arduino.cc/en/software).

2. **Install Required Libraries**:
   - In the Arduino IDE, go to **Tools > Manage Libraries**.
   - Search for and install the following libraries:
     - `Adafruit Circuit Playground`
     - `Adafruit ZeroFFT`
   
3. **Load the Code**:
   - Copy the code from this repository and paste it into a new Arduino sketch.
   - Ensure your Circuit Playground board is selected under **Tools > Board > Adafruit Circuit Playground**.
   - Select the correct port under **Tools > Port**.

4. **Upload the Code**:
   - Upload the sketch to the Circuit Playground by clicking the **Upload** button in the Arduino IDE.

5. **Run the Project**:
   - Once the code is uploaded, the Circuit Playground will begin detecting tremors based on accelerometer data.
   - The LEDs will light up in different patterns and colors depending on the tremor intensity, and sounds will be played to indicate severity.

## How It Works
1. The accelerometer data is continuously read from the **X**, **Y**, and **Z** axes.
2. A resultant magnitude is calculated using the square root of the sum of squares of the accelerometer readings.
3. This resultant magnitude is fed into a buffer and processed with Fast Fourier Transform (FFT) to isolate tremor frequencies (3-6 Hz).
4. Tremor intensity is averaged and compared against predefined thresholds to classify the tremor as **Light**, **Slight**, **Medium**, **Severe**, or **Serious**.
5. The **NeoPixels** on the Circuit Playground will light up in different colors and patterns depending on the tremor intensity.
6. A corresponding sound is played using the Circuit Playground's onboard buzzer.

### Tremor Classification:
- **Light Tremor**: NeoPixels turn green, buzzer plays tone for 700ms.
- **Slight Tremor**: NeoPixels turn yellow, buzzer plays tone for 500ms.
- **Medium Tremor**: NeoPixels turn red, buzzer plays tone for 300ms.
- **Severe Tremor**: NeoPixels turn orange, buzzer plays tone for 100ms.
- **Serious Tremor**: NeoPixels turn bright red, buzzer plays tone for 50ms.

## Project Structure
- **main.ino**: The main Arduino sketch that contains the logic for detecting tremors, processing FFT, and controlling the output (LEDs and buzzer).
- **checkArr()**: A helper function that checks if a minute's worth of tremor data exceeds the threshold, confirming tremor detection.
- **setupTimer()**: Initializes a timer interrupt for reading accelerometer data at the specified `sampleRate`.

## Customization
You can customize various parameters to adjust the tremor detection system:
- **sampleRate**: Change the `#define sampleRate 100` to increase or decrease the sampling rate for accelerometer readings.
- **Tremor Intensity Thresholds**: Adjust the tremor classification thresholds in the `loop()` function to refine tremor detection for different use cases.

## Future Improvements
- Implement a more sophisticated method of tremor classification based on machine learning techniques.
- Add data logging capabilities to store tremor data over longer periods.
- Integrate with mobile applications or cloud services for remote monitoring.

## License
This project is licensed under the MIT License. See the LICENSE file for more details.

