#include "Matriz.h"
#include "Erro.h"
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <exception>

//M�todo construtor sem nada, somento para inicializar
Matriz::Matriz() {

}

//M�todo construtor da matriz, aloca espa�o num vector para uma matriz de dimens�es m x n
Matriz::Matriz(int m, int n) {
	try {
		if ((m < 0) || (n < 0)) { //caso a matriz tenha dimens�es negativas
			throw Erro(100);
		}
		else if ((m == 0) || (n == 0)) { //caso alguma dimens�o seja igual a zero
			throw Erro(103);
		}
		else {
			this->m = m; //n�mero de linhas da matriz
			this->n = n; //n�mero de colunas da matriz
			this->a.resize(m * n); //vector respons�vel por armazenar todos os dados da matriz
		}
	}
	catch (Erro e) {
		std::cout << e.texto() << std::endl;
	}

	
}

//M�todo que ir� retornar a quantidade de linhas (m) da matriz
int Matriz::getM() {
	return this->m;
}

//M�todo que ir� retornar a quantidade de colunas (n) da matriz
int Matriz::getN() {
	return this->n;
}

//M�todo que ir� retornar o vector
std::vector<double> Matriz::getVector() {
	return this->a;
}

//M�todo que ir� definir o vector da matriz
void Matriz::setVector(std::vector<double> v) {
	this->a.clear();
	this->a.shrink_to_fit();
	this->a = v;
}

//M�todo que vai limpar e definir um novo tamanho para o vector do objeto
void Matriz::redimensionarMatriz(int m, int n) {
	try {
		if ((m < 0) || (n < 0)) { //caso a matriz tenha dimens�es negativas
			throw Erro(100); 
		}
		else if ((m==0) || (n==0)){ //caso alguma dimens�o tenha valor zero
			throw Erro(103);
		}
		else {
			this->m = m;
			this->n = n;
			this->a.clear();
			this->a.shrink_to_fit();
			this->a.resize(m * n);
		}
	}
	catch (Erro e) {
		std::cout << e.texto() << std::endl;
	}
}

//M�todo que ir� definir o valor de uma posi��o arbitr�ria a[i,j] da matriz
void Matriz::setValor(int i, int j, double valor) {
	try {
		int linhaLimite = this->getM() - 1;
		int colunaLimite = this->getN() - 1;

		if ((i > linhaLimite) || (j > colunaLimite) || (i < 0) || (j < 0)) { //caso tente acessar um valor fora do escopo da matriz
			throw Erro(101); 
		}
		else {
			int posicao = this->getN() * i + j;
			this->a[posicao] = valor;
		}
	}
	catch (Erro e) {
		std::cout << e.texto() << std::endl;
	}
}

//M�todo que ir� adicionar um valor numa posi��o arbitr�ria a[i,j] da matriz
void Matriz::addValor(int i, int j, double valor) {
	try {
		int linhaLimite = this->getM() - 1;
		int colunaLimite = this->getN() - 1;

		if ((i > linhaLimite) || (j > colunaLimite) || (i < 0) || (j < 0)) { //caso tente acessar um valor fora do escopo da matriz
			throw Erro(101);
		}
		else {
			int posicao = this->getN() * i + j;
			this->a[posicao] += valor;
		}
	}
	catch (Erro e) {
		std::cout << e.texto() << std::endl;
	}
}

//M�todo que ir� retornar o valor de uma posi��o arbitr�ria a[i,j] da matriz
double Matriz::getValor(int i, int j) {
	try {
		int linhaLimite = this->getM() - 1;
		int colunaLimite = this->getN() - 1;

		if ((i > linhaLimite) || (j > colunaLimite) || (i < 0) || (j < 0)) {
			throw Erro(102); 
		}
		else {
			int posicao = this->getN() * i + j;
			return this->a[posicao];
		}
	}
	catch (Erro e) {
		std::cout << e.texto() << std::endl;
	}
}

//Retorna a matriz [vetor] que representa a linha especificada
Matriz Matriz::getLinha(int linha) {
	try {
		int linhaLimite = this->getM() - 1;
		if ((linha > linhaLimite) || (linha < 0)) {
			throw Erro(111);
		}
		else {
			Matriz resultado(1, this->getN());
			
			for (int j = 0; j < this->getN(); j++) {
				resultado.setValor(0, j, this->getValor(linha, j));
			}

			return resultado;
		}

	}
	catch (Erro e) {
		std::cout << e.texto() << std::endl;
	}
}

//Retorna a matriz [vetor] que representa a coluna especificada
Matriz Matriz::getColuna(int coluna) {
	try {
		int colunaLimite = this->getN() - 1;
		if ((coluna > colunaLimite) || (coluna < 0)) {
			throw Erro(112);
		}
		else {
			Matriz resultado(this->getM(), 1);
			for (int i = 0; i < this->getM(); i++) {
				resultado.setValor(i, 0, this->getValor(i, coluna));
			}

			return resultado;
		}
	}
	catch (Erro e) {
		std::cout << e.texto() << std::endl;
	}
}


//M�todo que ir� definir, em uma �nica opera��o, toda uma linha da matriz
void Matriz::setLinha(int linha, Matriz l) {
	try {
		if ((l.getM() != 1) || (l.getN() != this->getN())) {
			throw Erro(109);
		}
		else {
			for (int j = 0; j < this->getN(); j++) {
				this->setValor(linha, j, l.getValor(0, j));
			}
		}
	}
	catch (Erro e) {
		std::cout << e.texto() << std::endl;
	}
}

//M�todo que ir� definir, em uma �nica opera��o, toda uma coluna da matriz
void Matriz::setColuna(int coluna, Matriz c) {
	try {
		if ((c.getN() != 1) || (c.getM() != this->getM())) {
			throw Erro(110);
		}
		else {
			for (int i = 0; i < this->getM(); i++) {
				this->setValor(i, coluna, c.getValor(i, 0));
			}
		}
	}
	catch (Erro e) {
		std::cout << e.texto() << std::endl;
	}
}

//Trocar duas linhas de lugar na matriz 
void Matriz::trocarLinha(int linha1, int linha2) {
	try {
		int linhaLimite = this->getM() - 1;

		if ((linha1 < 0) || (linha1 > linhaLimite) || (linha2 < 0) || (linha2 > linhaLimite)) {
			throw Erro(113);
		}
		else {
			Matriz l1Original = this->getLinha(linha1);
			Matriz l2Original = this->getLinha(linha2);

			this->setLinha(linha1, l2Original);
			this->setLinha(linha2, l1Original);

		}
	}
	catch (Erro e) {
		std::cout << e.texto() << std::endl;
	}
}

//Trocar duas colunas de lugar na matriz
void Matriz::trocarColuna(int coluna1, int coluna2) {
	try {
		int colunaLimite = this->getN() - 1;

		if ((coluna1 < 0) || (coluna1 > colunaLimite) || (coluna2 < 0) || (coluna2 > colunaLimite)) {
			throw Erro(114);
		}
		else {
			Matriz c1Original = this->getColuna(coluna1);
			Matriz c2Original = this->getColuna(coluna2);

			this->setColuna(coluna1, c2Original);
			this->setColuna(coluna2, c1Original);
		}
	}
	catch (Erro e) {
		std::cout << e.texto() << std::endl;
	}
}


//M�todo qu� ir� imprimir os valores da matriz no console. O objetivo � auxiliar no debug
void Matriz::imprimirValores() {
	std::cout.precision(4);

	for (int i = 0; i < this->getM(); i++) {
		std::cout << "|";

		for (int j = 0; j < this->getN(); j++) {
			if (this->getValor(i, j) < 0) {
				std::cout << std::fixed << "    " << this->getValor(i, j);
			}
			else {
				std::cout << std::fixed << "     " << this->getValor(i, j);
			}
		}
		std::cout << "    |\n";
	}
}

//M�todo para ler, atrav�s do console, os dados de uma matriz
void Matriz::lerValores() {
	double auxiliar = 0;
	for (int i = 0; i < this->getM(); i++) {
		for (int j = 0; j < this->getN(); j++) {
			std::cout << "Informe o valor da posicao a[" << i << "," << j << "] = ";
			std::cin >> auxiliar;

			this->setValor(i, j, auxiliar);
		}
	}
}

//M�todo para definir UM �NICO valor para todas as posi��es da matriz
void Matriz::preencher(double valor) {
	for (int i = 0; i < this->getM(); i++) {
		for (int j = 0; j < this->getN(); j++) {
			this->setValor(i, j, valor);
		}
	}
}

//M�todo que ir� retornar uma matriz quadrada identidade com a dimens�o especificada
Matriz Matriz::identidade(int m) {
	Matriz resultado(m, m);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			if (i == j) {
				resultado.setValor(i, j, 1);
			}
			else {
				resultado.setValor(i, j, 0);
			}
		}
	}
	return resultado;
}

//M�todo que ir� retornar a transposta da matriz objeto atual
Matriz Matriz::transposta(Matriz m) {
	Matriz resultado(m.getN(), m.getM());
	for (int i = 0; i < m.getM(); i++) {
		for (int j = 0; j < m.getN(); j++) {
			resultado.setValor(j, i, m.getValor(i, j));
		}
	}
	return resultado;
}

//M�todo que vai retornar a transposta da matriz objeto atual
void Matriz::transpor() {
	int linhaOriginal = this->getM();
	int colunaOriginal = this->getN();

	Matriz backup(this->getM(), this->getN());
	backup.setVector(this->getVector());

	this->redimensionarMatriz(this->getN(), this->getM());

	for (int i = 0; i < linhaOriginal; i++) {
		for (int j = 0; j < colunaOriginal; j++) {
			this->setValor(j, i, backup.getValor(i, j));
		}
	}

}

//M�todo que ir� apagar uma coluna do objeto atual
void Matriz::apagarColuna(int coluna) {
	try {
		if ((coluna < 0) || (coluna > (this->getN() - 1))) { //caso a coluna esteja fora do escopo da matriz
			throw Erro(104);
		}
		else {
			int linhaOriginal = this->getM();
			int colunaOriginal = this->getN();

			Matriz backup(linhaOriginal, colunaOriginal);
			backup.setVector(this->getVector());

			this->redimensionarMatriz(linhaOriginal, colunaOriginal - 1);

			for (int i = 0; i < linhaOriginal; i++) {
				for (int j = 0; j < colunaOriginal; j++) {
					if (j < coluna) {
						this->setValor(i, j, backup.getValor(i, j));
					}
					else if (j == coluna) {
						continue;
					}
					else {
						this->setValor(i, j - 1, backup.getValor(i, j));
					}
				}
			}
		}
	}
	catch (Erro e) {
		std::cout << e.texto() << std::endl;
	}
}

//M�todo que ir� apagar uma linha do objeto atual
void Matriz::apagarLinha(int linha) {
	try {
		if ((linha < 0) || (linha > (this->getM() - 1))) {
			throw Erro(105);
		}
		else {
			int linhaOriginal = this->getM();
			int colunaOriginal = this->getN();

			Matriz backup(linhaOriginal, colunaOriginal);
			backup.setVector(this->getVector());

			this->redimensionarMatriz(linhaOriginal - 1, colunaOriginal);

			for (int i = 0; i < linhaOriginal; i++) {
				for (int j = 0; j < colunaOriginal; j++) {
					if (i < linha) {
						this->setValor(i, j, backup.getValor(i, j));
					}
					else if (i == linha) {
						continue;
					}
					else {
						this->setValor(i - 1, j, backup.getValor(i, j));
					}
				}
			}
		}

	}
	catch (Erro e) {
		std::cout << e.texto() << std::endl;
	}
}

//M�todo est�tico que ir� retornar uma matriz sem a coluna especificada
Matriz Matriz::apagarColuna(Matriz m, int coluna) {
	m.apagarColuna(coluna);
	return m;
}

//M�todo est�tico que ir� retornar uma matriz sem a linha especificada
Matriz Matriz::apagarLinha(Matriz m, int linha) {
	m.apagarLinha(linha);
	return m;
}

//Adaptar o s�mbolo de adi��o para a manipula��o de matrizes
Matriz Matriz::operator+ (Matriz m2) {
	try {
		int linhaMatrizM1 = this->getM();
		int colunaMatrizM1 = this->getN();

		int linhaMatrizM2 = m2.getM();
		int colunaMatrizM2 = m2.getN();

		if ((linhaMatrizM1 != linhaMatrizM2) || (colunaMatrizM1 != colunaMatrizM2)) {
			throw Erro(106);
		}
		else {
			Matriz resultado(this->getM(), this->getN());
			for (int i = 0; i < getM(); i++) {
				for (int j = 0; j < getN(); j++) {
					double somaTermos = this->getValor(i, j) + m2.getValor(i, j);
					resultado.setValor(i, j, somaTermos);
				}
			}

			return resultado;
		}
	}
	catch (Erro e) {
		std::cout << e.texto() << std::endl;
	}
}

//Adaptar o s�mbolo de subtra��o para a manipula��o de matrizes
Matriz Matriz::operator- (Matriz m2) {
	try {
		int linhaMatrizM1 = this->getM();
		int colunaMatrizM1 = this->getN();

		int linhaMatrizM2 = m2.getM();
		int colunaMatrizM2 = m2.getN();

		if ((linhaMatrizM1 != linhaMatrizM2) || (colunaMatrizM1 != colunaMatrizM2)) {
			throw Erro(108);
		}
		else {
			Matriz resultado(this->getM(), this->getN());
			for (int i = 0; i < getM(); i++) {
				for (int j = 0; j < getN(); j++) {
					double resultadoSubtracao = this->getValor(i, j) - m2.getValor(i, j);
					resultado.setValor(i, j, resultadoSubtracao);
				}
			}

			return resultado;
		}
	}
	catch (Erro e) {
		std::cout << e.texto() << std::endl;
	}
}

//Adaptar o s�mbolo de multiplica��o para a manipula��o de matrizes
Matriz Matriz::operator* (Matriz m2) {
	try{
		//O primeiro passo � definir as linhas e colunas de cada uma das matrizes
		int linha_m1 = this->getM();
		int coluna_m1 = this->getN();

		int linha_m2 = m2.getM();
		int coluna_m2 = m2.getN();

		//Primeiro passo � verificar se o n�mero de colunas da primeira matriz � igual ao n�mero de linhas da segunda matriz
		if (coluna_m1 == linha_m2) {
			//A opera��o � v�lida
			Matriz resultado(linha_m1, coluna_m2);

			double cache = 0;
			for (int i = 0; i < linha_m1; i++) { //percorrer cada linha da matriz m1
				for (int k = 0; k < coluna_m2; k++) { //percorrer cada linha da matriz m2
					cache = 0;

					for (int j = 0; j < coluna_m1; j++) { //percorrer cada coluna da matriz m1
						cache += (this->getValor(i, j) * m2.getValor(j, k));
					}

					resultado.setValor(i, k, cache); //salva o valor obtido da multiplica��o no backup
				}
			}
			return resultado;
		}
		else {
			throw Erro(107);
		}
	}
	catch (Erro e) {
		std::cout << e.texto() << std::endl;
	}
} 

//Adaptar o s�mbolo de multiplica��o para permitir a utiliza��o de matrizes com escalares
Matriz Matriz::operator* (double k) {
	Matriz resultado(this->getM(), this->getN());

	for (int i = 0; i < (this->getM()); i++) {
		for (int j = 0; j < (this->getN()); j++) {
			resultado.setValor(i, j, this->getValor(i, j) * k);
		}
	}

	return resultado;
}

//Adaptar o s�mbolo de divis�o para permitir a utiliza��o de matrizes com escalares
Matriz Matriz::operator/ (double k) {
	Matriz resultado(this->getM(), this->getN());

	for (int i = 0; i < (this->getM()); i++) {
		for (int j = 0; j < (this->getN()); j++) {
			resultado.setValor(i, j, this->getValor(i, j) / k);
		}
	}

	return resultado;
}

//Adaptar o s�mbolo de incremento para a manipula��o de matrizes
void Matriz::operator+= (Matriz m2) {
	try {
		int linhaMatrizM1 = this->getM();
		int colunaMatrizM1 = this->getN();

		int linhaMatrizM2 = m2.getM();
		int colunaMatrizM2 = m2.getN();

		if ((linhaMatrizM1 != linhaMatrizM2) || (colunaMatrizM1 != colunaMatrizM2)) {
			throw Erro(106);
		}
		else {
			for (int i = 0; i < getM(); i++) {
				for (int j = 0; j < getN(); j++) {
					double somaTermos = this->getValor(i, j) + m2.getValor(i, j);
					this->setValor(i, j, somaTermos);
				}
			}
		}
	}
	catch (Erro e) {
		std::cout << e.texto() << std::endl;
	}
}

//Adaptar o s�mbolo de decremento para a manipula��o de matrizes
void Matriz::operator-=(Matriz m2) {
	try {
		int linhaMatrizM1 = this->getM();
		int colunaMatrizM1 = this->getN();

		int linhaMatrizM2 = m2.getM();
		int colunaMatrizM2 = m2.getN();

		if ((linhaMatrizM1 != linhaMatrizM2) || (colunaMatrizM1 != colunaMatrizM2)) {
			throw Erro(108);
		}
		else {
			for (int i = 0; i < this->getM(); i++) {
				for (int j = 0; j < this->getN(); j++) {
					double resultadoSubtracao = this->getValor(i, j) - m2.getValor(i, j);
					this->setValor(i, j, resultadoSubtracao);
				}
			}
		}
	}
	catch (Erro e) {
		std::cout << e.texto() << std::endl;
	}
}

//Adaptar o s�mbolo de igualdade para a manipula��o de matrizes
bool Matriz::operator== (Matriz m2) {
	bool resultado = true; //original o resultado � verdadeiro

	int linha_m1 = this->getM();
	int coluna_m1 = this->getN();
	int linha_m2 = this->getM();
	int coluna_m2 = this->getN();

	if ((linha_m1 == linha_m2) && (coluna_m1 == coluna_m2)) {
		//as matrizes possuem as mesmas dimens�es e podem ser comparadas
		for (int i = 0; i < linha_m1; i++) {
			for (int j = 0; j < coluna_m1; j++) {
				if (this->getValor(i, j) != m2.getValor(i, j)) {
					resultado = false;
					break;
				}
			}
		}
	
	}
	else {
		//as matrizes n�o possuem as mesmas dimens�es, logo o resultado � falso, pois elas s�o diferentes
		resultado = false;
	}

	return resultado;
}

//Adaptar o s�mbolo de "diferente" para a manipula��o de matrizes
bool Matriz::operator!= (Matriz m2) {
	bool resultado = false; //inicialmente � falso, pois se assume que as matrizes s�o iguais

	int linha_m1 = this->getM();
	int coluna_m1 = this->getN();
	int linha_m2 = this->getM();
	int coluna_m2 = this->getN();

	if ((linha_m1 == linha_m2) && (coluna_m1 == coluna_m2)) {
		//as matrizes possuem as mesmas dimens�es e podem ser comparadas
		for (int i = 0; i < linha_m1; i++) {
			for (int j = 0; j < coluna_m1; j++) {
				if (this->getValor(i, j) != m2.getValor(i, j)) {
					resultado = true;
					break;
				}
			}
		}
	}
	else {
		//as matrizes n�o possuem as mesmas dimens�es, logo o resultado � verdadeiro, pois elas s�o diferentes
		resultado = true;
	}
	return resultado;
}

