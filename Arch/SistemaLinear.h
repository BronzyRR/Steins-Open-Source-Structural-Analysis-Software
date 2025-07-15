#pragma once
#include "Matriz.h"

class SistemaLinear
{
public:
	static Matriz metodoDeGauss(Matriz A, Matriz B);
	static Matriz metodoDeJacobi(Matriz A, Matriz B);
	static Matriz metodoDeGaussDireto(Matriz A, Matriz B);
};

