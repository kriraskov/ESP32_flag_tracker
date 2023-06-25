# ESP32 WKF flag tracker

## Installing ESP-IDF

Clone the ESP-IDF git repository and run the installation script (for Windows,
use the `install.bat` script).

    git clone https://github.com/espressif/esp-idf.git
    cd esp-idf
    ./install.sh

Export the following variables to the IDE:

 - `IDF_PATH` - path to the esp-idf directory.
 - `IDF_TARGET` - ESP32 target to build (`esp32c3`).
 - `ESPPORT` - COM port of the ESP32.

The value of `IDF_PATH` can be found by running `${IDF_PATH}/export.sh`. This script
will also set the `PATH` variable, which needs to be exported to the IDE
accordingly.

## Enabling components

All the necessary components should be enabled in `./sdkconfig`. If not, run
`idf.py menuconfig` from the project directory and check that Bluetooth is
enabled and that the host is set to NimBLE.

## Building the project

Either run `idf.py flash` or **build** the `flash` configuration from an IDE.
This will build and flash the CMake project to the ESP32. Use the `monitor`
configuration to monitor the output.