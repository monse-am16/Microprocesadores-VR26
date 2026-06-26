# Practica 5: Multiplexacion e interrupciones externas

Este repositorio integra las 3 partes que componen la práctica 5. El objetivo principal de la práctica es comprender la tecnica de multiplexacion empleada en el control de varios displays de 7 segmentos, así como el manejo de interrupciones externas y la lectura de entradas digitales. Al igual que en practicas anteriores, la frecuencia del oscilador es de 8 MHz.  

---

## Clase 5A: Contador Multiplexado (0 - 9999)

### Descripcion
En esta primera parte se implementa un contador del 0 al 9999 utilizando un display de 7 segmentos de 4 digitos. Para visualizar los 4 numeros al mismo tiempo, se emplea la **multiplexacion**. 
El microcontrolador descompone el numero en millares, centenas, decenas y unidades. Luego, mediante el Puerto C, enciende un solo digito a la vez, enviando la secuencia correspondiente por el Puerto D. Este proceso se repite con retardos muy cortos (`__delay_ms(1)`), engañando al ojo humano por la persistencia de la vision.

### Codigo Fuente
El codigo de esta práctica se encuentra aqui: [Clase_7.c](Codigo/Clase_5A.c)

### Simulacion
* [Simulacion de Clase 5A](Simulacion/MP.%20Clase%205A.png) 


---

## Clase 5B: Interrupciones Externas

### Descripcion
Se introduce el uso de **Interrupciones Externas** por hardware. Se define el pin RB0 para detectar un flanco de bajada (`INTEDG = 0`).
El programa principal (bucle `while`) simplemente muestra un contador del 0 al 9 en un solo display de 7 segmentos. Sin embargo, al presionar el botón conectado a RB0, se activa la bandera `INTF` e interrumpe el programa para ejecutar la función `ISR` (Rutina de Servicio de Interrupción), la cual hace parpadear un LED conectado en RC0 antes de regresar a la cuenta normal.

### Codigo Fuente
El codigo de esta práctica se encuentra aqui: [Clase_7.c](Codigo/Clase_5B.c)

### Simulacion
* [Simulacion de Clase 5B](Simulacion/MP.%20Clase%205B.png) 

---

## Actividad 5: Contador Bidireccional Multiplexado

### Descripcion
Esta actividad combina la multiplexacion de la Clase 5A con la lectura de botones de la Clase 5B (utilizando las resistencias Pull-up internas del microcontrolador `WPUB = 0xFF`). 
El programa consiste en un contador de 0 a 9999 que se muestra en los 4 displays. Al detectar que el pulsador conectado a RB0 es presionado (cambio de estado de 1 a 0), el sistema invierte la direccion del conteo, permitiendo que el contador incremente o decremente dinamicamente. 

### Codigo Fuente
El codigo de esta actividad se encuentra aqui: [Actividad_7.c](Codigo/Actividad_5.c)

### Simulacion y Circuito Fisico

* [Simulacion de Actividad 7](Simulacion/MP.%20Practica%205.png) 
* [Circuito Practica 7](Circuito/Circuito_Practica_5.jpg) 
* [Video Practica 7](Circuito/Video_Practica_5.mp4) 

