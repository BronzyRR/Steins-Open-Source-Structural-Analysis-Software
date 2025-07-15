#pragma once
#include <string>
#include <vector>
#include "Node.h"
#include "Barra.h"

/*  O objetivo desta classe � obter os resultados dos deslocamentos, equa��es dos esfor�os internos, etc. Para
*   os n�s/barras fornecidos pela classe GeradorArquivo.
*/

class GeradorResultado
{
public:

	//Vai calcular os deslocamentos nos n�s e as equa��es dos esfor�os internos da estrutura.
	static void calcularResultado(std::string nomeArquivo, std::vector<Node>& nosEstrutura, std::vector<Barra>& barrasEstrutura);

	//Vai ler o arquivo com os dados dos n�s e das barras.
	static void lerArquivo(std::string path);
};

