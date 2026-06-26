# Practica 15: Comunicacion Serial (UART) entre dos Microcontroladores

El objetivo principal de esta sesion es establecer una comunicacion entre dos microcontroladores PIC. Para ello, se selecciono el protocolo serial asincrono UART (Universal Asynchronous Receiver-Transmitter). Esta practica se realizo en conjunto con otro equipo, permitiendo que un microcontrolador actue exclusivamente como transmisor y el otro como receptor. Al igual que en practicas anteriores, la frecuencia del oscilador esta configurada a 8 MHz, y se establecio una velocidad de comunicacion (Baud Rate) de 9600 baudios para sincronizar ambos dispositivos.

---

## Parte 1: PIC Transmisor

### Descripcion
En esta primera parte, se configuro el modulo EUSART del microcontrolador para transmitir datos a traves del pin TX (RC6). El programa monitorea constantemente el estado de un boton conectado en el pin RB0 como entrada digital, implementando una rutina de software (debounce) para evitar lecturas erroneas por los rebotes mecanicos del pulsador. 
La logica de transmision es la siguiente:
* Al detectar que el boton ha sido presionado (estado alto), el PIC envia el caracter **'A'** por el puerto serial.
* Al detectar que el boton ha sido soltado (estado bajo), el PIC envia el caracter **'B'**.

### Codigo Fuente
El codigo de este microcontrolador se encuentra aqui: [Transmisor.c](Codigo/Transmisor.c)

---

## Parte 2: PIC Receptor

### Descripcion
En esta segunda parte, se configuro el modulo EUSART del segundo microcontrolador para recibir datos a traves del pin RX (RC7). El programa realiza un sondeo (polling) continuo del buffer de recepcion. Como medida de seguridad y robustez, se implementaron rutinas que limpian el buffer en caso de detectar errores de desbordamiento (Overrun Error) o errores de trama por ruido (Framing Error).
La logica de recepcion evalua los caracteres entrantes para accionar un LED en el pin RD0:
* Si el dato recibido es el caracter **'A'**, el PIC enciende el LED.
* Si el dato recibido es el caracter **'B'**, el PIC apaga el LED.
Esto permite reflejar el estado exacto del boton del primer PIC de forma remota.

### Codigo Fuente
El codigo de este microcontrolador se encuentra aqui: [Receptor.c](Codigo/Receptor.c)

---

### Simulacion y Circuito Fisico

* [Simulacion Practica 15](<Simulacion/MP. Practica 15.png>) 
* [Circuito Practica 15](Circuito/Circuito_Practica_15.jpg) 
* [Video Practica 15](Circuito/Video_Practica_15.mp4) 
