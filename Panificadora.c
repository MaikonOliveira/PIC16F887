//Developed by Maikon Oliveira
#include <16f887.h>
#include <regs_887.h>
#include <LCD_kit.H>
#fuses INTRC_IO
#use delay (clock=4MHZ)

signed char memoria[3];
int cont=0, timer, FIM=0, etapa=1;
int16 potencia, pot;

//Função para grava dado na EEPROM
void gravar(int posicao)
 {
 WREN=1; //habilita escrita na EEPROM
 EEADR=posicao; //escreve em EEADR o endereço da EEPROM escolhido (10)
 EEDAT=memoria[posicao-10]; //escreve em EEDAT o dado a ser gravado (0x38)
 EECON2=0x55; //executa sequência lógica de proteção e sincronização
 EECON2=0xAA; //contra gravação indesejada
 WR=1; //grava na EEPROM, no endereço EEADR o dado EEDAT
 while(WR); //espera fim de escrita na EEPROM
 WREN=0; //desabilita escrita na EEPROM
 }
 
//Função para ler EEPROM
char ler(int endereco)
 {
 /***** Leitura *****/

 EEADR=endereco; //escreve em EEADR o endereço da EEPROM
 RD=1; //habilita leitura na EEPROM
 while(RD); //espera fim de leitura na EEPROM
 return EEDAT; //armazena o dado lido da EEPROM na PORTA
 while(true);
 }

// Seleciona qual a cor do pão desejada;
void selecionaCor()
{
   int cor=1;
   char flag=1;
   texto=("Cor: ");linha=0;coluna=0; textodisplay();
   texto=("1 - Clara:");linha=1;coluna=0; textodisplay();
   texto=("2 - Media:");linha=2;coluna=0; textodisplay();
   texto=("3 - Escura:");linha=3;coluna=0; textodisplay();
   PORTD=1;
   while(RB0==1)
      {
      linha=0;coluna=6; numerodisplay(cor);
      if ((RB1==0)&&(flag==1))
         {
         cor++;
         flag=0;
         if (cor==4)
            {
            cor=1;
            }
         }
      if (RB1==1) flag=1;
      }
   limpa();
   texto=("Cor selecionada: ");linha=0;coluna=0; textodisplay();
   memoria[0]=cor;
   gravar(10);
   delay_ms(500);
   if(cor==1)
      {
      texto=("Clara");linha=1;coluna=0; textodisplay();
      }
   else if(cor==2)
      {
      texto=("Media");linha=1;coluna=0; textodisplay();
      }
   else if(cor==3)
      {
      texto=("Escura");linha=1;coluna=0; textodisplay();
      }
   delay_ms(3000);
   limpa();
}

// Seleciona qual o tamanho do pão desejado;
void selecionaTamanho()
   {
   int tamanho=1;
   char flag=1;
   texto=("Tamanho: ");linha=0;coluna=0; textodisplay();
   texto=("1 - 450g");linha=1;coluna=0; textodisplay();
   texto=("2 - 600g");linha=2;coluna=0; textodisplay();
   texto=("3 - 900g");linha=3;coluna=0; textodisplay();
   PORTD=1;
   while(RB0==1)
      {
      linha=0;coluna=10; numerodisplay(tamanho);
      if ((RB1==0)&&(flag==1))
         {
         tamanho++;
         flag=0;
         if (tamanho==4)
            {
            tamanho=1;
            }
         }
      if (RB1==1) flag=1;
      }
   limpa();
   texto=("Tamanho selecionado: ");linha=0;coluna=0; textodisplay();
   memoria[1]=tamanho;
   gravar(11);
   delay_ms(500);
   if(tamanho==1)
      {
      texto=("450g");linha=1;coluna=0; textodisplay();
      }
   else if(tamanho==2)
      {
      texto=("600g");linha=1;coluna=0; textodisplay();
      }
   else if(tamanho==3)
      {
      texto=("900g");linha=1;coluna=0; textodisplay();
      }
   delay_ms(3000);
   limpa();
}

// Seleciona o modo de preparo desejado;
void selecionaModo()
   {
   int modo=1;
   char flag=1;
   texto=("Modo: ");linha=0;coluna=0; textodisplay();
   PORTD=1;
   while(RB0==1)
      {
      linha=0;coluna=8; numerodisplay(modo);
      texto=("1-Normal");linha=1;coluna=0; textodisplay();
      texto=("2-Frances");linha=2;coluna=0; textodisplay();
      texto=("3-Integral");linha=3;coluna=0; textodisplay();
      texto=("4-Rapido");linha=1;coluna=11; textodisplay();
      texto=("5-Amassar");linha=2;coluna=11; textodisplay();
      texto=("6-Assar");linha=3;coluna=11; textodisplay();
      if ((RB1==0)&&(flag==1))
         {
         modo++;
         flag=0;
         if (modo==7)
            {
            modo=1;
            }
         }
      if (RB1==1) flag=1;
      }
   limpa();
   texto=("Modo selecionado: ");linha=0;coluna=0; textodisplay();
   memoria[2]=modo;
   gravar(12);
   delay_ms(500);
   if(modo==1)
      {
      texto=("Normal");linha=1;coluna=0; textodisplay();
      }
   else if(modo==2)
      {
      texto=("Frances");linha=1;coluna=0; textodisplay();
      }
   else if(modo==3)
      {
      texto=("Integral");linha=1;coluna=0; textodisplay();
      }
   else if(modo==4)
      {
      texto=("Rapido");linha=1;coluna=0; textodisplay();
      }
   else if(modo==5)
      {
      texto=("Amassar");linha=1;coluna=0; textodisplay();
      }
   else if(modo==6)
      {
      texto=("Assar");linha=1;coluna=0; textodisplay();
      }
   delay_ms(3000);
   limpa();
}

//Ajuste de potencia da resistencia
void potenciaResistencia()
   {
   ADON=1;     // liga o sistema AD
   limpa();
   texto=("Potencia: ");linha=1;coluna=0; textodisplay();
   while(RB0==1)
      {
      GO_DONE=1;
      while (GO_DONE);
      pot=ADRESH;
      if(ler(10) == 1)
         {
         potencia=(63.75+(pot/4));
         linha=1;coluna=12; numerodisplay(((potencia+2)*100)/255);
         }
      else if(ler(10) == 2)
         {
         potencia=(127.5+(pot/4));
         linha=1;coluna=12; numerodisplay(((potencia+2)*100)/255);
         }
      else if(ler(10) == 3)
         {
         potencia=(191.25+(pot/4));
         linha=1;coluna=12; numerodisplay(((potencia+2)*100)/255);
         }
      }
   }

void modoNormal()
   {
   //Mistura 01 - 60s
   linha=2;coluna=7; numerodisplay(etapa);
   if(ler(11) == 1) timer=120;
   else if(ler(11) == 2) timer=150;
   else if(ler(11) == 3) timer=180;
   TMR1ON=1;
   RC3=1;
   while(TMR1ON==1);
   etapa++;
   
   //Descanso 01 - 30s
   linha=2;coluna=7; numerodisplay(etapa);
   RC3=0;
   timer=60;
   TMR1ON=1;
   while(TMR1ON==1);
   etapa++;
   
   //Mistura 02 - 30s
   linha=2;coluna=7; numerodisplay(etapa);
   if(ler(11) == 1) timer=60;
   else if(ler(11) == 2) timer=90;
   else if(ler(11) == 3) timer=120;
   TMR1ON=1;
   RC3=1;
   while(TMR1ON==1);
   etapa++;
   
   //Descanso 02 - 15s
   linha=2;coluna=7; numerodisplay(etapa);
   RC3=0;
   timer=30;
   TMR1ON=1;
   while(TMR1ON==1);
   etapa++;
   
   //Mistura 03 - 15s
   linha=2;coluna=7; numerodisplay(etapa);
   if(ler(11) == 1) timer=30;
   else if(ler(11) == 2) timer=60;
   else if(ler(11) == 3) timer=90;
   TMR1ON=1;
   RC3=1;
   while(TMR1ON==1);
   etapa++;
   
   //Descanso 03 - 5s
   linha=2;coluna=7; numerodisplay(etapa);
   RC3=0;
   timer=10;
   TMR1ON=1;
   while(TMR1ON==1);
   etapa++;
   
   //Assar - 60s
   linha=2;coluna=7; numerodisplay(etapa);
   CCPR1L=potencia;
   timer=120;
   TMR1ON=1;
   while(TMR1ON==1);
   CCPR1L=0;
   etapa=1;
   FIM=1;
   }
   
void modoIntegral()
   {
   //Mistura 01 - 60s
   linha=2;coluna=7; numerodisplay(etapa);
   if(ler(11) == 1) timer=120;
   else if(ler(11) == 2) timer=150;
   else if(ler(11) == 3) timer=180;
   TMR1ON=1;
   RC3=1;
   while(TMR1ON==1);
   etapa++;
   
   //Descanso 01 - 30s
   linha=2;coluna=7; numerodisplay(etapa);
   RC3=0;
   timer=60;
   TMR1ON=1;
   while(TMR1ON==1);
   etapa++;
   
   //Mistura 02 - 30s
   linha=2;coluna=7; numerodisplay(etapa);
   if(ler(11) == 1) timer=60;
   else if(ler(11) == 2) timer=90;
   else if(ler(11) == 3) timer=120;
   TMR1ON=1;
   RC3=1;
   while(TMR1ON==1);
   etapa++;
   
   //Descanso 02 - 15s
   linha=2;coluna=7; numerodisplay(etapa);
   RC3=0;
   timer=30;
   TMR1ON=1;
   while(TMR1ON==1);
   etapa++;
   
   //Mistura 03 - 15s
   linha=2;coluna=7; numerodisplay(etapa);
   if(ler(11) == 1) timer=30;
   else if(ler(11) == 2) timer=60;
   else if(ler(11) == 3) timer=90;
   TMR1ON=1;
   RC3=1;
   while(TMR1ON==1);
   etapa++;
   
   //Descanso 03 - 5s
   linha=2;coluna=7; numerodisplay(etapa);
   RC3=0;
   timer=10;
   TMR1ON=1;
   while(TMR1ON==1);
   etapa++;
   
   //Assar - 60s
   linha=2;coluna=7; numerodisplay(etapa);
   CCPR1L=potencia;
   timer=120;
   TMR1ON=1;
   while(TMR1ON==1);
   CCPR1L=0;
   etapa=1;
   FIM=1;
   }
   
void modoFrances()
   {
   //Mistura 01 - 60s
   linha=2;coluna=7; numerodisplay(etapa);
   if(ler(11) == 1) timer=120;
   else if(ler(11) == 2) timer=150;
   else if(ler(11) == 3) timer=180;
   TMR1ON=1;
   RC3=1;
   while(TMR1ON==1);
   etapa++;
   
   //Descanso 01 - 30s
   linha=2;coluna=7; numerodisplay(etapa);
   RC3=0;
   timer=60;
   TMR1ON=1;
   while(TMR1ON==1);
   etapa++;
   
   //Mistura 02 - 30s
   linha=2;coluna=7; numerodisplay(etapa);
   if(ler(11) == 1) timer=60;
   else if(ler(11) == 2) timer=90;
   else if(ler(11) == 3) timer=120;
   TMR1ON=1;
   RC3=1;
   while(TMR1ON==1);
   etapa++;
   
   //Descanso 02 - 15s
   linha=2;coluna=7; numerodisplay(etapa);
   RC3=0;
   timer=30;
   TMR1ON=1;
   while(TMR1ON==1);
   etapa++;
   
   //Mistura 03 - 15s
   linha=2;coluna=7; numerodisplay(etapa);
   if(ler(11) == 1) timer=30;
   else if(ler(11) == 2) timer=60;
   else if(ler(11) == 3) timer=120;
   TMR1ON=1;
   RC3=1;
   while(TMR1ON==1);
   etapa++;
   
   //Descanso 03 - 5s
   linha=2;coluna=7; numerodisplay(etapa);
   RC3=0;
   timer=10;
   TMR1ON=1;
   while(TMR1ON==1);
   etapa++;
   
   //Assar - 60s
   linha=2;coluna=7; numerodisplay(etapa);
   CCPR1L=potencia;
   timer=120;
   TMR1ON=1;
   while(TMR1ON==1);
   CCPR1L=0;
   etapa=1;
   FIM=1;
   }
void modoRapido()
   {
   //Mistura 01 - 60s
   linha=2;coluna=7; numerodisplay(etapa);
   if(ler(11) == 1) timer=120;
   else if(ler(11) == 2) timer=150;
   else if(ler(11) == 3) timer=180;
   TMR1ON=1;
   RC3=1;
   while(TMR1ON==1);
   etapa++;
   
   //Descanso 03 - 5s
   linha=2;coluna=7; numerodisplay(etapa);
   RC3=0;
   timer=10;
   TMR1ON=1;
   while(TMR1ON==1);
   etapa++;
   
   //Assar - 60s
   linha=2;coluna=7; numerodisplay(etapa);
   CCPR1L=potencia;
   timer=120;
   TMR1ON=1;
   while(TMR1ON==1);
   CCPR1L=0;
   etapa=1;
   FIM=1;
   }

void modoAmassar()
   {
   //Mistura 01 - 60s
   linha=2;coluna=7; numerodisplay(etapa);
   if(ler(11) == 1) timer=120;
   else if(ler(11) == 2) timer=150;
   else if(ler(11) == 3) timer=180;
   TMR1ON=1;
   RC3=1;
   while(TMR1ON==1);
   etapa++;
   
   //Descanso 02 - 15s
   linha=2;coluna=7; numerodisplay(etapa);
   RC3=0;
   timer=30;
   TMR1ON=1;
   while(TMR1ON==1);
   etapa++;
   
   //Descanso 03 - 5s
   linha=2;coluna=7; numerodisplay(etapa);
   RC3=0;
   timer=10;
   TMR1ON=1;
   while(TMR1ON==1);
   etapa=1;
   FIM=1;
   }

void modoAssar()
   {
   //Assar - 60s
   linha=2;coluna=7; numerodisplay(etapa);
   CCPR1L=potencia;
   timer=120;
   TMR1ON=1;
   while(TMR1ON==1);
   CCPR1L=0;
   FIM=1;
   }

void main(void)
{
int16 lido;
TRISD=0;
RD7=0;
TRISB=3;
TRISC=0; //RC2 - saída pwm
RC3=0;
RBPU=0;
WPUB=3;
TRISA=0x01;       
ANSEL=0x01;       
ADCS1=1; ADCS0=1; // RC interno                  
CHS3=0; CHS2=0; CHS1=0; CHS0=0;
ADFM=0;     // justificado a esquerda 8MSB
VCFG1=0;    // vref- =>VSS
VCFG0=0;    // vref+ =>VCC

//PWM no pino RC2 TIMER1
T2CKPS1=0; T2CKPS0=1; //prescaler 1:4
PR2=254; //f=10kHz <-> T=250us
CCPR1L=0; //DC=0%
DC1B1=0; //240 = 0x0f0 = 00|1111|0000 -> 0011 1100 00
DC1B0=0; //0011|1100 = 0x3C
P1M1=0; P1M0=0; //saída única
CCP1M3=1; //modo PWM
CCP1M2=1;
TMR2ON=1;

//EEPROM
EEPGD=0;

//TIMER1
TMR1CS=0; //temporizador (fclock/4)
T1CKPS1=1; T1CKPS0=1; // prescaler 1:1
TMR1H=0x0B; //tempo = 500ms
TMR1L=0xDC; //65536-((500ms*4MHz)/4*8)=65536-62500=3036 -> 0BDC
TMR1IE=1; PEIE=1; GIE=1; //habilita interrupção

inicializa();
texto=("Inicializando...");linha=1;coluna=0; textodisplay();
delay_ms(500);

while(true)
{
RD5=0;
RD6=0;
delay_ms(200);
limpa();
while(RB0==1)
   {
   texto=("PROJETO PANIFICADORA");linha=0;coluna=0; textodisplay();
   texto=("PIC16F887");linha=1;coluna=5; textodisplay();
   texto=("  OK para iniciar  ");linha=3;coluna=0; textodisplay();
   }
limpa();
delay_ms(200);
FIM=0;
selecionaModo();
if(ler(12) != 6) 
   {
   selecionaTamanho();
   }
else if(ler(12) == 6)
   {
   memoria[0]=0;
   gravar(10);
   }
if(ler(12) != 5)  
   {
   selecionaCor();
   potenciaResistencia();
   }
else if(ler(12) == 5)
   {
   memoria[1]=0;
   gravar(11);
   }
delay_ms(200);

//Iniciar o preparo;
limpa();
texto=("Iniciar o preparo ?");linha=0;coluna=0; textodisplay();
texto=("RB0 = Ok");linha=1;coluna=0; textodisplay();
texto=("RB1 = Sair");linha=2;coluna=0; textodisplay();
while(RB0==1 && RB1==1);
limpa();
if(RB1!=0){
texto=("Iniciando preparo...");linha=1;coluna=0; textodisplay();
delay_ms(2000);
limpa();

while(FIM==0)
   {
   texto=("Preparando...");linha=1;coluna=0; textodisplay();
   texto=("Etapa: ");linha=2;coluna=0; textodisplay();
   texto=("Potencia:");linha=3;coluna=0; textodisplay();
   lido=ler(12);
   texto=("M: ");linha=0;coluna=0; textodisplay();
   linha=0;coluna=3; numerodisplay(lido);
   lido=ler(10);
   texto=("C: ");linha=0;coluna=7; textodisplay();
   linha=0;coluna=10; numerodisplay(lido);
   lido=ler(11);
   texto=("T: ");linha=0;coluna=14; textodisplay();
   linha=0;coluna=17; numerodisplay(lido);
   linha=3;coluna=12; numerodisplay((potencia*100)/255);
   
   if(ler(12) == 1)
      {
      modoNormal();
      }
   else if(ler(12) == 2)
      {
      modoIntegral();
      }
   else if(ler(12) == 3)
      {
      modoFrances();
      }
   else if(ler(12) == 4)
      {
      modoRapido();
      }
   else if(ler(12) == 5)
      {
      modoAmassar();
      }
   else if(ler(12) == 6)
      {
      modoAssar();
      }
 }
  texto=("Processo finalizado!");linha=1;coluna=0; textodisplay();
  //FIM=0;
  RD5=0;
  RD6=1;
  for(int k=0;k<5;k++)
   {
   RD7=1; delay_ms(200); RD7=0; delay_ms(200);
   }
   delay_ms(5000);
   }
   }
}

#INT_TIMER1
void temporizador (void)
{
RD6=~RD6;
cont++;
if(cont==timer) 
   {
   TMR1ON=0;
   cont=0;
   }
TMR1H=0x0B;     
TMR1L=0xDC;  
TMR1IF=0; 
}
