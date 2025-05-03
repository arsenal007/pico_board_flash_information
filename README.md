# SPI Flash Info

This project is a simple application for the Raspberry Pi Pico that reads and displays the JEDEC ID and size of the connected SPI flash memory. It uses the Pico SDK to interact with the hardware and provides output via UART.

## Features

- Reads the JEDEC ID of the SPI flash memory.
- Calculates and displays the flash memory size based on the JEDEC ID.
- Outputs the information via UART.

## Prerequisites

- Raspberry Pi Pico or compatible hardware.
- Pico SDK installed and initialized.
- CMake build system.
- A UART terminal to view the output.

## Project Structure

```
├── .gitignore
├── CMakeLists.txt
├── pico_sdk_import.cmake
├── README.md
├── spi_flash.c
├── .vscode/
│   ├── c_cpp_properties.json
│   ├── cmake-kits.json
│   ├── extensions.json
│   ├── launch.json
│   ├── settings.json
│   ├── tasks.json
├── build/
│   ├── build.ninja
│   ├── CMakeCache.txt
│   ├── compile_commands.json
│   ├── spi_flash_info.elf
│   ├── spi_flash_info.uf2
│   └── ...
```

## How to Build

1. Clone the repository and navigate to the project directory.
2. Initialize the Pico SDK if not already done:
    ```sh
    git submodule update --init
    ```
3. Create a `build` directory and navigate into it:
    ```sh
    mkdir build && cd build
    ```
4. Run CMake to configure the project:
    ```sh
    cmake ..
    ```
5. Build the project:
    ```sh
    make
    ```

## How to Flash

1. Connect the Raspberry Pi Pico to your computer while holding the BOOTSEL button.
2. Copy the generated `.uf2` file (e.g., `spi_flash_info.uf2`) from the `build` directory to the Pico's USB mass storage device.

## How to Run

1. Open a UART terminal (e.g., PuTTY, minicom) and connect to the Pico's serial port.
2. Reset the Pico to start the program.
3. The terminal will display the JEDEC ID and flash size information, similar to the following:

    ```
    JEDEC ID: 0xEF 0x40 0x18
    Flash size: 2^24 = 16777216 bytes (16.00 MB)
    ```

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

## Acknowledgments

- [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk) for providing the development framework.
