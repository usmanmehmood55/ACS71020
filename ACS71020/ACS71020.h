/**
 * @file ACS71020.h
 * 
 * @author Usman Mehmood (usmanmehmood55@gmail.com)
 * 
 * @brief The Allegro ACS71020 power monitoring IC greatly simplifies
 * the addition of power monitoring to many AC powered systems.
 * The sensor may be powered from the same supply as the
 * system's MCU, eliminating the need for multiple power supplies
 * and expensive digital isolation ICs. The device's construction
 * includes a copper conduction path that generates a magnetic field
 * proportional to applied current. The magnetic field is sensed
 * differentially to reject errors introduced by common mode fields.
 * 
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
             * @param 00 No Error,
             * @param 01 Error detected and message corrected,
             * @param 10 Uncorrectable error,
             * @param 11 Don't care
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
        uint32_t resv : 10; // Reserved

        /**
         * @brief Offset adjustment for the current channel. This is a signed
         * 9-bit number with an input range of –256 to 255. With a step
         * size of 64 LSB, this equates to an offset trim range of –16384
         * to 16320 LSB, which is added to the icodes value. The trim is
         * implemented as shown in Figure 14. The current channel's offset
         * trim should be applied before the gain is trimmed.
         * @param Range: –256 to 255
         * @param Value: –16384 to 16320
         * @param Units LSB
         */
        uint32_t qvo_fine : 9;

        /**
         * @brief Gain adjustment for the current channel. This is a signed 9-bit
         * number with an input range of –256 to 255. This gain adjustment
         * is implemented as a percentage multiplier centered around 1 (i.e.
         * writing a 0 to this field multiplies the gain by 1, leaving the gain
         * unaffected). The fine sensitivity parameter ranges from 50% to
         * 150% of IP. The current channel's offset trim should be applied
         * before the gain is trimmed.
         * @param Range: –256 to 255
         * @param Value: 50 to 100
         * @param Units: %
         */
        uint32_t sns_fine : 9;

        /**
         * @brief Coarse gain adjustment for the current channel. This gain is
         * implemented in the analog domain before the ADC. This is a
         * 3-bit number that allows for 8 gain selections. Adjustments to
         * “crs_sns” may impact the device's performance over temperature.
         * Datasheet limits apply only to the factory settings for “crs_sns”.
         * The gain settings map to as shows in parameters:
         * @param 0 1×
         * @param 1 2×
         * @param 2 3×
         * @param 3 3.5×
         * @param 4 4×
         * @param 5 4.5×
         * @param 6 5.5×
         * @param 7 8×
         */
        uint32_t crs_sns : 3;

        /**
         * @brief Current Averaging selection enable.
         * @param 0 select vrms for averaging.
         * @param 1 select irms for averaging
         */
        uint32_t iavgselen : 1;
    } fields;
} eeprom_0x0B_t;

typedef union
{
    uint32_t eeprom_data;
    struct
    {
        uint32_t resv : 16; // Reserved

        /**
         * @brief Number of averages for the first averaging stage (vrmsavgonesec
         * or irmsavgonesec). The value written into this field directly maps
         * to the number of averages ranging from 0 to 127. For optimal
         * performance, an even number of averages should be used. The
         * channel to be averaged is selected by the “current average select
         * enable” bit (iavgselen).
         * @param Range: 0 to 127
         * @param Value: 0 to 127
         * @param Units: number of averages
         */
        uint32_t rms_avg_2 : 9;

        /**
         * @brief Number of averages for the second averaging stage (vrmsavgonemin
         * or irmsavgonemin). This stage averages the outputs of the
         * first averaging stage. The value written into this field directly maps
         * to the number of averages ranging from 0 to 1023. For optimal
         * performance, an even number of averages should be used. The
         * channel to be averaged is selected by the “current average select
         * enable” bit (iavgselen).
         * @param Range: 0 to 1023
         * @param Value: 0 to 1023
         * @param Units: number of averages
         */
        uint32_t rms_avg_1 : 7;
    } fields;
} eeprom_0x0C_t;

typedef union
{
    uint32_t eeprom_data;
    struct
    {
        uint32_t resv : 6;

        /**
         * @brief Setting for the Voltage Zero-Crossing Detection. When set to 0,
         * the zero-crossing event will be indicated by a pulse on the DIO
         * pin. When set to 1, the zero-crossing event will be indicated by a
         * level change on the DIO pin. Note that the device must be configured
         * to report Voltage-Zero-Crossing detection on the DIO pin.
         */
        uint32_t squarewave_en : 1;

        /**
         * @brief Setting for the voltage zero-crossing detection. When set to 0,
         * the voltage zero-crossing will be indicated on every rising edge.
         * When set to 1, the voltage zero-crossing will be indicated on both
         * rising and falling edges.
         */
        uint32_t halfcycle_en : 1;

        /**
         * @brief Fault delay setting of the amount of delay applied before flagging
         * a fault condition.
         * @param Range: 0 to 7,
         * @param Value: 0, 0, 4.75, 9.25, 13.75, 18.5, 23.25, 27.75,
         * @param Units: μSec
         */
        uint32_t fltdly : 3;

        /**
         * @brief Overcurrent fault threshold. This is an unsigned 8-bit number
         * with an input range of 0 to 255, which equates to a fault range of
         * 50% to 175% of IP. The factory setting of this field is 0.
         * @param Range: 0 to 255,
         * @param Value: 50 to 175,
         * @param Units: % of IP
         */
        uint32_t fault : 8;

        uint32_t resv1 : 1; // Reserved

        /**
         * @brief Sets the amount of delay applied to the voltage or current channel (set
         * by ichan_del_en).
         * @param Range: 0 to 7,
         * @param Value: 0 to 219 (vadc_rate_sel), Value: 0 to 875 (!vadc_rate_sel),
         * @param Units: μSec
         */
        uint32_t chan_del_sel : 3;

        uint32_t resv2 : 1; // Reserved

        /**
         * @brief Enables delay for either the voltage or current channel.
         * @param 0 voltage channel
         * @param 1 current channel
         */
        uint32_t ichan_del_en : 1;

        /**
         * @brief Offset trim in the active power calculation and is implemented
         * as shown in Figure 15. This is a signed 7-bit number with an
         * input range of –64 to 63. This equates to a trim range of –384 to
         * 378 LSB, which is added to the “pactive” value.
         * @param Range: –64 to 63
         * @param Value: –384 to 378
         * @param Units: LSB
         */
        uint32_t pacc_trim : 7;
    } fields;
} eeprom_0x0D_t;

typedef union
{
    uint32_t eeprom_data;
    struct
    {
        uint32_t resv : 11; // Reserved

        /**
         * @brief Selection bit for the width of pulse for a voltage zero-crossing
         * event. When set to 0, the pulse is 32 μs. When set to 1, the
         * pulse is 256 μs. When the squarewave_en bit is set, this field is
         * ignored.
         * @param Range 0 or 1
         * @param Value 32 or 256
         * @param Units μSec
         */
        uint32_t delaycnt_sel : 1;

        /**
         * @brief Sets the threshold of the undervoltage rms flag (uvrms). This is
         * a 6-bit number ranging from 0 to 63. This trip level spans one
         * entire range of the vrms register. The flag is set if the rms value is
         * below this threshold for the number of cycles selected in vevent_cycs.
         * @param Range 0 to 63
         * @param Value 0 to 32,768
         * @param Units LSB
         */
        uint32_t undervreg : 6;

        /**
         * @brief Sets the threshold of the overvoltage rms flag (ovrms). This is a
         * 6-bit number ranging from 0 to 63. This trip level spans the entire
         * range of the vrms register. The flag is set if the rms value is above
         * this threshold for the number of cycles selected in vevent_cycs.
         * @param Range 0 to 63
         * @param Value 0 to 32,768
         * @param Units LSB
         */
        uint32_t overvreg : 6;

        uint32_t resv1 : 1; // Reserved

        /**
         * @brief Sets the voltage ADC update rate. Setting this field to a 0 selects
         * a 32 kHz update. Setting this field to a 1 selects a 4 kHz update,
         * which will reduce the number of samples used in each rms calculation
         * but will allow for a larger phase delay correction between
         * channels (see chan_del_sel).
         * @param Range 0 or 1
         * @param Value 32 or 4
         * @param Units kHz
         */
        uint32_t vadc_rate_set : 1;

        /**
         * @brief Sets the number of cycles required to assert the OVRMS flag
         * or the UVRMS. This is an unsigned 6-bit number with an input
         * range of 0 to 63. The value in this field directly maps to the number
         * of cycles.
         * @param Range 0 to 63
         * @param Value 1 to 64
         * @param Units cycles
         */
        uint32_t vevent_cycs : 6;
    } fields;
} eeprom_0x0E_t;

typedef union
{
    uint32_t eeprom_data;
    struct
    {
        uint32_t resv1 : 12;           // Reserved

        /**
         * @brief Determines which flags are output on the DIO1 pin. Only used
         * when the device is in I2C programming mode.
         * @param 0 OCF: Overcurrent fault
         * @param 1 UVRMS: The VRMS undervoltage flag
         * @param 2 OVRMS: The VRMS overvoltage flag
         * @param 3 The OR of OVRMS, UVRMS, and OCF (if any of
         * the three flags are triggered, the DIO_0 pin will be
         * asserted).
         */
        uint32_t dio_1_sel : 2;
        
        /**
         * @brief Determines which flags are output on the DIO0 pin. Only used
         * when the device is in I2C programming mode.
         * @param 0 VZC: Voltage zero crossing
         * @param 1 OVRMS: The VRMS overvoltage flag
         * @param 2 UVRMS: The VRMS undervoltage flag
         * @param 3 The OR of OVRMS and UVRMS (if either flag is triggered, 
         * the DIO_0 pin will be asserted)
         */
        uint32_t dio_0_sel : 2;
        
        uint32_t resv2 : 6;            // Reserved

        /**
         * @brief Enables or disables the analog I2C slave address feature at power
         * on. When this bit is set, the I2C slave address will map directly to
         * i2c_slv_addr.
         */
        uint32_t i2c_dis_slv_addr : 1;
        
        /**
         * @brief Settings for the I2C Slave Address. The Voltage on the DIO pins
         * are measured at power and are used to set the device's slave
         * address.
         * Each DIO pin has 4 voltage “bins” which may be used to set
         * the I2C slave address. These voltages may be set using resistor
         * divider circuits from VCC to Ground.
         * @param Range 96 to 110
         * @param Units Slave address in decimal
         */
        uint32_t i2c_slv_addr : 7;
        
        uint32_t resv3 : 2;            // Reserved
    } fields;
} eeprom_0x0F_t;

///
/// TODO - The following code will be put into a seperate header file
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