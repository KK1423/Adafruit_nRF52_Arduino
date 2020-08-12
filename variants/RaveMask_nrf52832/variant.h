 /*
  Copyright (c) 2014-2015 Arduino LLC.  All right reserved.
  Copyright (c) 2016 Sandeep Mistry All right reserved.
  Copyright (c) 2018, Adafruit Industries (adafruit.com)

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _VARIANT_FEATHER52832_
#define _VARIANT_FEATHER52832_

/** Master clock frequency */
#define VARIANT_MCK       (64000000ul)

// #define USE_LFXO      // Board uses 32khz crystal for LF
#define USE_LFRC    // Board uses RC for LF

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "WVariant.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

// Number of pins defined in PinDescription array
#define PINS_COUNT           (9u)
#define NUM_DIGITAL_PINS     (9u)
#define NUM_ANALOG_INPUTS    (1u)
#define NUM_ANALOG_OUTPUTS   (0u)

// LEDs
#define PIN_LED1             (0xFF) // OOB value to disable LEDS
#define PIN_LED2             (0xFF)

#define LED_BUILTIN          PIN_LED1
#define LED_CONN             PIN_LED2

#define LED_RED              PIN_LED1
#define LED_BLUE             PIN_LED2

#define LED_STATE_ON         1         // State when LED is litted

/*
 * Analog pins
 */
#define PIN_A0               (4)

static const uint8_t A0  = PIN_A0 ;
#define ADC_RESOLUTION    14

// Other pins
#define PIN_VBAT           PIN_A0
#define PIN_INTB           0
#define PIN_SDB            3

/*
 * Serial interfaces
 */
#if 0
#define RTT_SERIAL
#define PIN_SERIAL1_RX       (8)
#define PIN_SERIAL1_TX       (7)
#else
#define PIN_SERIAL_RX       (8)
#define PIN_SERIAL_TX       (7)
#endif

/*
 * SPI Interfaces
 */
#define SPI_INTERFACES_COUNT 0
/*
#define PIN_SPI_MISO         (14)
#define PIN_SPI_MOSI         (13)
#define PIN_SPI_SCK          (12)

static const uint8_t SS   = 27 ;
static const uint8_t MOSI = PIN_SPI_MOSI ;
static const uint8_t MISO = PIN_SPI_MISO ;
static const uint8_t SCK  = PIN_SPI_SCK ;
*/


/*
 * Wire Interfaces
 */
#define WIRE_INTERFACES_COUNT 1

#define PIN_WIRE_SDA         (2u)
#define PIN_WIRE_SCL         (1u)

#ifdef __cplusplus
}
#endif

/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#endif
