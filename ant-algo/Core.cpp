#include "Core.h"
#include <math.h>

core::Node::Node(double x, double y, bool isHome, uint16_t id) : x(x), y(y), isHome(isHome), id(id) {};
bool core::Node::operator==(const core::Node& toCompare) {
	return this->id == toCompare.id;
}	

core::Node::Node() : id(0), isHome(true), x(0), y(0) {};	// Конструктор для муравейника

void core::Ant::updateCurrentPos(core::Node* node) {
	this->entireLength += this->curPos->paths[node->getId()].length;
	this->curPos = node;
	this->nodeIds.push_back(node->getId());
}

uint16_t core::Node::getId() {
	return this->id;
}

double core::findLength(double x1, double y1, double x2, double y2) {
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}