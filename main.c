/*
 * 74hc574.c
 *
 * Created: 2020-12-25
 * Author : User
 */ 
#include "LEDCUBE.h"
uint8_t state1			=	0;

ISR(PCINT1_vect){
	if((PINC&0x04) & 0X04){
		if(state1<7)	state1 += 1;
		else if(state1==7)		state1 =0;
	}
	delay_time(10);
}


int main(void)
{

	init();
	uint8_t column_line[7]	=	{line7,line1,line2,line3,line4,line5,line6};
	uint8_t row_line[7]		=	{line1,line2,line3,line4,line5,line6,line7};
	uint8_t layer[7]		=	{layer1,layer2,layer3,layer4,layer5,layer6,layer7};
	uint8_t layerData[7]	=	{0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	uint8_t randLayerData[7][7];
	uint8_t temp =0;
	while (1)
	{

		if(state1==0){
			if(temp==0){
				countNumber(column_line,1,100);
				temp++;
			}
			moveLine(column_line,layerData,5,5,50);
			block(layerData,column_line,50,3);
			block1(layerData,column_line,50,3);
			boxInOut(row_line,column_line,layerData,60,5);
			fireWorke(layer,row_line,column_line,layerData,100,5);
			rain1(7,randLayerData,column_line);
		}else if(state1==1){
			countNumber(column_line,1,100);
		}else if(state1==2){
			moveLine(column_line,layerData,1,1,50);
		}else if (state1==3){
			block(layerData,column_line,50,1);
		}else if (state1==4){
			block1(layerData,column_line,50,1);
		}else if (state1==5){
			boxInOut(row_line,column_line,layerData,60,1);
		}else if (state1==6){
			fireWorke(layer,row_line,column_line,layerData,100,1);
		}else if (state1==7){
			rain1(state1,randLayerData,column_line);
		}
    }
}

