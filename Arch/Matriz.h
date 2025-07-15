#pragma once
#include <vector>

/*
A classe Matriz foi criada com o intuito de servir como base matem�tica do programa de c�lculo estrutural Steins. Afinal,
grande parte das opera��es do m�todo dos elementos finitos pode ser descrita atrav�s de matrizes, as quais s�o simples de
serem representadas em um computador.

No caso, programou-se diversos m�todos que facilitariam a implementa��o do MEF. Alguns exemplos s�o: opera��es b�sicas
de matrizes atrav�s da sobrecarga de operadores (adi��o, multiplica��o, etc.), obten��o da matriz transposta (para transforma��o
de coordenadas locais-globais e vice-versa), elimina��o de linhas e colunas de uma matriz (para obten��o da matriz do sistema/p�rtico)
etc.
*/


class Matriz {
private:
	int m; //n�mero de linhas da matriz
	int n; //n�mero de colunas da matriz
	std::vector<double> a; //vetor que ir� guardar todos os dados da matriz

	void setVector(std::vector<double> v); //m�todo que ir� definir os valores do vector da classe
	std::vector<double> getVector(); //m�todo que ir� retornar o vector
	

public:
	Matriz(); //m�todo construtor sem nada
	Matriz(int m, int n); //m�todo construtor da matriz, vai alocar espa�o para uma matriz m x n

	//SE��O DOS M�TODOS GETTERS E SETTERS
	int getM(); //m�todo que ir� retornar o n�mero de linhas da matriz
	int getN(); //m�todo que ir� retornar o n�mero de colunas da matriz
	void setValor(int i, int j, double valor); //m�todo que ir� definir o valor numa posi��o arbitr�ria a[i,j] da matriz
	double getValor(int i, int j); //m�todo que ir� retornar o valor de uma posi��o arbitr�ria a[i,j] da matriz
	void addValor(int i, int j, double valor); //vai adicionar um valor numa posi��o arbitr�ria a[i,j] da matriz

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

	//SE��O DE LEITURA/IMPRESS�O DOS DADOS
	void imprimirValores(); //m�todo para imprimir os valores da matriz no console
	void lerValores(); //m�todo para ler, atrav�s do console, os valores da matriz

	//SE��O DE M�TODOS MATEM�TICOS GERAIS COM MATRIZES
	void preencher(double valor); //m�todo para definir UM �NICO valor para todas as posi��es da matriz
	static Matriz identidade(int m); //m�todo que ir� retornar uma matriz quadrada identidade com a dimens�o especificada
	static Matriz transposta(Matriz m); //m�todo que ir� retornar a transposta do objeto atual
	void transpor(); //m�todo que ir� retornar a transposta do objeto atual
	void apagarColuna(int coluna); //m�todo que ir� apagar uma coluna do objeto atual
	void apagarLinha(int linha); //m�todo que ir� apagar uma linha do objeto atual
	static Matriz apagarColuna(Matriz m, int coluna); //m�todo est�tico que ir� retornar uma matriz sem a coluna especificada
	static Matriz apagarLinha(Matriz m, int linha); //m�todo est�tico que ir� retornar uma matriz sem a linha especificada
	void redimensionarMatriz(int m, int n); //m�todo que vai limpar e definir um novo tamanho para o vector do objeto

	//SE��O DE SOBRECARGA DOS OPERADORES
	Matriz operator+ (Matriz m2); //adaptar o s�mbolo de adi��o para permitir a utiliza��o com matrizes
	Matriz operator- (Matriz m2); //adaptar o s�mbolo de subtra��o para permitir a utiliza��o com matrizes
	Matriz operator* (Matriz m2); //adaptar o s�mbolo de multiplica��o para permitir a utiliza��o com matrizes
	Matriz operator* (double k); //adaptar o s�mbolo de multiplica��o para permitir a utiliza��o de matrizes com escalares
	Matriz operator/ (double k); //adaptar o s�mbolo de divis�o para permitir a utiliza��o de matrizes com escalares
	void operator+= (Matriz m2); //Adaptar o s�mbolo de incremento para permitir a utiliza��o com matrizes
	void operator-= (Matriz m2); //Adaptar o s�mbolo de decremento para permitir a utiliza��o com matrizes
	bool operator== (Matriz m2); //Adaptar o s�mbolo de igualdade para permitir a utiliza��o com matrizes
	bool operator!= (Matriz m2); //Adaptar o s�mbolo de "diferente" para permitir a utiliza��o com matrizes

};