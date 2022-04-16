# ACS71020
The Allegro ACS71020 power monitoring IC greatly simplifies
the addition of power monitoring to many AC powered systems.
The sensor may be powered from the same supply as the
system’s MCU, eliminating the need for multiple power supplies
and expensive digital isolation ICs. The device’s construction
includes a copper conduction path that generates a magnetic field
proportional to applied current. The magnetic field is sensed
differentially to reject errors introduced by common mode fields.

## This Library
Is a comprehensive collection of register maps and their bitfields. 
When completed, developer would easily be able to get and set all
configurations, and read all measurements. The bitfields are indepedent
of protocol used, so both i2c and SPI will work. However, development
related to i2c will be preferred.

## Note
This is an incomplete library, and is not intended to be used in
its current form. Its concept has only been tested in software, never on
an actual hardware platform.