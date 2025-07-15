#pragma once
#include <vector>
#include "Node.h"
#include "Barra.h"
#include "Erro.h"
#include <string>

class Estrutura
{
public:

	/*Método para determinar as deformações nos nós da estrutura.E através deles, determinar as equações dos
	esforços internos nas barras. :)*/
	static void calcular(std::vector<Node>& nosAnalisados, std::vector<Barra>& barrasAnalisadas);

};

