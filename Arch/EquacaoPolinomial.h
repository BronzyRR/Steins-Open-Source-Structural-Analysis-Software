#pragma once
#include "Matriz.h"
#include <string>
/*
O objetivo dessa classe � servir (como o pr�prio nome indica) como uma fun��o polinomial. Atrav�s dela,
ser� poss�vel obter os valores da fun��o para um ponto x qualquer, suas derivadas e realizar opera��es
b�sicas entre elas.

Atrav�s de sua utiliza��o, ser� poss�vel descrever os esfor�os internos em um elemento de barra, ou seja,
descrever as equa��es de deslocamento, rota��o, momento fletor, esfor�o cortante e carregamento.

*/
class EquacaoPolinomial 
{
private:
	int grau; //qual o grau da fun��o. Se � quadr�tica, c�bica, etc.
	int tamanho; //tamanho efetivo do vetor da equa��o, no caso, � grau + 1

	Matriz coeficiente; //coeficientes da fun��o

public:
	
	//M�TODOS CONSTRUTORES
	EquacaoPolinomial(); //m�todo construtor vazio
	EquacaoPolinomial(int g); //m�todo construtor da equa��o
	EquacaoPolinomial(Matriz c); //m�todo construtor atrav�s de uma matriz com os coeficientes	

	//DERIVADAS
	EquacaoPolinomial derivada(); //vai retornar a derivada da fun��o do objeto atual
	void derivar(); //vai transformar o objeto atual em sua derivada

	//ACESSAR VALORES
	double valor(double x); //vai retornar o valor da fun��o em um ponto x espec�fico
	
	//M�TODOS GETTERS E SETTERS
	void setCoeficiente(int posicao, double c); //definir o valor do coeficiente de uma posi��o espec�fica
	double getCoeficiente(int posicao); //retorna o valor do coeficiente numa posi��o espec�fica
	int getGrau(); //retorna o valor do grau da fun��o
	int getTamanho(); //retorna o tamanho efetivo do vetor da equa��o
	void setVetorCoeficiente(Matriz c); //definir o vetor dos coeficientes atrav�s de uma matriz
	Matriz getVetorCoeficiente(); //retorna o vetor coeficiente da matriz

	//IMPRIMIR NO CONSOLE
	void imprimir(); //mostra a equa��o na tela
	std::string getString(); //vai retornar a string que representa a equa��o

	//SE��O DE SOBRECARGA DOS OPERADORES
	EquacaoPolinomial operator+(EquacaoPolinomial ep2); //adaptar o s�mbolo de adi��o para utiliza��o com as equa��es
	EquacaoPolinomial operator-(EquacaoPolinomial ep2); //adaptar o s�mbolo de subtra��o para utiliza��o com as equa��es
	EquacaoPolinomial operator*(EquacaoPolinomial ep2); //adaptar o s�mbolo de multiplica��o para utiliza��o com as equa��es
	EquacaoPolinomial operator*(double k); //adaptar o s�mbolo de mutliplica��o para utiliza��o com equa��es e escalares
	bool operator==(EquacaoPolinomial ep2); //adaptar o s�mbolo de igualdade para utiliza��o com equa��es
	bool operator!=(EquacaoPolinomial ep2); //adaptar o s�mbolo de desiguldade para utiliza��o com equa��es

};

