#pragma once
#include "Node.h"
#include "Matriz.h"
#include "EquacaoPolinomial.h"
#include <string>


class Barra
{
private:
	//VARIÁVEIS
	Matriz matrizRigidezLocal = Matriz(6,6); //matriz de rigidez local do elemento
	Matriz matrizRigidezGlobal = Matriz(6,6); //matriz de rigidez global do elemento
	Matriz matrizTransformacao = Matriz(6,6); //para transformar a global em local e vice-versa

	//Matriz dos deslocamentos
	Matriz desGlobal;
	Matriz desLocal;

	double comprimento; //comprimento da barra
	double area; //area da seção transversal do elemento
	double inercia; //momento de inércia da barra
	double elasticidade; //modulo de elasticidade da barra

	double cosseno; //cosseno da barra em relação ao sistema global de coordenadas
	double seno; //seno da barra em relação ao sistema global de coordenadas
	double alpha; //angulo da barra

	EquacaoPolinomial des; //equação do deslocamento interno da barra
	EquacaoPolinomial rot; //equação da rotação da barra
	EquacaoPolinomial momFletor; //equação do momento fletor da barra
	EquacaoPolinomial esfCortante; //equação do esforço cortante da barra
	EquacaoPolinomial desAxial; //equação do deslocamento axial da barra
	EquacaoPolinomial esfNormal; //equação do esforço normal da barra

	std::string configuracaoBarra; //configuração da barra no espaço (1° quadrante, 4° quadrante, horizontal ou vertical)

	double fxGlobal; //carregamento inicial na direção x [obs = sempre referente ao nó p1] [referencia global]
	double fyGlobal; //carregamento final na direção y [obs = sempre referente ao nó p2] [referencia global]

	double fxLocal; //carregamento inicial na direção x [obs = sempre referente ao nó p1] [referencia local]
	double fyLocal; //carregamento inicial na direção y [obs = sempre referente ao nó p1] [referencia local]

	double fxEquivalenteN1Local; //carregamento equivalente na direção x no nó n1 [referencia local]
	double fyEquivalenteN1Local; //carregamento equivalente na direção y no nó n1 [referencia local]
	double mzEquivalenteN1Local; //momento equivalente na direção z no nó n1 [referencia local]
	double fxEquivalenteN2Local; //carregamento equivalente na direção x no nó n2 [referencia local]
	double fyEquivalenteN2Local; //carregamento equivalente na direção y no nó n2 [referencia local]
	double mzEquivalenteN2Local; //momento equivalente na direção z no nó n2 [referencia local]

	double fxEquivalenteN1Global; //carregamento equivalente na direção x no nó n1 [referencia global]
	double fyEquivalenteN1Global; //carregamento equivalente na direção y no nó n1 [referencia global]
	double mzEquivalenteN1Global; //momento equivalente na direção z no nó n1 [referencia global]
	double fxEquivalenteN2Global; //carregamento equivalente na direção x no nó n2 [referencia global]
	double fyEquivalenteN2Global; //carregamento equivalente na direção y no nó n2 [referencia global]
	double mzEquivalenteN2Global; //momento equivalente na direção z no nó n2 [referencia global]

	//MÉTODOS PRIVADOS
	void calcularMatrizRigidezLocal(); //definir a matriz de rigidez local
	void calcularMatrizRigidezGlobal(); //definir a matriz de rigidez global
	void calcularMatrizTransformacao(); //definir a matriz de transformação da barra
	void calcularCargaEquivalente(); //método para definir as cargas nodais equivalentes do carregamento distribuido
	void calcularEsforcosInternos(); //definir as equações de esforço interno na barra

	//FLAGS PARA AS RÓTULAS
	bool rotulaN1 = false;
	bool rotulaN2 = false;

	//MOMENTOS NAS EXTREMIDADES DA BARRA
	double momentoFimBarraNo1;
	double momentoFimBarraNo2;


public:
	Node n1; //primeiro ponto da barra
	Node n2; //segundo ponto da barra

	//graus de liberdade da barra no nó 01
	std::pair<int, bool> glxNo1;
	std::pair<int, bool> glyNo1;
	std::pair<int, bool> glzNo1;

	//graus de liberdade da barra no nó 02
	std::pair<int, bool> glxNo2;
	std::pair<int, bool> glyNo2;
	std::pair<int, bool> glzNo2;

	Barra(Node ni, Node nj, double e, double area, double inercia, bool rotulaN1, bool rotulaN2); //método construtor da barra

	//MÉTODOS GETTERS
	double getElasticidade(); //vai retornar o módulo de elasticidade da barra
	double getInercia(); //vai retornar o momento de inércia da barra
	double getArea(); //vai retornar a área da barra
	double getComprimento(); //vai retornar o comprimento da barra
	double getAlpha(); //vai retornar o ângulo da barra
	double getCosseno(); //vai retornar o cosseno do ângulo
	double getSeno(); //vai retornar o seno do ângulo
	double getFxGlobal(); //vai retornar o valor da força distribuída no eixo x
	double getFyGlobal(); //vai retornar o valor da força distribuída no eixo y
	double getMomentoFimBarraN1(); //vai retornar o valor do momento no fim da barra [nó n1]
	double getMomentoFimBarraN2(); //vai retornar o valor do momento no fim da barra [nó n2]
	Matriz getMatrizRigidezLocal(); //vai retornar a matriz de rigidez local do elemento
	Matriz getMatrizTransformacao(); //vai retornar a matriz de transformação do elemento
	Matriz getMatrizRigidezGlobal(); //vai retornar a matriz de rigidez global do elemento

	//MÉTODOS SETTERS
	void setElasticidade(double e); //definir o módulo de elasticidade da barra
	void setArea(double a); //definir a área da seção transversal da barra
	void setInercia(double i); //definir o momento de inércia da barra
	void setDeslocamento(EquacaoPolinomial des); //definir a equação de deslocamento da barra
	void setCargaDistribuidaGlobal(double fx, double fy); //definir a carga distribuida atuante em x e y [eixo GLOBAL]
	void setMomentoFimBarra(double momentoFimBarraNo1, double momentoFimBarraNo2); //definir os momentos de fim de barra atuantes no nó n1 e n2

	//ESFORÇOS INTERNOS
	double deslocamento(double x); //vai retornar o valor do deslocamento em um ponto x
	double rotacao(double x); //vai retornar o valor da rotação em um ponto x
	double momentoFletor(double x); //vai retornar o valor do momento fletor em um ponto x
	double esforcoCortante(double x); //vai retornar o valor do esforço cortante em um ponto x
	double esforçoNormal(double x); //vai retornar o valor do esforço normal em um ponto x

	//Método para calcular os esforços internos na barra
	void calcularEquacaoEsforcosInternos(double dxNo1, double dyNo1, double rzNo1,
									     double dxNo2, double dyNo2, double rzNo2); 

	//Método para calcular o esforço normal na barra
	void calcularEquacaoEsforcoNormal();

	//CARGAS EQUIVALENTES
	double getFxEquivalenteGlobal_N1(); //obter o carregamento equivalente na direção X no nó N1 devido à carga distribuída [global]
	double getFyEquivalenteGlobal_N1(); //obter o carregamento equivalente na direção Y no nó N1 devido à carga distribuída [global]
	double getMzEquivalenteGlobal_N1(); //obter o momento equivalente na direção Z no nó N1 devido à carga distribuída [global]
	double getFxEquivalenteGlobal_N2(); //obter o carregamento equivalente na direção X no nó N2 devido à carga distribuída [global]
	double getFyEquivalenteGlobal_N2(); //obter o carregamento equivalente na direção Y no nó N2 devido à carga distribuída [global]
	double getMzEquivalenteGlobal_N2(); //obter o momento equivalente na direção Z no nó N2	 devido à carga distribuída [global]

	//MÉTODOS GETTERS PARA AS EQUAÇÕES DOS ESFORÇOS INTERNOS
	EquacaoPolinomial getEquacaoDeslocamento();
	EquacaoPolinomial getEquacaoRotacao();
	EquacaoPolinomial getEquacaoMomentoFletor();
	EquacaoPolinomial getEquacaoEsforcoCortante();
	EquacaoPolinomial getEquacaoEsforcoNormal();
	EquacaoPolinomial getEquacaoDeslocamentoAxial();

	//MÉTODOS GETTERS PARA AS RÓTULAS
	bool getRotulaN1();
	bool getRotulaN2();

};

