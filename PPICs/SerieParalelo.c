#include <18F4550.h>                         //libreria del microcontrolador

#fuses HS, NOWRT, NOWDT, NOPROTECT, NOPUT, NOLVP   //configuracion de los fusibles

#use delay(crystal=8000000)                     //Frecuencia del oscilador 8MHz.Crystal significa cristak externo

#include <stdlib.h>

#define INIT_UART_BAUDRATE   9600
#use rs232(baud=INIT_UART_BAUDRATE, parity=N, xmit=PIN_C6, rcv = PIN_C7, bits = 8)

#define RD PIN_A0
#define WR PIN_A1
#define CS1FX PIN_A2
#define DA0 PIN_A3
#define DA1 PIN_A4
#define DA2 PIN_A5

int8 comando = 0x00;
int8 trama_index = 0;
int8 dir_l;
int8 dir_h;
int8 data_l;
int8 data_h;

void put_address(void);

int main()
{     
      set_tris_a(0x00);
      output_low (CS1FX); 
      while(1)
      {
         if(kbhit())
         {
            if(trama_index == 0){
               comando = getc();
               ++trama_index;
               break;
            }
            else if(trama_index == 1){
               dir_l = getc();
               ++trama_index;
               break;
            }
            else if(trama_index == 2){
               dir_h = getc();
               ++trama_index;
               break;
            }
            else if((comando == 3) & (trama_index == 3)){
               put_address(); 
               set_tris_b(0xFF);
               set_tris_d(0xFF);
               output_low (RD);
               delay_ms(10);
               data_l = input_b();
               //data_h = input_d();
               
               putc(data_l);
               trama_index = 0;
               break;
            }
            else if(trama_index == 3){
               data_l = getc();
               ++trama_index;
               break;
            }
            else if((trama_index == 4) & (comando == 1)){
               put_address();
               output_b(data_l);
               delay_ms(10);
               trama_index = 0;
               break;
            }
            else if(trama_index == 4){
               data_h = getc();
               ++trama_index;
               break;
            }
            else if(trama_index == 5)
            {
               put_address();
               output_b(data_l);
               output_b(data_h);
               delay_ms(10);
               trama_index = 0;
               break;
            }
            else
               return 1;    
            
         }
      }
  /*    set_tris_b(0);              //Programa de prueba
      set_tris_d(0);
      int8 dato1 = 0;
      int8 dato2 = 0;
      unsigned int i=1;
      while(1)
      {
          if(kbhit())
          {
             if(i){
             dato1=getc();
             output_b(dato1);
             i=0;
             }
             else{
             dato2=getc();
             output_d(dato2);
             i=1;
             }
           delay_ms(100);
          }
      }
   */         
   return 0;
}

void put_address(void){
   set_tris_b(0x00);
   set_tris_d(0x00);
   output_b(dir_l);
   output_d(dir_h);
   //dudas con se�ales DA0,DA1 y DA2
   output_low (WR);
   delay_ms(10);
   /*output_low (DA1);
   output_low (DA0);
   output_high (DA1);*/
}
