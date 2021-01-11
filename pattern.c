/*
 * haha.c
 *
 * Created: 2020-12-25
 *  Author: User
 */ 
#include "LEDCUBE.h"

void cat(uint8_t * column_line){
	uint8_t layerData[4][7]	=	{{0x41,0x14,0x08,0x22,0x00,0x5d,0x22},
	{0x40,0x15,0x08,0x22,0x00,0x5d,0x22},
	{0x01,0x54,0x08,0x22,0x00,0x5d,0x22},
	{0x41,0x14,0x08,0x63,0x00,0x5d,0x22}};
	for(uint8_t i=0; i<4;i++){
		columnTotalControl(column_line[6]);
		layerTotalControl(layerData[i]);
		delay_time(300);
	}
}


void block(uint8_t * layerData, uint8_t *column_line, uint16_t time1,uint8_t loop){
	for(uint8_t i=0; i<loop;i++){
		int a=0x00;
		for(uint8_t i=0;i<7;i++){
			a=(a<<1)+1;
			uint8_t b=0;
			for(uint8_t j=0;j<(i+1);j++){
				layerData[j]=a;
				b+=column_line[j];
			}
			columnTotalControl(b);
			layerTotalControl(layerData);
			delay_time(time1);
		}
		//layerInit(layerData);
		for(int8_t i=6;i>=0;i--){
			uint8_t b=0x00;
			a=a>>1;
			layerData[i]=0x00;
			for(int j=(i-1);j>=0;j--){
				layerData[j]=a;
				b|=column_line[j];
			}
			columnTotalControl(b);
			layerTotalControl(layerData);
			delay_time(time1);
		}
		
	}
}

void block1(uint8_t * layerData, uint8_t *column_line, uint16_t time1,uint8_t loop){
	for(uint8_t i=0; i<loop;i++){
		uint8_t a=0x00;
		for(uint8_t i=0;i<7;i++){
			a|=0x01<<i;
			uint8_t b=0;
			for(uint8_t j=0;j<(i+1);j++){
				layerData[j]=a;
				b+=column_line[j];
			}
			columnTotalControl(b);
			layerTotalControl(layerData);
			delay_time(time1);
		}
		for(uint8_t i=1;i<7;i++){
			uint8_t b=0;
			a&=a<<1;
			for(uint8_t j=i;j<7;j++){
				layerData[j]=a;
				b+=column_line[j];
			}
			layerData[i-1]=0x00;
			columnTotalControl(b);
			layerTotalControl(layerData);
			delay_time(time1);
		}
		layerInit(layerData);

	}
}

void countNumber(uint8_t *column_line,uint8_t loop,uint8_t time1){
	for(uint8_t i=0;i<loop;i++){
		uint8_t layerDataNumber[5][7]=	{{0x3e,0x20,0x20,0x3e,0x02,0x02,0x3e}
										,{0x10,0x10,0x3e,0x12,0x14,0x18,0x10}
										,{0x3e,0x20,0x20,0x3e,0x20,0x20,0x03e}
										,{0x3e,0x02,0x02,0x3e,0x20,0x20,0x3e}
										,{0x3e,0x08,0x08,0x08,0x0a,0x0c,0x08}};
				
		for(uint8_t j=0;j<5;j++){
			layerTotalControl(layerDataNumber[j]);
			for(uint8_t k=6;k>=1;k--){
				columnTotalControl(column_line[k]);
				delay_time(time1-k*10+j*20);
			}
		}
	}
}

void boxInOut(uint8_t * row_line, uint8_t * column_line, uint8_t *layerData, uint16_t time1,uint8_t loop){
	for(uint8_t i=0;i<loop;i++){
		uint8_t row = 0;
		uint8_t column = 0;
		uint8_t temp = 3;
		for(uint8_t i=1;i<8;){
			for(uint8_t j=0;j<i;j++){
				row|=row_line[temp+j];
				column|=column_line[temp+j];
			}
			for(uint8_t j=0;j<i;j++){
				layerData[temp+j]=row;
			}
			layerTotalControl(layerData);
			columnTotalControl(column);
			delay_time(time1);
			layerInit(layerData);
			i+=2;
			temp-=1;
		}
		temp=1;
		column=0;
		row=0;
		for(int8_t i=5;i>0;){
			for(int8_t j=0;j<i;j++){
				row|=row_line[temp+j];
				column|=column_line[temp+j];
			}
			for(uint8_t j=0;j<i;j++){
				layerData[temp+j]=row;
			}
			layerTotalControl(layerData);
			columnTotalControl(column);
			delay_time(time1);
			layerInit(layerData);
			i-=2;
			temp+=1;
			column=0;
			row=0;
		}
	}
}

void horse(uint8_t * column_line){
	uint8_t layerData[4][7]	=	{{0x48,0x24,0x3e,0x3e,0x10,0x50,0x20},
	{0x24,0x24,0x3e,0x3e,0x10,0x50,0x20},
	{0x12,0x24,0x3e,0x3e,0x10,0x50,0x20},
	{0x09,0x12,0x3e,0x3e,0x10,0x50,0x20}};
	for(uint8_t i=0; i<4;i++){
		columnTotalControl(column_line[6]);
		layerTotalControl(layerData[i]);
		delay_time(100);
	}
}

void fireWorke(uint8_t *layer,uint8_t *row_line,uint8_t *column_line,uint8_t *layerData,uint16_t time1,uint8_t loop ){
	for(uint8_t i=0;i<loop;i++){
		uint8_t row = 0x00;
		uint8_t column = 0x00;
		uint8_t tempRow = (rand()%3)+2;
		uint8_t tempcolumn = (rand()%3)+2;
		
		for(int8_t i=0;i<5;i++){
			pointControl(layer[i],row_line[tempRow],column_line[tempcolumn],time1);
			rowTotalControl(0x00);
		}
		
		for (int8_t i=0;i<3;i++){
			row|=row_line[tempRow-1+i];
			column|=column_line[tempcolumn-1+i];
		}
		layerData[5]=row;
		layerData[4]=row;
		layerData[3]=row;
		layerTotalControl(layerData);
		columnTotalControl(column);
		row=0x00;
		column=0x00;
		delay_time(time1);
		rowTotalControl(0x00);
		layerInit(layerData);
		
		for (int8_t i=0;i<5;i++){
			row|=row_line[tempRow-2+i];
			column|=column_line[tempcolumn-2+i];
			i++;
		}
		for(int8_t j=6;j>=0;j--){
			for(int8_t i=0;i<5;i++){
				if((j-i)>=0)	layerData[j-i]=row;
				i++;
			}
			layerTotalControl(layerData);
			columnTotalControl(column);
			delay_time(time1);
			rowTotalControl(0x00);
			layerInit(layerData);
		}
	}
}


void moveLine(uint8_t *column_line, uint8_t *layerData, uint8_t loop1,uint8_t loop2,uint16_t time1){

	for(uint8_t i=0; i<loop1;i++){
		uint8_t temp=0x01;
		uint8_t temp1=0x40;
		uint8_t temp2=0;
		for (uint8_t j=0;j<7;j++){
			temp2=(temp<<j)|(temp1>>j);
			rowTotalControl(temp2);
			columnTotalControl(0x7f);
			delay_time(time1);
		
		}
	}
// 	for(uint8_t i=0; i<loop1;i++){
// 		for(uint8_t i=0; i<7;i++){
// 			rowTotalControl(0x7f);
// 			columnTotalControl(column_line[i]|column_line[6-i]);
// 			delay_time(50);
// 		}
// 	}
	
	for(uint8_t i=0;i<loop2;i++){
		for(uint8_t i=0; i<7;i++){
			layerData[i]=0x7f;
			layerData[6-i]=0x7f;
			layerTotalControl(layerData);
			columnTotalControl(0x7f);
			delay_time(time1);
			layerInit(layerData);
		}
	}
	
	
	
	
}

void rain(uint8_t *layer, uint8_t *column_line,uint8_t loop){
	for(uint8_t i=0;i<loop;i++){
		uint8_t a=rand()%7;
		uint8_t b=rand()%7;
		for(int8_t i=6;i>=0;i--){
			pointControl(layer[i],0x01<<a,column_line[b],150-(120-(i*20)));
			pointControl(layer[i],0x00,column_line[b],0);
		}
	}
}

void rain1(uint8_t state1, uint8_t (*randLayerData)[7],uint8_t *column_line){
	uint8_t temp1=1;
	uint8_t temp2=1;
	uint8_t temp3=250;
	while(temp3){
			temp1++;
			temp2++;
			temp3--;
			for(int i=0;i<7;i++){
				layerTotalControl(randLayerData[i]);
				columnTotalControl(column_line[i]);
				delay_time(2);
			}
			if(temp1==8){
				temp1=1;
				for(uint8_t i=0;i<7;i++){
					for(uint8_t j=0;j<6;j++) randLayerData[i][j]=randLayerData[i][j+1];
					randLayerData[i][6]=0x00;
				}
			}
			if(temp2==20){
				temp2=1;
				for(uint8_t i=0;i<(rand()%15)+2;i++) randLayerData[rand()%7][6]|=0x01<<(rand()%7);
			}
		
	}
}



//  void test(){
// 		temp2++;
// 		temp1++;
// 		for(int8_t i=0;i<7;i++){
// 			layerTotalControl(randLayerData[i]);
// 			columnTotalControl(column_line[i]);
// 			delay_time(3);
// 		}
// 		if(temp1==50){
// 			temp1=1;
// 			for(int8_t j=0;j<10;j++){
// 				int8_t a=rand()%7;
// 				int8_t b=rand()%7;
// 				for(int8_t i=0;i<5;i++){
// 					randLayerData[a][i+2]=0x01<<b;
// 				}
// 			}
// 		}
// 		if(temp2==30){
// 			temp2=1;
// 			for(int8_t i=0;i<7;i++){
// 				for(int8_t j=1;j<6;j++){
// 					randLayerData[i][j]=randLayerData[i][j+1];
// 				}
// 				randLayerData[i][6]=0x00;
// 			}
// 		}
// }