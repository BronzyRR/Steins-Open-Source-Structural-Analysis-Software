#include "Estrutura.h"
#include "Barra.h"
#include "Node.h"
#include "SistemaLinear.h"
#include <vector>
#include <set>
#include <map>
#include <iostream>


/*Método para determinar as deformações nos nós da estrutura.E através deles, determinar as equações dos
	esforços internos nas barras.*/
void Estrutura::calcular(std::vector<Node>& nosAnalisados, std::vector<Barra>& barrasAnalisadas){

	/*Primeiramente, deve-se criar um map relacionando o id do nó com sua posição no vetor.
	Isso irá simplificar a implementação dos procedimentos do MEF*/
	std::map<int, int> posicaoDoNoPeloId;
	for (int i = 0; i < nosAnalisados.size(); i++) {
		posicaoDoNoPeloId.insert(std::make_pair(nosAnalisados[i].getId(), i));
	}

	/*Definir o tamanho da matriz de rigidez total, levando em conta os graus de liberdade
	extras provenientes das rótulas*/
	int contadorGrauDeLiberdadeTotal = 0;
	std::vector<double> vetorForca;
	for (int i = 0; i < nosAnalisados.size(); i++) {
		int id = nosAnalisados[i].getId();
		int grauLiberdadeEmX = contadorGrauDeLiberdadeTotal++; //o grau de liberdade em x será o mesmo para todas as barras, independentemente se é uma rótula ou não
		int grauLiberdadeEmY = contadorGrauDeLiberdadeTotal++; //o grau de liberdade em y será o mesmo para todas as barras, independentemente se é uma rótula ou não

		nosAnalisados[i].glx = grauLiberdadeEmX;
		nosAnalisados[i].gly = grauLiberdadeEmY;

		vetorForca.push_back(nosAnalisados[i].getFx());
		vetorForca.push_back(nosAnalisados[i].getFy());


		int glBaseEmZ = -1;
		for (int j = 0; j < barrasAnalisadas.size(); j++) {
			if ((barrasAnalisadas[j].n1.getId() == id)) { //se o nó n1 da barra for igual ao nó analisado
				if (barrasAnalisadas[j].getRotulaN1()) { //se for uma rótula
					int grauLiberdadeEmZ = contadorGrauDeLiberdadeTotal++;
					vetorForca.push_back(barrasAnalisadas[j].getMzEquivalenteGlobal_N1());

					barrasAnalisadas[j].glxNo1.first = grauLiberdadeEmX;
					barrasAnalisadas[j].glyNo1.first = grauLiberdadeEmY;
					barrasAnalisadas[j].glzNo1.first = grauLiberdadeEmZ;

					barrasAnalisadas[j].glxNo1.second = nosAnalisados[i].getRh();
					barrasAnalisadas[j].glyNo1.second = nosAnalisados[i].getRv();
					barrasAnalisadas[j].glzNo1.second = false;
				}
				else { //se não for uma rótula
					if (glBaseEmZ == -1) {
						glBaseEmZ = 1;

						int grauLiberdadeEmZ = contadorGrauDeLiberdadeTotal++;
						glBaseEmZ = grauLiberdadeEmZ;
						vetorForca.push_back(nosAnalisados[i].getMz());

						barrasAnalisadas[j].glxNo1.first = grauLiberdadeEmX;
						barrasAnalisadas[j].glyNo1.first = grauLiberdadeEmY;
						barrasAnalisadas[j].glzNo1.first = grauLiberdadeEmZ;

						barrasAnalisadas[j].glxNo1.second = nosAnalisados[i].getRh();
						barrasAnalisadas[j].glyNo1.second = nosAnalisados[i].getRv();
						barrasAnalisadas[j].glzNo1.second = nosAnalisados[i].getRz();
					}
					else {
						barrasAnalisadas[j].glxNo1.first = grauLiberdadeEmX;
						barrasAnalisadas[j].glyNo1.first = grauLiberdadeEmY;
						barrasAnalisadas[j].glzNo1.first = glBaseEmZ;

						barrasAnalisadas[j].glxNo1.second = nosAnalisados[i].getRh();
						barrasAnalisadas[j].glyNo1.second = nosAnalisados[i].getRv();
						barrasAnalisadas[j].glzNo1.second = nosAnalisados[i].getRz();
					}
				}
			}

			if ((barrasAnalisadas[j].n2.getId() == id)) { //se o nó n2 da barra for igual ao nó analisado
				if (barrasAnalisadas[j].getRotulaN2()) { //se for uma rótula
					int grauLiberdadeEmZ = contadorGrauDeLiberdadeTotal++;
					vetorForca.push_back(barrasAnalisadas[j].getMzEquivalenteGlobal_N2());

					barrasAnalisadas[j].glxNo2.first = grauLiberdadeEmX;
					barrasAnalisadas[j].glyNo2.first = grauLiberdadeEmY;
					barrasAnalisadas[j].glzNo2.first = grauLiberdadeEmZ;

					barrasAnalisadas[j].glxNo2.second = nosAnalisados[i].getRh();
					barrasAnalisadas[j].glyNo2.second = nosAnalisados[i].getRv();
					barrasAnalisadas[j].glzNo2.second = false;
				}
				else { //se não for uma rótula
					if (glBaseEmZ == -1) {
						int grauLiberdadeEmZ = contadorGrauDeLiberdadeTotal++;
						glBaseEmZ = grauLiberdadeEmZ;
						vetorForca.push_back(nosAnalisados[i].getMz());

						barrasAnalisadas[j].glxNo2.first = grauLiberdadeEmX;
						barrasAnalisadas[j].glyNo2.first = grauLiberdadeEmY;
						barrasAnalisadas[j].glzNo2.first = grauLiberdadeEmZ;

						barrasAnalisadas[j].glxNo2.second = nosAnalisados[i].getRh();
						barrasAnalisadas[j].glyNo2.second = nosAnalisados[i].getRv();
						barrasAnalisadas[j].glzNo2.second = nosAnalisados[i].getRz();
					}
					else {
						barrasAnalisadas[j].glxNo2.first = grauLiberdadeEmX;
						barrasAnalisadas[j].glyNo2.first = grauLiberdadeEmY;
						barrasAnalisadas[j].glzNo2.first = glBaseEmZ;

						barrasAnalisadas[j].glxNo2.second = nosAnalisados[i].getRh();
						barrasAnalisadas[j].glyNo2.second = nosAnalisados[i].getRv();
						barrasAnalisadas[j].glzNo2.second = nosAnalisados[i].getRz();
					}
				}
			}
		}

		nosAnalisados[i].glz = glBaseEmZ;
	}

	/*Deve-se transformar o vetorForca em uma matriz (para posterior utilização na resolução
	do sistema linear).*/
	Matriz matrizForca(vetorForca.size(), 1);
	for (int i = 0; i < vetorForca.size(); i++) {
		matrizForca.setValor(i, 0, vetorForca[i]);
	}

	/*Logo após, cria-se a matriz de rigidez total da estrutura*/
	Matriz matrizDeRigidezTotal(contadorGrauDeLiberdadeTotal, contadorGrauDeLiberdadeTotal);
	matrizDeRigidezTotal.preencher(0);

	for (int i = 0; i < barrasAnalisadas.size(); i++) {
		int posDxNo1 = barrasAnalisadas[i].glxNo1.first;
		int posDyNo1 = barrasAnalisadas[i].glyNo1.first;
		int posRzNo1 = barrasAnalisadas[i].glzNo1.first;

		int posDxNo2 = barrasAnalisadas[i].glxNo2.first;
		int posDyNo2 = barrasAnalisadas[i].glyNo2.first;
		int posRzNo2 = barrasAnalisadas[i].glzNo2.first;

		//Logo após, deve-se obter a matriz de rigidez global da barra em questão
		Matriz matrizDeRigidezGlobalBarra = barrasAnalisadas[i].getMatrizRigidezGlobal();

		//PRIMEIRA LINHA [referente ao grau de liberdade em x do nó 01]
		matrizDeRigidezTotal.addValor(posDxNo1, posDxNo1, matrizDeRigidezGlobalBarra.getValor(0, 0));
		matrizDeRigidezTotal.addValor(posDxNo1, posDyNo1, matrizDeRigidezGlobalBarra.getValor(0, 1));
		matrizDeRigidezTotal.addValor(posDxNo1, posRzNo1, matrizDeRigidezGlobalBarra.getValor(0, 2));
		matrizDeRigidezTotal.addValor(posDxNo1, posDxNo2, matrizDeRigidezGlobalBarra.getValor(0, 3));
		matrizDeRigidezTotal.addValor(posDxNo1, posDyNo2, matrizDeRigidezGlobalBarra.getValor(0, 4));
		matrizDeRigidezTotal.addValor(posDxNo1, posRzNo2, matrizDeRigidezGlobalBarra.getValor(0, 5));

		//SEGUNDA LINHA [referente ao grau de liberdade em y do nó 01]
		matrizDeRigidezTotal.addValor(posDyNo1, posDxNo1, matrizDeRigidezGlobalBarra.getValor(1, 0));
		matrizDeRigidezTotal.addValor(posDyNo1, posDyNo1, matrizDeRigidezGlobalBarra.getValor(1, 1));
		matrizDeRigidezTotal.addValor(posDyNo1, posRzNo1, matrizDeRigidezGlobalBarra.getValor(1, 2));
		matrizDeRigidezTotal.addValor(posDyNo1, posDxNo2, matrizDeRigidezGlobalBarra.getValor(1, 3));
		matrizDeRigidezTotal.addValor(posDyNo1, posDyNo2, matrizDeRigidezGlobalBarra.getValor(1, 4));
		matrizDeRigidezTotal.addValor(posDyNo1, posRzNo2, matrizDeRigidezGlobalBarra.getValor(1, 5));

		//TERCEIRA LINHA [referente ao grau de liberdade em z do nó 01]
		matrizDeRigidezTotal.addValor(posRzNo1, posDxNo1, matrizDeRigidezGlobalBarra.getValor(2, 0));
		matrizDeRigidezTotal.addValor(posRzNo1, posDyNo1, matrizDeRigidezGlobalBarra.getValor(2, 1));
		matrizDeRigidezTotal.addValor(posRzNo1, posRzNo1, matrizDeRigidezGlobalBarra.getValor(2, 2));
		matrizDeRigidezTotal.addValor(posRzNo1, posDxNo2, matrizDeRigidezGlobalBarra.getValor(2, 3));
		matrizDeRigidezTotal.addValor(posRzNo1, posDyNo2, matrizDeRigidezGlobalBarra.getValor(2, 4));
		matrizDeRigidezTotal.addValor(posRzNo1, posRzNo2, matrizDeRigidezGlobalBarra.getValor(2, 5));

		//QUARTA LINHA [referente ao grau de liberdade em x do nó 02]
		matrizDeRigidezTotal.addValor(posDxNo2, posDxNo1, matrizDeRigidezGlobalBarra.getValor(3, 0));
		matrizDeRigidezTotal.addValor(posDxNo2, posDyNo1, matrizDeRigidezGlobalBarra.getValor(3, 1));
		matrizDeRigidezTotal.addValor(posDxNo2, posRzNo1, matrizDeRigidezGlobalBarra.getValor(3, 2));
		matrizDeRigidezTotal.addValor(posDxNo2, posDxNo2, matrizDeRigidezGlobalBarra.getValor(3, 3));
		matrizDeRigidezTotal.addValor(posDxNo2, posDyNo2, matrizDeRigidezGlobalBarra.getValor(3, 4));
		matrizDeRigidezTotal.addValor(posDxNo2, posRzNo2, matrizDeRigidezGlobalBarra.getValor(3, 5));

		//QUINTA LINHA [referente ao grau de liberdade em y do nó 02]
		matrizDeRigidezTotal.addValor(posDyNo2, posDxNo1, matrizDeRigidezGlobalBarra.getValor(4, 0));
		matrizDeRigidezTotal.addValor(posDyNo2, posDyNo1, matrizDeRigidezGlobalBarra.getValor(4, 1));
		matrizDeRigidezTotal.addValor(posDyNo2, posRzNo1, matrizDeRigidezGlobalBarra.getValor(4, 2));
		matrizDeRigidezTotal.addValor(posDyNo2, posDxNo2, matrizDeRigidezGlobalBarra.getValor(4, 3));
		matrizDeRigidezTotal.addValor(posDyNo2, posDyNo2, matrizDeRigidezGlobalBarra.getValor(4, 4));
		matrizDeRigidezTotal.addValor(posDyNo2, posRzNo2, matrizDeRigidezGlobalBarra.getValor(4, 5));

		//SEXTA LINHA [referente ao grau de liberdade em z do nó 02]
		matrizDeRigidezTotal.addValor(posRzNo2, posDxNo1, matrizDeRigidezGlobalBarra.getValor(5, 0));
		matrizDeRigidezTotal.addValor(posRzNo2, posDyNo1, matrizDeRigidezGlobalBarra.getValor(5, 1));
		matrizDeRigidezTotal.addValor(posRzNo2, posRzNo1, matrizDeRigidezGlobalBarra.getValor(5, 2));
		matrizDeRigidezTotal.addValor(posRzNo2, posDxNo2, matrizDeRigidezGlobalBarra.getValor(5, 3));
		matrizDeRigidezTotal.addValor(posRzNo2, posDyNo2, matrizDeRigidezGlobalBarra.getValor(5, 4));
		matrizDeRigidezTotal.addValor(posRzNo2, posRzNo2, matrizDeRigidezGlobalBarra.getValor(5, 5));
	}

	Matriz matrizDeRigidezTotalBackup = matrizDeRigidezTotal;
	

	/*Remover as linhas e colunas da matriz de rigidez global referentes às restrições*/
	std::set<int> grausApagar; //graus que devem ser apagados
	
	for (int i = 0; i < barrasAnalisadas.size(); i++) {
		if (barrasAnalisadas[i].glxNo1.second) {
			grausApagar.insert(barrasAnalisadas[i].glxNo1.first);
		}

		if (barrasAnalisadas[i].glyNo1.second) {
			grausApagar.insert(barrasAnalisadas[i].glyNo1.first);
		}

		if (barrasAnalisadas[i].glzNo1.second) {
			grausApagar.insert(barrasAnalisadas[i].glzNo1.first);
		}

		if (barrasAnalisadas[i].glxNo2.second) {
			grausApagar.insert(barrasAnalisadas[i].glxNo2.first);
		}

		if (barrasAnalisadas[i].glyNo2.second) {
			grausApagar.insert(barrasAnalisadas[i].glyNo2.first);
		}

		if (barrasAnalisadas[i].glzNo2.second) {
			grausApagar.insert(barrasAnalisadas[i].glzNo2.first);
		}
	}

	int correcao = 0;
	std::set<int>::iterator it;
	for (it = grausApagar.begin(); it != grausApagar.end(); it++) {
		int linha = *it - correcao;
		int coluna = *it - correcao;
		correcao += 1;

		matrizDeRigidezTotal.apagarLinha(linha);
		matrizDeRigidezTotal.apagarColuna(coluna);

		matrizForca.apagarLinha(linha);
	}

	//Com tudo isso definido, basta calcular o sistema linear e obter as deformações nos nós!
	Matriz resultado = SistemaLinear::metodoDeGaussDireto(matrizDeRigidezTotal, matrizForca);

	//Logo após, deve-se definir o vetor com os deslocamentos globais de toda a estrutura (adicionando 0 onde for restrito)
	Matriz deslocamentosEstrutura(contadorGrauDeLiberdadeTotal, 1);
	correcao = 0;
	for (int i = 0; i < contadorGrauDeLiberdadeTotal; i++) {
		if (grausApagar.find(i) != grausApagar.end()) {
			correcao++;
			deslocamentosEstrutura.setValor(i, 0, 0.0);
		}
		else {
			deslocamentosEstrutura.setValor(i, 0, resultado.getValor(i - correcao, 0));
		}
	}
	
	
	for (int i = 0; i < barrasAnalisadas.size(); i++) {
		barrasAnalisadas[i].calcularEquacaoEsforcosInternos(deslocamentosEstrutura.getValor(barrasAnalisadas[i].glxNo1.first, 0),
															deslocamentosEstrutura.getValor(barrasAnalisadas[i].glyNo1.first, 0),
															deslocamentosEstrutura.getValor(barrasAnalisadas[i].glzNo1.first, 0),
															deslocamentosEstrutura.getValor(barrasAnalisadas[i].glxNo2.first, 0),
															deslocamentosEstrutura.getValor(barrasAnalisadas[i].glyNo2.first, 0),
															deslocamentosEstrutura.getValor(barrasAnalisadas[i].glzNo2.first, 0));
	}

	Matriz resultadoReacoes = matrizDeRigidezTotalBackup * deslocamentosEstrutura;

	for (int i = 0; i < nosAnalisados.size(); i++) {
		int posx = nosAnalisados[i].glx;
		int posy = nosAnalisados[i].gly;

		nosAnalisados[i].setReacaoEmX(resultadoReacoes.getValor(posx, 0) - nosAnalisados[i].getFx());
		nosAnalisados[i].setReacaoEmY(resultadoReacoes.getValor(posy, 0) - nosAnalisados[i].getFy());

		nosAnalisados[i].setDxGlobal(deslocamentosEstrutura.getValor(posx, 0));
		nosAnalisados[i].setDyGlobal(deslocamentosEstrutura.getValor(posy, 0));

		if (nosAnalisados[i].glz == -1) {
			if (nosAnalisados[i].getRz()) {
				nosAnalisados[i].setReacaoEmZ(0 - nosAnalisados[i].getMz());
				nosAnalisados[i].setRzGlobal(0);
			}
			else {
				nosAnalisados[i].setReacaoEmZ(0);
				nosAnalisados[i].setRzGlobal(0);
			}
			
		}
		else {
			int posz = nosAnalisados[i].glz;
			nosAnalisados[i].setReacaoEmZ(resultadoReacoes.getValor(posz, 0) - nosAnalisados[i].getMz());
			nosAnalisados[i].setRzGlobal(deslocamentosEstrutura.getValor(posz, 0));
		}
	}

}

