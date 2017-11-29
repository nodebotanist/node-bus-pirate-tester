#define BAUD 9600
#define BAUD_RATE ((F_CPU)/(BAUD*16UL)-1)

void uart_init(void);
void print_byte(uint8_t data);
uint8_t recieve_byte(void);
void print_string(const char string_to_send);
void recieve_string(char string_recieved[], uint8_t max_string_length);
char four_bits_to_hex(uint8_t four_bits);
void print_hex_byte(uint8_t byte);