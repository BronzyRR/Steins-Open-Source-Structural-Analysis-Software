#include "Erro.h"
#include <string>

//Os erros que começam em 1 são referentes a matrizes
//Os erros que começam em 2 são referentes a sistemas lineares
//Os erros que começam em 3 são referentes as equações polinomiais
//Os erros que começam em 4 são referentes as barras da estrutura
//Os erros que começam em 5 são referentes ao gerador de arquivos

Erro::Erro(int codigo) {
	switch (codigo) {
		case 100:
			this->setMensagem("ERRO: A matriz nao pode ter dimensoes negativas.");
			break;
		case 101:
			this->setMensagem("ERRO: Houve a tentativa de inserir um valor em uma posicao fora do escopo da matriz.");
			break;
		case 102:
			this->setMensagem("ERRO: Houve a tentativa de acessar um valor em uma posicao fora do escopo da matriz.");
			break;
		case 103:
			this->setMensagem("ERRO: Todas as dimensoes da matriz devem possuir valor diferente de zero.");
			break;
		case 104:
			this->setMensagem("ERRO: Houve a tentativa de apagar uma coluna fora do escopo da matriz.");
			break;
		case 105:
			this->setMensagem("ERRO: Houve a tentativa de apagar uma linha fora do escopo da matriz.");
			break;
		case 106:
			this->setMensagem("ERRO: Para realizar a soma as matrizes devem possuir as mesmas dimensoes.");
			break;
		case 107:
			this->setMensagem("ERRO: Para realizar a multiplicacao, o numero de colunas da primeira matriz deve ser igual ao numero de linhas da segunda.");
			break;
		case 108:
			this->setMensagem("ERRO: Para realizar a subtracao as matrizes devem possuir as mesmas dimensoes.");
			break;
		case 109:
			this->setMensagem("ERRO: O vetor linha deve ter o mesmo número de colunas que a matriz.");
			break;
		case 110:
			this->setMensagem("ERRO: O vetor coluna deve ter o mesmo número de linhas que a matriz.");
			break;
		case 111:
			this->setMensagem("ERRO: Houve a tentativa de se obter uma linha fora do escopo da matriz.");
			break;
		case 112:
			this->setMensagem("ERRO: Houve a tentativa de se obter uma coluna fora do escopo da matriz.");
			break;
		case 113:
			this->setMensagem("ERRO: Houve a tentativa de trocar linhas fora do escopo da matriz.");
			break;
		case 114:
			this->setMensagem("ERRO: Houve a tentativa de trocar colunas fora do escopo da matriz.");
			break;
		case 201:
			this->setMensagem("ERRO: A matriz dos coeficientes e dos resultados devem possuir dimensoes adequadas.");
			break;
		case 301:
			this->setMensagem("ERRO: A função não pode ter grau negativo.");
			break;
		case 302:
			this->setMensagem("ERRO: Houve a tentativa de acessar uma posicao fora do escopo da EQUACAO.");
			break;
		case 303:
			this->setMensagem("ERRO: A matriz dos coeficientes deve ter dimensoes adequadas!");
			break;
		case 401:
			this->setMensagem("ERRO: A barra nao pode ter dois pontos iguais!");
			break;
		case 501:
			this->setMensagem("ERRO: Nao foi possivel criar o arquivo!");
			break;
	}
}

void Erro::setMensagem(std::string mensagem) {
	this->mensagem = mensagem;
}

std::string Erro::texto() {
	return this->mensagem;
}