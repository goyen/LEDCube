/*
 * init.c
 *
 * Created: 2020-12-25
 *  Author: User
 */ 
#include "LEDCUBE.h"

int layerA[7]		=	{layer1,layer2,layer3,layer4,layer5,layer6,layer7};
void delay_time(uint16_t temp_t1){
	while(temp_t1>0){
		_delay_ms(1);
		temp_t1-=1;
	}
}

void init(void){
	DDRC= 0x38; //pc0,pc1,pc2 digital out
	DDRD= 0xff; // 1111 1111
	DDRB= 0x3f; // 0011 1111
	
	PORTC= 0X04;//PC1,PC2 PULL UP INPUT
	PCICR |= (1<<PCIE1);
	PCMSK1 |= (/*(1<<PCINT9)|*/(1<<PCINT10));
	sei();
	
	rowTotalControl(0x00);	//init
	PORTB= 0x3f;
	PORTD = (PORTD&0X7f)|0x80;
}

//row 574   column tr
void pointControl(uint8_t layer, uint8_t row,uint8_t column,uint16_t temp_t1){
	PORTB = (PORTB&0Xc0)|(column&0x3f);		// select tr 1bit~6bit
	PORTD = (PORTD&0X7f)|((column&0x40)<<1);		// select tr 7it
	
	PORTC =(PORTC&0Xc7)|((layer&0x07)<<3);		// select layer
	//_delay_ms(2);
	PORTD =(PORTD&0X80)|(row&0x7f);
	//_delay_ms(2);
	PORTC |= 0x38;
	delay_time(temp_t1);
}

void rowTotalControl(uint8_t data){					//control one row
	PORTD =(PORTD&0X80)|(data&0x7f);
	for(uint8_t i=0;i<7;i++){
		PORTC =(PORTC&0Xc7)|((layerA[i]&0x07)<<3);
	}
}

void layerTotalControl(uint8_t *data){				//control each row by data[]
	for(int8_t i=0;i<8;i++){
		PORTC =(PORTC&0Xc7)|((layerA[i]&0x07)<<3);
		PORTD =(PORTD&0X80)|(data[i]&0x7f);
	}
}

void columnTotalControl(uint8_t data){				//control column
	PORTB = (PORTB&0Xc0)|(data&0x3f);
	PORTD = (PORTD&0X7f)|((data&0x40)<<1);
}

void layerInit(uint8_t *layerData){
	for(int8_t i=0;i<7;i++){
		layerData[i]=0x00;
	}
}
