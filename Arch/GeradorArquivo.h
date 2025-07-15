#pragma once
#include <string>
#include <vector>
#include "Node.h"
#include "Barra.h"

/*  O objetivo desta classe � gerar um arquivo .txt contendo todos os dados da estrutura, ou seja,
*   a posi��o dos seus n�s, as barras, as for�as nodais atuantes nos n�s, as for�as distribu�das atuantes nas
*   barras, etc. 
*/

class GeradorArquivo
{
public:
	/*O m�todo obterDadosPeloConsole vai obter os dados dos n�s, barras, etc. atrav�s do console. O seu objetivo
	  principal � obter os dados "brutos", ou seja, sem tratamento. Outra op��o seria obter os dados atrav�s de 
	  uma interface gr�fica, que � o objetivo principal futuro. */
	static void obterDadosPeloConsole();

	/*Esse m�todo ir� "tratar" os dados brutos, tornando-os mais simples de serem aplicados no m�todo dos elementos finitos.
	  Al�m disso, ir� salv�-los todos em um arquivo .ste de nome definido pelo usu�rio :)*/
	static void criarArquivo(std::string nomeArquivo, std::vector<Node> nosEstrutura, std::vector<Barra> barrasEstrutura);
};

