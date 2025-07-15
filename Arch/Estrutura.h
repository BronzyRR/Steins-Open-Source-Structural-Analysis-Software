#pragma once
#include <vector>
#include "Node.h"
#include "Barra.h"
#include "Erro.h"
#include <string>

class Estrutura
{
public:

	/*M�todo para determinar as deforma��es nos n�s da estrutura.E atrav�s deles, determinar as equa��es dos
	esfor�os internos nas barras. :)*/
	static void calcular(std::vector<Node>& nosAnalisados, std::vector<Barra>& barrasAnalisadas);

};

