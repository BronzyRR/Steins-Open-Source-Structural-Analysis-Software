#include "Ponto.h"
#include <cmath>

//Método construtor que cria um objeto vazio
Ponto::Ponto() {

}

//Método construtor com a posição do ponto em um plano de duas dimensões
Ponto::Ponto(double x, double y) {
	this->x = x;
	this->y = y;
}

//Definir o ponto X do ponto
void Ponto::setX(double x) {
	this->x = x;
}

//Definir o ponto Y do ponto
void Ponto::setY(double y) {
	this->y = y;
}

//Retorna o valor de X do ponto
double Ponto::getX() {
	return this->x;
}

//Retorna o valor de Y do ponto
double Ponto::getY() {
	return this->y;
}

//Retorna a distancia entre dois pontos
double Ponto::distancia(Ponto p1, Ponto p2) {
	double resultado = 0;
	resultado = sqrt(pow((p1.getX() - p2.getX()), 2) + pow((p1.getY() - p2.getY()), 2));
	return resultado;
}

//Retorna a distância entre o ponto objeto atual e outro p2
double Ponto::distancia(Ponto p2) {
	double resultado = 0;
	resultado = sqrt(pow((this->getX() - p2.getX()), 2) + pow((this->getY() - p2.getY()), 2));
	return resultado;
}

//Sobrecarga do símbolo de adição para utilização com pontos
Ponto Ponto::operator+(Ponto p2) {
	double rx, ry;

	rx = this->getX() + p2.getX();
	ry = this->getY() + p2.getY();

	return Ponto(rx, ry);
}

//Sobrecarga do símbolo de subtração para utilização com pontos
Ponto Ponto::operator-(Ponto p2) {
	double rx, ry;
	
	rx = this->getX() - p2.getX();
	ry = this->getY() - p2.getY();

	return Ponto(rx, ry);
}

//Sobrecarga do símbolo de igualdade para utilização com pontos
bool Ponto::operator==(Ponto p2) {
	if ((this->getX() == p2.getX()) && (this->getY() == p2.getY())) {
		return true;
	}
	else {
		return false;
	}
}

//Sobrecarga do símbolo de desigualdade para utilização com pontos
bool Ponto::operator!=(Ponto p2) {
	if ((this->getX() != p2.getX()) || (this->getY() != p2.getY())) {
		return true;
	}
	else {
		return false;
	}
}

