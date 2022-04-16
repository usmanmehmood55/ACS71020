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
#include "ACS71020_eeprom.h"
#include "ACS71020_volatile.h"

/**
 * register maps and bit fields are in ACS71020_eeprom.h and ACS71020_volatile.h
 * this file will contain the functions to read and write to the registers, and
 * to perform power related operations
 */

#endif // _ACS71020_H_