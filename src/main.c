#include <stdio.h>
#include <stdint.h>
#include "ACS71020.h"

void main()
{
    eeprom_reg_t reg;
    reg.address = 123;
    reg.frame.value = 4294967295;

    eeprom_0x0D_t addr_0x0D;
    addr_0x0D.eeprom_data = reg.frame.fields.eeprom_data;
    
    printf("\npacc_trim: %d", addr_0x0D.fields.pacc_trim);
    printf("\nichan_del_en: %d", addr_0x0D.fields.ichan_del_en);
    printf("\nchan_del_sel: %d", addr_0x0D.fields.chan_del_sel);
    printf("\nfault: %d", addr_0x0D.fields.fault);
    printf("\nfltdly: %d", addr_0x0D.fields.fltdly);
    printf("\nhalfcycle_en: %d", addr_0x0D.fields.halfcycle_en);
    printf("\nsquarewave_en: %d", addr_0x0D.fields.squarewave_en);
}