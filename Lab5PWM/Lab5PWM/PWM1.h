#ifndef PWM1_H_
#define PWM1_H_
#include <stdint.h>
#include <avr/io.h>

void init_PWM1A(int INVERSOR,int MODO, int Prescaler,uint16_t Frecuencia);
//void init_PWM1B(int INVERSOR);
void duty_cycle1A(uint16_t duty);
//void duty_cycle1B(uint16_t duty);


void init_PWM1A(int INVERSOR,int MODO, int Prescaler,uint16_t Frecuencia ){
	//Definimos el puerto de salida
	DDRB |= (1<<PINB1);
	TCCR1A=0;
	TCCR1B=0;
	
	//Definimos la orientaci?n
	if (INVERSOR==0){
		//No invertido
		TCCR1A |= (1<<COM1A1);
		}else{
		//invertido
		TCCR1A |= (1<<COM1A1) | (1<<COM1A0);
	}
	
	//Definimos MODO de operaci?n FAST O PhaseCorrect
	if (MODO==0){
		//FAST con 8 bits
		TCCR1A |= (1<<WGM10);
		TCCR1B |= (1<<WGM12);
		}else if(MODO==1){
		//Fast con 9 bits
		TCCR1A |= (1<<WGM11);
		TCCR1B |= (1<<WGM12);
		}else if(MODO==2){
		//FAST con 10 bits
		TCCR1A |= (1<<WGM11)|(1<<WGM10);
		TCCR1B |= (1<<WGM12);
		}else if(MODO==3){
		//PhaseCorrect con 8 bits
		TCCR1A |= (1<<WGM10);
		}else if(MODO==4){
		//PhaseCorrect con 9 bits
		TCCR1A |= (1<<WGM11);
		}else if(MODO==5){
		//PhaseCorrect con 10 bits
		TCCR1A |= (1<<WGM11)|(1<<WGM10);
		}else if (MODO==6){
		//FAST con ICR1 TOP
		TCCR1A |= (1<<WGM11);
		TCCR1B |= (1<<WGM12)|(1<<WGM13);
		}else if (MODO==7){
		//PhaseCorrect con ICR1 TOP
		TCCR1A |= (1<<WGM11);
		TCCR1B |= (1<<WGM13);
	}
	
	//Definimos el Prescaler
	switch(Prescaler){
		case 0:
		TCCR1B |= (1<<CS10);
		break;
		case 8:
		TCCR1B |= (1<<CS11);
		break;
		case 64:
		TCCR1B |= (1<<CS11)|(1<<CS10);
		break;
		case 256:
		TCCR1B |= (1<<CS12);
		break;
		case 1024:
		TCCR1B |= (1<<CS12)|(1<<CS10);
		break;
	}
	//Definimos la frecuencia (unicamente funciona en MODO donde el top es ICR1)
	ICR1 = Frecuencia;
}


void duty_cycle1A(uint16_t duty){
	OCR1AH = duty;
}


#endif /* PWM1_H_ */