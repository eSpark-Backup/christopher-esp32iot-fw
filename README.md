# christopher-esp32iot-fw
## Build & Flash via Zip
### Building your Project
1. Download zip from Github.
2. Open it using VS Code.
3. Change the SSID & password of wifi with your wifi credentials using sdkconfig.
4. Open terminal & run 'idf.py build' to build your project.
### Setting up the Hardware
1. Connect Vcc, GND & Data pin of your led strip with ESP32 at 5V, GND, GPIO18 respectively.
### Flashing your Project
1. Connect your ESP32 to your PC via USB cable & check the COM Ports through device manager.
2. Then, open terminal on VS Code, run 'idf.py -p COMxx flash monitor' to flash your esp32 chip.                   
   **NOTE: DO NOT FORGET TO REPLACE xx with your COM Port number at which the ESP32 is connected.**
## Build & Flash via Flash Tool
### Required Software
1. [ESP32 Flash Download Tool](https://www.espressif.com/en/support/download/other-tools)

### Building & Flashing Procedure
1. Connect the ESP32 Dev Module to the PC via MicroUSB cable.
2. Open flash download tool and select options as shown in screenshot below and click OK to proceed.      
![image](https://github.com/eSpark-Consultants/bradfairman-fishpipe-firmware/assets/144008938/eeeed66f-e3f0-4014-b35e-5e5686e71752)
3. Click erase button on new window that opens, to first completely wipe off the ESP32 memory.
4. Upload the provided [Code Binaries](https://github.com/eSpark-Consultants/christopher-esp32iot-fw/tree/main/Binaries) as follows:
    * MPU6050_DMP6.ino.bootloader.bin -> 0x1000
    * MPU6050_DMP6.ino.partitions.bin -> 0x8000
    * MPU6050_DMP6.ino.bin -> 0x10000
5. Select the COM Port and press the start button to start the flashing process as shown in screenshot below:
![image](https://github.com/eSpark-Consultants/bradfairman-fishpipe-firmware/assets/144008938/df68ce66-abdf-4ec1-bc65-92f982b4d45a)

6. Once finished, close the software and reset the ESP32.                             
**NOTE: The credetials for the given binaries are:**                 ![image](https://github.com/eSpark-Consultants/christopher-esp32iot-fw/assets/144008938/1b339f7c-5bed-4d44-a552-0f4fc9d07049)
