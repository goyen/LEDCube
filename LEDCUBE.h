/*
 * haha.c
 *
 * Created: 2020-12-25
 *  Author: User
 */
#define F_CPU		16000000UL
#include <avr/io.h>
#include "util/delay.h"
#include <stdlib.h>
#include <avr/interrupt.h>

#define layer1		0x06
#define layer2		0x02
#define layer3		0x05
#define layer4		0x01
#define layer5		0x03
#define layer6		0x00
#define layer7		0x04

#define line0		0x00
#define line1		0x01
#define line2		0x02
#define line3		0x04
#define line4		0x08
#define line5		0x10
#define line6		0x20
#define line7		0x40




void delay_time(uint16_t temp_t1);

ISR(PCINT1_vect);

//row 574   column tr
void init(void);
void layerInit(uint8_t *layerData);
void rowTotalControl(uint8_t data);
void columnTotalControl(uint8_t data);
void layerTotalControl(uint8_t *data);
void pointControl(uint8_t layer,uint8_t row,uint8_t column,uint16_t temp_t1);

void block(uint8_t * layerData, uint8_t *column_line, uint16_t time1,uint8_t loop);
void block1(uint8_t * layerData, uint8_t *column_line, uint16_t time1,uint8_t loop);
void countNumber(uint8_t *column_line,uint8_t loop,uint8_t time1);
void boxInOut(uint8_t * row_line, uint8_t * column_line, uint8_t *layerData, uint16_t time1,uint8_t loop);
void fireWorke(uint8_t *layer,uint8_t *row_line,uint8_t *column_line,uint8_t *layerData,uint16_t time1,uint8_t loop );
void moveLine(uint8_t *column_line, uint8_t *layerData, uint8_t loop1,uint8_t loop2,uint16_t time1);
void rain(uint8_t *layer, uint8_t *column_line,uint8_t loop);
void cat(uint8_t *column_line);
void horse(uint8_t * column_line);
void rain1(uint8_t state1, uint8_t (*randLayerData)[7],uint8_t *column_line);