#include "EquacaoPolinomial.h"
#include <iostream>
#include "Matriz.h"
#include "Erro.h"

//Método construtor vazio
EquacaoPolinomial::EquacaoPolinomial() {

}

//Método construtor de uma função de grau g qualquer
EquacaoPolinomial::EquacaoPolinomial(int g){
	try {
		if (g < 0) {
			throw Erro(301);
		}
		else {
			this->grau = g;
			this->tamanho = g + 1;
			this->coeficiente = Matriz(1, this->tamanho);
			this->coeficiente.preencher(0);
		}
	}
	catch (Erro e) {
		std::cout << e.texto() << std::endl;
	}	
}

//Método construtor de uma função através de uma matriz de coeficientes
EquacaoPolinomial::EquacaoPolinomial(Matriz c) {
	try {
		if ((c.getM() != 1) || (c.getN()==0)) {
			throw Erro(303);
		}
		else {
			this->tamanho = c.getN();
			this->grau = c.getN() - 1;
			this->coeficiente = c;

		}
	}
	catch (Erro e) {
		std::cout << e.texto() << std::endl;
	}
}

//Retorna o valor da função para uma posição específica de x
double EquacaoPolinomial::valor(double x) {
	double resultado = 0;
	for (int i = 0; i < this->tamanho; i++) {
		if (i == 0) {
			resultado += coeficiente.getValor(0, i);
		}
		else {
			resultado += pow(x, i) * coeficiente.getValor(0, i);
		}
	}

	return resultado;
}

//Definir um coeficiente da função
void EquacaoPolinomial::setCoeficiente(int posicao, double c) {
	try {
		if ((posicao < 0) || (posicao > grau)) {
			throw Erro(302);
		}
		else {
			this->coeficiente.setValor(0, posicao, c);
		}
	}
	catch (Erro e) {
		std::cout << e.texto() << std::endl;
	}
}

//Retorna o coeficiente de uma posição específica da função
double EquacaoPolinomial::getCoeficiente(int posicao) {
	try {
		if ((posicao < 0) || (posicao > grau)) {
			throw Erro(302);
		}
		else {
			return this->coeficiente.getValor(0, posicao);
		}
	}
	catch (Erro e) {
		std::cout << e.texto() << std::endl;
	}
}

//Retorna o grau da função
int EquacaoPolinomial::getGrau() {
	return this->grau;
}

//Retorna o tamanho do vetor da função (grau + 1)
int EquacaoPolinomial::getTamanho() {
	return this->tamanho;
}

//Definir o vetor dos coeficientes através de uma matriz
void EquacaoPolinomial::setVetorCoeficiente(Matriz c) {
	try {
		if (c.getN() == this->getTamanho()) {
			for (int i = 0; i < this->getTamanho(); i++) {
				this->setCoeficiente(i, c.getValor(0, i));
			}
		}
		else {
			throw Erro(303);
		}
	}
	catch (Erro e) {
		std::cout << e.texto() << std::endl;
	}
}

//Retorna o vetor dos coeficientes da equação
Matriz EquacaoPolinomial::getVetorCoeficiente() {
	return this->coeficiente;
}

//Imprime a função no console
void EquacaoPolinomial::imprimir() {
	for (int i = 0; i < this->tamanho; i++) {
		if (i == 0) {
			std::cout << coeficiente.getValor(0, i);
		}
		else {
			if (coeficiente.getValor(0, i) < 0) {
				std::cout << " - " << abs(coeficiente.getValor(0, i)) << "*x^" << i;
			}
			else {
				std::cout << " + " << coeficiente.getValor(0, i) << "*x^" << i;
			}
		}
	}

	std::cout << std::endl;
}

//Vai retornar a string que representa a função
std::string EquacaoPolinomial::getString() {
	std::string resultado = "";

	for (int i = 0; i < this->tamanho; i++) {
		if (i == 0) {
			resultado += std::to_string(coeficiente.getValor(0, i));
		}
		else {
			if (coeficiente.getValor(0, i) < 0) {
				resultado += " - " + std::to_string(abs(coeficiente.getValor(0, i))) + "*x^" + std::to_string(i);
			}
			else {
				resultado += " + " + std::to_string(coeficiente.getValor(0, i)) + "*x^" + std::to_string(i);
			}
		}
	}

	resultado += "\n";
	return resultado;
}

//Retorna a derivada da função
EquacaoPolinomial EquacaoPolinomial::derivada() {

	EquacaoPolinomial resultado((this->grau - 1));
	
	double termoDerivada = 0;
	for (int i = 1; i < this->tamanho; i++) { //pula a primeira posição, referente a constante
		termoDerivada = (this->getCoeficiente(i)) * i;
		resultado.setCoeficiente((i - 1), termoDerivada);
	}

	return resultado;
}

//Transforma o objeto atual em sua derivada
void EquacaoPolinomial::derivar() {
	*this = this->derivada();
}

//Adaptar o símbolo de adição para utilização com equações
EquacaoPolinomial EquacaoPolinomial::operator+ (EquacaoPolinomial ep2) {
	int grau1 = this->getGrau();
	int grau2 = ep2.getGrau();

	if (grau1 > grau2) {
		EquacaoPolinomial resultado(grau1);

		double somaCoeficientes = 0;
		for (int i = 0; i < ep2.getTamanho(); i++) {
			somaCoeficientes = this->getCoeficiente(i) + ep2.getCoeficiente(i);
			resultado.setCoeficiente(i, somaCoeficientes);
		}

		return resultado;
	}
	else {
		EquacaoPolinomial resultado(grau2);

		double somaCoeficientes = 0;
		for (int i = 0; i < this->getTamanho(); i++) {
			somaCoeficientes = this->getCoeficiente(i) + ep2.getCoeficiente(i);
			resultado.setCoeficiente(i, somaCoeficientes);
		}

		return resultado;
	}
}

//Adaptar o símbolo de subtração para a utilização com equações
EquacaoPolinomial EquacaoPolinomial::operator- (EquacaoPolinomial ep2) {
	int grau1 = this->getGrau();
	int grau2 = ep2.getGrau();

	if (grau1 > grau2) {
		EquacaoPolinomial resultado(grau1);

		double somaCoeficientes = 0;
		for (int i = 0; i < ep2.getTamanho(); i++) {
			somaCoeficientes = this->getCoeficiente(i) - ep2.getCoeficiente(i);
			resultado.setCoeficiente(i, somaCoeficientes);
		}

		return resultado;
	}
	else {
		EquacaoPolinomial resultado(grau2);

		double somaCoeficientes = 0;
		for (int i = 0; i < this->getTamanho(); i++) {
			somaCoeficientes = this->getCoeficiente(i) - ep2.getCoeficiente(i);
			resultado.setCoeficiente(i, somaCoeficientes);
		}

		return resultado;
	}
}

//Adaptar o símbolo de multiplicação para a utilização com equações
EquacaoPolinomial EquacaoPolinomial::operator* (EquacaoPolinomial ep2) {
	int grau1 = this->getGrau();
	int grau2 = ep2.getGrau();
	
	int grauResultado = grau1 + grau2;

	EquacaoPolinomial resultado(grauResultado);
	
	for (int i = 0; i < this->getTamanho(); i++) {
		for (int j = 0; j < ep2.getTamanho(); j++) {
			int posicao = i + j; //grau do termo resultante
			double resultadoMultiplicacao = this->getCoeficiente(i) * ep2.getCoeficiente(j);

			resultado.setCoeficiente(posicao, (resultado.getCoeficiente(posicao) + resultadoMultiplicacao));
		}
	}
	
	return resultado;
}

//Adaptar o símbolo de multiplicação para a utilização com equações e escalares
EquacaoPolinomial EquacaoPolinomial::operator*(double k) {
	EquacaoPolinomial resultado(this->getGrau());

	for (int i = 0; i < this->getTamanho(); i++) {
		resultado.setCoeficiente(i, (this->getCoeficiente(i) * k));
	}

	return resultado;
}

//Adaptar o símbolo de igualdade para a utilização com equações
bool EquacaoPolinomial::operator==(EquacaoPolinomial ep2) {
	//o primeiro passo é verificar se tem o mesmo grau
	bool resultado = true;

	int grau1 = this->getGrau();
	int grau2 = ep2.getGrau();

	if (grau1 == grau2) {
		for (int i = 0; i < this->getTamanho(); i++) {
			if (this->getCoeficiente(i) != ep2.getCoeficiente(i)) {
				resultado = false;
				break;
			}
		}
	}
	else {
		resultado = false;
	}
	return resultado;
}

//Adaptar o símbolo de desigualdade para a utilização com equações
bool EquacaoPolinomial::operator!=(EquacaoPolinomial ep2) {
	//o primeiro passo é verificar se tem o mesmo grau
	bool resultado = false;

	int grau1 = this->getGrau();
	int grau2 = ep2.getGrau();

	if (grau1 == grau2) {
		for (int i = 0; i < this->getTamanho(); i++) {
			if (this->getCoeficiente(i) != ep2.getCoeficiente(i)) {
				resultado = true;
				break;
			}
		}
	}
	else {
		resultado = true;
	}
	return resultado;
}

