#include <iostream>
#include "Matriz.h"
#include "SistemaLinear.h"
#include "EquacaoPolinomial.h"
#include "Ponto.h"
#include "Node.h"
#include "Barra.h"
#include "GeradorResultado.h"
#include "GeradorArquivo.h"
#include <string>
#include <map>
#define PI 3.14159265358979323846

int main() {
	while (true) {
		int resposta;
		std::cout << "**********MENU**********" << std::endl;
		std::cout << "Criar um arquivo [digite 01]" << std::endl;
		std::cout << "Ler um arquivo [digite 02]" << std::endl;
		std::cout << "Parar o programa [digite 03]" << std::endl;
		std::cin >> resposta;

		if (resposta == 1) {
			GeradorArquivo::obterDadosPeloConsole();
		}
		else if (resposta == 2) {
			std::string arquivo;
			std::cout << "Nome do arquivo = ";
			std::cin >> arquivo;

			GeradorResultado::lerArquivo(arquivo);
		}
		else if (resposta == 3) {
			break;
		}
	}

	return 0;
}

