#include "Node.h"

//Método construtor vazio
Node::Node() {

}

//Método construtor apenas com a posição do nó
Node::Node(int id, double x, double y) {
	this->id = id;
	this->pos.setX(x);
	this->pos.setY(y);
}

//Método construtor com a posição do nó e tipo de apoio
Node::Node(int id, double x, double y, int tipo) {
	this->pos.setX(x);
	this->pos.setY(y);
	this->id = id;
	switch (tipo) {
		//Nó totalmente livre
		case 1:
			this->restricaoHorizontal = false;
			this->restricaoVertical = false;
			this->restricaoRotacao = false;
			break;
		//Nó com restrição apenas ao deslocamento transversal em x
		case 2:
			this->restricaoHorizontal = true;
			this->restricaoVertical = false;
			this->restricaoRotacao = false;
			break;
		//Nó com restrição apenas ao deslocamento transversal em y
		case 3:
			this->restricaoHorizontal = false;
			this->restricaoVertical = true;
			this->restricaoRotacao = false;
			break;
		//Nó com restrição apenas à rotação em z
		case 4:
			this->restricaoHorizontal = false;
			this->restricaoVertical = false;
			this->restricaoRotacao = true;
			break;
		//Nó com restrição ao deslocamento transversal em x e y
		case 5:
			this->restricaoHorizontal = true;
			this->restricaoVertical = true;
			this->restricaoRotacao = false;
			break;
		//Nó com restrição ao deslocamento transversal em x e rotação em z
		case 6:
			this->restricaoHorizontal = true;
			this->restricaoVertical = false;
			this->restricaoRotacao = true;
			break;
		//Nó com restrição ao deslocamento transversal em y e rotação em z
		case 7:
			this->restricaoHorizontal = false;
			this->restricaoVertical = true;
			this->restricaoRotacao = true;
			break;
		//Nó com restrição a tudo (engaste)
		case 8:
			this->restricaoHorizontal = true;
			this->restricaoVertical = true;
			this->restricaoRotacao = true;
			break;
	}
}

//Método construtor com a posição do nó e descrição das restrições
Node::Node(int id, double x, double y, bool rH, bool rV, bool rR) {
	this->pos.setX(x);
	this->pos.setY(y);
	this->restricaoHorizontal = rH;
	this->restricaoVertical = rV;
	this->restricaoRotacao = rR;
	this->id = id;
}

//Método para adicionar uma carga no nó
void Node::addCarga(double fx, double fy, double mz) {
	this->fx += fx;
	this->fy += fy;
	this->mz += mz;
}

//Método para remover as cargas de um nó
void Node::zerarCarga() {
	this->fx = 0;
	this->fy = 0;
	this->mz = 0;
}

//Método para adicionar uma carga em x
void Node::addFx(double fx) {
	this->fx += fx;
}

//Método para adicionar uma carga em y
void Node::addFy(double fy) {
	this->fy += fy;
}

//Método para adicionar um momento em z
void Node::addMz(double mz) {
	this->mz += mz;
}

//Método para definir fx do nó
void Node::setFx(double fx) {
	this->fx = fx;
}

//Método para obter fx do nó
double Node::getFx() {
	return this->fx;
}

//Método para definir fy do nó
void Node::setFy(double fy) {
	this->fy = fy;
}

//Método para obter fy do nó
double Node::getFy() {
	return this->fy;
}

//Método para definir mz do nó
void Node::setMz(double mz) {
	this->mz = mz;
}

//Método para obter mz do nó
double Node::getMz() {
	return this->mz;
}

//Método para definir o deslocamento em x [direção global]
void Node::setDxGlobal(double dx)
{
	this->dxGlobal = dx;
}

//Método para definir o deslocamento em y [direção global]
void Node::setDyGlobal(double dy)
{
	this->dyGlobal = dy;
}

//Método para definir a rotação em z do nó [direção global]
void Node::setRzGlobal(double rz)
{
	this->rzGlobal = rz;
}

//Vai retornar o deslocamento em x [direção global]
double Node::getDxGlobal()
{
	return this->dxGlobal;
}

//Vai retornar o deslocamento em y [direção global]
double Node::getDyGlobal() {
	return this->dyGlobal;
}

//Vai retornar a rotação em z [direção global]
double Node::getRzGlobal() {
	return this->rzGlobal;
}

//Vai retornar a reação em x
double Node::getReacaoEmX() {
	return this->reacaoEmX;
}

//Vai retornar a reação em y
double Node::getReacaoEmY() {
	return this->reacaoEmY;
}

//Vai retornar a reação em z
double Node::getReacaoEmZ() {
	return this->reacaoEmZ;
}

//Método para definir a reação em x
void Node::setReacaoEmX(double reacaoEmX) {
	this->reacaoEmX = reacaoEmX;
}

//Método para definir a reação em y
void Node::setReacaoEmY(double reacaoEmY) {
	this->reacaoEmY = reacaoEmY;
}

//Método para definir a reação em z
void Node::setReacaoEmZ(double reacaoEmZ) {
	this->reacaoEmZ = reacaoEmZ;
}

//Método para definir o id do nó
void Node::setId(int id) {
	this->id = id;
}

//Método para obter o id do nó
int Node::getId() {
	return this->id;
}

//Método para obter informações sobre a restrição horizontal
bool Node::getRh() {
	return this->restricaoHorizontal;
}

//Método para obter informações sobre a restrição vertical
bool Node::getRv() {
	return this->restricaoVertical;
}

//Método para obter informações sobre a restrição à rotação em Z
bool Node::getRz() {
	return this->restricaoRotacao;
}
