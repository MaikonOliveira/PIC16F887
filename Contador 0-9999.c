#include <main.h>
#include <stdint.h>

const unsigned char disp[10] = {//pgfedcba
                          0b00111111, // digito 0
                          0b00000110, // digito 1
                          0b01011011, // digito 2
                          0b01001111, // digito 3
                          0b01100110, // digito 4
                          0b01101101, // digito 5
                          0b01111100, // digito 6
                          0b00000111, // digito 7
                          0b01111111, // digito 8
                          0b01100111, // digito 9
                         };
void main()
{
   int m=0, c=0, d=0, u=0;
   int16_t cont=0;
   
   set_tris_d(0x00);
   set_tris_b(0x0f);
   
   while(TRUE)
   {
   
     m=(cont/1000); 
     c=((cont%1000)/100); 
     d=((cont%100)/10);             
     u=cont%10;  
     
      output_d(disp[u]);
      output_high(PIN_B4);
      delay_ms(20);
      output_low(PIN_B4);
         
      output_d(disp[d]);
      output_high(PIN_B5);
      delay_ms(20);
      output_low(PIN_B5);
      
      output_d(disp[c]);
      output_high(PIN_B6);
      delay_ms(20);
      output_low(PIN_B6);
      
      output_d(disp[m]);
      output_high(PIN_B7);
      delay_ms(20);
      output_low(PIN_B7);
      
      cont++;
      if(cont>9999) cont=0;
   }
}
