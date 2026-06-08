# Práctica 2: Despliegue de Caracteres en Matriz de LEDs 8x8 mediante Multiplexación

Esta práctica consiste en el control y la visualización de caracteres en una matriz de LEDs de 8x8 utilizando un microcontrolador PIC programado en C con el compilador **MPLAB XC8**. 

## Descripción General

El propósito principal de la práctica es optimizar el uso de los pines del microcontrolador mediante la técnica de **multiplexación**, reduciendo las conexiones necesarias de 64 a solo 16 pines (8 para filas en el `PORTB` y 8 para columnas en el `PORTD`). 

Aprovechando el fenómeno de la **Persistencia de la Visión (POV)** con retardos de 5 ms por fila, el sistema realiza un escaneo dinámico tan rápido que el ojo humano percibe una imagen integrada y estable. El repositorio incluye dos lógicas de funcionamiento:
1. **Despliegue Secuencial:** Muestra cíclicamente las letras **'D', 'G', 'M', 'N'**, reteniendo cada carácter en pantalla durante aproximadamente un segundo.
2. **Patrón Estático:** Despliega una letra fija **'X'**.

---

## Contenido de la Carpeta

* **Códigos Fuente (`main.c`):** Archivos con la configuración de fusibles, mapeo de patrones en binario/hexadecimal y el algoritmo de barrido dinámico.
* **Simulación en Proteus:** Archivo de circuito virtual para validar el comportamiento lógico de los puertos y la multiplexación antes del montaje físico.
* **Imágenes de Evidencia:** Fotografías que demuestran el armado del circuito físico.
* **Videos de Prueba:** Demostración en video del funcionamiento en tiempo real.
