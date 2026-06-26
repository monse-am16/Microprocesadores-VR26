# Practica 14: Control de Servomotor con Modulacion por Ancho de Pulso (PWM)

El objetivo principal de esta sesion es el control de posicion de un servomotor. En la primera actividad se busca controlar el ciclo completo del servomotor (de 0 a 180 grados y de regreso) mediante señales PWM generadas por hardware. En la segunda actividad, el objetivo es controlar el angulo del servomotor empleando un potenciometro, haciendo uso del modulo ADC y de PWM generado por software. Al igual que en practicas anteriores, la frecuencia del oscilador esta configurada a 8 MHz.

---

## Actividad 1: Ciclo Automatico del Servomotor (0 a 180 grados)

### Descripcion
En esta primera actividad, se utiliza el modulo CCP1 configurado en modo comparador para generar una señal PWM precisa por hardware. Utilizando el Timer1, el microcontrolador alterna el estado del pin RC2 entre ALTO y BAJO. Al enviar un pulso especifico (1000 ticks del timer), el servo se posiciona en 0 grados, y al enviar un pulso mayor (4800 ticks), el servo se mueve a 180 grados. El programa principal se encarga de alternar entre estas dos posiciones de forma continua cada segundo.

### Codigo Fuente
El codigo de esta actividad se encuentra aqui: [Actividad_1.c](Codigo/Actividad_1.c)

### Simulacion y Circuito Fisico

* [Simulacion de Actividad 1](Simulacion/Simulacion_Actividad_14A.png) 
* [Circuito Practica 14](Circuito/Circuito_Actividad_14A.jpg) 
* [Video Practica 14](Circuito/Video_Actividad_14A.mp4) 

---

## Actividad 2: Control de Angulo con Potenciometro

### Descripcion
Para esta actividad se integra el modulo ADC para leer el voltaje de un potenciometro conectado al pin RB0. El valor leido (de 0 a 1023) se mapea matematicamente para calcular el ancho de pulso requerido (entre el limite inferior y superior correspondientes a 0 y 180 grados). Dado el cambio de estructura, en esta ocasion se genera la señal PWM por software utilizando las interrupciones del Timer1 en el pin RC0. A medida que el usuario gira el potenciometro, el servo actualiza su posicion en tiempo real respondiendo al ancho del pulso modificado.

### Codigo Fuente
El codigo de esta actividad se encuentra aqui: [Actividad_2.c](Codigo/Actividad_2.c)

### Simulacion y Circuito Fisico

* [Simulacion de Actividad 2](Simulacion/Simmulacion_Practica_14_2.png) 
* [Circuito Practica 14](Circuito/Circuito_Actividad_14B.png) 
* [Video Practica 14](Circuito/Video_Actividad_14B.mp4) 
