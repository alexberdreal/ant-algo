#include "Core.h"
#include <math.h>


core::Node::Node() : isHome(true), x(10), y(10), id(0) { };


core::Node::Node(double x, double y, unsigned id) : x(x), y(y), isHome(false), id(id) { };

void core::Node::initPaths() {
	//srand(time(NULL));

	unsigned i = 0;

	for (auto& el : nodes) {
		if (mapContainsKey(nodes[i].paths, el.getId())) {
			paths.insert(std::make_pair(i, nodes[i].paths[el.getId()]));
		}
		if (el.getId() != this->id) {
			paths.insert(std::make_pair(el.getId(), Path{ findLength(x, y, el.x, el.y), 0.2 }));
		}
	}
}

bool core::Node::operator==(const core::Node& toCompare) {
	return this->id == toCompare.id;
}	

void core::Ant::updateCurrentPos(core::Node* node) {
	this->entireLength += this->curPos->paths[node->getId()].length;
	this->curPos = node;
	this->nodeIds.push_back(node->getId());
}

unsigned core::Node::getId() const {
	return this->id;
}

double core::findLength(double x1, double y1, double x2, double y2) {
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}