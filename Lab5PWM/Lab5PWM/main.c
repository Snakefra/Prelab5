/*****************************************************************************
 * Universidad del Valle de Guatemala
 * IE2023: Programación de microcontroladores
 * Autor: Oscar Melchor
 * Proyecto: PWM y Librerias
 * Archivo: main.c
 * Hardware : ATMEGA328P
 * Created: 17/04/2024 08:41:07
 *****************************************************************************/ 
#define F_CPU 16000000
//#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//#include "PWM0/PMW0.h"
#include "PWM1.h"
#include "ADC.h"
volatile uint8_t VADC=0;
volatile uint8_t PuertoADC=4;
volatile uint16_t limite=0;

void init_pines(void){
	// Configurar los pines PC4, PC5 y A6 como entradas y habilitar resistencias de pull-up
	DDRC &= ~(1 << DDC4) & ~(1 << DDC5) & ~(1 << DDC6);
	PORTC |= (1 << PORTC4) | (1 << PORTC5)| (1 << PORTC6);

}

uint16_t reescalar(uint8_t Valor, uint8_t max_origen, uint16_t max_limite) {
	// Convertir el Valor al rango 0 - max_origen
	float Valor_normalizado = (float)Valor / max_origen;

	// Escalar el Valor al rango 0 - max_limite
	uint16_t Valor_reescalado = Valor_normalizado * max_limite;

	return Valor_reescalado;
}

int main() {
	init_pines();
	//frecuencia del adc -> 16M/128 = 125kHz
	init_ADC(0,0,128);
	
	limite=100;
	int Prescaler=1024;
	
	init_PWM1A(0,6,Prescaler, 50);
	uint8_t Valor = 0;


	while (1) {
		Valor = readADC(4);
		uint16_t Valor_reescalado = reescalar(Valor, 255, limite);
		duty_cycle1A(Valor_reescalado);
	}

	return 0;
}