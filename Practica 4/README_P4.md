# Práctica 4: Configuración de Entradas Digitales y Contador Bidireccional de 0 a 99

El objetivo principal de esta sesión es comprender e implementar la configuración de pines como entradas digitales en el microcontrolador PIC, aprovechando las resistencias de *pull-up* internas del Puerto B. Asimismo, se desarrollan lógicas de control esenciales para la lectura de pulsadores, tales como la mitigación de rebotes mecánicos (*debounce*) y la detección de flancos para el control de un contador bidireccional de dos dígitos (0 a 99) visualizado en displays de 7 segmentos. Al igual que en las sesiones anteriores, se utiliza un oscilador de cristal configurado a 8 MHz (HS).

---

## Clase 4: Lectura de Botones y Control de Salidas Digitales

### Descripción
En esta actividad de clase se realiza la transición de funciones analógicas a digitales mediante la desactivación de los registros `ANSEL = 0` y `ANSELH = 0`. Para simplificar el hardware y evitar el uso de resistencias externas, se activan las resistencias de *pull-up* internas globales del Puerto B borrando el bit 7 del registro de opciones (`OPTION_REG = OPTION_REG & 0b01111111`).

El Puerto B se configura en su totalidad como entrada (`TRISB = 0xFF`) y el Puerto D como salida (`TRISD = 0x0`). El programa ejecuta un bucle infinito donde lee en tiempo real el estado de los pines `RB0`, `RB1` y `RB2`. Dado que la configuración *pull-up* mantiene un estado ALTO (`1`) por defecto y envía un BAJO (`0`) al presionarse el botón, se aplica el operador de negación lógica (`!`) para invertir el valor y transferirlo directamente a los pines de salida `RD0`, `RD1` y `RD2`, logrando que los LEDs correspondientes se enciendan únicamente al presionar su respectivo pulsador.

### Código Fuente
El código de esta práctica se encuentra aquí: [Clase_4.c](Codigo/Clase_4.c)

### Simulación y Circuito Físico
* [Simulación Clase 4](Simulacion/MP.%20Clase%204.png)
* [Circuito Práctica 4](Circuito/Circuito_Clase_4.jgg)
* [Video Práctica 4](Circuito/Video_Clase_4.mp4)

---

## Actividad 4: Contador de 0 a 99 de Pasos Variables con Displays de 7 Segmentos

### Descripción
Esta actividad expande la lógica de lectura digital mediante el desarrollo de un contador numérico de dos dígitos (0 a 99) de rango circular, cuyos valores se visualizan en dos displays de 7 segmentos de ánodo común. Para decodificar los valores numéricos a los pines físicos, se define un arreglo hexadecimal de 10 posiciones (`display[10]`) conteniendo las máscaras de bits correspondientes del 0 al 9.

La interfaz de control por hardware se compone de tres pulsadores conectados al Puerto B:
* **Botón de Incremento (RB0):** Suma al valor acumulado la magnitud configurada en la variable `paso`. Incorpora un ajuste matemático para el desbordamiento superior (`if (contador > 99) contador -= 100`) para reiniciar el ciclo en 0.
* **Botón de Decremento (RB1):** Resta al valor acumulado la magnitud del `paso`. Incluye un ajuste matemático para el desbordamiento inferior (`if (contador < 0) contador += 100`), permitiendo pasar directamente al valor superior (ej. de 0 a 99 o 98).
* **Botón de Modo (RB2):** Al ser presionado, conmuta el valor de la variable `paso` alternando entre incrementos/decrementos unitarios (`paso = 1`) o dobles (`paso = 2`).

**Lógica Anti-rebote y Control por Flancos:** Con el propósito de evitar un conteo continuo e incontrolable mientras el usuario mantiene presionado un botón, el software implementa un control estricto por flancos empleando variables de estado anterior (`estado_inc_anterior`, `estado_dec_anterior`, `estado_modo_anterior`). Combinando esto con retardos de estabilización de 20 ms (`__delay_ms(20)`), se garantiza que cada pulsación física incremente, decremente o cambie de modo exactamente una sola vez por evento de presión.

Finalmente, el valor decimal del contador se divide matemáticamente para aislar sus componentes mediante una división entera para extraer las decenas (`contador / 10`) y una operación de residuo para las unidades (`contador % 10`). Las decenas se envían al `PORTC` y las unidades al `PORTD` para encender los displays de forma independiente.

### Código Fuente
El código de esta actividad se encuentra aquí: [Actividad_4.c](Codigo/Actividad_4.c)

### Simulación y Circuito Físico
* [Simulación Actividad 4](Simulacion/MP.%20Practica%204.png)
* [Circuito Práctica 4](Circuito/Circuito_Actividad_4.jgg)
* [Video Práctica 4](Circuito/Video_Actividad_4.mp4)
