/*
    This file is part of ArduPREMO.

    ArduPREMO is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "ArduPREMO.h"

void ArduPREMO::ParseHIDData(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) {

        if (len && buf)  {
                pBUFF = Getbuf(buf);
                Screening();

                #if 0
                for (uint8_t i = 0; i < len; i++) {
                  Serial.print(pBUFF[i],HEX);
                  Serial.print(" ; ");
                }
                Serial.println("");
                #endif
        }


}


uint8_t ArduPREMO::OnInitSuccessful() { // Called by the HIDUniversal library on success (BOOLEAN)
        if (HIDUniversal::VID != AmfiHUB_VID || HIDUniversal::PID != AmfiHUB_PID){ // Make sure the right device is actually connected
                return 0;
        }

        return 1;
}


void ArduPREMO::Screening() {
  uint8_t pkg[64];

  for(uint8_t cont{0}; cont<64; ++cont){
    pkg[cont] = pBUFF[cont];             //Copy of buffer to use it in Screening function.
  }

 if ((pkg[7]!= 0x00 and pkg[0] == 0x02) and (pkg[1] == 0x0B) and (pkg[2] == 0x83) and
     (pkg[6] == 0x17) and (pkg[33] == 0x00)) {

   TxUID_bool = true;

   TxId = pkg[4];
   TxUID = pkg[7];

   posX = intFromBytes(pkg[10], pkg[11], pkg[12], true, true);
   posY = intFromBytes(pkg[13], pkg[14], pkg[15], true, true);
   posZ = intFromBytes(pkg[16], pkg[17], pkg[18], true, true);
   quatX = intFromBytes(pkg[19], pkg[20], pkg[21], true, true);
   quatY = intFromBytes(pkg[22], pkg[23], pkg[24], true, true);
   quatZ = intFromBytes(pkg[25], pkg[26], pkg[27], true, true);
   quatW = intFromBytes(pkg[28], pkg[29], pkg[30], true, true);

   Serial.println("Todos los datos coinciden y se han calculado a decimal: ");
 } else if(pkg[7] == 0x00) {TxUID_bool = false;}

}//void Screening()



/*
 * intFromBytes - makes an long integer from its bytes
 * This function is from Víctor E. Torres López - professor in University of Málaga.
 */
long ArduPREMO::intFromBytes(uint8_t b0, uint8_t b1, uint8_t b2, bool little, bool _signed) {
  long value;

  if (little) { // little-endian
    value = b2;
    value = value << 8;
    value = value + b1;
    value = value << 8;
    value = value + b0;
  }
  else { // big-endian
    value = b0;
    value = value << 8;
    value = value + b1;
    value = value << 8;
    value = value + b2;
  }

  if (_signed and (value & 0x800000)) { // the 24 bits number is negative
    value = value | 0xFF000000; // Sign extension by padding the left side with ones
  }

  return value;
}

