# christopher-esp32iot-fw
## Building your Project
1. Download zip from Github.
2. Open it using VS Code.
3. Change the SSID & password of wifi with your wifi credentials using sdkconfig.
4. Open terminal & run 'idf.py build' to build your project.
## Setting up the Hardware
1. Connect Vcc, GND & Data pin of your led strip with ESP32 at 5V, GND, GPIO18 respectively.
## Flashing your Project
1. Connect your ESP32 to your PC via USB cable & check the COM Ports through device manager.
2. Then, open terminal on VS Code, run 'idf.py -p COMxx flash monitor' to flash your esp32 chip.                   
   **NOTE: DO NOT FORGET TO REPLACE xx with your COM Port number at which the ESP32 is connected.**
