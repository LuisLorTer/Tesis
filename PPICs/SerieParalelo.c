#include <18F4550.h>                         //libreria del microcontrolador

#fuses HS, NOWRT, NOWDT, NOPROTECT, NOPUT, NOLVP   //configuracion de los fusibles

#use delay(crystal=8000000)                     //Frecuencia del oscilador 8MHz.Crystal significa cristak externo

#include <stdlib.h>

#define INIT_UART_BAUDRATE   9600
#use rs232(baud=INIT_UART_BAUDRATE, parity=N, xmit=PIN_C6, rcv = PIN_C7, bits = 8)

int main()
{
      set_tris_b(0);
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
            
   return 0;
}
