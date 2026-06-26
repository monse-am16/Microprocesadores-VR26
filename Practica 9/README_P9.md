# Práctica 9: Conteo de Tiempo con Timer0, Interrupciones y Lectura ADC en Pantalla LCD

El objetivo principal de esta sesión es la configuración y uso del temporizador Timer0 mediante interrupciones para llevar un registro de tiempo preciso, visualizado dinámicamente en una pantalla LCD. Además, se integra el procesamiento secuencial de señales analógicas empleando el módulo ADC del microcontrolador. Al igual que en prácticas anteriores, la frecuencia del oscilador (HS) está configurada a 8 MHz.

---

## Clase 9: Cronómetro Digital mediante Interrupciones (Timer0)

### Descripción
En esta práctica se configura el registro `OPTION_REG = 0x7` y se inicializa el registro `TMR0 = 178` para establecer el preescalador y habilitar el temporizador Timer0. El sistema utiliza interrupciones (habilitando `T0IE = 1` y `GIE = 1`) para monitorear el desbordamiento del temporizador. 

Cada vez que la bandera de interrupción `T0IF` se activa, se incrementa una variable `contador`. Al alcanzar los 100 ciclos, el programa incrementa la variable global `tiempo` en una unidad y reinicia el contador, restableciendo también el valor de `TMR0`. En el bucle principal, este tiempo en segundos se formatea a un estilo de reloj digital (`MM:SS`) separando minutos (`tiempo/60`) y segundos (`tiempo%60`) mediante la función `sprintf`, imprimiéndolo de forma continua en la segunda fila de la pantalla LCD.

### Código Fuente
El código de esta práctica se encuentra aquí: [Clase_9.c](Codigo/Clase_9.c)

### Simulación y Circuito Físico
* [Simulación Clase 9](Simulacion/MP.%20Practica%209.png) 
* [Circuito Práctica 9](Circuito/Circuito_Clase_9.jpg) 
* [Video Práctica 9](Circuito/Video_Clase_9.mp4) 

*El circuito y el video son los mismos para la práctica y la actividad de clase, ya que en la actividad se integran ambos funcionamientos.*

---

## Actividad 9: Multímetro con Cronómetro Integrado

### Descripción
Esta actividad amplía el sistema de tiempo base al integrar la lectura de canales analógicos, creando un dispositivo multifuncional. Se inicializa el módulo ADC configurando los pines A0 y A1 como analógicos (`ANSEL = 0x03`) con justificación a la derecha (`ADCON1 = 0x80`).

Dentro del bucle de ejecución continua, el programa llama a la función `ADC_Read(0)` para realizar la conversión digital del canal 0. El valor resultante se escala a un voltaje de 0 a 5 Volts mediante la operación matemática `(adc_result * 50000UL) / 1023`. Para optimizar los recursos del microcontrolador y evitar tipos de datos flotantes, la parte entera y decimal se extraen dividiendo entre 10,000 y calculando el residuo.

Finalmente, la información se organiza en la pantalla de la siguiente manera:
* **Fila 1:** Se muestra el letrero "Voltaje:" seguido del cálculo extraído en tiempo real con cuatro decimales.
* **Fila 2:** Se ubica el reloj digital (Timer0) en la esquina inferior derecha (columna 11) actualizando los minutos y segundos simultáneamente sin interrumpir la lectura del ADC.

### Código Fuente
El código de esta actividad se encuentra aquí: [Actividad_9.c](Codigo/Actividad_9.c)
