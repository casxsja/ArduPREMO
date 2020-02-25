# ArduPREMO

The code is released under the GNU General Public License.

## Summary

Arduino library for projects with kit Amfitrack of Amfitech and PREMO Group. With this project you could use this kit with your Arduino board (*only all official Arduino AVR boards*) and USB Host Shield with Amfitrack's sensors and hub, also you need to download the library of Arduino Host Shield 2.0 of Felis for use USB Host Shield. This library is based on this library for USB communications.
This project was my thesis, so you can find the document in pdf extension in the main folder, but it is completely in Spanish language.

![[(https://raw.githubusercontent.com/casxsja/ArduPREMO/master/assets/draft.jpg)]]

The library has the variables and functions above:

**Structs**

▪ Position and Quaternion structs:
   These structs are defined in header file and out of ArduPREMO class. The target is to create position and orientation variables (six degrees of freedom) float type and calculate them in millimeters (more info in USB protocol of Amfitrack).

**Variables of ArduPREMO class**

In this section we can find variables from ArduPREMO class. The variables are below:

▪ uint8_t TxUID:
   This variable is used to identify ID of 3Dcoil sensor connected to your Hub Amfitrack. If does not exist any sensor connected (TxUID_bool), the program will print a notification. TxUID byte stay in the data packet that Hub sends.

▪ long int posX
▪ long int posY
▪ long int posZ
▪ long int quatX
▪ long int quatY
▪ long int quatZ
▪ long int quatW

  These seven variables are sensor's position and orientation (we will get them from intFromBytes). They are long because the sensor sends 3D positioning for positive and negative axis, so we need a bigger bytes number. I suggest to the user not use these variables directly and implement getPosition and getQuaternion functions which are explained in the next section.

▪ uint8_t* pBUFF:
  pBUFF variable is a data pointer. It has the data packet that Amfitrack's Hub sends to Arduino MEGA2560. It should be noted that this pointer is created acquiring the data from Buf pointer which does not always has the data packet. This depends of enumeration process and this pointer has not the data packet until this machine state is in running (configured) state.

▪ bool TxUID_bool:
  This boolean is used to point out if a 3D sensor is connected (True) or disconnected (False).

▪ Definition CYCLE_TIME:
  This definition is used in Amfitrack_viewer.ino sketch. The user can use it to slow down the variables obtaining and read the Arduino console better.

**Functions of ArduPREMO class**

In this section are detailed the functions created in ArduPREMO class. The functions are below:

▪ Void ParseHIDData:
  This function is used to analyze the data of USB HID. It was reimplemented from HIDUniversal class of USB HOST SHIELD 2.0 library (HIDUniversal has the virtual method called ParseHIDData.
  *Note: A virtual method is a function associated to an object that point out how has a function to be defined, although it does not        indicate how to resolve the problem. Because of it, every library has a different ParseHIDData function.*

In this context, ParseHIDDATA method of ArduPREMO class is responsible of copying the buffer and confirming that it is the data pointer that we need.

▪ Void Screening:
  Screening is a filter for data packets. With that we can confirm that the data pointer is like the data packet of USB protocol of Amfitrack documentation.

▪ Bool connected:
  This function is a boolean that is True when ID Vendor and Product of your Hub is the same that the ID Vendor and Product specified in ArduPREMO.h. If it is False, the data pointer will not be printed in Arduino_viewer.ino sketch.
*Important: ID Vendor and ID Product could change from specified in ArduPREMO.h. Use a sniffer to know the IDs of your own kit Amfitrack.)

▪ Long intFromBytes:
  This function is used to convert bytes from data pointer to decimal. Also, it allows to user to choose between Little Endian or Big Endian. Little Endian is predetermined here.
  
▪ Const uint8_t* Getbuf:
  This function was created to make a copy of the data pointer. Is of Const type to avoid any change that the library could do accidentaly.

▪ Float getQuaternion y Float getPosition:
  Both functions are needed for the user if he wants to get the results of position and orientation calculus from Amfitrack's hardware. They have a Switch. The user can use this Switch to choose the information about position or orientation that he wants to get from  Hub. They run on the same way.

▪ Quaternion getQuaternion y Position getPosition:
  These functions are used to make a copy of calculated variables. So the user does not worry if he accidentaly remove these variables when he is playing with the library or implementing the library in his project.

## IMPORTANT:
At first, the USB communication could fail due to STALL problem. To fix it just unplug and plug the USB from USB Host Shield. An optimal solution is implementing a virtual switch like in this example: https://web.archive.org/web/20160821185145/https://www.circuitsathome.com/mcu/vbus-power-control-on-usb-host-shield  .


