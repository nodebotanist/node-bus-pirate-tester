#define BAUD 9600
#define BAUD_RATE ((F_CPU)/(BAUD*16UL)-1)

void uart_init(void);