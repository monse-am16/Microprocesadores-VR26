# Practica 13: Control de Motor DC con Modulacion por Ancho de Pulso (PWM) y Puente H

El objetivo principal de esta sesion es el control de motores de corriente continua (DC). En la primera parte se busca controlar la velocidad de giro mediante un circuito driver de motor DC basado en un transistor BJT. En la segunda parte, el objetivo es controlar tanto la velocidad como el sentido de giro del motor implementando un Puente H. Al igual que en practicas anteriores, la frecuencia del oscilador esta configurada a 8 MHz.

---

## Actividad 1: Control de Velocidad con Driver BJT

### Descripcion
En esta primera actividad, se utiliza el modulo ADC en el pin A0 para leer el valor de voltaje (de un potenciometro). Este valor original de 10 bits es ajustado mediante un desplazamiento a la derecha (2 bits) para convertirlo en un valor de 8 bits que encaje en el registro `CCPR1L`. Este registro controla el ciclo de trabajo del modulo PWM configurado en el pin RC2. 
Esta señal PWM ataca a un transistor BJT configurado como driver, regulando asi la cantidad de energia que llega al motor DC y, en consecuencia, variando su velocidad de giro.

### Codigo Fuente
El codigo de esta actividad se encuentra aqui: [Actividad_1.c](Codigo/Actividad_1.c)

### Simulacion y Circuito Fisico

* [Simulacion de Actividad 1](<Simulacion/MP. Practica 13_1.png>) 
* [Circuito Practica 13A](Circuito/Circuito_Actividad_13A.jpg) 
* [Video Practica 13A](Circuito/Video_Actividad_13A.mp4) 

---

## Actividad 2: Control de Velocidad y Giro con Puente H

### Descripcion
Para esta actividad se integra un circuito Puente H (en este caso el L298N), lo que permite controlar no solo la velocidad, sino tambien el sentido de giro del motor. La velocidad sigue siendo controlada mediante la señal PWM generada en RC2 a partir de la lectura del ADC. 
Adicionalmente, se configuro el pin RB0 como entrada digital para leer el estado de un interruptor. Dependiendo de este estado, se envian señales logicas por los pines RD0 y RD1 hacia las entradas de control del Puente H (IN1 e IN2), logrando que el motor gire hacia la derecha o hacia la izquierda.

### Codigo Fuente
El codigo de esta actividad se encuentra aqui: [Actividad_2.c](Codigo/Actividad_2.c)

### Simulacion y Circuito Fisico

* [Simulacion de Actividad 2](<Simulacion/MP. Practica 13_2.png>) 
* [Circuito Practica 13B](Circuito/Circuito_Actividad_13B.jpg) 
* [Video Practica 13B](Circuito/Video_Actividad_13B.mp4)
