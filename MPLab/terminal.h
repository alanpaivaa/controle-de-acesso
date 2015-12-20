#ifndef TERMINAL_H_INCLUDED
#define TERMINAL_H_INCLUDED

// Definicoes

/** Escreve uma letra no terminal */
void terminalEscreveLetra(char letra);

/** Escreve uma linha no terminal */
void terminalEscreveLinha(char *linha, int tamanho);

/** Escreve no terminal que uma pessoa tentou realizar um login */
void terminalEscreveTentativaLogin();

/** Escreve no terminal que um usuario conseguiu acesso */
void terminalEscreveLoginRealizado(char usuario);

/** Pega o momento do log */
void terminalMomentLog(char *log);

/** Log de que um usuario foi cadastrado */
void terminalUsuarioCadastrado(char usuario);

/** Log de que um usuario foi deletado */
void terminalUsuarioDeletado(char usuario);

/** Log de quando se tenta deletar um usuario inexistente */
void terminalEscreveTentativaDelecao();

// Implementacoes

void terminalEscreveLetra(char letra) {

		char aux;
		char mask = 0b10000000;
		char delay = 20;

		TERMINAL = 1;
		Delay10TCYx(delay);

		TERMINAL = 0;
		Delay10TCYx(delay);

		aux = (letra << 7) & mask;
		aux = aux >> 7;
		TERMINAL = aux; // 1
		Delay10TCYx(delay);

		aux = (letra << 6) & mask;
		aux = aux >> 7;
		TERMINAL = aux; // 2
		Delay10TCYx(delay);

		aux = (letra << 5) & mask;
		aux = aux >> 7;			
		TERMINAL = aux; //3
		Delay10TCYx(delay);

		aux = (letra << 4) & mask;
		aux = aux >> 7;
		TERMINAL = aux; //4
		Delay10TCYx(delay);

		aux = (letra << 3) & mask;
		aux = aux >> 7;
		TERMINAL = aux; //5
		Delay10TCYx(delay);

		aux = (letra << 2) & mask;
		aux = aux >> 7;
		TERMINAL = aux; //6
		Delay10TCYx(delay);

		aux = (letra << 1) & mask;
		aux = aux >> 7;
		TERMINAL = aux; //7
		Delay10TCYx(delay);

		aux = letra & mask;
		aux = aux >> 7;
		TERMINAL = aux; //8
		Delay10TCYx(delay);

		TERMINAL = 1; // 1111
		Delay10TCYx(20);

}

void terminalEscreveLinha(char *linha, int tamanho) {
	int i;
	for(i=0; i<tamanho; i++) {
		terminalEscreveLetra(linha[i]);
	}
	terminalEscreveLetra(13);
}

void terminalEscreveTentativaLogin() {
	char linha[42];
	char str[] = "Tentativa de login";
	terminalMomentLog(linha);
	strcpy(linha + 23, str);
	terminalEscreveLinha(linha, 41);
}

void terminalEscreveLoginRealizado(char usuario) {
	char linha[50];
	char str[] = "Usuario X conseguiu acesso";
	terminalMomentLog(linha);
	strcpy(linha + 23, str);
	linha[31] = usuario + 48;
	terminalEscreveLinha(linha, 49);
}

void terminalUsuarioCadastrado(char usuario) {
	char linha[44];
	char str[] = "Usuario X cadastrado";
	terminalMomentLog(linha);
	strcpy(linha + 23, str);
	linha[31] = usuario + 48;
	terminalEscreveLinha(linha, 43);
}

void terminalMomentLog(char *log) {
	rtcLeData(log);
	log[20] = ' ';
	log[21] = '-';
	log[22] = ' ';
}

void terminalUsuarioDeletado(char usuario) {
	char linha[42];
	char str[] = "Usuario X deletado";
	terminalMomentLog(linha);
	strcpy(linha + 23, str);
	linha[31] = usuario + 48;
	terminalEscreveLinha(linha, 41);
}

void terminalEscreveTentativaDelecao() {
	char linha[44];
	char str[] = "Tentativa de delecao";
	terminalMomentLog(linha);
	strcpy(linha + 23, str);
	terminalEscreveLinha(linha, 43);
}

#endif