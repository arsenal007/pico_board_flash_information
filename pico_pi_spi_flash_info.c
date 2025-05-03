#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/flash.h"
#include "hardware/flash.h"

#define FLASHCMD_READ_JEDEC_ID 0x9F

uint8_t jedec_id[4] = {0};

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
        printf("JEDEC ID: 0x%02X 0x%02X 0x%02X\n", jedec_id[1], jedec_id[2], jedec_id[3]);
        sleep_ms(10000);
        uint8_t log2_size = jedec_id[3];
        uint32_t size = 1u << log2_size;
        printf("Flash size: 2^%u = %u bytes (%.2f MB)\n",
               log2_size, size, size / 1024.0 / 1024.0);
    }
}
