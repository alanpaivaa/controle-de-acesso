#include <p18f4550.h>
#include <delays.h>
#include <string.h>

// Configuração do microcontrolador para execução de instruções
#pragma config FOSC = HS    /// EXTERN CLOCK 8MHZ
#pragma config WDT = OFF   /// DISABLE WATCHDOG TIMER
#pragma config WDTPS = 32768 /// WATCHDOG TIMER 32768s
#pragma config PBADEN = OFF   /// PORTB.RB0,1,2,3,4 AS I/O DIGITAL
#pragma config MCLRE = OFF

// Variaveis do LCD
#define LCD_RS LATEbits.LATE0
#define LCD_RW LATEbits.LATE2
#define LCD_E LATEbits.LATE1
#define LCD_DATA LATD

// Variaveis do teclado
#define Linha_1 LATBbits.LATB4
#define Linha_2 LATBbits.LATB5
#define Linha_3 LATBbits.LATB6
#define Linha_4 LATBbits.LATB7
#define Coluna_1 PORTBbits.RB3
#define Coluna_2 PORTBbits.RB2
#define Coluna_3 PORTBbits.RB1
#define Coluna_4 PORTBbits.RB0

// Variaveis de terminal
#define TERMINAL LATCbits.LATC0

// Include da galera
#include "lcd.h"
#include "menu.h"
#include "teclado.h"
#include "core.h"
#include "terminal.h"

void configuraSistema();
void lcdEnviaInstrucao(char instrucao);
void lcdEnviaDado(char dado);
void delay_us(int quantidade);

/** Seta os tris da galera */
void configuraSistema() {
	ADCON1=0x0F;
	TRISD = 0b00000000;  
	TRISE = 0b11111000;
	TRISB = 0b00001111;
	TRISC = 0b00000000;
}

void main() {

	char tecla;
	char estado = 1;
	char kakaroto[9] = "Kakaroto";

	/** Estados
	     1 - Menu inicial
	     2 - Digitando uma senha
	     3 - Acesso permitido / negado
	*/

	configuraSistema();
	lcdInicializa();
	menuInicial();

	while(1) {
		terminalEscreveLinha(kakaroto, 8);
		tecla = varreTeclado();
		estado = processaTecla(tecla, estado);
	}
}