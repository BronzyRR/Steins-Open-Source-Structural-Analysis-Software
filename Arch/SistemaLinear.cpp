#include "SistemaLinear.h"
#include "Erro.h"
#include <iostream>
#include <vector>
#include "Matriz.h"

#define ITERACOES 250

Matriz SistemaLinear::metodoDeGauss(Matriz A, Matriz B) {
	try {
		if ((A.getM() == A.getN()) && (A.getM() == B.getM()) && (B.getN() == 1) && (A.getM()!=0)){
			//Inicializar o vetor com os valores de X
			int tamanhoVetor = A.getM();
			Matriz xAtual(tamanhoVetor, 1);
			xAtual.preencher(0.00);

			for (int k = 0; k < ITERACOES; k++) {
				for (int i = 0; i < A.getM(); i++) {
					double somaTermos = B.getValor(i, 0);

					for (int j = 0; j < A.getN(); j++) {
						if (i == j) {
							continue;
						}
						else {
							somaTermos -= A.getValor(i, j) * xAtual.getValor(j, 0);
						}
					}

					somaTermos /= A.getValor(i, i);
					xAtual.setValor(i, 0, somaTermos);
				}
			}
			return xAtual;
		}
		else {
			throw Erro(201);
		}
	}
	catch (Erro e) {
		std::cout << e.texto() << std::endl;
	}
}

Matriz SistemaLinear::metodoDeJacobi(Matriz A, Matriz B) {
	//Inicializar o vetor com os valores de x
	try {
		if ((A.getM() == A.getN()) && (A.getM() == B.getM()) && (B.getN() == 1) && (A.getM() != 0)) {
			int tamanhoVetor = A.getM();
			Matriz xAtual(tamanhoVetor, 1);
			xAtual.preencher(0.00);

			Matriz xAnterior(tamanhoVetor, 1);
			xAnterior.preencher(0.00);

			for (int k = 0; k < ITERACOES; k++) {
				for (int i = 0; i < A.getM(); i++) {
					xAnterior.setValor(i, 0, xAtual.getValor(i, 0));
				}

				for (int i = 0; i < A.getM(); i++) {
					double somaTermos = B.getValor(i, 0);

					for (int j = 0; j < A.getN(); j++) {
						if (i == j) {
							continue;
						}
						else {
							somaTermos -= (A.getValor(i, j)) * (xAnterior.getValor(j, 0));
						}
					}

					somaTermos /= A.getValor(i, i);
					xAtual.setValor(i, 0, somaTermos);
				}
			}
			return xAtual;
		}
		else {
			throw Erro(201);
		}
	}
	catch (Erro e) {
		std::cout << e.texto() << std::endl;
	}
}

Matriz SistemaLinear::metodoDeGaussDireto(Matriz A, Matriz B) {
	/*O primeiro passo é uniformizar a matriz, ou seja, deixar todos os seus valores em 
	uma escala de grandeza semelhante. Essa etapa é necessária para evitar erros de 
	arredondamento.*/
	for (int i = 0; i < A.getM(); i++) {
		double maiorNumero = 0;

		for (int j = 0; j < A.getN(); j++) {
			double numeroAtual = abs(A.getValor(i, j));
			if (numeroAtual > maiorNumero) {
				maiorNumero = numeroAtual;
			}
		}

		Matriz linhaAtualCoeficientes = A.getLinha(i);
		linhaAtualCoeficientes = linhaAtualCoeficientes / maiorNumero;
		A.setLinha(i, linhaAtualCoeficientes);

		Matriz linhaAtualResultado = B.getLinha(i);
		linhaAtualResultado = linhaAtualResultado / maiorNumero;
		B.setLinha(i, linhaAtualResultado);
	}

	std::vector<std::pair<int, int>> trocasLinhas; //vector que irá guardar todas as trocas de linha
	/*O próximo passo é realizar a pivotação parcial*/
	for (int i = 0; i < A.getM(); i++) {
		double maiorNumero = 0; 
		double linhaMaiorNumero = 0; //linha que contém o maior numero para a posicao a[i,i]
		
		for (int k = i; k < A.getM(); k++) {
			double numeroAtual = abs(A.getValor(k, i));

			if (numeroAtual > maiorNumero) {
				maiorNumero = numeroAtual;
				linhaMaiorNumero = k;
			}
		}

		A.trocarLinha(linhaMaiorNumero, i);
		B.trocarLinha(linhaMaiorNumero, i);

		trocasLinhas.push_back(std::make_pair(linhaMaiorNumero, i));
	}

	/*Após finalizar as etapas de preparação da matriz, pode-se iniciar o método de Gauss
	propriamente dito.
	Para isso, deve-se escalonar a matriz.*/
	for (int i = 0; i < (A.getM()-1); i++) {
		double elementoDiagonal = A.getValor(i, i);
		
		for (int k = i+1; k < A.getM(); k++) {
			double mki = A.getValor(k, i)/elementoDiagonal;
			
			for (int j = 0; j < A.getN(); j++) {
				double novoValor = A.getValor(k, j) - mki * A.getValor(i, j);
				A.setValor(k, j, novoValor);
			}

			B.setValor(k, 0, B.getValor(k, 0) - mki * B.getValor(i, 0));
		}
	}

	Matriz resultado(A.getM(), 1);
	for (int i = (A.getM() - 1); i >= 0; i--) {
		double xi = 0;
		xi = B.getValor(i, 0);

		for (int j = i; j < A.getN(); j++) {
			xi -= resultado.getValor(j, 0) * A.getValor(i, j);
		}

		xi /= A.getValor(i, i);
		resultado.setValor(i, 0, xi);
	}

	//Trocar as linhas
	for (int i = (trocasLinhas.size()-1); i >= 0; i--) {
		resultado.trocarLinha(trocasLinhas[i].first, trocasLinhas[i].second);
	}

	return resultado;
}

