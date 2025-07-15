#pragma once
#include <vector>

/*
A classe Matriz foi criada com o intuito de servir como base matemática do programa de cálculo estrutural Steins. Afinal,
grande parte das operações do método dos elementos finitos pode ser descrita através de matrizes, as quais são simples de
serem representadas em um computador.

No caso, programou-se diversos métodos que facilitariam a implementação do MEF. Alguns exemplos são: operações básicas
de matrizes através da sobrecarga de operadores (adição, multiplicação, etc.), obtenção da matriz transposta (para transformação
de coordenadas locais-globais e vice-versa), eliminação de linhas e colunas de uma matriz (para obtenção da matriz do sistema/pórtico)
etc.
*/


class Matriz {
private:
	int m; //número de linhas da matriz
	int n; //número de colunas da matriz
	std::vector<double> a; //vetor que irá guardar todos os dados da matriz

	void setVector(std::vector<double> v); //método que irá definir os valores do vector da classe
	std::vector<double> getVector(); //método que irá retornar o vector
	

public:
	Matriz(); //método construtor sem nada
	Matriz(int m, int n); //método construtor da matriz, vai alocar espaço para uma matriz m x n

	//SEÇÃO DOS MÉTODOS GETTERS E SETTERS
	int getM(); //método que irá retornar o número de linhas da matriz
	int getN(); //método que irá retornar o número de colunas da matriz
	void setValor(int i, int j, double valor); //método que irá definir o valor numa posição arbitrária a[i,j] da matriz
	double getValor(int i, int j); //método que irá retornar o valor de uma posição arbitrária a[i,j] da matriz
	void addValor(int i, int j, double valor); //vai adicionar um valor numa posição arbitrária a[i,j] da matriz

	//Retorna a matriz [vetor] que representa a linha especificada
	Matriz getLinha(int linha);
	
	//Retorna a matriz [vetor] que representa a coluna especificada
	Matriz getColuna(int coluna);

	//Definir uma linha inteira da matriz de uma vez
 	void setLinha(int linha, Matriz l); 

	//definir uma coluna inteira da matriz de uma vez
	void setColuna(int coluna, Matriz c); 

	//Trocar duas linhas de lugar na matriz 
	void trocarLinha(int linha1, int linha2);

	//Trocar duas colunas de lugar na matriz
	void trocarColuna(int coluna1, int coluna2);

	//SEÇÃO DE LEITURA/IMPRESSÃO DOS DADOS
	void imprimirValores(); //método para imprimir os valores da matriz no console
	void lerValores(); //método para ler, através do console, os valores da matriz

	//SEÇÃO DE MÉTODOS MATEMÁTICOS GERAIS COM MATRIZES
	void preencher(double valor); //método para definir UM ÚNICO valor para todas as posições da matriz
	static Matriz identidade(int m); //método que irá retornar uma matriz quadrada identidade com a dimensão especificada
	static Matriz transposta(Matriz m); //método que irá retornar a transposta do objeto atual
	void transpor(); //método que irá retornar a transposta do objeto atual
	void apagarColuna(int coluna); //método que irá apagar uma coluna do objeto atual
	void apagarLinha(int linha); //método que irá apagar uma linha do objeto atual
	static Matriz apagarColuna(Matriz m, int coluna); //método estático que irá retornar uma matriz sem a coluna especificada
	static Matriz apagarLinha(Matriz m, int linha); //método estático que irá retornar uma matriz sem a linha especificada
	void redimensionarMatriz(int m, int n); //método que vai limpar e definir um novo tamanho para o vector do objeto

	//SEÇÃO DE SOBRECARGA DOS OPERADORES
	Matriz operator+ (Matriz m2); //adaptar o símbolo de adição para permitir a utilização com matrizes
	Matriz operator- (Matriz m2); //adaptar o símbolo de subtração para permitir a utilização com matrizes
	Matriz operator* (Matriz m2); //adaptar o símbolo de multiplicação para permitir a utilização com matrizes
	Matriz operator* (double k); //adaptar o símbolo de multiplicação para permitir a utilização de matrizes com escalares
	Matriz operator/ (double k); //adaptar o símbolo de divisão para permitir a utilização de matrizes com escalares
	void operator+= (Matriz m2); //Adaptar o símbolo de incremento para permitir a utilização com matrizes
	void operator-= (Matriz m2); //Adaptar o símbolo de decremento para permitir a utilização com matrizes
	bool operator== (Matriz m2); //Adaptar o símbolo de igualdade para permitir a utilização com matrizes
	bool operator!= (Matriz m2); //Adaptar o símbolo de "diferente" para permitir a utilização com matrizes

};