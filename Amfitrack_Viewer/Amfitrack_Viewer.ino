/*
    This file is part of ArduPREMO.

    ArduPREMO is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ArduPREMO is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <hiduniversal.h>
#include <ArduPREMO.h>

/*OBJETOS Y VARIABLES GLOBALES*/
USB Usb;
ArduPREMO premo(&Usb);


/* ARDUINO SETUP&CODE */

void setup()
{
  Serial.begin( TRANSMISSION_SPEED );
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif

  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  } else Serial.println(F("\r\n Kit Amfitrack for Arduino program START"));

}


void loop() {

    Usb.Task();    //Enumeración --- Llega a --> Estado Funcionamiento de USB
    
    if(Usb.getUsbTaskState() == USB_STATE_RUNNING){
     
      if(premo.connected()){

        if(premo.TxUID_bool == true){ //Any 3Dcoil sensor ON? YES... PRINT
          //Imprime ID y posición
          Serial.print("Data package : ");
          Serial.print("Posicion X, Y, Z :");
          Serial.print("\t");
          Serial.print(premo.getPosition(0));
          Serial.print("\t");
          Serial.print(premo.getPosition(1));
          Serial.print("\t");
          Serial.println(premo.getPosition(2));
          Serial.print("Orientacion Yaw, Pitch, Roll, Momentum :");
          Serial.print("\t");
          Serial.print(premo.getQuaternion(0));
          Serial.print("\t");
          Serial.print(premo.getQuaternion(1));
          Serial.print("\t");
          Serial.print(premo.getQuaternion(2));
          Serial.print("\t");
          Serial.println(premo.getQuaternion(3));

          #if 1
           //delays next cycle
           delay(CYCLE_TIME);
          #endif
          
        } else Serial.println("No 3DCoil connected.");
        
      }//if(premo.connected)
    } //if(Usb.getUsbTaskState) ... RUNNING

}
