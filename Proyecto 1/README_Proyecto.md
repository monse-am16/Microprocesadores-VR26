# Proyecto 1: Mini-Juego Interactivo con Joystick y Pantalla LCD

El objetivo de este proyecto es integrar los conocimientos adquiridos durante el curso (ADC, LCD, botones, pull-ups, retardos y lógica de control) para desarrollar un mini-juego interactivo visualizado en una pantalla LCD de 16x2. El usuario controla un avatar en dos dimensiones utilizando un joystick analógico bidireccional, esquivando obstáculos para evitar perder la partida. Al igual que a lo largo del curso, la frecuencia del oscilador (HS) está configurada a 8 MHz.

---

## Descripción del Proyecto

El sistema utiliza un **Joystick Analógico** como interfaz principal de control del usuario. El microcontrolador lee secuencialmente dos canales analógicos (AN0 para el eje X y AN1 para el eje Y) empleando el módulo **ADC**. Al evaluar la lectura analógica y compararla contra umbrales definidos (menor a 300 o mayor a 600), el programa determina la dirección del movimiento y actualiza las coordenadas matriciales `(x, y)` del personaje principal.

### Características Principales:

1. **Movimiento Libre y Envolvencia (Wrap-around):** El personaje puede desplazarse libremente a través de las 2 filas y 16 columnas. Se implementó una lógica de límites (*bounds checking*) de forma que, si el jugador sale de la pantalla por el extremo derecho o izquierdo, reaparece por el lado opuesto. Al ocurrir este cambio de "pantalla", la posición del obstáculo también se desplaza de manera dinámica para simular un avance progresivo en el nivel.
2. **Generación de Caracteres (CGRAM):** Se hace uso de la memoria interna de la LCD para escribir y desplegar caracteres diseñados a medida que no están incluidos en el estándar ASCII. Se crearon dos *sprites* jugables: un **Corazón** y una **Carita Feliz**.
3. **Control del Avatar (Botón de Joystick):** El pulsador físico integrado en el joystick se encuentra conectado al pin `RB0`, el cual aprovecha la resistencia *pull-up* interna del microcontrolador (`WPUB = 0xFF`). A través de una lectura con técnica *anti-rebotes (debounce)* por software, el usuario puede presionar el joystick como botón para cambiar en tiempo real entre los dos personajes disponibles.
4. **Detección de Colisiones y Estado "Game Over":** El entorno de juego incluye un obstáculo representado por un bloque sólido (carácter ASCII `255`). En cada iteración, el programa evalúa si las coordenadas actuales del jugador coinciden de manera exacta con las del obstáculo (`pos[0] == obs_x && pos[1] == obs_y`). De ser así, se activa la secuencia de pérdida: la pantalla se limpia, se imprime el texto `" GAME OVER "` durante dos segundos, y todas las variables se reinician a su estado inicial para comenzar una nueva partida.

### Código Fuente
El código de este proyecto final se encuentra aquí: [Proyecto.c](Codigo/Proyecto.c)

### Simulación y Circuito Físico
* [Simulación del Proyecto](Simulacion/MP.%20Proyecto%201.png) 
* [Circuito del Proyecto](Circuito/Circuito_Proyecto.jpg) 
* [Video del Proyecto](Circuito/Video_Proyecto.mp4)
