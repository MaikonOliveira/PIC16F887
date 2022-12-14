//Contador 0-9 utilizando o lcd no proteus
//Foram utilizadas 2 bibliotecas(display.h e regs_887.h) criadas para o display e para os registradores SFR do PIC16F887.
//Desenvolvido por Maikon Oliveira

#include <16f887.h>
#use delay (clock=4MHz)
#include <display.h>
#fuses INTRC_IO
void main(void)
 {
   int count=0;
   char texto[17];
   TRISC=0; TRISE=0;
   inicializa();
   strcpy(texto,"MICROCONTROLADOR");
   escreve (0x80, texto);
   strcpy(texto,"   PIC 16F887   ");
   escreve (0xC0, texto);
   strcpy(texto,"  Hello World!  ");
   escreve (0x90, texto);
   while(true)
   {
      strcpy(texto,"    Count:   ");
      texto[11] = count+'0';
      escreve(0xD0, texto);
      delay_ms(500);
      count++;
      if(count == 10) count=0;  
   }
 }
