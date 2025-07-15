#pragma once
class Ponto
{
private:
	double x;
	double y;

public:
	//MÉTODO CONSTRUTOR
	Ponto();
	Ponto(double x, double y);

	//MÉTODOS GETTERS E SETTERS
	void setX(double x); 
	double getX();
	void setY(double y);
	double getY();

	//MÉTODOS MATEMÁTICOS
	static double distancia(Ponto p1, Ponto p2); //vai retornar a distancia entre dois pontos
	double distancia(Ponto p2); //vai retornar a distancia entre o ponto objeto atual e outro ponto p2
	
	//SOBRECARGA DOS OPERADORES
	Ponto operator+(Ponto p2); //adaptar o símbolo de adição para utilização com nós
	Ponto operator-(Ponto p2); //adaptar o símbolo de subtração para utilização com nós
	bool operator==(Ponto p2); //adaptar o símbolo de igualdade para utilização com nós
	bool operator!=(Ponto p2); //adaptar o símbolo de desigualdade para utilização com nós

};

