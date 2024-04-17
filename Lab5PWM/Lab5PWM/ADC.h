#ifndef ADC_H_
#define ADC_H_
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void init_ADC(int Referencia,int IOD,int Prescaler);
uint8_t readADC(int canal);

void init_ADC(int Referencia,int IOD,int Prescaler){
	ADMUX=0;
	ADCSRA=0;
	//Definimos la Referencia que va a tener el ADC
	if (Referencia==0){
		//Voltaje de Referencia interna de 5V.
		ADMUX |= (1<<REFS0);
		} else if (Referencia==1){
		//Voltaje de Referencia interna de 1.1V.
		ADMUX |= (1<<REFS0)|(1<<REFS1);
	}
	
	//Escogemos la justificaci?n (IZQUIERDA O DERECHA)
	if (IOD==0){
		//Justificaci?n izquierda
		ADMUX |= (1<<ADLAR);
		} else if (IOD==1){
		//Justificaci?n derecha
		ADMUX &= ~(1<<ADLAR);
	}
	
	//Escogemos el Prescaler
	if (Prescaler==2){
		//Prescaler 2 -> frecuencia del adc = Foscilador/2
		ADCSRA |= (1<<ADPS0);
		} else if (Prescaler==4){
		//Prescaler 2 -> frecuencia del adc = Foscilador/2
		ADCSRA |=(1<<ADPS1);
		}else if (Prescaler==8){
		//Prescaler 2 -> frecuencia del adc = Foscilador/8
		ADCSRA |=(1<<ADPS1) | (1<<ADPS0);
		}else if (Prescaler==16){
		//Prescaler 2 -> frecuencia del adc = Foscilador/16
		ADCSRA |= (1<<ADPS2);
		}else if (Prescaler==32){
		//Prescaler 2 -> frecuencia del adc = Foscilador/32
		ADCSRA |= (1<<ADPS2)|(1<<ADPS0);
		}else if (Prescaler==64){
		//Prescaler 2 -> frecuencia del adc = Foscilador/64
		ADCSRA |= (1<<ADPS2) | (1<<ADPS1);
		} else if (Prescaler==128){
		//Prescaler 2 -> frecuencia del adc = Foscilador/128
		ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	}
	
	//Habilitando la interrupci?n del ADC
	ADCSRA |= (1<<ADIE);
	
	//Enciendo el ADC
	ADCSRA |= (1 << ADEN);

}

uint8_t readADC(int canal){
	//Borramos el MUX DEL ADC
	ADMUX &= ~(1<<MUX3)& ~(1<<MUX2) & ~(1<<MUX1) & ~(1<<MUX0);
	
	//Encendemos el puerto deseado
	if (canal==0){
		//Seleccionar puerto (ADC0 - A0)
		ADMUX &= ~(1<<MUX3)& ~(1<<MUX2) & ~(1<<MUX1) & ~(1<<MUX0);
		}else if (canal==1){
		// Seleccionar puerto (ADC1 - A1)
		ADMUX |= (1<<MUX0);
		}else if (canal==2){
		// Seleccionar puerto (ADC2 - A2)
		ADMUX |= (1<<MUX1);
		}else if (canal==3){
		// Seleccionar puerto (ADC3 - A3)
		ADMUX |= (1<<MUX1)|(1<<MUX0);
		}else if (canal==4){
		//Seleccionar puerto (ADC4 - A4)
		ADMUX |= (1<<MUX2);
		} else if (canal==5){
		//Seleccionar puerto (ADC5 - A5)
		ADMUX |= (1<<MUX2)|(1<<MUX0);
		} else if (canal==6){
		//Seleccionar puerto (ADC6 - A6)
		ADMUX |= (1<<MUX2)|(1<<MUX1);
	}
	
	//INICIAMOS LECTURA
	ADCSRA |= (1 << ADSC);
	
	while (ADCSRA & (1 << ADSC)) {
		// Esperar
	}
	uint8_t VADC_H = ADCH;
	return VADC_H;
}

#endif /* ADC_H_ */