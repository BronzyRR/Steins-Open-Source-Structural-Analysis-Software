#pragma once
#include "Ponto.h"
#include <string>

class Node
{
private:
	int id; //identificador do n�, vai facilitar em alguns processos, como o flood fill para definir os p�rticos

	bool restricaoHorizontal = false; //se existe restri��o ao deslocamento transversal em x
	bool restricaoVertical = false; //se existe restri��o ao deslocamento transversal em y
	bool restricaoRotacao = false; //se existe restri��o � rota��o em z

	//FOR�AS NODAIS ATUANTES
	double fx = 0; //for�a atuante na dire��o x
	double fy = 0; //for�a atuante na dire��o y
	double mz = 0; //momento atuante na dire��o z

	//DESLOCAMENTOS [RESULTADOS]
	double dxGlobal; //deslocamento na dire��o x [global]
	double dyGlobal; //deslocamento na dire��o y [global]
	double rzGlobal; //rota��o na dire��o z [global]

	//REA��ES
	double reacaoEmX; //for�a [rea��o] na dire��o x
	double reacaoEmY; //for�a [rea��o] na dire��o y
	double reacaoEmZ; //for�a [rea��o] na dire��o z

public:
	double fxBackup = 0;
	double fyBackup = 0;
	double mzBackup = 0;

	Ponto pos; //vai guardar a posi��o do n� num espa�o bidimensional
	
	Node(); //m�todo construtor vazio
	Node(int id, double x, double y); //inicializar o n� apenas com a posi��o. Neste caso, ser� automaticamente um n� livre
	Node(int id, double x, double y, int tipo); //inicializar o n� com a posi��o e tipo de apoio (se � n� livre, restrito em x, etc.)
	Node(int id, double x, double y, bool rH, bool rV, bool rR); //rh = restricaoHorizontal; rv = restricaoVertical; rr=restricaoRotacao
	
	void addCarga(double fx, double fy, double mz); //m�todo para adicionar uma carga (em x, y ou z) no n� em quest�o
	void addFx(double fx); //m�todo para adicionar uma carga em x
	void addFy(double fy); //m�todo para adicionar uma carga em y
	void addMz(double mz); //m�todo para adicionar um momento em z
	void zerarCarga(); //m�todo para remover todas as cargas de um determinado n�

	//M�TODOS GETTERS E SETTERS
	void setId(int id); //definir o id do n�
	int getId(); //obter o valor do id do n�
	void setFx(double fx); //definir o valor de fx
	double getFx(); //obter o valor de fx
	void setFy(double fy); //definir o valor de fy
	double getFy(); //obter o valor de fy
	void setMz(double mz); //definir o valor de mz
	double getMz(); //obter o valor de mz
	
	//M�TODOS GETTERS E SETTERS PARA OS DESLOCAMENTOS
	void setDxGlobal(double dx);
	void setDyGlobal(double dy);
	void setRzGlobal(double rz);
	double getDxGlobal();
	double getDyGlobal();
	double getRzGlobal();

	//M�TODOS GETTERS E SETTERS PARA AS REA��ES
	double getReacaoEmX();
	void setReacaoEmX(double reacaoEmX);
	double getReacaoEmY();
	void setReacaoEmY(double reacaoEmY);
	double getReacaoEmZ();
	void setReacaoEmZ(double reacaoEmZ);

	//M�TODO [RETORNA STRING] PARA OBTER INFORMA��ES DAS RESTRI��ES
	bool getRh();
	bool getRv();
	bool getRz();

	//GRAUS DE LIBERDADE REFERENTES A ESTRUTURA TOTAL
	int glx;
	int gly;
	int glz;
};

