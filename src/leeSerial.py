#
# escribeESP32.py
#
# Este programa lee envia y recibe mensajes a un Microcontrolador
# ESP32 por el puerto serie
#
import serial
# Crea una instancia de la clase Serial para usar el puerto serie
# y lo configura al puerto serie de la PC al que se conectara el
# Microcontrolador ESP32, la velocidad de conexion y el timeout.
# timeout es el tiempo que la funcion readline() espera por datos
# en el puerto serie. readline() interpreta el timeout como un
# fin de linea.
#
# Para saber a que puerto se conecto el Microcontrolador ESP32
# se puede checar en la esquina inferior derecha del IDE 2.0 de
# Arduino
# Velocidad de transmisión del puerto serie



def menus(menu=1):
    comando = ""
    if(menu == 1):
        print('Para apagar los Led, teclea el comando "off"')
        print('Para encender los Led de izquierda a derecha, teclea el comando "ltr"')
        print('Para encender los Led de derecha a izquierda, teclea el comando "rtl"')
        print('Para flashear los led, teclea el comando "rtl"')
        print('Para salir, teclea el comando "exit"')
        print()
        comando = input('Comando deseado? ')
        print()
        
    elif(menu == 2):
        print('Para apagar el Led, teclea el comando "off"')
        print()
        comando = input('Comando deseado? ')
        print()  
        
    return comando;      


BAUD_RATE = 115200
esp32 = serial.Serial('COM6', BAUD_RATE, timeout=5)
while True:
    comando = menus()
    if comando == 'exit':
        break
    if comando == 'off':
        esp32.write(b'off')
    elif comando == 'ltr':
        esp32.write(b'ltr')
        comando = menus(2)
    elif comando == 'rtl':
        esp32.write(b'rtl')
    elif comando == 'flash':
        esp32.write(b'flash')
    else:
        print('Comando desconocido')
    continue
    # Lee el puerto serie. Elimina los dos ultimos caracteres que
    # son el salto de linea
data = esp32.readline()[:-2]
    # Si se leyeron datos del puerto serie
if data:
    # Convierte la cadena de bytes a una cadena
    sdata = data.decode('utf-8')
    print(sdata)
    # Lee el puerto serie. Elimina los dos ultimos caracteres que
    # son el salto de linea
    data = esp32.readline()[:-2]
    # Si se leyeron datos del puerto serie
    if data:
    # Convierte la cadena de bytes a una cadena
        sdata = data.decode('utf-8')
        print(sdata)
        print()
