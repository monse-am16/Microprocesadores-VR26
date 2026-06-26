# Proyecto Final: Record & Play de Posiciones de Servomotor

El objetivo principal de este proyecto final es diseñar e implementar un sistema interactivo capaz de controlar la posicion de un servomotor mediante un potenciometro, dotandolo de una memoria para grabar secuencias de movimiento y reproducirlas de forma automatica. Para este proyecto, el microcontrolador hace uso de su oscilador interno configurado a 8 MHz.

---

## Descripcion del Sistema y Modos de Operacion

El programa funciona mediante una maquina de estados que evalua entradas digitales (botones con rutinas antirrebote) para alternar entre diferentes modos de funcionamiento. La señal de control del servomotor (PWM) se genera por software utilizando las interrupciones del Timer1.

El sistema cuenta con 3 modos principales:

1. **Modo Normal:** Al iniciar, el usuario tiene control manual y directo sobre el angulo del servomotor girando el potenciometro (leido a traves del modulo ADC en el pin RB0). Los LEDs indicadores permanecen apagados.
2. **Modo Grabacion:** Se ingresa presionando el boton `BTN_GRABAR` (RB1). El indicador `LED_GRABANDO` (RC1) se enciende. En este modo, el usuario puede mover el servo a la posicion deseada y presionar el boton `BTN_GUARDAR` (RB2) para registrar ese angulo exacto en la memoria (hasta un limite de 20 posiciones).
3. **Modo Reproduccion:** Al presionar `BTN_REPRODUCIR` (RB3), el indicador `LED_REPRODUCIENDO` (RC2) se enciende. El microcontrolador ignora temporalmente el potenciometro y comienza a ejecutar de forma automatica y secuencial todas las posiciones guardadas en su arreglo de memoria.

Adicionalmente, se cuenta con un boton de emergencia/reinicio (`BTN_PARAR_BORRAR` en RB4). Si se presiona en cualquier momento, el sistema aborta la reproduccion, regresa al Modo Normal y borra por completo la secuencia almacenada en la memoria (`total_pasos = 0`).

### Codigo Fuente
El codigo principal de este proyecto se encuentra aqui: [Proyecto_Final.c](Codigo/main.c)

### Simulacion y Circuito Fisico
* [Simulacion del Proyecto Final](<Simulacion/MP. Proyecto Final.png>)
* [Circuito Proyecto Final](<Circuito/Circuito_Proyecto_Final.jpg>)
* [Video Proyecto Final](<Circuito/Video_Proyecto_Final.mp4>)
