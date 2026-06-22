# Practica 5: Multiplexacion e interrupciones externas

Este repositorio integra las 3 partes que componen la práctica 5. El objetivo principal de la práctica es comprender la tecnica de multiplexacion empleada en el control de varios displays de 7 segmentos, así como el manejo de interrupciones externas y la lectura de entradas digitales. Al igual que en practicas anteriores, la frecuencia del oscilador es de 8 MHz.  

---

## Clase 5A: Lectura de voltaje analogico

### Descripción
Se configura el pin A0 (`ANSEL = 0x01`) para realizar lecturas analógicas con una resolucizn de 10 bits, es decir, una lectura de valores de 0 a 1023 (ADC). El programa lee el valor analógico y realiza la conversión matemática para obtener el voltaje real, empleando en este caso como maximo el valor de 5V, empleando una regla de 3 para obtener el voltaje proporcional. 

Para evitar el uso intensivo de variables de punto flotante (`float`), el código multiplica el resultado por 50,000 y separa la parte entera de la decimal mediante divisiones y residuos, convirtiéndolo a texto (`sprintf`) para mostrarlo en la pantalla LCD conectada al Puerto C.

### Codigo Fuente
El código de esta práctica se encuentra aqui: [Clase_7.c](Codigo/Clase_7.c)

### Simulacion y Circuito Fisico

* [Simulacion de Clase](Simulacion/Simulacion_Clase_7.png) 
* [Circuito Practica 7](Circuito/Circuito_Practica_7.png) 
* [Video Practica 7](Circuito/Video_Practica_7.mp4) 

*El circuito y el video son los mismos para la practica y la actividad de clase, ya que en la actividad de clase se integra el codigo desarrollado con el profesor*

---

## Clase 5B: Lectura de voltaje analogico

### Descripción
Se configura el pin A0 (`ANSEL = 0x01`) para realizar lecturas analógicas con una resolucizn de 10 bits, es decir, una lectura de valores de 0 a 1023 (ADC). El programa lee el valor analógico y realiza la conversión matemática para obtener el voltaje real, empleando en este caso como maximo el valor de 5V, empleando una regla de 3 para obtener el voltaje proporcional. 

Para evitar el uso intensivo de variables de punto flotante (`float`), el código multiplica el resultado por 50,000 y separa la parte entera de la decimal mediante divisiones y residuos, convirtiéndolo a texto (`sprintf`) para mostrarlo en la pantalla LCD conectada al Puerto C.

### Codigo Fuente
El código de esta práctica se encuentra aqui: [Clase_7.c](Codigo/Clase_7.c)

### Simulacion y Circuito Fisico

* [Simulacion de Clase](Simulacion/Simulacion_Clase_7.png) 
* [Circuito Practica 7](Circuito/Circuito_Practica_7.png) 
* [Video Practica 7](Circuito/Video_Practica_7.mp4) 

*El circuito y el video son los mismos para la practica y la actividad de clase, ya que en la actividad de clase se integra el codigo desarrollado con el profesor*

---

## Actividad 5: Multímetro con Menú Interactivo (Botón)

### Descripción
Esta actividad toma como base la practica de clase, pero añade una interrupcion, permitiendo que se establezca una interaccion con el circuito mediante un pulsador conectado al pin RB0. Se establece una *Interrupción Externa* en el flanco de bajada (`INTEDG = 0`). 

Cada vez que se presiona el pulsador, la interrupcion cambia el valor de una variable de estado (`disp_mod`), lo que permite alternar la informacion mostrada en la pantalla LCD en tres modos diferentes:
1. **Voltaje:** Muestra la lectura escalada de 0 a 5 Volts.
2. **Porcentaje:** Muestra la lectura analogica como un porcentaje (0% a 100%).
3. **ADC:** Muestra el valor crudo de los ADC (0 a 1023).

### Codigo Fuente
El código de esta actividad se encuentra aqui: [Actividad_7.c](Codigo/Actividad_7.c)

### Simulacion y Circuito Fisico

* [Simulacion de Actividad 7](Simulacion/Simulacion_Actividad_7.png) 
* [Circuito Practica 7](Circuito/Circuito_Practica_7.png) 
* [Video Practica 7](Circuito/Video_Practica_7.mp4) 

*El circuito y el video son los mismos para la practica y la actividad de clase, ya que en la actividad de la sesion se integra el codigo desarrollado con el profesor*

