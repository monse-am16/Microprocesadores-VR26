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

El código de esta práctica se encuentra aquí: [Clase.c](Clase.c)

### Evidencia de Simulacion y Circuito Fisico
![Simulacion Practica de Clase](simulacion_clase.png) 
![Circuito Practica de Clase](circuito_clase.jpg)

---

## Actividad 1: Contador Binario de 6 Bits

### 📝 Descripción
Esta actividad consiste en un contador binario ascendente. Mediante un ciclo `for` que va del 0 al 63, el valor decimal se asigna directamente al registro `PORTD`. Esto provoca que los primeros 6 LEDs del puerto representen visualmente el conteo en formato binario, con un retardo de 500 ms entre cada incremento.

### 💻 Código Fuente
El código de esta actividad se encuentra aquí: [contador.c](contador.c) *(Asegúrate de poner el nombre exacto de tu archivo)*.

### ⚙️ Evidencia de Simulación y Circuito Físico
![Simulación Contador](simulacion_contador.png) 
![Circuito Contador](circuito_contador.jpg)

---

## 🔴 Actividad 2: Caminata de 8 LEDs

### 📝 Descripción
Esta actividad crea un efecto visual de "ida y vuelta" con un solo LED encendido a la vez recorriendo todo el Puerto D. Para lograrlo, se utilizan operaciones de desplazamiento de bits a la izquierda (`1<<i`). El primer ciclo `for` realiza la secuencia de ida (del pin 0 al 7), y el segundo ciclo realiza el regreso (del pin 6 al 0), repitiéndose de forma continua.

### 💻 Código Fuente
El código de esta actividad se encuentra aquí: [caminata.c](caminata.c) *(Asegúrate de poner el nombre exacto de tu archivo)*.

### ⚙️ Evidencia de Simulación y Circuito Físico
![Simulación Caminata](simulacion_caminata.png) 
![Circuito Caminata](circuito_caminata.jpg)
