# PC_Display_1602_changed_by_AlexGyver

This is a simplified version of the original **PCdisplay** project by [AlexGyver](https://github.com/AlexGyver).  
It displays basic PC performance statistics on a 1602 I2C LCD screen using an Arduino-compatible microcontroller.

---

## 🔧 What's Changed

This modified version removes all extra features to keep the project minimal and focused:

- ❌ Removed: Button functions  
- ❌ Removed: Fan control and setup logic  
- ❌ Removed: CPU and GPU temperature display  
- ✅ Kept: Main information screen only  
- 🔁 Merged: Page 1 and Page 2 into a single continuous display

---

## 📟 Displayed Information

The display shows the following PC stats:

- **CPU Load (%)**
- **GPU Load (%)**
- **RAM Usage (%)**
- **GPU Memory Usage (%)**

If the serial connection is lost, the screen switches to:

- **Connection lost message**
- **Current time and date** (last synced from PC)

---

## 🛠️ Hardware Requirements

- Arduino-compatible board (e.g., Arduino Nano)
- 1602 LCD with I2C interface
- USB connection to the PC

---

## 🚀 How to Use

1. Flash the Arduino sketch to your microcontroller.
2. Connect the LCD screen via I2C as shown above.
3. Use a compatible PC-side script or monitoring tool (Modified HardwareMonitor) that sends data over serial.
4. Enjoy a real-time, minimal PC status display.

---

## 📁 Original Full Version

Looking for more features (fan control, temperature, buttons, multiple screens)?  
Check the original project by AlexGyver:

**👉 [AlexGyver/PCdisplay](https://github.com/AlexGyver/PCdisplay)**

---
