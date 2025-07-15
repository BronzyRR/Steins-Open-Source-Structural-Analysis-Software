#pragma once
#include "Node.h"
#include "Matriz.h"
#include "EquacaoPolinomial.h"
#include <string>


class Barra
{
private:
	//VARI�VEIS
	Matriz matrizRigidezLocal = Matriz(6,6); //matriz de rigidez local do elemento
	Matriz matrizRigidezGlobal = Matriz(6,6); //matriz de rigidez global do elemento
	Matriz matrizTransformacao = Matriz(6,6); //para transformar a global em local e vice-versa

	//Matriz dos deslocamentos
	Matriz desGlobal;
	Matriz desLocal;

	double comprimento; //comprimento da barra
	double area; //area da se��o transversal do elemento
	double inercia; //momento de in�rcia da barra
	double elasticidade; //modulo de elasticidade da barra

	double cosseno; //cosseno da barra em rela��o ao sistema global de coordenadas
	double seno; //seno da barra em rela��o ao sistema global de coordenadas
	double alpha; //angulo da barra

	EquacaoPolinomial des; //equa��o do deslocamento interno da barra
	EquacaoPolinomial rot; //equa��o da rota��o da barra
	EquacaoPolinomial momFletor; //equa��o do momento fletor da barra
	EquacaoPolinomial esfCortante; //equa��o do esfor�o cortante da barra
	EquacaoPolinomial desAxial; //equa��o do deslocamento axial da barra
	EquacaoPolinomial esfNormal; //equa��o do esfor�o normal da barra

	std::string configuracaoBarra; //configura��o da barra no espa�o (1� quadrante, 4� quadrante, horizontal ou vertical)

	double fxGlobal; //carregamento inicial na dire��o x [obs = sempre referente ao n� p1] [referencia global]
	double fyGlobal; //carregamento final na dire��o y [obs = sempre referente ao n� p2] [referencia global]

	double fxLocal; //carregamento inicial na dire��o x [obs = sempre referente ao n� p1] [referencia local]
	double fyLocal; //carregamento inicial na dire��o y [obs = sempre referente ao n� p1] [referencia local]

	double fxEquivalenteN1Local; //carregamento equivalente na dire��o x no n� n1 [referencia local]
	double fyEquivalenteN1Local; //carregamento equivalente na dire��o y no n� n1 [referencia local]
	double mzEquivalenteN1Local; //momento equivalente na dire��o z no n� n1 [referencia local]
	double fxEquivalenteN2Local; //carregamento equivalente na dire��o x no n� n2 [referencia local]
	double fyEquivalenteN2Local; //carregamento equivalente na dire��o y no n� n2 [referencia local]
	double mzEquivalenteN2Local; //momento equivalente na dire��o z no n� n2 [referencia local]

	double fxEquivalenteN1Global; //carregamento equivalente na dire��o x no n� n1 [referencia global]
	double fyEquivalenteN1Global; //carregamento equivalente na dire��o y no n� n1 [referencia global]
	double mzEquivalenteN1Global; //momento equivalente na dire��o z no n� n1 [referencia global]
	double fxEquivalenteN2Global; //carregamento equivalente na dire��o x no n� n2 [referencia global]
	double fyEquivalenteN2Global; //carregamento equivalente na dire��o y no n� n2 [referencia global]
	double mzEquivalenteN2Global; //momento equivalente na dire��o z no n� n2 [referencia global]

	//M�TODOS PRIVADOS
	void calcularMatrizRigidezLocal(); //definir a matriz de rigidez local
	void calcularMatrizRigidezGlobal(); //definir a matriz de rigidez global
	void calcularMatrizTransformacao(); //definir a matriz de transforma��o da barra
	void calcularCargaEquivalente(); //m�todo para definir as cargas nodais equivalentes do carregamento distribuido
	void calcularEsforcosInternos(); //definir as equa��es de esfor�o interno na barra

	//FLAGS PARA AS R�TULAS
	bool rotulaN1 = false;
	bool rotulaN2 = false;

	//MOMENTOS NAS EXTREMIDADES DA BARRA
	double momentoFimBarraNo1;
	double momentoFimBarraNo2;


public:
	Node n1; //primeiro ponto da barra
	Node n2; //segundo ponto da barra

	//graus de liberdade da barra no n� 01
	std::pair<int, bool> glxNo1;
	std::pair<int, bool> glyNo1;
	std::pair<int, bool> glzNo1;

	//graus de liberdade da barra no n� 02
	std::pair<int, bool> glxNo2;
	std::pair<int, bool> glyNo2;
	std::pair<int, bool> glzNo2;

	Barra(Node ni, Node nj, double e, double area, double inercia, bool rotulaN1, bool rotulaN2); //m�todo construtor da barra

	//M�TODOS GETTERS
	double getElasticidade(); //vai retornar o m�dulo de elasticidade da barra
	double getInercia(); //vai retornar o momento de in�rcia da barra
	double getArea(); //vai retornar a �rea da barra
	double getComprimento(); //vai retornar o comprimento da barra
	double getAlpha(); //vai retornar o �ngulo da barra
	double getCosseno(); //vai retornar o cosseno do �ngulo
	double getSeno(); //vai retornar o seno do �ngulo
	double getFxGlobal(); //vai retornar o valor da for�a distribu�da no eixo x
	double getFyGlobal(); //vai retornar o valor da for�a distribu�da no eixo y
	double getMomentoFimBarraN1(); //vai retornar o valor do momento no fim da barra [n� n1]
	double getMomentoFimBarraN2(); //vai retornar o valor do momento no fim da barra [n� n2]
	Matriz getMatrizRigidezLocal(); //vai retornar a matriz de rigidez local do elemento
	Matriz getMatrizTransformacao(); //vai retornar a matriz de transforma��o do elemento
	Matriz getMatrizRigidezGlobal(); //vai retornar a matriz de rigidez global do elemento

	//M�TODOS SETTERS
	void setElasticidade(double e); //definir o m�dulo de elasticidade da barra
	void setArea(double a); //definir a �rea da se��o transversal da barra
	void setInercia(double i); //definir o momento de in�rcia da barra
	void setDeslocamento(EquacaoPolinomial des); //definir a equa��o de deslocamento da barra
	void setCargaDistribuidaGlobal(double fx, double fy); //definir a carga distribuida atuante em x e y [eixo GLOBAL]
	void setMomentoFimBarra(double momentoFimBarraNo1, double momentoFimBarraNo2); //definir os momentos de fim de barra atuantes no n� n1 e n2

	//ESFOR�OS INTERNOS
	double deslocamento(double x); //vai retornar o valor do deslocamento em um ponto x
	double rotacao(double x); //vai retornar o valor da rota��o em um ponto x
	double momentoFletor(double x); //vai retornar o valor do momento fletor em um ponto x
	double esforcoCortante(double x); //vai retornar o valor do esfor�o cortante em um ponto x
	double esfor�oNormal(double x); //vai retornar o valor do esfor�o normal em um ponto x

	//M�todo para calcular os esfor�os internos na barra
	void calcularEquacaoEsforcosInternos(double dxNo1, double dyNo1, double rzNo1,
									     double dxNo2, double dyNo2, double rzNo2); 

	//M�todo para calcular o esfor�o normal na barra
	void calcularEquacaoEsforcoNormal();

	//CARGAS EQUIVALENTES
	double getFxEquivalenteGlobal_N1(); //obter o carregamento equivalente na dire��o X no n� N1 devido � carga distribu�da [global]
	double getFyEquivalenteGlobal_N1(); //obter o carregamento equivalente na dire��o Y no n� N1 devido � carga distribu�da [global]
	double getMzEquivalenteGlobal_N1(); //obter o momento equivalente na dire��o Z no n� N1 devido � carga distribu�da [global]
	double getFxEquivalenteGlobal_N2(); //obter o carregamento equivalente na dire��o X no n� N2 devido � carga distribu�da [global]
	double getFyEquivalenteGlobal_N2(); //obter o carregamento equivalente na dire��o Y no n� N2 devido � carga distribu�da [global]
	double getMzEquivalenteGlobal_N2(); //obter o momento equivalente na dire��o Z no n� N2	 devido � carga distribu�da [global]

	//M�TODOS GETTERS PARA AS EQUA��ES DOS ESFOR�OS INTERNOS
	EquacaoPolinomial getEquacaoDeslocamento();
	EquacaoPolinomial getEquacaoRotacao();
	EquacaoPolinomial getEquacaoMomentoFletor();
	EquacaoPolinomial getEquacaoEsforcoCortante();
	EquacaoPolinomial getEquacaoEsforcoNormal();
	EquacaoPolinomial getEquacaoDeslocamentoAxial();

	//M�TODOS GETTERS PARA AS R�TULAS
	bool getRotulaN1();
	bool getRotulaN2();

};

