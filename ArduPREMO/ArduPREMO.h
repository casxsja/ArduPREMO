/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

*   It was created for academic purpose (tesis project) by Álvaro José Ávila-Casanova Ureña from University of Málaga.

*   Contact: R&D PREMO Group - https://www.grupopremo.com/

*/


#ifndef ARDUPREMO_H
#define ARDUPREMO_H

#include <HIDUniversal.h>
#include <SPI.h>
#include <usbhub.h>

struct Position {
    float X;
    float Y;
    float Z;
    Position()=delete;
    Position(long pX,long pY,long pZ):
                X{static_cast<float>(pX)*0.01},
                Y{static_cast<float>(pY)*0.01},
                Z{static_cast<float>(pZ)*0.01} {}
};


struct Quaternion {
    float X;
    float Y;
    float Z;
    float W;
    Quaternion()=delete;
    Quaternion(long pX,long pY,long pZ,long pW):
                X{static_cast<float>(pX)/1000000.0},
                Y{static_cast<float>(pY)/1000000.0},
                Z{static_cast<float>(pZ)/1000000.0},
                W{static_cast<float>(pW)/1000000.0} {}
};

class ArduPREMO : public HIDUniversal
{
public:

        USB Usb;

        // CONSTANTS
        #define AmfiHUB_VID       0x0C17
        #define AmfiHUB_PID       0x0D12
        #define MAX_DATA 64 // [bytes]
        #define TRANSMISSION_SPEED 115200 // [bps]
        #define CYCLE_TIME 200 // [ms]

        bool TxUID_bool = false;


private:
        uint8_t TxId = 0; // Message number
        uint8_t TxUID = 0; // Sensor ID
        long int posX = 0;
        long int posY = 0;
        long int posZ = 0;
        long int quatX = 0;
        long int quatY = 0;
        long int quatZ = 0;
        long int quatW = 0;
        uint8_t* pBUFF; //puntero copia

        void ParseHIDData(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf); // Called by the HIDUniversal library
        void Screening();
        uint8_t OnInitSuccessful(); // Called by the HIDUniversal library on success (BOOLEAN)

public:
        ArduPREMO(USB *p) : HIDUniversal(p) {};
        bool connected() {
                return (HIDUniversal::isReady() && HIDUniversal::VID == AmfiHUB_VID && HIDUniversal::PID == AmfiHUB_PID);
        };            /*linea93 hiduniversal.h*/

        long intFromBytes(uint8_t b0, uint8_t b1, uint8_t b2, bool little, bool _signed);


        uint8_t* Getbuf( uint8_t *buffealo){
          return buffealo;
        }

        float getQuaternion(uint8_t n_comp) const {
            Quaternion copia(quatX,quatY,quatZ,quatW);
            switch(n_comp) {
                case 0 : return copia.X;
                case 1 : return copia.Y;
                case 2 : return copia.Z;
                default : return copia.W;
            }
        }
        Quaternion getQuaternion() const {
            Quaternion copia(quatX,quatY,quatZ,quatW);
            return copia;
        }

        float getPosition(uint8_t n_comp) const {
            Position copia(posX,posY,posZ);
            switch(n_comp) {
                case 0 : return copia.X;
                case 1 : return copia.Y;
                default : return copia.Z;
            }
        }
        Position getPosition() const {
            Position copia(posX,posY,posZ);
            return copia;
        }
};

#endif // ARDUPREMO_H
