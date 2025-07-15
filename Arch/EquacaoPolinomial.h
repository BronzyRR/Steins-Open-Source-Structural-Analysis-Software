#pragma once
#include "Matriz.h"
#include <string>
/*
O objetivo dessa classe é servir (como o próprio nome indica) como uma função polinomial. Através dela,
será possível obter os valores da função para um ponto x qualquer, suas derivadas e realizar operações
básicas entre elas.

Através de sua utilização, será possível descrever os esforços internos em um elemento de barra, ou seja,
descrever as equações de deslocamento, rotação, momento fletor, esforço cortante e carregamento.

*/
class EquacaoPolinomial 
{
private:
	int grau; //qual o grau da função. Se é quadrática, cúbica, etc.
	int tamanho; //tamanho efetivo do vetor da equação, no caso, é grau + 1

	Matriz coeficiente; //coeficientes da função

public:
	
	//MÉTODOS CONSTRUTORES
	EquacaoPolinomial(); //método construtor vazio
	EquacaoPolinomial(int g); //método construtor da equação
	EquacaoPolinomial(Matriz c); //método construtor através de uma matriz com os coeficientes	

	//DERIVADAS
	EquacaoPolinomial derivada(); //vai retornar a derivada da função do objeto atual
	void derivar(); //vai transformar o objeto atual em sua derivada

	//ACESSAR VALORES
	double valor(double x); //vai retornar o valor da função em um ponto x específico
	
	//MÉTODOS GETTERS E SETTERS
	void setCoeficiente(int posicao, double c); //definir o valor do coeficiente de uma posição específica
	double getCoeficiente(int posicao); //retorna o valor do coeficiente numa posição específica
	int getGrau(); //retorna o valor do grau da função
	int getTamanho(); //retorna o tamanho efetivo do vetor da equação
	void setVetorCoeficiente(Matriz c); //definir o vetor dos coeficientes através de uma matriz
	Matriz getVetorCoeficiente(); //retorna o vetor coeficiente da matriz

	//IMPRIMIR NO CONSOLE
	void imprimir(); //mostra a equação na tela
	std::string getString(); //vai retornar a string que representa a equação

	//SEÇÃO DE SOBRECARGA DOS OPERADORES
	EquacaoPolinomial operator+(EquacaoPolinomial ep2); //adaptar o símbolo de adição para utilização com as equações
	EquacaoPolinomial operator-(EquacaoPolinomial ep2); //adaptar o símbolo de subtração para utilização com as equações
	EquacaoPolinomial operator*(EquacaoPolinomial ep2); //adaptar o símbolo de multiplicação para utilização com as equações
	EquacaoPolinomial operator*(double k); //adaptar o símbolo de mutliplicação para utilização com equações e escalares
	bool operator==(EquacaoPolinomial ep2); //adaptar o símbolo de igualdade para utilização com equações
	bool operator!=(EquacaoPolinomial ep2); //adaptar o símbolo de desiguldade para utilização com equações

};

