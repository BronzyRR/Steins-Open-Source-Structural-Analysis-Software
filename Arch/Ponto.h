#pragma once
class Ponto
{
private:
	double x;
	double y;

public:
	//M�TODO CONSTRUTOR
	Ponto();
	Ponto(double x, double y);

	//M�TODOS GETTERS E SETTERS
	void setX(double x); 
	double getX();
	void setY(double y);
	double getY();

	//M�TODOS MATEM�TICOS
	static double distancia(Ponto p1, Ponto p2); //vai retornar a distancia entre dois pontos
	double distancia(Ponto p2); //vai retornar a distancia entre o ponto objeto atual e outro ponto p2
	
	//SOBRECARGA DOS OPERADORES
	Ponto operator+(Ponto p2); //adaptar o s�mbolo de adi��o para utiliza��o com n�s
	Ponto operator-(Ponto p2); //adaptar o s�mbolo de subtra��o para utiliza��o com n�s
	bool operator==(Ponto p2); //adaptar o s�mbolo de igualdade para utiliza��o com n�s
	bool operator!=(Ponto p2); //adaptar o s�mbolo de desigualdade para utiliza��o com n�s

};

