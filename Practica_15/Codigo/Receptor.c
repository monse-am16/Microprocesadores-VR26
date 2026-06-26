#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//=============================================================================
// CONFIGURACIÓN DE FUSES
//=============================================================================
#pragma config FOSC = HS        // Oscilador de alta velocidad (Cristal de 8 MHz)
#pragma config WDTE = OFF       // Watchdog Timer desactivado
#pragma config PWRTE = OFF      // Power-up Timer desactivado
#pragma config BOREN = ON       // Brown-out Reset activado
#pragma config LVP = OFF        // Programación de bajo voltaje desactivada
#pragma config CPD = OFF        
#pragma config WRT = OFF        
#pragma config CP = OFF         

#define _XTAL_FREQ 8000000      


void UART_Init(void) {
    TRISCbits.TRISC6 = 1;       // Pin TX como entrada 
    TRISCbits.TRISC7 = 1;       // Pin RX como entrada
    
    SPBRG = 51;                 // 9600 baudios con cristal de 8MHz
    TXSTA = 0x24;               // Transmisión habilitada, alta velocidad (BRGH=1)
    RCSTA = 0x90;               // Puerto serial habilitado, recepción continua (CREN=1)
    
}


char UART_Read(void) {
    // Si hay un error de desbordamiento (Overrun Error)
    if(RCSTAbits.OERR) {        
        RCSTAbits.CREN = 0;     // Resetear la recepción para limpiar el error
        RCSTAbits.CREN = 1;
        return 0;               // Retorna vacío por seguridad
    }
    
    // Si hay un error de trama (Framing Error / Ruido)
    if(RCSTAbits.FERR) {
        char basura = RCREG;    // Leer el registro para vaciar el búfer descuidando el dato corrupto
        return 0;
    }
    
    // Si el flag RCIF está en 1, significa que hay un dato legítimo listo
    if(PIR1bits.RCIF == 1) {
        return RCREG;           // Al leer RCREG, el flag RCIF se limpia automáticamente
    }
    
    return 0;                   // Si no hay datos, retorna 0
}


void main(void) {
    TRISDbits.TRISD0 = 0;       // RD0 como salida (LED)
    PORTDbits.RD0 = 0;          // Iniciar con el LED apagado
    
    UART_Init();                // Inicializar UART
    
    while(1) {
        // Almacenar el resultado del sondeo
        char dato_recibido = UART_Read();
        
        // Evaluar el dato recibido
        if (dato_recibido == 'A') {
            PORTDbits.RD0 = 1;  // Enciende el LED
        } 
        else if (dato_recibido == 'B') {
            PORTDbits.RD0 = 0;  // Apaga el LED
        }
    }
}
