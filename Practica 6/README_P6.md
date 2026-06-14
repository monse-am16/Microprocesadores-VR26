# Práctica: Interfaz de Pantalla LCD, Creación de Caracteres Personalizados (CGRAM) y Control de Menús

El objetivo principal de esta sesión es dominar la interfaz de comunicación en modo de 4 bits entre el microcontrolador y una pantalla LCD alfanumérica de 16x2 empleando la librería `lcd.h`. Se analiza el funcionamiento de la memoria interna del módulo LCD para la creación de caracteres especiales diseñados por el usuario, combinándolo con la lectura de entradas digitales para conmutar estados de visualización de manera limpia y eficiente.

---

## Clase: Escritura Secuencial de Caracteres en LCD

### Descripción
En esta actividad de clase se realiza la inicialización básica de la pantalla LCD mapeando sus pines de control y datos al Puerto C (`&PORTC, 2, 3, 4, 5, 6, 7`). El programa ilustra cómo interactuar con el display imprimiendo un mensaje estático `" HELLO WORLD! "` en la primera línea (`fila 0, columna 0`). 

Posteriormente, implementa un ciclo interactivo utilizando un bucle `for` que recorre secuencialmente caracteres en formato ASCII partiendo desde la letra `'A'` hasta la `'Q'` (exclusivo, deteniéndose en la `'P'`). Cada carácter es enviado a la segunda línea del display de manera individual con un retardo de 300 ms, generando un efecto de escritura automática en tiempo real. Al completarse la línea, el sistema hace una pausa de 1 segundo, limpia la pantalla mediante `LCD_Clear()` y reinicia el proceso de forma cíclica.

### Código Fuente
El código de esta práctica se encuentra aquí: [Clase.c](Codigo/Clase.c)

### Simulación y Circuito Físico
* [Simulación Clase](Simulacion/MP.%20Clase%206.png)
* [Circuito Físico Clase](Circuito/Circuito_Clase_6.jpg)
* [Video de Funcionamiento Clase](Circuito/Video_Clase_6.mp4)

---

## Actividad: Menú Interactivo con Botón y Caracteres Personalizados (CGRAM)

### Descripción
Esta actividad expande los conceptos de la clase al añadir interactividad por hardware mediante botones y explotar la memoria gráfica del LCD (**CGRAM**). El microcontrolador utiliza arreglos de bits en formato binario de 8x5 para diseñar dos formas personalizadas inexistentes en la tabla ASCII estándar: un **Corazón** (posición de memoria 0) y una **Carita Feliz** (posición de memoria 1). A través de la función `LCD_Custom_Char`, estos mapas de bits se cargan directamente en los primeros bloques de memoria del controlador interno de la pantalla.

El circuito incorpora control interactivo configurando el pin `RB0` como entrada digital e inicializando las resistencias de pull-up internas globales del Puerto B (`OPTION_REGbits.nRBPU = 0`). Un pulsador conectado a tierra conmuta una variable lógica de estado cada vez que se presiona, implementando un retardo por software de 30ms para mitigar los rebotes mecánicos ("debounce").

Se diseñan dos pantallas o modos de visualización controlados por la variable `estado`:
* **Modo 1 (estado = false):** Muestra el mensaje en inglés `" HELLO WORLD! "` en la fila superior y la leyenda `" MODO 1 "` enmarcada entre dos caracteres de **Corazón** en la fila inferior.
* **Modo 2 (estado = true):** Muestra el mensaje en español `" HOLA MUNDO! "` en la fila superior y la leyenda `" MODO 2 "` enmarcada entre dos caracteres de **Carita Feliz** en la fila inferior.

**Optimización de Pantalla:** Se incorpora una bandera lógica llamada `actualizar_pantalla`. El comando de borrado (`LCD_Clear()`) y reescritura de texto se ejecutan de manera exclusiva en el instante exacto en que ocurre una pulsación legítima del botón. Al evitar ciclos constantes de borrado y escritura dentro del bucle infinito principal, se elimina por completo el efecto de parpadeo ("flickering"), asegurando una visualización nítida y profesional en el display.

### Código Fuente
El código de esta actividad se encuentra aquí: [Actividad.c](Codigo/Actividad.c)

### Simulación y Circuito Físico
* [Simulación Actividad](Simulacion/MP.%20Practica%206.png)
* [Circuito Físico Actividad](Circuito/Circuito_Actividad_6.jpg)
* [Video de Funcionamiento Actividad](Circuito/Video_Actividad_6.mp4)
