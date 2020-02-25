# ArduPREMO

The code is released under the GNU General Public License.

## Summary

Arduino library for projects with kit Amfitrack of Amfitech and PREMO Group. With this project you could use this kit with your Arduino board (*only all official Arduino AVR boards*) and USB Host Shield with Amfitrack's sensors and hub, also you need to download the library of Arduino Host Shield 2.0 of Felis for use USB Host Shield. This library is based on this library for USB communications.
This project was my thesis, so you can find the document in pdf extension in the main folder, but it is completely in Spanish language.

![draft of connections of all the elements](https://raw.githubusercontent.com/casxsja/ArduPREMO/master/assets/draft.jpg)

The library has the variables and functions above:

*Structs*

▪ Position and Quaternion structs:
   These structs are defined in header file and out of ArduPREMO class. The target is to create position and orientation variables (six degrees of freedom) float type and calculate them in millimeters (more info in USB protocol of Amfitrack).

*Variables of ArduPREMO class*

In this section we can find variables from ArduPREMO class. The variables are below:

▪ uint8_t TxUID
   This variable is used to identify ID of 3Dcoil sensor connected to your Hub Amfitrack. If does not exist any sensor connected (TxUID_bool), the program will print a notification. TxUID byte stay in the data packet that Hub sends.

▪ long int posX
▪ long int posY
▪ long int posZ
▪ long int quatX
▪ long int quatY
▪ long int quatZ
▪ long int quatW
  These seven variables are sensor's position and orientation (we will get them from intFromBytes). They are long because the sensor sends 3D positioning for positive and negative axis, so we need a bigger bytes number. I suggest to the user not use these variables directly and implement getPosition and getQuaternion functions which are explained in the next section.

▪ uint8_t* pBUFF
  pBUFF variable is a data pointer. It has the data packet that Amfitrack's Hub sends to Arduino MEGA2560. It should be noted that this pointer is created acquiring the data from Buf pointer which does not always has the data packet. This depends of enumeration process and this pointer has not the data packet until this machine state is in running (configured) state.

▪ bool TxUID_bool
  This boolean is used to point out if a 3D sensor is connected (True) or disconnected (False).

▪ Definition CYCLE_TIME
  This definition is used in Amfitrack_viewer.ino sketch. The user can use it to slow down the variables obtaining and read the Arduino console better.

**Functions of ArduPREMO class**

En esta sección se detallan las funciones creadas en la clase ArduPREMO. Las funciones son las siguientes:

▪ Void ParseHIDData
  Esta función se usa para analizar los datos del USB HID. Fue reimplementada de la clase HIDUniversal, es decir, HIDUniversal contiene un método virtual llamado ParseHIDData y se utiliza en la librería desarrollada. Un método virtual es una función asociada a un objeto que indica cómo ha de definirse una función, pero no indica cómo resuelve el problema que se plantee [35]. Por ello, cada librería tiene una función ParseHIDData distinta.

En el contexto del presente proyecto, el método ParseHIDData de la clase ArduPREMO se encarga de copiar el buffer y de confirmar que se trata del puntero de datos buscado.

▪ Void Screening
  Screening es un filtro para el paquete de datos. Con ello se puede confirmar que el puntero de datos obtenido es el especificado en el protocolo USB proporcionado por Amfitech, se puede encontrar en el Anexo.

▪ Bool connected
  Esta función es un booleano que resulta verdadero cuando el ID Vendor y el ID Product del Hub coinciden con los definidos dentro del archivo ArduPREMO.h. Si es falso, no se imprimirá ningún puntero de datos.

▪ Long intFromBytes
  Función para pasar los bytes del paquete de datos a decimal. Además, permite al usuario seleccionar si el paquete está en Little Endian o Big Endian, si necesita el posicionamiento con signo o sin signo.

▪ Const uint8_t* Getbuf
  Esta función sirve para hacer una copia del puntero de datos. Es del tipo constante para prevenir que sea alterado en alguna otra parte del programa.

▪ Float getQuaternion y Float getPosition
  Ambas funciones son las que necesita utilizar el usuario si quiere recibir los resultados del cálculo de posicionamiento y orientación del Sensor Receptor Amfitrack. Estas funcionan con un case en el que, si el usuario en su código escribe 0, 1 o 2, le entregará la orientación o posición respecto a los ejes X, Y o Z, respectivamente. El case 3 solo sirve para la orientación, ya que entrega el Momento.

▪ Quaternion getQuaternion y Position getPosition
  Estas funciones sirven para realizar una copia de las variables calculadas. Así el usuario no debe preocuparse de si elimina por
error dichas variables durante la manipulación de la librería en el momento de la implementación en su respectivo proyecto.


## IMPORTANT:
At first, the USB communication could fail due to STALL problem. To fix it just unplug and plug the USB from USB Host Shield. Other solution is implement a virtual switch like in this example: https://web.archive.org/web/20160821185145/https://www.circuitsathome.com/mcu/vbus-power-control-on-usb-host-shield  .


