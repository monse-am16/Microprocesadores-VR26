# Practica 1

**Materia:** Microprocesadores 

**Integrantes del equipo:**
* [Diego Adrian Castro Ovalle]
* [Monserrat Ayala Muñoz]

En este repositorio se encuentran documentadas la practica realizada durante la sesion de clase y las dos actividades complementarias. En todas las practicas se utiliza el **Puerto D** configurado como salida digital y un cristal de cuarzo como oscilador configurado a 8 MHz.

---
## Practica de clase: Hacer parpadear LEDs 

### Descripcion Practica de clase
El objetivo de esta práctica es la familiarización con la configuración básica del PIC y la manipulación de puertos completos; esto mediante el encendido y apagado de LEDs, o blinks.  

En la practica, el programa manda un estado ALTO (`0xFF`) para encender todos los LEDs del puerto D, espera 500 milisegundos, e invierte el estado logico (`~PORTD`) para apagarlos, en un ciclo infinito.

### Codigo 
El codigo de esta practica se encuentra aqui: [Clase_1.c](Codigo/Clase_1.c)

### Evidencia de Simulacion y Circuito Fisico
[Simulacion Practica de Clase](Simulacion/Simulacion_P1.jpeg) 
*La simulacion es la misma para todas las practicas realizadas en clase*
[Circuito Practica de Clase](Circuito/Circuito_Practica_1.png) 
*Se empleo el mismo circuito fisico para todas las practicas, solo se hicieron cambios en el codigo*
[Video de funcionamiento](Circuito/Video_Practica_1.mp4) 
*En el video se muestran las secuencias definidas para todas las practicas*

---

## Actividad 1: Contador Binario de 6 Bits

### Descripcion
La actividad 1 consiste en un contador binario ascendente de 6 bits, pero considerando 8 LEDs. Mediante un ciclo `for` que va del 0 al 63, el valor decimal se asigna directamente al registro `PORTD`. De esta manera los primeros 6 LEDs del puerto representan visualmente el conteo en formato binario, con un retardo de 500 ms entre cada incremento.

### Codigo 
El codigo de la actividad se encuentra aqui: [Actividad1_P1.c](Codigo/Actividad1_P1.c)

### Evidencia de Simulacion y Circuito Fisico
[Simulación Contador](Simulacion/Simulacion_P1.jpeg)
[Circuito Contador](Circuito/Circuito_Practica_1.png) 
[Video de funcionamiento](Circuito/Video_Practica_1.mp4) 

---

## Actividad 2: Caminata de 8 LEDs

### Descripcion
En esta actividad se busca crear un efecto visual de "ida y vuelta" con un solo LED encendido a la vez recorriendo todo el Puerto D. Para esto, se utilizaron operaciones de desplazamiento de bits a la izquierda (`1<<i`). El primer ciclo `for` realiza la secuencia de ida (del pin 0 al 7), y el segundo ciclo realiza el regreso (del pin 6 al 0), repitiendo el ciclo de forma continua.

### Codigo
El codigo de esta actividad se encuentra aqui: [Actividad2_P1.c](Codigo/Actividad2_P1.c)

### Evidencia de Simulacion y Circuito Fisico
[Simulación Caminata](Simulacion/Simulacion_P1.jpeg)
[Circuito Caminata](Circuito/Circuito_Practica_1.png) 
[Video de funcionamiento](Circuito/Video_Practica_1.mp4) 
