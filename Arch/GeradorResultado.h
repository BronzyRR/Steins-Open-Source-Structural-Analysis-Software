#pragma once
#include <string>
#include <vector>
#include "Node.h"
#include "Barra.h"

/*  O objetivo desta classe é obter os resultados dos deslocamentos, equações dos esforços internos, etc. Para
*   os nós/barras fornecidos pela classe GeradorArquivo.
*/

class GeradorResultado
{
public:

	//Vai calcular os deslocamentos nos nós e as equações dos esforços internos da estrutura.
	static void calcularResultado(std::string nomeArquivo, std::vector<Node>& nosEstrutura, std::vector<Barra>& barrasEstrutura);

	//Vai ler o arquivo com os dados dos nós e das barras.
	static void lerArquivo(std::string path);
};

