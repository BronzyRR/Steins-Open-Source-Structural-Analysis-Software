#pragma once
#include <string>
#include <vector>
#include "Node.h"
#include "Barra.h"

/*  O objetivo desta classe é gerar um arquivo .txt contendo todos os dados da estrutura, ou seja,
*   a posição dos seus nós, as barras, as forças nodais atuantes nos nós, as forças distribuídas atuantes nas
*   barras, etc. 
*/

class GeradorArquivo
{
public:
	/*O método obterDadosPeloConsole vai obter os dados dos nós, barras, etc. através do console. O seu objetivo
	  principal é obter os dados "brutos", ou seja, sem tratamento. Outra opção seria obter os dados através de 
	  uma interface gráfica, que é o objetivo principal futuro. */
	static void obterDadosPeloConsole();

	/*Esse método irá "tratar" os dados brutos, tornando-os mais simples de serem aplicados no método dos elementos finitos.
	  Além disso, irá salvá-los todos em um arquivo .ste de nome definido pelo usuário :)*/
	static void criarArquivo(std::string nomeArquivo, std::vector<Node> nosEstrutura, std::vector<Barra> barrasEstrutura);
};

