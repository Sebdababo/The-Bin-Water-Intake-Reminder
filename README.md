# The Bin Water Intake Reminder

This project is designed to help you track your daily water intake and remind you to stay hydrated. The system uses multiple sensors to monitor environmental conditions, such as temperature and humidity, and adjusts your recommended daily water intake accordingly. It displays real-time information on an LCD and OLED display, and you can use an infrared remote to update your water intake. 

This project is also available as a Wokwi simulation for testing and demonstration purposes.

## Components Required

- Arduino-compatible microcontroller (e.g., ESP32)
- 16x2 LCD Display
- 128x64 OLED Display (I2C)
- DHT22 Temperature and Humidity Sensor
- DS18B20 Waterproof Temperature Sensor
- RTC DS3231 Real-Time Clock Module
- Infrared Receiver Module (e.g., IRrecv)
- Buzzer
- Potentiometer
- Connecting wires
- Breadboard

## Libraries Required

Ensure you have the following libraries installed in your Arduino IDE:

- `Wire.h` - For I2C communication
- `LiquidCrystal.h` - For controlling the LCD
- `Adafruit_GFX.h` - For graphics on the OLED
- `Adafruit_SSD1306.h` - For controlling the OLED
- `DHT.h` - For reading data from the DHT22 sensor
- `OneWire.h` - For communication with the DS18B20 sensor
- `DallasTemperature.h` - For handling the DS18B20 sensor
- `RTClib.h` - For the DS3231 real-time clock
- `IRremoteESP8266.h`, `IRrecv.h`, `IRutils.h` - For handling IR remote input

## Circuit Diagram

1. **LCD Display (16x2) Connections:**
   - RS to digital pin `25`
   - EN to digital pin `26`
   - D4 to digital pin `12`
   - D5 to digital pin `13`
   - D6 to digital pin `14`
   - D7 to digital pin `27`

2. **OLED Display (128x64) Connections:**
   - SCL to `SCL` on the microcontroller
   - SDA to `SDA` on the microcontroller
   - Power (VCC) to `3.3V` or `5V`
   - Ground (GND) to `GND`

3. **DHT22 Sensor:**
   - Data pin to digital pin `4`
   - Power (VCC) to `3.3V` or `5V`
   - Ground (GND) to `GND`

4. **DS18B20 Waterproof Temperature Sensor:**
   - Data pin to digital pin `5`
   - Power (VCC) to `3.3V` or `5V`
   - Ground (GND) to `GND`

5. **IR Receiver:**
   - Signal pin to digital pin `19`
   - Power (VCC) to `3.3V` or `5V`
   - Ground (GND) to `GND`

6. **Buzzer:**
   - Signal pin to digital pin `18`
   - Power (VCC) to `3.3V` or `5V`
   - Ground (GND) to `GND`

7. **Potentiometer:**
   - Middle pin to analog pin `34`
   - Side pins to `VCC` and `GND`

8. **RTC DS3231 Module:**
   - SCL to `SCL` on the microcontroller
   - SDA to `SDA` on the microcontroller
   - Power (VCC) to `3.3V` or `5V`
   - Ground (GND) to `GND`

## Setup Instructions

1. **Hardware Setup:**
   - Connect all components as per the circuit diagram described above.
   - Ensure proper power connections to all components to avoid any damage.

2. **Software Setup:**
   - Open the Arduino IDE and install the required libraries listed above via the Library Manager.
   - Download or clone this repository.
   - Open the project sketch (`.ino` file) in the Arduino IDE.
   - Upload the sketch to your Arduino-compatible microcontroller.

## How to Use

1. **Reading Sensor Data:**
   - The DHT22 sensor provides the ambient temperature and humidity readings.
   - The DS18B20 sensor provides the temperature of the liquid (e.g., water bottle).
   - These readings are displayed on both the LCD and OLED screens.

2. **Water Intake and Goals:**
   - You can set your daily water intake goal using the potentiometer. Adjust it between 1000ml and 5000ml.
   - Use the IR remote to log your water intake:
     - Button 1 adds 100ml
     - Button 2 adds 250ml
     - Button 3 adds 500ml
   - The current intake and goal are displayed on the LCD.

3. **Reminders:**
   - If your intake is below the daily goal, the buzzer will sound every hour to remind you to drink water.

4. **Display Information:**
   - The OLED screen shows the temperature, humidity, liquid temperature, recommended water intake, and the current time.
   - The LCD displays your current water intake and daily goal.

## Simulation

You can also test this project using the [Wokwi simulation platform](https://wokwi.com/projects/405753331814653953). The simulation provides a virtual environment to experiment with the project without needing the physical hardware.
