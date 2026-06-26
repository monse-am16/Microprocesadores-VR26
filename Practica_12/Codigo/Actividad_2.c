#include <xc.h>         // Biblioteca principal del compilador XC8
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lcd.h"
#include "Keypad.h"

//=============================================================================
// CONFIGURACI N DE BITS DE CONFIGURACI N (FUSES)
//=============================================================================

// Selecci n de oscilador (usar XT si est s usando un cristal de 4 MHz)
#pragma config FOSC = HS        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (disabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection (disabled)
#pragma config WRT = OFF        // Flash Program Memory Write Enable (disabled)
#pragma config CP = OFF         // Flash Program Memory Code Protection (disabled)

//=============================================================================
// DEFINICIONES
//=============================================================================

#define _XTAL_FREQ 8000000      // Frecuencia del oscilador (para __delay_ms y __delay_us)

void main(void){
    OSCCON = 0x71;
    ANSEL = 0x00;
   
    InitKeypad();
    LCD lcd = {&PORTC, 2, 3, 4, 5, 6, 7};
   
    LCD_Init(lcd);
    LCD_Set_Cursor(0,0);
    LCD_putrs(" Calculadora "); // Mensaje inicial de la calculadora
    LCD_Set_Cursor(1, 0);       // Nos posicionamos en la segunda fila (Fila 1) para dar el resultado
   
    long num1 = 0; //Primer numero ingresado
    long num2 = 0; //Segundo numero ingresado
    long res_ent = 0; //Variable para almacenar resulado de la operacion
    long ent = 0; //Entero de la division
    long partdec = 0; //Modulo de la division
    long dec = 0; //Almacena la conversion a dos decimales del modulo de la division
    char operacion = 0; //Opcion de la operacion a realizar
    char estado = 1; // Estado 1: Escribir num1; Estado 2: Escribir num2; Estado 3: Escrib   ir numeros esa bloqueado
    char buffer[16]; //Almacenamiento temporal para mostrar el resultado en la LCD.
    char teclaPresionada;
   
    while(1){
        // Esta función se queda esperando (bloqueada) hasta que el usuario pulse una tecla
        teclaPresionada = switch_press_scan();
       
        // Caso 1: Si se presiona '*', se borra lo escrito y se reinicia la calculadora
        if (teclaPresionada == '*'){
            num1 = 0;
            num2 = 0;
            operacion = 0;
            estado = 1;
            LCD_Clear();
            LCD_Set_Cursor(0,0);
            LCD_putrs(" Calculadora ");
            LCD_Set_Cursor(1,0);
        }
        // Caso 2: Si se presiona el numero del '0' al '9' y reconstruirlo a su valor entero
        else if (teclaPresionada >= '0' && teclaPresionada <= '9' && estado != 3){
            LCD_putc(teclaPresionada);
            
            if (estado == 1){ // Almacenar el numero ingresado como el primer numero
                num1 = (num1 * 10) + (teclaPresionada - '0');
            } else if (estado == 2){ // Almacenar el numero igresado en el segundo numero
                num2 = (num2 * 10) + (teclaPresionada - '0');
            }
        }
        // Caso 3: Si se presiona una de las teclas para una operacion (A,B,C,D) solo si estamos en estado 1
        else if ((teclaPresionada == 'A' || teclaPresionada == 'B' || teclaPresionada == 'C' || teclaPresionada == 'D') && estado == 1){
            operacion = teclaPresionada;
            estado = 2; // Para capturar el segundo numero
            
            switch (operacion){
                case 'A': LCD_putc('/'); break; 
                case 'B': LCD_putc('*'); break;
                case 'C': LCD_putc('-'); break;
                case 'D': LCD_putc('+'); break; 
            }
        }
        // Caso 4: Si se presiona '#', se toma como '='. Solo valido en estado = 2
        else if (teclaPresionada == '#' && estado == 2){
            LCD_putc('=');
                    
            switch(operacion){
                
                // Ejecucion de la operacion seleccionada
                case 'D': // Suma
                    res_ent = num1 + num2;
                    sprintf(buffer,"%ld",res_ent);
                    LCD_puts(buffer);
                    break;
                case 'C': //Resta
                    res_ent = num1 - num2;
                    sprintf(buffer,"%ld",res_ent);
                    LCD_puts(buffer);
                    break;
                case 'B': //Multiplicacion
                    res_ent = num1 * num2;
                    sprintf(buffer,"%ld",res_ent);
                    LCD_puts(buffer);
                    break;
                case 'A': //Division
                    if (num2 == 0){
                        LCD_putrs("Error: Div 0"); //No permite division por 0
                    } else {
                        ent = num1 / num2;
                        partdec = num1 % num2;
                        dec = (partdec*100)/num2; //Para que de los dos decimales
                        if (dec < 0) dec = -dec; // Si la parte decimal da negativo, se convierte a positivo
                        sprintf(buffer,"%ld.%02ld",ent,dec);
                        LCD_puts(buffer);
                    }
                    break;
            }
            estado = 3; //Bloquea el input de numeros despues de mostrar el resultado hasta presionar en C (clear)
        }
    }
}
