
#include "StdTypes.h"
#include "LCD_Interface.h"
#include "ADC_Interface.h"
#include "Kaset.h"
#include "KASET_Cfg.h"

u16 volume=1;

u8 customChar[] = {
	0x1F,
	0x1F,
	0x1F,
	0x1F,
	0x1F,
	0x1F,
	0x1F,
	0x1F
};

void KASET_Init(void)
{
	LCD_CustomChar(0,customChar);
	ADC_SetInterruptCallBack(KASET_ReadVol);
	ADC_StartConversion_INT(KASET_CH);
}
void KASET_APP(void)
{
	LCD_WriteStringGoto(line1,2,"AUDIO VOLUME");
	static u8 prev_vol=0;
	if(volume>prev_vol)
	{
		LCD_GoTo(line2,prev_vol);
		for (u8 i=prev_vol;i<volume;i++)
		{
			LCD_WriteChar(0);
		}
	}
	else if(volume<prev_vol)
	{
		LCD_GoTo(line2,volume);
		for (u8 i=volume;i<prev_vol;i++)
		{
			LCD_WriteString(" ");
		}
	}
	prev_vol=volume;
	ADC_StartConversion_INT(KASET_CH);
}
void KASET_ReadVol(void)
{
	u16 adc=ADC_Read_INT();
	u16 vol=(adc*(u32)5000)/1024;
	KASET_SetVolume(vol/312);
}
void KASET_SetVolume(u16 vol)
{
	volume=vol;
}