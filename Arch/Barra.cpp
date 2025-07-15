#include "Barra.h"
#include "Matriz.h"
#include "Ponto.h"
#include "Erro.h"
#include "EquacaoPolinomial.h"
#include "SistemaLinear.h"
#include <iostream>
#include <string>

#define PI 3.14159265358979323846

//Método construtor da barra
Barra::Barra(Node ni, Node nj, double elasticidade, double area, double inercia, bool rotulaN1, bool rotulaN2) {

	/* O primeiro passo é dispor os nós da maneira correta. No caso, o ideal é que 
	* eles fiquem no primeiro quadrante, no quarto quadrante ou na posição 
	* horizontal- vertical. Desta maneira, será mais fácil de realizar os cálculos.
	*/
	try {
		//Primeiro deve se verificar se os nós não são os mesmos
		if (ni.pos == nj.pos) {
			throw Erro(401);
		}
		else {
			this->elasticidade = elasticidade;
			this->area = area;
			this->inercia = inercia;
			this->comprimento = Ponto::distancia(ni.pos, nj.pos);
			this->rotulaN1 = rotulaN1;
			this->rotulaN2 = rotulaN2;

			this->fxEquivalenteN1Local = 0;
			this->fxEquivalenteN2Local = 0;
			this->fyEquivalenteN1Local = 0;
			this->fyEquivalenteN2Local = 0;
			this->mzEquivalenteN1Local = 0;
			this->mzEquivalenteN2Local = 0;

			this->fxEquivalenteN1Global = 0;
			this->fyEquivalenteN1Global = 0;
			this->mzEquivalenteN1Global = 0;
			this->fxEquivalenteN2Global = 0;
			this->fyEquivalenteN2Global = 0;
			this->mzEquivalenteN2Global = 0;
		}
	
		if (ni.pos.getX() == nj.pos.getX()) { //caso a barra esteja na vertical, n1 será igual ao nó com o menor y
			if (ni.pos.getY() < nj.pos.getY()) {
				this->n1 = ni;
				this->n2 = nj;
			}
			else {
				this->n1 = nj;
				this->n2 = ni;
			}

			this->alpha = PI / 2;
			this->cosseno = cos(alpha);
			this->seno = sin(alpha);
			this->configuracaoBarra = "vertical";
		}
		else if (ni.pos.getY() == nj.pos.getY()) { //caso a barra esteja na horizontal, n1 será igual ao nó com o menor x
			if (ni.pos.getX() < nj.pos.getX()) {
				this->n1 = ni;
				this->n2 = nj;
			}
			else {
				this->n1 = nj;
				this->n2 = ni;
			}

			this->alpha = 0;
			this->cosseno = cos(this->alpha);
			this->seno = sin(this->alpha);
			this->configuracaoBarra = "horizontal";
		}
		else { //caso esteja inclinada, n1 será sempre igual ao nó com o menor x
			if (ni.pos.getX() < nj.pos.getX()) { //definindo n1 e n2
				this->n1 = ni;
				this->n2 = nj;
			}
			else {
				this->n1 = nj;
				this->n2 = ni;
			}

			double dy = 0;
			double dx = 0;

			if (this->n1.pos.getY() < this->n2.pos.getY()) { //1° quadrante
				dy = n2.pos.getY() - n1.pos.getY();
				dx = n2.pos.getX() - n1.pos.getX();

				this->alpha = atan(dy / dx);
				this->cosseno = cos(this->alpha);
				this->seno = sin(this->alpha);
				this->configuracaoBarra = "1quadrante";
			}
			else { //4° quadrante
				dy = n2.pos.getY() - n1.pos.getY();
				dx = n2.pos.getX() - n1.pos.getX();

				double tgalpha = atan(abs(dy / dx));
				this->alpha = 2 * PI - tgalpha;
				this->cosseno = cos(this->alpha);
				this->seno = sin(this->alpha);
				this->configuracaoBarra = "4quadrante";
			}
		}

		this->calcularMatrizRigidezLocal();
		this->calcularMatrizTransformacao();
		this->calcularMatrizRigidezGlobal();
	}
	catch (Erro e) {
		std::cout << e.texto() << std::endl;
	}	
}


//Vai retornar o módulo de elasticidade da barra
double Barra::getElasticidade() {
	return this->elasticidade;
}

//Vai retornar o momento de inércia da barra
double Barra::getInercia() {
	return this->inercia;
}

//Vai retornar a área da seção transversal da barra
double Barra::getArea() {
	return this->area;
}

//Vai retornar o comprimento da barra
double Barra::getComprimento() {
	return this->comprimento;
}

//Vai retornar o ângulo da barra
double Barra::getAlpha() {
	return this->alpha;
}

//Vai retornar o cosseno do ângulo
double Barra::getCosseno() {
	return this->cosseno;
}

//Vai retornar o seno do ângulo
double Barra::getSeno() {
	return this->seno;
}

//Vai retornar o valor da força distribuída no eixo x
double Barra::getFxGlobal() {
	return this->fxGlobal;
}

//Vai retornar o valor da força distribuída no eixo y
double Barra::getFyGlobal() {
	return this->fyGlobal;
}

double Barra::getMomentoFimBarraN1() {
	return this->momentoFimBarraNo1;
}

double Barra::getMomentoFimBarraN2() {
	return this->momentoFimBarraNo2;
}

//Vai retornar a matriz de rigidez local do elemento de barra
Matriz Barra::getMatrizRigidezLocal() {
	return this->matrizRigidezLocal;
}

//Vai retornar a matriz de rigidez global do elemento de barra
Matriz Barra::getMatrizRigidezGlobal() {
	return this->matrizRigidezGlobal;
}

//Vai retornar a matriz de transformação da barra
Matriz Barra::getMatrizTransformacao() {
	return this->matrizTransformacao;
}
    
//Definir o módulo de elasticidade da barra
void Barra::setElasticidade(double e) {
	this->elasticidade = e;
}

//Definir a área da seção transversal da barra
void Barra::setArea(double a) {
	this->area = a;
}

//Definir o momento de inércia da seção transversal da barra
void Barra::setInercia(double i) {
	this->inercia = i;
}

//Definir a equação do deslocamento da barra
void Barra::setDeslocamento(EquacaoPolinomial des) {
	this->des = des;
	this->rot = this->des.derivada(); //a equação da rotação será igual à derivada do deslocamento
	this->momFletor = this->rot.derivada(); //a equação do momento fletor será igual à derivada da rotação
	this->esfCortante = this->momFletor.derivada(); //a equação do esforço cortante será igual à derivada do momento fletor
}

//Definir o carregamento distribuído atuante em x e y
void Barra::setCargaDistribuidaGlobal(double fx, double fy) {
	this->fxGlobal = fx;
	this->fyGlobal = fy;
	this->calcularCargaEquivalente();
}

//Definir os momentos de fim de barra
void Barra::setMomentoFimBarra(double momentoFimBarraNo1, double momentoFimBarraNo2) {
	this->momentoFimBarraNo1 = momentoFimBarraNo1;
	this->momentoFimBarraNo2 = momentoFimBarraNo2;

	this->mzEquivalenteN1Global += momentoFimBarraNo1;
	this->mzEquivalenteN2Global += momentoFimBarraNo2;
}

//Esforços internos
//Vai retornar o valor do deslocamento em um ponto x
double Barra::deslocamento(double x) {
	return this->des.valor(x);
}

//Vai retornar o valor da rotação em um ponto x qualquer
double Barra::rotacao(double x) {
	return this->rot.valor(x);
}

//Vai retornar o valor do momento fletor em um ponto x qualquer
double Barra::momentoFletor(double x) {
	return this->momFletor.valor(x);
}

//Vai retornar o valor do esforço cortante em um ponto x qualquer
double Barra::esforcoCortante(double x) {
	return this->esfCortante.valor(x);
}

//Vai retornar o valor do esforço normal em um ponto x qualquer
double Barra::esforçoNormal(double x) {
	return this->esfNormal.valor(x);
}

//Método para calcular a matriz de rigidez local
void Barra::calcularMatrizRigidezLocal() {
	double a = (this->elasticidade * this->area) / (this->comprimento);
	double b = (this->elasticidade * this->inercia) / (pow(this->comprimento, 3));
	double l = this->comprimento;

	//DEFININDO A MATRIZ LOCAL
	//1° linha
	this->matrizRigidezLocal.setValor(0, 0, a);
	this->matrizRigidezLocal.setValor(0, 1, 0);
	this->matrizRigidezLocal.setValor(0, 2, 0);
	this->matrizRigidezLocal.setValor(0, 3, -a);
	this->matrizRigidezLocal.setValor(0, 4, 0);
	this->matrizRigidezLocal.setValor(0, 5, 0);
	//2° linha
	this->matrizRigidezLocal.setValor(1, 0, 0);
	this->matrizRigidezLocal.setValor(1, 1, 12*b);
	this->matrizRigidezLocal.setValor(1, 2, 6*b*l);
	this->matrizRigidezLocal.setValor(1, 3, 0);
	this->matrizRigidezLocal.setValor(1, 4, -12*b);
	this->matrizRigidezLocal.setValor(1, 5, 6*b*l);
	//3° linha
	this->matrizRigidezLocal.setValor(2, 0, 0);
	this->matrizRigidezLocal.setValor(2, 1, 6*b*l);
	this->matrizRigidezLocal.setValor(2, 2, 4*b*l*l);
	this->matrizRigidezLocal.setValor(2, 3, 0);
	this->matrizRigidezLocal.setValor(2, 4, -6*b*l);
	this->matrizRigidezLocal.setValor(2, 5, 2*b*l*l);
	//4° linha
	this->matrizRigidezLocal.setValor(3, 0, -a);
	this->matrizRigidezLocal.setValor(3, 1, 0);
	this->matrizRigidezLocal.setValor(3, 2, 0);
	this->matrizRigidezLocal.setValor(3, 3, a);
	this->matrizRigidezLocal.setValor(3, 4, 0);
	this->matrizRigidezLocal.setValor(3, 5, 0);
	//5° linha
	this->matrizRigidezLocal.setValor(4, 0, 0);
	this->matrizRigidezLocal.setValor(4, 1, -12*b);
	this->matrizRigidezLocal.setValor(4, 2, -6*b*l);
	this->matrizRigidezLocal.setValor(4, 3, 0);
	this->matrizRigidezLocal.setValor(4, 4, 12*b);
	this->matrizRigidezLocal.setValor(4, 5, -6*b*l);
	//6° linha
	this->matrizRigidezLocal.setValor(5, 0, 0);
	this->matrizRigidezLocal.setValor(5, 1, 6*b*l);
	this->matrizRigidezLocal.setValor(5, 2, 2*b*l*l);
	this->matrizRigidezLocal.setValor(5, 3, 0);
	this->matrizRigidezLocal.setValor(5, 4, -6*b*l);
	this->matrizRigidezLocal.setValor(5, 5, 4 * b * l * l);
}

//Método para calcular a matriz de transformação
void Barra::calcularMatrizTransformacao() {
	double mi = this->seno;
	double lambda = this->cosseno;

	//DEFININDO A MATRIZ DE TRANSFORMAÇÃO
	//1° linha
	this->matrizTransformacao.setValor(0, 0, lambda);
	this->matrizTransformacao.setValor(0, 1, mi);
	this->matrizTransformacao.setValor(0, 2, 0);
	this->matrizTransformacao.setValor(0, 3, 0);
	this->matrizTransformacao.setValor(0, 4, 0);
	this->matrizTransformacao.setValor(0, 5, 0);
	//2° linha
	this->matrizTransformacao.setValor(1, 0, -mi);
	this->matrizTransformacao.setValor(1, 1, lambda);
	this->matrizTransformacao.setValor(1, 2, 0);
	this->matrizTransformacao.setValor(1, 3, 0);
	this->matrizTransformacao.setValor(1, 4, 0);
	this->matrizTransformacao.setValor(1, 5, 0);
	//3° linha
	this->matrizTransformacao.setValor(2, 0, 0);
	this->matrizTransformacao.setValor(2, 1, 0);
	this->matrizTransformacao.setValor(2, 2, 1);
	this->matrizTransformacao.setValor(2, 3, 0);
	this->matrizTransformacao.setValor(2, 4, 0);
	this->matrizTransformacao.setValor(2, 5, 0);
	//4° linha
	this->matrizTransformacao.setValor(3, 0, 0);
	this->matrizTransformacao.setValor(3, 1, 0);
	this->matrizTransformacao.setValor(3, 2, 0);
	this->matrizTransformacao.setValor(3, 3, lambda);
	this->matrizTransformacao.setValor(3, 4, mi);
	this->matrizTransformacao.setValor(3, 5, 0);
	//5° linha
	this->matrizTransformacao.setValor(4, 0, 0);
	this->matrizTransformacao.setValor(4, 1, 0);
	this->matrizTransformacao.setValor(4, 2, 0);
	this->matrizTransformacao.setValor(4, 3, -mi);
	this->matrizTransformacao.setValor(4, 4, lambda);
	this->matrizTransformacao.setValor(4, 5, 0);
	//6° linha
	this->matrizTransformacao.setValor(5, 0, 0);
	this->matrizTransformacao.setValor(5, 1, 0);
	this->matrizTransformacao.setValor(5, 2, 0);
	this->matrizTransformacao.setValor(5, 3, 0);
	this->matrizTransformacao.setValor(5, 4, 0);
	this->matrizTransformacao.setValor(5, 5, 1);

}

//Método para calcular a matriz de rigidez global
void Barra::calcularMatrizRigidezGlobal() {
	Matriz transformacaoTransposta = Matriz::transposta(this->matrizTransformacao);

	this->matrizRigidezGlobal = transformacaoTransposta * this->matrizRigidezLocal * this->matrizTransformacao;

}	

//CARGAS EQUIVALENTES
void Barra::calcularCargaEquivalente() {
	/*O primeiro passo é transformar os carregamentos do sistema de referencia global para o local. 
      Para isso, deve-se inicializar um vetor contendo as forças. */
	Matriz vetorForcaDistribuidaGlobal(6, 1);
	vetorForcaDistribuidaGlobal.setValor(0, 0, this->fxGlobal);
	vetorForcaDistribuidaGlobal.setValor(1, 0, this->fyGlobal);
	vetorForcaDistribuidaGlobal.setValor(2, 0, 0);
	vetorForcaDistribuidaGlobal.setValor(3, 0, this->fxGlobal);
	vetorForcaDistribuidaGlobal.setValor(4, 0, this->fyGlobal);
	vetorForcaDistribuidaGlobal.setValor(5, 0, 0);

	Matriz vetorForcaDistribuidaLocal = this->matrizTransformacao * vetorForcaDistribuidaGlobal;

	this->fxLocal = vetorForcaDistribuidaLocal.getValor(0, 0);
	this->fyLocal = vetorForcaDistribuidaLocal.getValor(1, 0);

	this->fxEquivalenteN1Local += this->fxLocal * this->comprimento / 2;
	this->fxEquivalenteN2Local += this->fxLocal * this->comprimento / 2;
	this->fyEquivalenteN1Local += this->fyLocal * this->comprimento / 2;
	this->fyEquivalenteN2Local += this->fyLocal * this->comprimento / 2;
	this->mzEquivalenteN1Local += this->fyLocal * this->comprimento * this->comprimento / 12;
	this->mzEquivalenteN2Local += -this->fyLocal * this->comprimento * this->comprimento / 12;

	Matriz vetorForcaEquivalenteLocal(6, 1);
	Matriz vetorForcaEquivalenteGlobal(6, 1);

	vetorForcaDistribuidaLocal.setValor(0, 0, this->fxEquivalenteN1Local);
	vetorForcaDistribuidaLocal.setValor(1, 0, this->fyEquivalenteN1Local);
	vetorForcaDistribuidaLocal.setValor(2, 0, this->mzEquivalenteN1Local);
	vetorForcaDistribuidaLocal.setValor(3, 0, this->fxEquivalenteN2Local);
	vetorForcaDistribuidaLocal.setValor(4, 0, this->fyEquivalenteN2Local);
	vetorForcaDistribuidaLocal.setValor(5, 0, this->mzEquivalenteN2Local);

	vetorForcaDistribuidaGlobal = (Matriz::transposta(this->matrizTransformacao)) * (vetorForcaDistribuidaLocal);

	this->fxEquivalenteN1Global += vetorForcaDistribuidaGlobal.getValor(0, 0);
	this->fyEquivalenteN1Global += vetorForcaDistribuidaGlobal.getValor(1, 0);
	this->mzEquivalenteN1Global += vetorForcaDistribuidaGlobal.getValor(2, 0);
	this->fxEquivalenteN2Global += vetorForcaDistribuidaGlobal.getValor(3, 0);
	this->fyEquivalenteN2Global += vetorForcaDistribuidaGlobal.getValor(4, 0);
	this->mzEquivalenteN2Global += vetorForcaDistribuidaGlobal.getValor(5, 0);
}

//Obter o carregamento equivalente em x no nó N1 da barra
double Barra::getFxEquivalenteGlobal_N1() {
	return this->fxEquivalenteN1Global;
}

//Obter o carregameto equivalente em y no nó N1 da barra
double Barra::getFyEquivalenteGlobal_N1() {
	return this->fyEquivalenteN1Global;
}

//Vai retornar a equação polinomial do deslocamento
EquacaoPolinomial Barra::getEquacaoDeslocamento()
{
	return this->des;
}

//Vai retornar a equação polinomial da rotação
EquacaoPolinomial Barra::getEquacaoRotacao() {
	return this->rot;
}

//Vai retornar a equação polinomial do momento fletor
EquacaoPolinomial Barra::getEquacaoMomentoFletor() {
	return this->momFletor;
}

//Vai retornar a equação polinomial do esforço cortante
EquacaoPolinomial Barra::getEquacaoEsforcoCortante() {
	return this->esfCortante;
}

//Vai retornar a equação polinomial do esforço normal
EquacaoPolinomial Barra::getEquacaoEsforcoNormal() {
	return this->esfNormal;
}

//Vai retornar a equação polinomial do deslocamento axial
EquacaoPolinomial Barra::getEquacaoDeslocamentoAxial()
{
	return this->desAxial;
}

//Obter o momento equivalente em z no nó N1 da barra
double Barra::getMzEquivalenteGlobal_N1() {
	return this->mzEquivalenteN1Global;
}

//Obter o carregamento equivalente em x no nó N2 da barra
double Barra::getFxEquivalenteGlobal_N2() {
	return this->fxEquivalenteN2Global;
}

//Obter o carregamento equivalente em y no nó N2 da barra
double Barra::getFyEquivalenteGlobal_N2() {
	return this->fyEquivalenteN2Global;
}

//Obter o momento equivalente em z no nó N2 da barra
double Barra::getMzEquivalenteGlobal_N2() {
	return this->mzEquivalenteN2Global;
}

//Calcular os esforços internos na barra
void Barra::calcularEquacaoEsforcosInternos(double dxNo1, double dyNo1, double rzNo1, 
											double dxNo2, double dyNo2, double rzNo2) {

	Matriz deslocamentoGlobal(6, 1); //matriz com os deslocamentos dos nós da barra no sistema de referência global
	deslocamentoGlobal.setValor(0, 0, dxNo1);
	deslocamentoGlobal.setValor(1, 0, dyNo1);
	deslocamentoGlobal.setValor(2, 0, rzNo1);
	deslocamentoGlobal.setValor(3, 0, dxNo2);
	deslocamentoGlobal.setValor(4, 0, dyNo2);
	deslocamentoGlobal.setValor(5, 0, rzNo2);

	Matriz deslocamentoLocal(6, 1); //matriz com os deslocamentos dos nós da barra no sistema de referência local
	deslocamentoLocal = this->matrizTransformacao * deslocamentoGlobal;

	this->desGlobal = deslocamentoGlobal;
	this->desLocal = deslocamentoLocal;

	Matriz forcaGlobal(6, 1); //matriz com o carregamento distribuido da barra no sistema de referência global
	forcaGlobal.setValor(0, 0, this->fxGlobal);
	forcaGlobal.setValor(1, 0, this->fyGlobal);
	forcaGlobal.setValor(2, 0, 0);
	forcaGlobal.setValor(3, 0, this->fxGlobal);
	forcaGlobal.setValor(4, 0, this->fyGlobal);
	forcaGlobal.setValor(5, 0, 0);

	Matriz forcaLocal(6, 1); //matriz com o carregamento distribuido da barra no sistema de referência local
	forcaLocal = this->matrizTransformacao * forcaGlobal;

	Matriz resultadoEquacao(6, 1);
	resultadoEquacao.setValor(0, 0, deslocamentoLocal.getValor(1, 0));
	resultadoEquacao.setValor(1, 0, deslocamentoLocal.getValor(2, 0));
	resultadoEquacao.setValor(2, 0, deslocamentoLocal.getValor(4, 0));
	resultadoEquacao.setValor(3, 0, deslocamentoLocal.getValor(5, 0));
	resultadoEquacao.setValor(4, 0, forcaLocal.getValor(1, 0));
	resultadoEquacao.setValor(5, 0, forcaLocal.getValor(1, 0));

	Matriz coeficienteEquacao(6, 6); //matriz com os coeficientes para cálculo da equação do deslocamento

	//PRIMEIRA LINHA
	coeficienteEquacao.setValor(0, 0, 1);
	coeficienteEquacao.setValor(0, 1, 0);
	coeficienteEquacao.setValor(0, 2, 0);
	coeficienteEquacao.setValor(0, 3, 0);
	coeficienteEquacao.setValor(0, 4, 0);
	coeficienteEquacao.setValor(0, 5, 0);

	//SEGUNDA LINHA
	coeficienteEquacao.setValor(1, 0, 0);
	coeficienteEquacao.setValor(1, 1, 1);
	coeficienteEquacao.setValor(1, 2, 0);
	coeficienteEquacao.setValor(1, 3, 0);
	coeficienteEquacao.setValor(1, 4, 0);
	coeficienteEquacao.setValor(1, 5, 0);

	//TERCEIRA LINHA
	coeficienteEquacao.setValor(2, 0, 1);
	coeficienteEquacao.setValor(2, 1, pow(this->comprimento, 1));
	coeficienteEquacao.setValor(2, 2, pow(this->comprimento, 2));
	coeficienteEquacao.setValor(2, 3, pow(this->comprimento, 3));
	coeficienteEquacao.setValor(2, 4, pow(this->comprimento, 4));
	coeficienteEquacao.setValor(2, 5, pow(this->comprimento, 5));

	//QUARTA LINHA
	coeficienteEquacao.setValor(3, 0, 0);
	coeficienteEquacao.setValor(3, 1, 1);
	coeficienteEquacao.setValor(3, 2, 2*pow(this->comprimento, 1));
	coeficienteEquacao.setValor(3, 3, 3*pow(this->comprimento, 2));
	coeficienteEquacao.setValor(3, 4, 4*pow(this->comprimento, 3));
	coeficienteEquacao.setValor(3, 5, 5*pow(this->comprimento, 4));

	//QUINTA LINHA
	coeficienteEquacao.setValor(4, 0, 0);
	coeficienteEquacao.setValor(4, 1, 0);
	coeficienteEquacao.setValor(4, 2, 0);
	coeficienteEquacao.setValor(4, 3, 0);
	coeficienteEquacao.setValor(4, 4, 24);
	coeficienteEquacao.setValor(4, 5, 0);

	//SEXTA LINHA
	coeficienteEquacao.setValor(5, 0, 0);
	coeficienteEquacao.setValor(5, 1, 0);
	coeficienteEquacao.setValor(5, 2, 0);
	coeficienteEquacao.setValor(5, 3, 0);
	coeficienteEquacao.setValor(5, 4, 24);
	coeficienteEquacao.setValor(5, 5, 120 * pow(this->comprimento, 1));

	Matriz resultado = SistemaLinear::metodoDeGaussDireto(coeficienteEquacao, resultadoEquacao);
	resultado.transpor();

	EquacaoPolinomial deslocamento(5);
	deslocamento.setVetorCoeficiente(resultado);

	this->setDeslocamento(deslocamento);


	//Logo após, pode-se definir a equação do esforço normal
	Matriz resultadoEquacaoNormal(4, 1);
	resultadoEquacaoNormal.setValor(0, 0, deslocamentoLocal.getValor(0, 0));
	resultadoEquacaoNormal.setValor(1, 0, deslocamentoLocal.getValor(3, 0));
	resultadoEquacaoNormal.setValor(2, 0, -this->fxLocal); //fxi
	resultadoEquacaoNormal.setValor(3, 0, -this->fxLocal); //fxj

	//Cria-se a função de forma para determinação do esforço normal
	Matriz coeficienteEquacaoNormal(4, 4);
	
	//1 LINHA
	coeficienteEquacaoNormal.setValor(0, 0, 1);
	coeficienteEquacaoNormal.setValor(0, 1, 0);
	coeficienteEquacaoNormal.setValor(0, 2, 0);
	coeficienteEquacaoNormal.setValor(0, 3, 0);

	//2 LINHA
	coeficienteEquacaoNormal.setValor(1, 0, 1);
	coeficienteEquacaoNormal.setValor(1, 1, this->comprimento);
	coeficienteEquacaoNormal.setValor(1, 2, pow(this->comprimento, 2));
	coeficienteEquacaoNormal.setValor(1, 3, pow(this->comprimento, 3));

	//3 LINHA
	coeficienteEquacaoNormal.setValor(2, 0, 0);
	coeficienteEquacaoNormal.setValor(2, 1, 0);
	coeficienteEquacaoNormal.setValor(2, 2, 2 * this->elasticidade * this->area);
	coeficienteEquacaoNormal.setValor(2, 3, 0);

	//4 LINHA
	coeficienteEquacaoNormal.setValor(3, 0, 0);
	coeficienteEquacaoNormal.setValor(3, 1, 0);
	coeficienteEquacaoNormal.setValor(3, 2, 2 * this->elasticidade * this->area);
	coeficienteEquacaoNormal.setValor(3, 3, 6 * this->comprimento * this->elasticidade * this->area);

	//Resultados da equação do deslocamento axial
	Matriz coeficientesDeslocamentoAxial = SistemaLinear::metodoDeGaussDireto(coeficienteEquacaoNormal, resultadoEquacaoNormal);
	EquacaoPolinomial deslocamentoAxial(3);
	deslocamentoAxial.setCoeficiente(0, coeficientesDeslocamentoAxial.getValor(0, 0));
	deslocamentoAxial.setCoeficiente(1, coeficientesDeslocamentoAxial.getValor(1, 0));
	deslocamentoAxial.setCoeficiente(2, coeficientesDeslocamentoAxial.getValor(2, 0));
	deslocamentoAxial.setCoeficiente(3, coeficientesDeslocamentoAxial.getValor(3, 0));

	EquacaoPolinomial esforcoNormal = deslocamentoAxial.derivada();
	esforcoNormal = esforcoNormal * (this->elasticidade * this->area);

	this->desAxial = deslocamentoAxial;
	this->esfNormal = esforcoNormal;
}

//Vai retornar se há ou não rótula no nó 01 da barra
bool Barra::getRotulaN1() {
	return this->rotulaN1;
}

//Vai retornar se há ou não rótula no nó 02 da barra
bool Barra::getRotulaN2() {
	return this->rotulaN2;
}

