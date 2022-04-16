#include <stdio.h>
#include <stdint.h>
#include "ACS71020.h"

void main()
{
    eeprom_reg_t reg = {.address = 0x12};

    reg.frame.value = 4294967295;

    eeprom_0x0D_t addr_0x0D;

    addr_0x0D.eeprom_data = reg.frame.fields.eeprom_data;
}