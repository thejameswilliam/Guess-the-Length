# 🚗 Size Does Matter

**Size Does Matter** is a carnival-style game created for the Maker Olympics at Make Santa Fe. Contestants press a button to launch a stepper-motor-powered car along a timing belt. Their goal? Guess how far the car will travel!

The car's travel distance is randomized and displayed on a small OLED screen after launch. Built using an **ESP32-WROOM-32** microcontroller and a **DRV8825 stepper motor driver**, this project combines precision hardware control with playful design.

---

## 🛠 Tech Stack

- **Programming Language**: C++ (Arduino Framework)
- **Platform**: ESP32-WROOM-32
- **Development Environment**: [PlatformIO](https://platformio.org/) in Visual Studio Code
- **Display**: 128x64 I2C OLED (SSD1306)
- **Motor Driver**: DRV8825
- **Stepper Motor**: 200-step/rev NEMA 17 (or similar)
- **Belt System**: GT2 timing belt with 20T pulley
- **Power**: 
  - ESP32 via USB
  - Stepper motor via 12–24V external power supply

---

## ⚡ Wiring and Pinout

### ESP32 Pin Assignments

| Component        | Pin Label | ESP32 Pin | Notes                          |
|------------------|-----------|-----------|--------------------------------|
| Stepper `STEP`   |           | GPIO 26   | Step signal                    |
| Stepper `DIR`    |           | GPIO 25   | Direction control              |
| Button           |           | GPIO 33   | Uses internal pull-up          |
| OLED `SDA`       |           | GPIO 21   | I2C data                       |
| OLED `SCL`       |           | GPIO 22   | I2C clock                      |
| OLED `VCC`       |           | 3.3V      | (or 5V depending on model)     |
| OLED `GND`       |           | GND       | Ground                         |
| Stepper `EN`     |           | GND       | Tie to GND to always enable    |
| Stepper `VMOT`   |           | 12–24V    | External motor power           |
| Stepper `GND`    |           | GND       | Shared with VMOT supply        |

> 💡 Don’t forget to place a 100µF capacitor between `VMOT` and `GND` near the DRV8825.

---

## 🎚 Microstepping Configuration (DIP Switches)

For smoother motion, set the DRV8825 DIP switches as follows:

| MS1 | MS2 | MS3 | Microstepping Mode |
|-----|-----|-----|---------------------|
| OFF | OFF | ON  | 1/16 step (recommended) |

---

## 🧮 Motion Calculation

- **Pulley**: 20 teeth
- **Belt Pitch**: 2 mm (GT2)
- **Motor**: 200 steps/rev
- **Microstepping**: 1/16

> 🎯 **Distance per step** ≈ 0.0125 mm  
> (Calculated as `(2mm × 20T) / (200 × 16)`)

---

## 📦 Dependencies

These libraries are managed via PlatformIO:

```ini
lib_deps =
  adafruit/Adafruit SSD1306
  adafruit/Adafruit GFX Library