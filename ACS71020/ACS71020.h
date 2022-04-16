/**
 * @file ACS71020.h
 * @author Usman Mehmood (usmanmehmood55@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-04-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef _ACS71020_H_
#define _ACS71020_H_

#include <stdio.h>
#include <stdint.h>

typedef struct
{
    uint8_t address;

    union
    {
        uint32_t value;
        struct
        {
            uint32_t resv : 4; // Reserved
            /**
             * @brief Error code: 
             * 00 = No Error,
             * 01 = Error detected and message corrected,
             * 10 = Uncorrectable error,
             * 11 = Don't care
             */
            uint32_t EEC : 2;
            uint32_t eeprom_data : 26; // EEPROM data
        } fields;

    } frame;

} eeprom_reg_t;

typedef union
{
    uint32_t eeprom_data;
    struct
    {
        uint32_t resv : 10;     // Reserved
        uint32_t qvo_fine : 9;  // Offset fine trimming on current channel
        uint32_t sns_fine : 9;  // Fine gain trimming on the current channel
        uint32_t crs_sns : 3;   // Coarse gain setting
        uint32_t iavgselen : 1; // Current Averaging selection
    } fields;
} eeprom_0x0B_t;

typedef union
{
    uint32_t eeprom_data;
    struct
    {
        uint32_t resv : 16;     // Reserved
        uint32_t rms_avg_2 : 9; // Average of the rms voltage or current – stage 2
        uint32_t rms_avg_1 : 7; // Average of the rms voltage or current – stage 1
    } fields;
} eeprom_0x0C_t;

typedef union
{
    uint32_t eeprom_data;
    struct
    {
        uint32_t resv : 6;          // Reserved
        uint32_t squarewave_en : 1; // Selects pulse or square wave output for the zero-crossing reporting
        uint32_t halfcycle_en : 1;  // Outputs pulses at every zero crossing when enabled, and every rising edge when disabled
        uint32_t fltdly : 3;        // Sets the overcurrent fault delay
        uint32_t fault : 8;         // Sets the overcurrent fault threshold
        uint32_t resv1 : 1;         // Reserved
        uint32_t chan_del_sel : 3;  // Sets phase delay on voltage or current channel
        uint32_t resv2 : 1;         // Reserved
        uint32_t ichan_del_en : 1;  // Enable phase delay on voltage or current channel
        uint32_t pacc_trim : 7;     // Trims the active power
    } fields;
} eeprom_0x0D_t;

typedef union
{
    uint32_t eeprom_data;
    struct
    {
        uint32_t resv : 11;         // Reserved
        uint32_t delaycnt_sel : 1;  // Sets the width of the voltage zero-crossing output pulse
        uint32_t undervreg : 6;     // Sets the undervoltage fault threshold
        uint32_t overvreg : 6;      // Sets the overvoltage fault threshold
        uint32_t resv1 : 1;         // Reserved
        uint32_t vadc_rate_set : 1; // Sample Frequency Selection
        uint32_t vevent_cycs : 6;   // Sets the number of qualifying cycles needed to flag overvoltage or undervoltage
    } fields;
} eeprom_0x0E_t;

typedef union
{
    uint32_t eeprom_data;
    struct
    {
        uint32_t resv1 : 12;           // Reserved
        uint32_t dio_1_sel : 2;        // Digital output 1 multiplexor selection bits
        uint32_t dio_0_sel : 2;        // Digital output 0 multiplexor selection bits
        uint32_t resv2 : 6;            // Reserved
        uint32_t i2c_dis_slv_addr : 1; // Disable I2C slave address selection circuit
        uint32_t i2c_slv_addr : 7;     // 2C slave address selection
        uint32_t resv3 : 2;            // Reserved
    } fields;
} eeprom_0x0F_t;

///
/// =====================================================================================================
///
typedef struct
{
    uint8_t address;
    uint32_t register_value;
} acs_reg_t;

typedef union
{
    uint32_t register_value;
    struct
    {
        uint32_t resv1 : 1; // Reserved
        uint32_t irms : 15; // Current RMS value
        uint32_t resv2 : 1; // Reserved
        uint32_t vrms : 15; // Voltage RMS value
    } fields;
} acs_0x20_t;

typedef union
{
    uint32_t register_value;
    struct
    {
        uint32_t pactive : 17; // Active power
        uint32_t resv : 15;    // Reserved
    } fields;
} acs_0x21_t;

typedef union
{
    uint32_t register_value;
    struct
    {
        /**
         * @brief Apparent power output. This field is an unsigned 16-bit fixed
         * point number with 15 fractional bits. It ranges from 0 to ~2 with
         * a step size of 1/215. This number should be multiplied by the
         * overall full-scale power in order to get to VA. For example, if full
         * scale voltage is 250 V and IPR is 30 A, then the multiplier will be
         * 7500 VA. “papparent” is further described in Table 22.
         */
        uint32_t papparent : 16;
        uint32_t resv : 16; // Reserved
    } fields;
} acs_0x22_t;

typedef union
{
    uint32_t register_value;
    struct
    {
        uint32_t pimag : 16;
        uint32_t resv : 16; // Reserved
    } fields;
} acs_0x23_t;

typedef union
{
    uint32_t register_value;
    struct
    {
        uint32_t pfactor : 11;
        uint32_t resv : 21; // Reserved
    } fields;
} acs_0x24_t;

typedef union
{
    uint32_t register_value;
    struct
    {
        uint32_t pfactor : 9;
        uint32_t resv : 23; // Reserved
    } fields;
} acs_0x25_t;

typedef union
{
    uint32_t register_value;
    struct
    {
        uint32_t irmsavgonesec : 15;
        uint32_t resv1 : 1; // Reserved
        uint32_t vrmsavgonesec : 15;
        uint32_t resv2 : 1; // Reserved
    } fields;
} acs_0x26_t;

typedef union
{
    uint32_t register_value;
    struct
    {
        uint32_t irmsavgonemin : 15;
        uint32_t resv1 : 1; // Reserved
        uint32_t vrmsavgonemin : 15;
        uint32_t resv2 : 1; // Reserved
    } fields;
} acs_0x27_t;

typedef union
{
    uint32_t register_value;
    struct
    {
        uint32_t pactavgonesec : 17;
        uint32_t resv : 15; // Reserved
    } fields;
} acs_0x28_t;

typedef union
{
    uint32_t register_value;
    struct
    {
        uint32_t pactavgonemin : 17;
        uint32_t resv : 15; // Reserved
    } fields;
} acs_0x29_t;

typedef union
{
    uint32_t register_value;
    struct
    {
        uint32_t vcodes : 17;
        uint32_t resv : 15; // Reserved
    } fields;
} acs_0x2A_t;

typedef union
{
    uint32_t register_value;
    struct
    {
        uint32_t icodes : 17;
        uint32_t resv : 15; // Reserved
    } fields;
} acs_0x2B_t;

typedef union
{
    uint32_t register_value;
    struct
    {
        uint32_t pinstant : 32;
    } fields;
} acs_0x2C_t;

typedef union
{
    uint32_t register_value;
    struct
    {
        uint32_t vzerocrossout : 1;
        uint32_t faultout : 1;
        uint32_t faultlatched : 1;
        uint32_t overvoltage : 1;
        uint32_t undervoltage : 1;
        uint32_t posangle : 1;
        uint32_t pospf : 1;
        uint32_t resv : 25; // Reserved
    } fields;
} acs_0x2D_t;

typedef union
{
    uint32_t register_value;
    struct
    {
        uint32_t access_code : 32;
    } fields;
} acs_0x2F_t;

typedef union
{
    uint32_t register_value;
    struct
    {
        uint32_t customer_access : 1;
    } fields;
} acs_0x30_t;

#endif // _ACS71020_H_