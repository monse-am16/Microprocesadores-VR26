# Práctica 10: Conteo de Tiempo con Timer1, Interrupciones y Lectura ADC en Pantalla LCD

El objetivo principal de esta sesión es la configuración y uso del temporizador **Timer1** (de 16 bits) mediante interrupciones para llevar un registro de tiempo preciso, visualizado dinámicamente en una pantalla LCD. Además, se integra el procesamiento continuo de señales analógicas empleando el módulo ADC del microcontrolador. Al igual que en prácticas anteriores, la frecuencia del oscilador (HS) está configurada a 8 MHz.

---

## Clase 10: Cronómetro Digital mediante Interrupciones (Timer1)

### Descripción
En esta práctica se configura el temporizador Timer1, el cual es de 16 bits. A través del registro `T1CON = 0b00110001`, se establece un preescalador de 1:8, se selecciona el reloj interno (Fosc/4) y se enciende el módulo. Los registros `TMR1H` y `TMR1L` se inicializan con el valor hexadecimal `0xF63C` (63036 en decimal) para generar un desbordamiento exacto cada 10 ms (considerando los cálculos basados en el reloj de 8 MHz). 

El sistema utiliza las interrupciones de periféricos (`PEIE = 1`) y globales (`GIE = 1`) para monitorear la bandera de interrupción `TMR1IF`. Cada vez que ocurre la interrupción, se incrementa una variable `contador`. Al alcanzar los 100 ciclos (100 * 10 ms = 1 segundo), se incrementa la variable global `tiempo` en una unidad, se reinicia el contador y se recargan los valores de `TMR1H` y `TMR1L`. En el bucle principal, este tiempo se formatea a un estilo de reloj digital (`MM:SS`) y se imprime continuamente en la segunda fila de la pantalla LCD.

### Código Fuente
El código de esta práctica se encuentra aquí: [Clase_10.c](Codigo/Clase_10.c)

### Simulación y Circuito Físico
* [Simulación Clase 10](Simulacion/MP.%20Practica%2010.png) 
* [Circuito Práctica 10](Circuito/Circuito_Clase_10.jpg) 
* [Video Práctica 10](Circuito/Video_Clase_10.mp4) 

---

## Actividad 10: Multímetro con Cronómetro Integrado (Timer1)

### Descripción
Esta actividad fusiona el cronómetro exacto basado en Timer1 con la lectura analógica (ADC), creando un sistema multitarea. Se inicializa el módulo ADC configurando el puerto analógico (`ANSEL = 0x03`) con justificación a la derecha.

En el ciclo infinito (`while(1)`), el microcontrolador lee constantemente el canal analógico 0 (`ADC_Read(0)`). El valor obtenido se escala para representar el voltaje real (de 0 a 5 Volts) aplicando la operación matemática `(adc_result * 50000UL) / 1023`. Para mantener la eficiencia y evitar el uso de datos flotantes, se extraen las partes entera y decimal dividiendo entre 10,000.

La interfaz de la pantalla LCD se organiza de la siguiente manera:
* **Fila 1:** Muestra el texto "Voltaje:" junto con la lectura en tiempo real procesada con cuatro cifras decimales.
* **Fila 2:** Muestra el cronómetro dinámico en la esquina inferior derecha (`MM:SS`), el cual se actualiza en segundo plano gracias a las interrupciones del Timer1, garantizando que el tiempo transcurra de manera precisa sin verse retrasado por la ejecución y procesamiento del convertidor ADC.

### Código Fuente
El código de esta actividad se encuentra aquí: [Actividad_10.c](Codigo/Actividad_10.c)

* [Simulación Clase 10](Simulacion/MP.%20Practica%2010.png) 
* [Circuito Práctica 10](Circuito/Circuito_Actividad_10.jpg) 
* [Video Práctica 10](Circuito/Video_Actividad_10.mp4) 
