# Práctica 11: Generación de Señales PWM por Hardware y Software con Control ADC

El objetivo principal de esta sesión es la implementación y comparación de dos métodos distintos para generar señales de Modulación por Ancho de Pulso (PWM): uno manejado por el hardware dedicado del microcontrolador (módulo CCP) y otro recreado lógicamente por software mediante interrupciones. El ciclo de trabajo (*duty cycle*) de ambas señales se controla dinámicamente en tiempo real mediante conversiones analógico-digitales (ADC). La frecuencia del oscilador (HS) está configurada a 8 MHz.

---

## Actividad 11: Control Dual de PWM (Hardware y Software)

### Descripción
Esta actividad integra la lectura de dos señales analógicas independientes (ej. potenciómetros) para manipular el ancho de pulso de dos salidas distintas. Se lee el valor de los canales analógicos 0 y 1 utilizando la función `ADC_Read()`. Como el convertidor ADC es de 10 bits (resolución de 0 a 1023) y los generadores de PWM operan sobre una base de 8 bits (0 a 255), se realiza una optimización matemática aplicando un corrimiento a la derecha de 2 bits (`>> 2`), lo cual equivale a dividir el valor entre 4, escalando los datos de forma limpia y directa sin requerir operaciones aritméticas pesadas.

El sistema se divide en dos métodos de generación PWM ejecutándose en paralelo:
1. **PWM por Hardware (Módulo CCP1):** Se emplea el pin `RC2`. Se inicializa el Timer2 (`T2CON = 0b00000100`) y se configura el registro `PR2 = 255` para establecer el periodo de la señal. El módulo de Captura, Comparación y PWM (CCP1) se ajusta en modo PWM (`CCP1CON = 0b00001100`). El ciclo de trabajo se actualiza de manera automática inyectando la lectura procesada del ADC 1 en el registro `CCPR1L`. Esta técnica es sumamente eficiente ya que el hardware se encarga de la modulación, liberando tiempo de procesamiento.
2. **PWM por Software (Interrupciones Timer0):** Se emplea el pin `RD0`. Se aprovecha el desbordamiento constante del Timer0 (sin pre-escalador y precargado con 128 para aumentar la frecuencia base) para disparar interrupciones globales. En la Rutina de Servicio de Interrupción (`ISR`), un contador (`soft_pwm_counter`) se incrementa continuamente. Se utiliza un comparador lógico (`if (soft_pwm_counter < duty_cycle_2)`) para encender o apagar el puerto de salida, recreando con alta precisión una señal PWM por código, controlada dinámicamente por la lectura del ADC 2 global.

### Código Fuente
El código de esta actividad se encuentra aquí: [Actividad_11.c](Codigo/Actividad_11.c)

### Simulación y Circuito Físico
* [Simulación Actividad 11](Simulacion/MP.%20Practica%2011.png) 
* [Circuito Práctica 11](Circuito/Circuito_Practica_11.jpg) 
* [Video Práctica 11](Circuito/Video_Practica_11.mp4)
