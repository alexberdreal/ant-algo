#include "Core.h"

Node::Node(double x, double y, bool isHome, uint16_t id) : x(x), y(y), isHome(isHome), id(id) {};
bool Node::operator==(const Node& toCompare) {
	return this->id == toCompare.id;
}