# Practica 12: Teclado Matricial y Calculadora Basica

El objetivo principal de esta practica es la integracion y manejo de un teclado matricial 4x4 junto con una pantalla LCD. Para lograr una estructura modular, se hizo uso de librerias personalizadas ([keypad.c](<Codigo/keypad.c>), [keypad.h](Codigo/keypad.h)) desarrolladas para el control de los perifericos. Al igual que en practicas anteriores, la frecuencia del oscilador es de 8 MHz.

---

## Actividad 1: Lectura de Teclado Matricial en LCD

### Descripcion
En esta actividad, el microcontrolador escanea continuamente las filas y columnas del teclado matricial 4x4. Al detectar que el usuario presiona un boton (haciendo uso de la funcion `switch_press_scan()` de la libreria), el sistema decodifica que tecla fue pulsada y la imprime de manera inmediata en la pantalla LCD.

### Codigo Fuente
El codigo de esta actividad se encuentra aqui: [Actividad_1.c](Codigo/Actividad_1.c)

### Simulacion y Circuito Fisico

* [Simulacion de Actividad 1](Simulacion/Simulacion_Practica_12.png) 
* [Circuito Actividad 1](Circuito/Circuito_Actividad_12.jpg) 
* [Video Actividad 1](Circuito/Video_Actividad_12A.mp4) 

*El circuito y la simulacion son los mismos para ambas actividades*

---

## Actividad 2: Calculadora Basica

### Descripcion
Haciendo uso de la lectura del teclado matricial y la visualizacion en la pantalla LCD, se programo una calculadora funcional capaz de realizar las cuatro operaciones aritmeticas basicas entre dos numeros. 
Las teclas alfabeticas del Keypad se mapearon para ejecutar las siguientes operaciones:
1. **D:** Suma
2. **C:** Resta
3. **B:** Multiplicacion
4. **A:** Division (Muestra hasta 2 numeros decimales y cuenta con proteccion para evitar el error de division entre cero).

El programa funciona mediante una maquina de estados que permite al usuario ingresar el primer numero, seleccionar la operacion deseada, teclear el segundo numero y presionar el boton correspondiente para desplegar el resultado en la LCD.

### Codigo Fuente
El codigo de esta actividad se encuentra aqui: [Actividad_2.c](Codigo/Actividad_2.c)

### Simulacion y Circuito Fisico

* [Simulacion de Actividad 2](Simulacion/Simulacion_Practica_12.png) 
* [Circuito Practica 12](Circuito/Circuito_Actividad_12.jpg) 
* [Video Practica 12](Circuito/Video_Actividad_12B.mp4) 

---

## Librerias Utilizadas

### Descripcion
Para mantener el programa principal limpio y facilitar la reutilizacion de codigo, el control de los perifericos se dividio en las siguientes librerias de C, las cuales tambien se incluyen en la carpeta del codigo:

* **Control de Pantalla LCD:** [lcd.c](Codigo/lcd.c) y [lcd.h](Codigo/lcd.h)
* **Control del Teclado Matricial:** [Keypad.c](Codigo/Keypad.c) y [Keypad.h](Codigo/Keypad.h)
