#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <avr/pgmspace.h>

#define SERIAL_BUFFER_SIZE 64


#define UART_BAUDRATE 38400   
#define BAUD_PRESCALE (((F_CPU / (UART_BAUDRATE * 16UL))) - 1)

char uart_in_buffer[SERIAL_BUFFER_SIZE];
volatile int bytes_in_ready=0;
int uart_scroll_loc = 0;

class UART0_Term: public Terminal{
public:
	void write(char c){
		while((UCSR0A &(1<<UDRE0)) == 0);
		UDR0 = c;
	}
	void print(char* d){
		for(int i=0;d[i]!=0;i++)
			write(d[i]);
	}
	void stdo(char* d){
		//Serial.print(d);
		print(d);
	}

	void stde(char* d){
		//Serial.print(d);
		print(d);
	}

	bool available(){
		return bytes_in_ready>0;
	}

	char read(){
		if(bytes_in_ready<=0)return 0;
		if(bytes_in_ready==1){
			uart_scroll_loc = 0;
			bytes_in_ready = 0;
			return uart_in_buffer[0];
		}else{
			bytes_in_ready--;
			uart_scroll_loc++;
			return uart_in_buffer[uart_scroll_loc-1];
		}
	}
	
	void setup_port(int baudrate){
		UBRR0L = BAUD_PRESCALE&255;
		UBRR0H = (BAUD_PRESCALE >> 8);
		UCSR0B = ((1<<TXEN0)|(1<<RXEN0) | (1<<RXCIE0));  // Enable UART and ISR
	};

	void uart_preinit(){
		
		set_primary_terminal(this);
		g_stdo("UART set to primary terminal.\n");
	}
	
	char* get_path(){
		return "uart0";
	}
};

ISR(USART_RXC_vect){
	char value = UDR0;             //read UART register into value
	if(bytes_in_ready<SERIAL_BUFFER_SIZE){
		uart_in_buffer[bytes_in_ready+uart_scroll_loc] = value;
		bytes_in_ready++;
	}
}

UART0_Term uart;
