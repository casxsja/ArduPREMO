# ArduPREMO

The code is released under the GNU General Public License.

# Summary

Arduino library for projects with kit Amfitrack of Amfitech and PREMO Group. With this project you could use this kit with your Arduino board (only all official Arduino AVR boards) and USB Host Shield with Amfitrack's sensors and hub, also you need to download the library of Arduino Host Shield 2.0 of Felis for use USB Host Shield. This library is based on this library for USB communications.
This project was my thesis, so you can find the document in pdf extension in the main folder, but it is completely in Spanish language.

https://raw.githubusercontent.com/casxsja/ArduPREMO/master/asset/draft.jpeg

The library has the variables and functions above:

Estructuras Position y Quaternion
Estas estructuras se definen en el archivo header y fuera de la clase ArduPREMO. Su finalidad es la de crear una serie de variables de posicionamiento (position) y orientación (quaternion) del tipo flotante (número con decimales) y calcularlos en milímetros, según marca el protocolo USB de Amfitech recogido en el Anexo del presente documento.

***Variables de la clase ArduPREMO

En esta sección se describen las variables creadas en la clase ArduPREMO. Las variables son las siguientes:

▪ uint8_t TxUID
   Variable que sirve para identificar la ID del receptor 3DCoild conectado al Hub Amfitrack. Si no hay ningún receptor conectado el                programa imprime un aviso por pantalla. El byte TxUID está contenido en el paquete de datos que envía el Hub Amfitrack.

▪ long int posX
▪ long int posY
▪ long int posZ
▪ long int quatX
▪ long int quatY
▪ long int quatZ
▪ long int quatW
  Estas siete variables son el posicionamiento y la orientación del receptor obtenido tras el cálculo de la función intFromBytes.     Tienen una extensión long int (entero largo) porque el receptor envía el posicionamiento 3D para los ejes tanto positivos como negativos, necesitando así un mayor número de bytes. Se aconseja al usuario no utilizar estas variables directamente y sí implementar las funciones getPosition y getQuaternion descritas más abajo.

▪ uint8_t* pBUFF
  La variable pBUFF es un puntero de datos. Este contiene el paquete de datos que el Hub envía al Arduino MEGA2560. Hay que señalar que este puntero se crea consiguiendo los datos del puntero Buf, el cual no siempre posee el paquete de datos. Esto depende del proceso de enumeración y no contiene el paquete hasta que esa enumeración ha sido recorrida con éxito.

▪ bool TxUID_bool
  Este booleano sirve para indicar si se ha conectado (True) o no (False) un receptor 3D coil.

▪ Definición CYCLE_TIME
  Esta definición sirve para el ejemplo creado Amfitrack_Viewer. Con él, el usuario puede ralentizar la obtención de las variables para poder leer mejor la consola.

***Funciones de la clase ArduPREMO

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


# IMPORTANT:
At first, the USB communication could fail due to STALL problem. To fix it just unplug and plug the USB from USB Host Shield. Other solution is implement a virtual switch like in this example: https://web.archive.org/web/20160821185145/https://www.circuitsathome.com/mcu/vbus-power-control-on-usb-host-shield  .


