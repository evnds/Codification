#include <stdio.h>
#include <stdlib.h>

#define TAM 						300	// Number of bytes to codify
#define TAM_CODIFICADO_BYTES		(TAM + TAM/7 + (TAM%7>0)) // OR (int)(TAM*8.0/7.0) + ((int)(TAM*8.0/7.0)!=(TAM*8.0/7.0))
#define TAM_CODIFICADO_BITS			((TAM + TAM/7)*8) + TAM%7
#define randLim(min,max)			(rand() % (max + 1 - min) + min)
#define bitRead(byte,index)			((byte>>index) & 0x01)
#define setBit(byte,index,bit)		((byte & ~(0x01<<index))|(bit<<index))

// Buffers
unsigned char stream_tx[TAM];
unsigned char tx[TAM_CODIFICADO_BYTES];
unsigned char stream_rx[TAM];
	
// Codifica tudo
void codifica_ascii_visivel(unsigned char *entrada, unsigned char *saida, unsigned short entrada_byte_size){
	unsigned short leitura_byte_idx = 0;
	unsigned short leitura_bit_idx 	= 7;
	unsigned short escrita_byte_idx = 0;
	unsigned short escrita_bit_idx 	= 7;
	while(entrada_byte_size>leitura_byte_idx){
		
		if(escrita_bit_idx==5) {
			saida[escrita_byte_idx] = setBit(saida[escrita_byte_idx],escrita_bit_idx, 1);
		}else{
			saida[escrita_byte_idx] = setBit(saida[escrita_byte_idx],escrita_bit_idx, bitRead(entrada[leitura_byte_idx],leitura_bit_idx));
		}
	
		// Atualiza os índices
		leitura_byte_idx	+= 		(leitura_bit_idx==0) * (escrita_bit_idx!=5);
		escrita_byte_idx	+= 		(escrita_bit_idx==0);
		leitura_bit_idx 	= 		leitura_bit_idx - ((1 - 8*(leitura_bit_idx==0)) * (escrita_bit_idx!=5));
		escrita_bit_idx 	= 		escrita_bit_idx - 1 + 8*(escrita_bit_idx==0);
	}
}

// Codifica tudo
void decodifica_ascii_visivel(unsigned char *entrada, unsigned char *saida, unsigned short entrada_byte_size){
	unsigned short leitura_byte_idx = 0;
	unsigned short leitura_bit_idx 	= 7;
	unsigned short escrita_byte_idx = 0;
	unsigned short escrita_bit_idx 	= 7;
	while(entrada_byte_size>leitura_byte_idx){
		
		if(escrita_bit_idx!=5) {
			saida[leitura_byte_idx] = setBit(saida[leitura_byte_idx],leitura_bit_idx, bitRead(entrada[escrita_byte_idx],escrita_bit_idx));
		}
	
		// Atualiza os índices
		leitura_byte_idx	+= 		(leitura_bit_idx==0) * (escrita_bit_idx!=5);
		escrita_byte_idx	+= 		(escrita_bit_idx==0);
		leitura_bit_idx 	= 		leitura_bit_idx - ((1 - 8*(leitura_bit_idx==0)) * (escrita_bit_idx!=5));
		escrita_bit_idx 	= 		escrita_bit_idx - 1 + 8*(escrita_bit_idx==0);
	}
}

void main() {
	// Força o número aleatório
	srand(time(NULL));

	// Limpa o terminal de comando
	//system("mode 70,30");
	system("color f0");
	system("title Codificacao");
	system("cls");
	printf("\n\r\n\r\t\t*** Inicio do Programa ***\n\r\n\r");	
	
	printf("\tNormal: %d Bytes\n\r",TAM);
	printf("\tCodificado: %d Bytes ou %d bits \n\r",TAM_CODIFICADO_BYTES,TAM_CODIFICADO_BITS);

	// Monta a stream de transmissão
	unsigned short idx;
	for ( idx=0; idx<TAM; idx++)
		stream_tx[idx] = randLim(0, 255);//;
	
	// Realiza a codificação
	codifica_ascii_visivel(&stream_tx, &tx, TAM);

	// Realiza a decodificação
	decodifica_ascii_visivel(&tx, &stream_rx, TAM);
	
	printf("\n\r\tBuffer:\n\r\t-------\n\r\t");
	for ( idx=0; idx<TAM-1; idx++)
		printf("%d, ", stream_tx[idx]);
	printf("%d\n\r\n\r",stream_tx[TAM-1]);
	
	printf("\n\r\tStream:\n\r\t-------\n\r\t");
	for ( idx=0; idx<TAM_CODIFICADO_BYTES-1; idx++)
		printf("%d, ", tx[idx]);
	printf("%d\n\r\n\r",tx[TAM_CODIFICADO_BYTES-1]);

	printf("\n\r\tStream em String:\n\r\t-------\n\r\t");
	for ( idx=0; idx<TAM_CODIFICADO_BYTES; idx++)
		printf("%c", tx[idx]);
	printf("\n\r\n\r");
	
	printf("\n\r\tStream Rx:\n\r\t-------\n\r\t");
	for ( idx=0; idx<TAM-1; idx++)
		printf("%d, ", stream_rx[idx]);
	printf("%d\n\r\n\r",stream_rx[TAM-1]);
	
	printf("\n\r\n\r\t\t*** Fim do Programa ***\n\r");
	
}