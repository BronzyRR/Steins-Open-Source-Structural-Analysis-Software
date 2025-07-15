#pragma once
#include "Ponto.h"
#include <string>

class Node
{
private:
	int id; //identificador do nó, vai facilitar em alguns processos, como o flood fill para definir os pórticos

	bool restricaoHorizontal = false; //se existe restrição ao deslocamento transversal em x
	bool restricaoVertical = false; //se existe restrição ao deslocamento transversal em y
	bool restricaoRotacao = false; //se existe restrição à rotação em z

	//FORÇAS NODAIS ATUANTES
	double fx = 0; //força atuante na direção x
	double fy = 0; //força atuante na direção y
	double mz = 0; //momento atuante na direção z

	//DESLOCAMENTOS [RESULTADOS]
	double dxGlobal; //deslocamento na direção x [global]
	double dyGlobal; //deslocamento na direção y [global]
	double rzGlobal; //rotação na direção z [global]

	//REAÇÕES
	double reacaoEmX; //força [reação] na direção x
	double reacaoEmY; //força [reação] na direção y
	double reacaoEmZ; //força [reação] na direção z

public:
	double fxBackup = 0;
	double fyBackup = 0;
	double mzBackup = 0;

	Ponto pos; //vai guardar a posição do nó num espaço bidimensional
	
	Node(); //método construtor vazio
	Node(int id, double x, double y); //inicializar o nó apenas com a posição. Neste caso, será automaticamente um nó livre
	Node(int id, double x, double y, int tipo); //inicializar o nó com a posição e tipo de apoio (se é nó livre, restrito em x, etc.)
	Node(int id, double x, double y, bool rH, bool rV, bool rR); //rh = restricaoHorizontal; rv = restricaoVertical; rr=restricaoRotacao
	
	void addCarga(double fx, double fy, double mz); //método para adicionar uma carga (em x, y ou z) no nó em questão
	void addFx(double fx); //método para adicionar uma carga em x
	void addFy(double fy); //método para adicionar uma carga em y
	void addMz(double mz); //método para adicionar um momento em z
	void zerarCarga(); //método para remover todas as cargas de um determinado nó

	//MÉTODOS GETTERS E SETTERS
	void setId(int id); //definir o id do nó
	int getId(); //obter o valor do id do nó
	void setFx(double fx); //definir o valor de fx
	double getFx(); //obter o valor de fx
	void setFy(double fy); //definir o valor de fy
	double getFy(); //obter o valor de fy
	void setMz(double mz); //definir o valor de mz
	double getMz(); //obter o valor de mz
	
	//MÉTODOS GETTERS E SETTERS PARA OS DESLOCAMENTOS
	void setDxGlobal(double dx);
	void setDyGlobal(double dy);
	void setRzGlobal(double rz);
	double getDxGlobal();
	double getDyGlobal();
	double getRzGlobal();

	//MÉTODOS GETTERS E SETTERS PARA AS REAÇÕES
	double getReacaoEmX();
	void setReacaoEmX(double reacaoEmX);
	double getReacaoEmY();
	void setReacaoEmY(double reacaoEmY);
	double getReacaoEmZ();
	void setReacaoEmZ(double reacaoEmZ);

	//MÉTODO [RETORNA STRING] PARA OBTER INFORMAÇÕES DAS RESTRIÇÕES
	bool getRh();
	bool getRv();
	bool getRz();

	//GRAUS DE LIBERDADE REFERENTES A ESTRUTURA TOTAL
	int glx;
	int gly;
	int glz;
};

