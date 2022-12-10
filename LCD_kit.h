#define RS PIN_E0
#define RW PIN_E1
#define E PIN_E2
#define D4 PIN_D0
#define D5 PIN_D1
#define D6 PIN_D2
#define D7 PIN_D3
#use delay(clock=4000000)

unsigned char coluna=0,linha=0,endereco=0;
int16 palavra=0;

char texto[21];
void tempo(void)
{
output_high(E);
delay_us(500);
output_low(E);
}

void inicializa (void)
{
output_low(E); output_low(RW);output_low(RS); //Ativa o enable e a instrucao
output_low(D7);   output_low(D6);   output_low(D5);   output_low(D4);   tempo();//0
delay_ms(16); 
 output_low(D7);   output_low(D6);   output_high(D5);   output_high(D4);   tempo();//0 D7=0; D6=0; D5=1; D4=1;  E=1; delay_us(w); E=0;delay_us(w);
 delay_ms(5);
 output_low(D7);   output_low(D6);   output_high(D5);  output_high(D4);   tempo(); //2 D7=0; D6=0; D5=1; D4=1;  E=1; delay_us(w); E=0;delay_us(w);

 output_low(D7);   output_low(D6);  output_high(D5);   output_high(D4);  tempo();//2 D7=0; D6=0; D5=1; D4=1;  E=1; delay_us(w); E=0;delay_us(w);
output_low(D7);  output_low(D6);  output_high(D5);  output_low(D4);  tempo();    //8 D7=0; D6=0; D5=1; D4=0;  E=1; delay_us(w); E=0;delay_us(w);

 output_low(D7);  output_low(D6);   output_high(D5);  output_low(D4);   tempo();//2 D7=0; D6=0; D5=1; D4=0;    E=1; delay_us(w); E=0;delay_us(w);//display 4 linhas
output_high(D7);  output_low(D6);   output_low(D5);  output_low(D4);   tempo(); //6 D7=1; D6=0; D5=0; D4=0;    E=1; delay_us(w); E=0;delay_us(w);

 output_low(D7);  output_low(D6);   output_low(D5);   output_low(D4);   tempo();//0 D7=0; D6=0; D5=0; D4=0;    E=1; delay_us(w); E=0;delay_us(w);//blink off cursor off
output_high(D7); output_high(D6);   output_low(D5);   output_low(D4);   tempo();//C ou 12  D7=1; D6=1; D5=0; D4=0;    E=1; delay_us(w); E=0;delay_us(w);

 output_low(D7);  output_low(D6);   output_low(D5);   output_low(D4);   tempo();//0 D7=0; D6=0; D5=0; D4=0;    E=1; delay_us(w); E=0;delay_us(w);//clear
 output_low(D7);  output_low(D6);   output_low(D5);  output_high(D4);   tempo();//1 D7=0; D6=0; D5=0; D4=1;    E=1; delay_us(w); E=0;delay_us(w);
 
 output_low(D7);  output_low(D6);   output_low(D5);   output_high(D4);   tempo();//  D7=0; D6=0; D5=0; D4=1;    E=1; delay_us(w); E=0;delay_us(w);//clear
 output_low(D7);  output_high(D6);   output_low(D5);   output_high(D4);   tempo();//  D7=0; D6=1; D5=0; D4=1;    E=1; delay_us(w); E=0;delay_us(w);
}

void escreve (unsigned char posicao, char t[]) // retorna um void, o nome da funcao e escreve, e os parametros sao unsigned char e char
{
unsigned char i=0;
output_low(RS);
if (bit_test(posicao,4)==1){output_high(D4);}else{output_low(D4);}
if (bit_test(posicao,5)==1){output_high(D5);}else{output_low(D5);}
if (bit_test(posicao,6)==1){output_high(D6);}else{output_low(D6);}
if (bit_test(posicao,7)==1){output_high(D7);}else{output_low(D7);}
tempo();
if (bit_test(posicao,0)==1){output_high(D4);}else{output_low(D4);}
if (bit_test(posicao,1)==1){output_high(D5);}else{output_low(D5);}
if (bit_test(posicao,2)==1){output_high(D6);}else{output_low(D6);}
if (bit_test(posicao,3)==1){output_high(D7);}else{output_low(D7);}
tempo();
output_high(RS);
while (t[i]!=0)
{
if (bit_test(t[i],4)==1){output_high(D4);}else{output_low(D4);}
if (bit_test(t[i],5)==1){output_high(D5);}else{output_low(D5);}
if (bit_test(t[i],6)==1){output_high(D6);}else{output_low(D6);}
if (bit_test(t[i],7)==1){output_high(D7);}else{output_low(D7);}
tempo();
if (bit_test(t[i],0)==1){output_high(D4);}else{output_low(D4);}
if (bit_test(t[i],1)==1){output_high(D5);}else{output_low(D5);}
if (bit_test(t[i],2)==1){output_high(D6);}else{output_low(D6);}
if (bit_test(t[i],3)==1){output_high(D7);}else{output_low(D7);}
tempo();
i++;
}
}

void limpa (void)
{
output_low(RS);
output_low(D7);  output_low(D6);   output_low(D5);   output_low(D4);   tempo();//0
output_low(D7);  output_low(D6);   output_low(D5);  output_high(D4);   tempo();//1

output_low(D7);  output_low(D6);   output_low(D5);   output_high(D4);   tempo();//1  
output_low(D7);  output_high(D6);  output_low(D5);   output_high(D4);   tempo();//5
   
output_high(RS);
}

void textodisplay (void)
{
if(linha==0){endereco=coluna+0X80;}
if(linha==1){endereco=coluna+0XC0;}
if(linha==2){endereco=coluna+0X94;}
if(linha==3){endereco=coluna+0XD4;}
escreve(endereco,texto);
}

void numerodisplay (int16 num)
{
if(linha==0){endereco=coluna+0X80;}
if(linha==1){endereco=coluna+0XC0;}
if(linha==2){endereco=coluna+0X94;}
if(linha==3){endereco=coluna+0XD4;}
sprintf(texto,"%03Ld",num);
escreve(endereco,texto);
}
