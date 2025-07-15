#include "Node.h"

//M�todo construtor vazio
Node::Node() {

}

//M�todo construtor apenas com a posi��o do n�
Node::Node(int id, double x, double y) {
	this->id = id;
	this->pos.setX(x);
	this->pos.setY(y);
}

//M�todo construtor com a posi��o do n� e tipo de apoio
Node::Node(int id, double x, double y, int tipo) {
	this->pos.setX(x);
	this->pos.setY(y);
	this->id = id;
	switch (tipo) {
		//N� totalmente livre
		case 1:
			this->restricaoHorizontal = false;
			this->restricaoVertical = false;
			this->restricaoRotacao = false;
			break;
		//N� com restri��o apenas ao deslocamento transversal em x
		case 2:
			this->restricaoHorizontal = true;
			this->restricaoVertical = false;
			this->restricaoRotacao = false;
			break;
		//N� com restri��o apenas ao deslocamento transversal em y
		case 3:
			this->restricaoHorizontal = false;
			this->restricaoVertical = true;
			this->restricaoRotacao = false;
			break;
		//N� com restri��o apenas � rota��o em z
		case 4:
			this->restricaoHorizontal = false;
			this->restricaoVertical = false;
			this->restricaoRotacao = true;
			break;
		//N� com restri��o ao deslocamento transversal em x e y
		case 5:
			this->restricaoHorizontal = true;
			this->restricaoVertical = true;
			this->restricaoRotacao = false;
			break;
		//N� com restri��o ao deslocamento transversal em x e rota��o em z
		case 6:
			this->restricaoHorizontal = true;
			this->restricaoVertical = false;
			this->restricaoRotacao = true;
			break;
		//N� com restri��o ao deslocamento transversal em y e rota��o em z
		case 7:
			this->restricaoHorizontal = false;
			this->restricaoVertical = true;
			this->restricaoRotacao = true;
			break;
		//N� com restri��o a tudo (engaste)
		case 8:
			this->restricaoHorizontal = true;
			this->restricaoVertical = true;
			this->restricaoRotacao = true;
			break;
	}
}

//M�todo construtor com a posi��o do n� e descri��o das restri��es
Node::Node(int id, double x, double y, bool rH, bool rV, bool rR) {
	this->pos.setX(x);
	this->pos.setY(y);
	this->restricaoHorizontal = rH;
	this->restricaoVertical = rV;
	this->restricaoRotacao = rR;
	this->id = id;
}

//M�todo para adicionar uma carga no n�
void Node::addCarga(double fx, double fy, double mz) {
	this->fx += fx;
	this->fy += fy;
	this->mz += mz;
}

//M�todo para remover as cargas de um n�
void Node::zerarCarga() {
	this->fx = 0;
	this->fy = 0;
	this->mz = 0;
}

//M�todo para adicionar uma carga em x
void Node::addFx(double fx) {
	this->fx += fx;
}

//M�todo para adicionar uma carga em y
void Node::addFy(double fy) {
	this->fy += fy;
}

//M�todo para adicionar um momento em z
void Node::addMz(double mz) {
	this->mz += mz;
}

//M�todo para definir fx do n�
void Node::setFx(double fx) {
	this->fx = fx;
}

//M�todo para obter fx do n�
double Node::getFx() {
	return this->fx;
}

//M�todo para definir fy do n�
void Node::setFy(double fy) {
	this->fy = fy;
}

//M�todo para obter fy do n�
double Node::getFy() {
	return this->fy;
}

//M�todo para definir mz do n�
void Node::setMz(double mz) {
	this->mz = mz;
}

//M�todo para obter mz do n�
double Node::getMz() {
	return this->mz;
}

//M�todo para definir o deslocamento em x [dire��o global]
void Node::setDxGlobal(double dx)
{
	this->dxGlobal = dx;
}

//M�todo para definir o deslocamento em y [dire��o global]
void Node::setDyGlobal(double dy)
{
	this->dyGlobal = dy;
}

//M�todo para definir a rota��o em z do n� [dire��o global]
void Node::setRzGlobal(double rz)
{
	this->rzGlobal = rz;
}

//Vai retornar o deslocamento em x [dire��o global]
double Node::getDxGlobal()
{
	return this->dxGlobal;
}

//Vai retornar o deslocamento em y [dire��o global]
double Node::getDyGlobal() {
	return this->dyGlobal;
}

//Vai retornar a rota��o em z [dire��o global]
double Node::getRzGlobal() {
	return this->rzGlobal;
}

//Vai retornar a rea��o em x
double Node::getReacaoEmX() {
	return this->reacaoEmX;
}

//Vai retornar a rea��o em y
double Node::getReacaoEmY() {
	return this->reacaoEmY;
}

//Vai retornar a rea��o em z
double Node::getReacaoEmZ() {
	return this->reacaoEmZ;
}

//M�todo para definir a rea��o em x
void Node::setReacaoEmX(double reacaoEmX) {
	this->reacaoEmX = reacaoEmX;
}

//M�todo para definir a rea��o em y
void Node::setReacaoEmY(double reacaoEmY) {
	this->reacaoEmY = reacaoEmY;
}

//M�todo para definir a rea��o em z
void Node::setReacaoEmZ(double reacaoEmZ) {
	this->reacaoEmZ = reacaoEmZ;
}

//M�todo para definir o id do n�
void Node::setId(int id) {
	this->id = id;
}

//M�todo para obter o id do n�
int Node::getId() {
	return this->id;
}

//M�todo para obter informa��es sobre a restri��o horizontal
bool Node::getRh() {
	return this->restricaoHorizontal;
}

//M�todo para obter informa��es sobre a restri��o vertical
bool Node::getRv() {
	return this->restricaoVertical;
}

//M�todo para obter informa��es sobre a restri��o � rota��o em Z
bool Node::getRz() {
	return this->restricaoRotacao;
}
