/**************************************************************************/
/*!
    @file     BLEBms.cpp
    @author   karthikkaryamapudi@gmail.com

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2018, Adafruit Industries (adafruit.com)
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**************************************************************************/

#include "bluefruit.h"
#include "InternalFileSystem.h"

#define UUID16_BMS_SERVICE 0x181E
#define UUID16_BMS_CONTROL 0x2AA4
#define UUID16_BMS_FEATURE 0x2AA5

#define BLE_BMS_REQUESTING_DEVICE_BR_LE (0x01 << 0)
#define BLE_BMS_REQUESTING_DEVICE_BR_LE_AUTH_CODE (0x01 << 1)
#define BLE_BMS_REQUESTING_DEVICE_BR (0x01 << 2)
#define BLE_BMS_REQUESTING_DEVICE_BR_AUTH_CODE (0x01 << 3)
#define BLE_BMS_REQUESTING_DEVICE_LE (0x01 << 4)
#define BLE_BMS_REQUESTING_DEVICE_LE_AUTH_CODE (0x01 << 5)
#define BLE_BMS_ALL_BONDS_BR_LE (0x01 << 6)
#define BLE_BMS_ALL_BONDS_BR_LE_AUTH_CODE (0x01 << 7)
#define BLE_BMS_ALL_BONDS_BR (0x01 << 8)
#define BLE_BMS_ALL_BONDS_BR_AUTH_CODE (0x01 << 9)
#define BLE_BMS_ALL_BONDS_LE (0x01 << 10)
#define BLE_BMS_ALL_BONDS_LE_AUTH_CODE (0x01 << 11)
#define BLE_BMS_ALL_EXCEPT_REQUESTING_DEVICE_BR_LE (0x01 << 12)
#define BLE_BMS_ALL_EXCEPT_REQUESTING_DEVICE_BR_LE_AUTH_CODE (0x01 << 13)
#define BLE_BMS_ALL_EXCEPT_REQUESTING_DEVICE_BR (0x01 << 14)
#define BLE_BMS_ALL_EXCEPT_REQUESTING_DEVICE_BR_AUTH_CODE (0x01 << 15)
#define BLE_BMS_ALL_EXCEPT_REQUESTING_DEVICE_LE (0x01 << 16)
#define BLE_BMS_ALL_EXCEPT_REQUESTING_DEVICE_LE_AUTH_CODE (0x01 << 17)

BLEBms::BLEBms(void)
    : BLEService(UUID16_BMS_SERVICE), _chr_control(UUID16_BMS_CONTROL)
{
}

void BMSWriteCallback(uint16_t conn_hdl, BLECharacteristic *chr, uint8_t *data, uint16_t len)
{
    (void)chr;

    if (len == 1)
    {
        bond_keys_t keys;
        switch (data[0])
        {
        case 0x03: // Delete requesting
            Bluefruit.Connection(conn_hdl)->removeBondKey();
            break;

        case 0x09: // Delete all except requesting
            Bluefruit.Connection(conn_hdl)->loadBondKey(&keys);
        case 0x06: // Delete all
            Bluefruit.Periph.clearBonds();
            break;
            
        default:
        break;
        }

        if(data[0] == 0x09)
            Bluefruit.Connection(conn_hdl)->saveBondKey(&keys);
    }
}

err_t BLEBms::begin(void)
{
    // Invoke base class begin()
    VERIFY_STATUS(BLEService::begin());

    _chr_control.setProperties(CHR_PROPS_WRITE);
    _chr_control.setMaxLen(1);
    _chr_control.setPermission(SECMODE_NO_ACCESS, SECMODE_ENC_WITH_MITM);
    _chr_control.setWriteCallback(BMSWriteCallback);
    VERIFY_STATUS(_chr_control.begin());

    BLECharacteristic chr_feature(UUID16_BMS_FEATURE);
    chr_feature.setTempMemory();
    chr_feature.setProperties(CHR_PROPS_READ);
    chr_feature.setFixedLen(4);
    chr_feature.setPermission(SECMODE_ENC_WITH_MITM, SECMODE_NO_ACCESS);
    VERIFY_STATUS(chr_feature.begin());
    chr_feature.write32(BLE_BMS_REQUESTING_DEVICE_LE |
                        BLE_BMS_ALL_BONDS_LE |
                        BLE_BMS_ALL_EXCEPT_REQUESTING_DEVICE_LE);

    return ERROR_NONE;
}
