/**
 * @file ACS71020_volatile.h
 * @author Usman Mehmood (usmanmehmood55@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _ACS71020_volatile_H_
#define _ACS71020_volatile_H_

#include <stdio.h>
#include <stdint.h>

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

        /**
         * @brief RMS current output. This field is an unsigned 15-bit fixed point
         * number with 14 fractional bits. It ranges from 0 to ~2 with a step
         * size of (1/2)^14. This number should be multiplied by the overall full
         * scale of the current path in order to get to amps. For example, if
         * the device is trimmed to a full-scale input of 30 A, then the multiplier
         * should be 30 A.
         */
        uint32_t irms : 15;

        uint32_t resv2 : 1; // Reserved

        /**
         * @brief RMS voltage output. This field is an unsigned 15-bit fixed point
         * number with 15 fractional bits. It ranges from 0 to ~1 with a step
         * size of (1/2)^15. This number should be multiplied by the overall full
         * scale of the voltage path in order to get to volts. For example, the
         * device is trimmed to a full scale input of 275 mV, and if a resistor
         * divider network is used to create 275 mV when it has 250 V
         * across it, then the multiplier should be 250 V
         */
        uint32_t vrms : 15;
    } fields;
} acs_0x20_t;

typedef union
{
    uint32_t register_value;
    struct
    {
        /**
         * @brief Active power output. This field is a signed 17-bit fixed point
         * number with 15 fractional bits. It ranges from -2 to ~2 with a step
         * size of (1/2)^15. This number should be multiplied by the overall
         * full-scale power in order to get to watts. For example, if full-scale
         * voltage is 250 V and IPR is 30 A, the multiplier will be 7500 W.
         */
        uint32_t pactive : 17;

        uint32_t resv : 15; // Reserved
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
         * a step size of (1/2)^15. This number should be multiplied by the
         * overall full-scale power in order to get to VA. For example, if full
         * scale voltage is 250 V and IPR is 30 A, then the multiplier will be
         * 7500 VA.
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
        /**
         * @brief Reactive power output. This field is an unsigned 16-bit fixed
         * point number with 15 fractional bits. It ranges from 0 to ~2 with
         * a step size of (1/2)^15. This number should be multiplied by the
         * overall full-scale power in order to get to VAR. For example, if
         * full-scale voltage is 250 V and IPR is 30 A, then the multiplier
         * will be 7500 VAR.
         */
        uint32_t pimag : 16;

        uint32_t resv : 16; // Reserved
    } fields;
} acs_0x23_t;

typedef union
{
    uint32_t register_value;
    struct
    {
        /**
         * @brief Power factor output. This field is a signed 11-bit fixed point number
         * with 9 fractional bits. It ranges from –2 to ~2 with a step size
         * of (1/2)^9.
         */
        uint32_t pfactor : 11;

        uint32_t resv : 21; // Reserved
    } fields;
} acs_0x24_t;

typedef union
{
    uint32_t register_value;
    struct
    {
        /**
         * @brief Number of points used in the rms calculation. This will be the
         * dynamic value that is evaluated internal to the device based on
         * zero crossings of the voltage channel.
         */
        uint32_t numptsout : 9;

        uint32_t resv : 23; // Reserved
    } fields;
} acs_0x25_t;

typedef union
{
    uint32_t register_value;
    struct
    {
        /**
         * @brief Current RMS value averaged according to rms_avg_1. This register
         * will be zero if iavgselen = 0.
         */
        uint32_t irmsavgonesec : 15;

        uint32_t resv1 : 1; // Reserved

        /**
         * @brief Voltage RMS value averaged according to rms_avg_1. This register
         * will be zero if iavgselen = 1.
         */
        uint32_t vrmsavgonesec : 15;

        uint32_t resv2 : 1; // Reserved
    } fields;
} acs_0x26_t;

typedef union
{
    uint32_t register_value;
    struct
    {
        /**
         * @brief Current RMS value averaged according to rms_avg_2. This register
         * will be zero if iavgselen = 0.
         */
        uint32_t irmsavgonemin : 15;

        uint32_t resv1 : 1; // Reserved

        /**
         * @brief Voltage RMS value averaged according to rms_avg_2. This register
         * will be zero if iavgselen = 1.
         */
        uint32_t vrmsavgonemin : 15;

        uint32_t resv2 : 1; // Reserved
    } fields;
} acs_0x27_t;

typedef union
{
    uint32_t register_value;
    struct
    {
        /**
         * @brief Active power value averaged according to rms_avg_1.
         */
        uint32_t pactavgonesec : 17;

        uint32_t resv : 15; // Reserved
    } fields;
} acs_0x28_t;

typedef union
{
    uint32_t register_value;
    struct
    {
        /**
         * @brief Active power value averaged according to rms_avg_2.
         */
        uint32_t pactavgonemin : 17;

        uint32_t resv : 15; // Reserved
    } fields;
} acs_0x29_t;

typedef union
{
    uint32_t register_value;
    struct
    {
        /**
         * @brief This field contains the instantaneous voltage measurement before
         * any rms calculations are done. It is a 17-bit signed fixed-point
         * number with 16 fractional bits. It ranges from –1 to ~1 with a step
         * size of (1/2)^16. This number should be multiplied by the overall full
         * scale of the voltage path in order to get volts. For example, the
         * device is trimmed to a full-scale input of 275 mV, and if a resistor
         * divider network is used to create 275 mV, when it has 250 V
         * across it, then the multiplier should be 250 V.
         */
        uint32_t vcodes : 17;

        uint32_t resv : 15; // Reserved
    } fields;
} acs_0x2A_t;

typedef union
{
    uint32_t register_value;
    struct
    {
        /**
         * @brief This field contains the instantaneous current measurement before
         * any rms calculations are done. This field is a signed 17-bit fixed
         * point number with 15 fractional bits. It ranges from –2 to ~2
         * with a step size of (1/2)^15. This number should be multiplied by
         * the overall full scale of the current path in order to get amps. For
         * example, the device is trimmed to a full-scale input of 30 A, then
         * the multiplier should be 30 A.
         */
        uint32_t icodes : 17;

        uint32_t resv : 15; // Reserved
    } fields;
} acs_0x2B_t;

typedef union
{
    uint32_t register_value;
    struct
    {
        /**
         * @brief This field contains the instantaneous power measurement before
         * any rms calculations are done. This field is a signed 32-bit fixed
         * point number with 29 fractional bits. It ranges from –4 to ~4 with
         * a step size of (1/2)^29. This number should be multiplied by the
         * overall full-scale power in order to get to watts. For example, if
         * full scale voltage is 250 V and IPR is 30 A, then the multiplier will
         * be 7500 W.
         */
        uint32_t pinstant : 32;
    } fields;
} acs_0x2C_t;

typedef union
{
    uint32_t register_value;
    struct
    {
        /**
         * @brief Flag for the voltage zero-crossing events. Will be present and
         * active regardless of DIO_0_Sel and DIO_1_Sel. This flag will
         * still follow the halfcycle_en and squarewave_en settings.
         */
        uint32_t vzerocrossout : 1;

        /**
         * @brief Flag for the overcurrent events. Will be present and active regardless
         * of DIO_0_Sel and DIO_1_Sel. Will only be set when fault is
         * present.
         */
        uint32_t faultout : 1;

        /**
         * @brief Flag for the overcurrent events. This bit will latch and will remain
         * 1 as soon as an overcurrent event is detected. This can be reset by
         * writing a 1 to this field. Will be present and active regardless of
         * DIO settings.
         */
        uint32_t faultlatched : 1;

        /**
         * @brief Flag for the overvoltage events. Will be present and active
         * regardless of DIO_0_Sel and DIO_1_Sel. Will only be set when
         * fault is present.
         */
        uint32_t overvoltage : 1;

        /**
         * @brief Flag for the undervoltage events. Will be present and active
         * regardless of DIO_0_Sel and DIO_1_Sel. Will only be set when
         * fault is present.
         */
        uint32_t undervoltage : 1;

        /**
         * @brief Bit to represent leading or lagging.
         * @param 0 current leading
         * @param 1 current lagging.
         */
        uint32_t posangle : 1;

        /**
         * @brief Sign bit to represent if the power is being generated or consumed.
         * @param 0 generated
         * @param 1 consumed
         */
        uint32_t pospf : 1;

        uint32_t resv : 25; // Reserved
    } fields;
} acs_0x2D_t;

typedef union
{
    uint32_t register_value;
    struct
    {
        /**
         * @brief Access code register:
         * Customer code: 0x4F70656E
         */
        uint32_t access_code : 32;
    } fields;
} acs_0x2F_t;

typedef union
{
    uint32_t register_value;
    struct
    {
        /**
         * @brief Customer write access enabled.
         * 0 = Non-Customer mode
         * 1 = Customer mode
         */
        uint32_t customer_access : 1;
    } fields;
} acs_0x30_t;

#endif // _ACS71020_volatile_H_