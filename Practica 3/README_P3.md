# Práctica 3: Contador de 0 a 9 y 0 a F en Display de 7 Segmentos (Ánodo Común)

Esta práctica consiste en la implementación de dos contadores secuenciales utilizando un microcontrolador PIC programado en C con el compilador **MPLAB XC8** y visualizados a través de un display de 7 segmentos.

## Descripción General

El propósito de esta práctica es diseñar y codificar la lógica necesaria para controlar un display de 7 segmentos de **ánodo común** conectado al puerto de salida `PORTD`. 

El sistema incluye dos modos de conteo independientes mediante bucles cíclicos:
1. **Contador Decimal (0 a 9):** Realiza una secuencia continua a través de los diez dígitos básicos de la base decimal.
2. **Contador Hexadecimal (0 a F):** Amplía el rango para incluir las representaciones de los caracteres de la 'A' a la 'F', completando los 16 estados del sistema hexadecimal.

Dado que el display es de **ánodo común**, los segmentos individuales se encienden cuando reciben un cero lógico (`0` o tierra). Por este motivo, en el código se utiliza el operador de inversión bit a bit NOT (**`~`**) justo antes de enviar el dato al puerto (`PORTD = ~display[i];`). Cada estado del conteo se mantiene visible en pantalla durante exactamente **1 segundo** (`__delay_ms(1000)`).

---

## Contenido de la Carpeta

Esta carpeta contiene todos los entregables y evidencias del desarrollo de la práctica:

* **Códigos Fuente (`main.c`):** Archivos que contienen la configuración de fusibles (fuses) para el oscilador XT, los arreglos de datos mapeados para el display y los bucles secuenciales.
* **Simulación en Proteus:** Archivo del circuito virtual para validar la correcta secuencia de encendido de los pines y descartar errores lógicos antes del montaje físico.
* **Circuito:** Carpeta que almacena los registros y evidencias del circuito físico montado en la protoboard:
  * **Imágenes de Evidencia:** Fotografías detalladas de la conexión del microcontrolador, resistencias limitadoras y el display de 7 segmentos.
  * **Videos de Prueba:** Demostraciones en video que comprueban el funcionamiento exacto del temporizador de 1 segundo por cada dígito.
