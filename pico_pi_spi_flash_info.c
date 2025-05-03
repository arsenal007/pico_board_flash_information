#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/flash.h"
#include "hardware/flash.h"

#define FLASHCMD_READ_JEDEC_ID 0x9F

uint8_t jedec_id[4] = {0};

// Define a structure for manufacturer and device information
typedef struct {
    uint8_t manufacturer_id;
    uint8_t device_id;
    uint8_t size_id;
    const char *manufacturer_name;
    const char *device_name;
} flash_info_t;

// Define a table of known manufacturers and devices
const flash_info_t flash_info_table[] = {
    {0xEF, 0x40, 0x18, "Winbond", "W25Q128 (16 MB)"},
    {0xEF, 0x40, 0x16, "Winbond", "W25Q32 (4 MB)"}, 
    {0xC2, 0x20, 0x17, "Macronix", "MX25L64 (8 MB)"},
    {0x1F, 0x84, 0x16, "Adesto", "AT25SF321 (4 MB)"},
    {0x20, 0xBA, 0x19, "Micron", "MT25QL256 (32 MB)"},
    {0xC8, 0x60, 0x16, "GigaDevice", "GD25Q32 (4 MB)"},
    {0x85, 0x60, 0x15, "Puya", "P25Q16H (2 MB)"},
    {0x00, 0x00, 0x00, "Unknown", "Unknown"} // Default entry for unknown devices
};

// Function to find flash information based on JEDEC ID
const flash_info_t *get_flash_info(uint8_t manufacturer_id, uint8_t device_id, uint8_t size_id)
{
    for (size_t i = 0; i < sizeof(flash_info_table) / sizeof(flash_info_table[0]); i++)
    {
        if (flash_info_table[i].manufacturer_id == manufacturer_id &&
            flash_info_table[i].device_id == device_id &&
            flash_info_table[i].size_id == size_id)
        {
            return &flash_info_table[i];
        }
    }
    return &flash_info_table[sizeof(flash_info_table) / sizeof(flash_info_table[0]) - 1]; 
}

__attribute__((section(".time_critical"))) void read_jedec_id()
{
    uint8_t cmd[4] = {FLASHCMD_READ_JEDEC_ID, 0, 0, 0};
    flash_do_cmd(cmd, jedec_id, 4);
}

int main()
{
    stdio_init_all();
    sleep_ms(5000);
    read_jedec_id();

    while (1)
    {
        uint8_t manufacturer_id = jedec_id[1];
        uint8_t device_id = jedec_id[2];
        uint8_t size_id = jedec_id[3];
        uint32_t size = 1u << size_id;

        const flash_info_t *info = get_flash_info(manufacturer_id, device_id, size_id);

        printf("JEDEC ID: 0x%02X 0x%02X 0x%02X\n", manufacturer_id, device_id, size_id);
        printf("Manufacturer: %s\n", info->manufacturer_name);
        printf("Device: %s\n", info->device_name);
        printf("Flash size: 2^%u = %u bytes (%.2f MB)\n",
               size_id, size, size / 1024.0 / 1024.0);

        sleep_ms(10000);
    }
}