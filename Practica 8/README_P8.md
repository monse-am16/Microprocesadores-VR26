# Práctica 8: Lectura de Múltiples Canales ADC y Control de Menú Interactivo en LCD

El objetivo principal de esta sesión es la configuración y lectura de múltiples canales analógicos empleando el módulo ADC del microcontrolador (pines RA0 y RA1). Los datos obtenidos son procesados y visualizados de manera simultánea e interactiva en una pantalla LCD. Al igual que en prácticas anteriores, la frecuencia del oscilador (HS) está configurada a 8 MHz.

---

## Clase 8: Lectura Simultánea de Dos Canales Analógicos

### Descripción
Se configura el registro `ANSEL = 0x03` para habilitar las lecturas analógicas en dos pines distintos: AN0 (Pin A0) y AN1 (Pin A1). Mediante la función `ADC_Read(channel)`, el microcontrolador selecciona el canal mediante un corrimiento de bits y realiza la conversión digital. 

El programa procesa secuencialmente ambos canales, transformando el valor digital crudo (0 a 1023) en un valor de voltaje equivalente (0 a 5V) empleando aritmética de enteros, divisiones y residuos. Finalmente, los resultados de ambos canales se imprimen continuamente, ocupando las dos filas de la pantalla LCD.

### Código Fuente
El código de esta práctica se encuentra aquí: [Clase_8.c](Codigo/Clase_8.c)

### Simulación y Circuito Físico
[Simulación Clase 8](Simulacion/MP.Practica 8.png) 
[Circuito Práctica 8](Circuito/Circuito_Practica_8.png) 
[Video Práctica 8](Circuito/Video_Practica_8.mp4) 

*El circuito y el video son los mismos para la práctica y la actividad de clase, ya que en la actividad de clase se integra toda la lógica de los canales.*

---

## Actividad 8: Multímetro de Dos Canales con Menú Interactivo

### Descripción
Esta actividad amplía la lógica desarrollada en clase incorporando botones de control para crear una interfaz dinámica. Todo el Puerto B se configura como entrada (`TRISB = 0xFF`) con resistencias pull-up habilitadas (`WPUB = 0xFF`). Se emplean dos pulsadores conectados a los pines `RB0` y `RB1` para manipular variables de estado:

* **Botón 1 (RB0 - Modo de Display):** Cada vez que se presiona, alterna la información que se muestra en pantalla entre tres formatos distintos:
    1. **Voltaje:** Muestra la lectura analógica escalada de 0 a 5 Volts.
    2. **Porcentaje:** Muestra la lectura equivalente en un rango de 0% a 100%.
    3. **ADC:** Muestra el valor digital crudo procesado por el convertidor (0 a 1023).
* **Botón 2 (RB1 - Modo de Canal):** Permite cambiar el canal analógico que se está leyendo y visualizando en la pantalla, alternando entre el **Canal 1** (AN0) y el **Canal 2** (AN1).

El programa limpia la pantalla (`LCD_Clear()`) únicamente cuando detecta un cambio de estado en los botones, evitando así parpadeos innecesarios en la actualización continua de las lecturas.

### Código Fuente
El código de esta actividad se encuentra aquí: [Actividad_8.c](Codigo/Actividad_8.c)
