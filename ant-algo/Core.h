#ifndef GENERAL
#define GENERAL
#include <vector>

class Node {
private:
	const uint16_t id;
	const bool isHome;
public:
	Node(double x, double y, bool isHome, uint16_t id);
	double x, y;
	bool operator==(const Node& toCompare);
};

class Ant {
private:
	Position* curPos;
	double entireLength;
public:
	void addPosition(Node node);
	void setEntireLength();
	void getEntireLength();
};

class State {
public:
	std::vector<Node> nodes;
	std::vector<Ant> ants;

	void addNode(Node& node);
	void addAnt(Ant& ant);
};

enum class AppEvent
{
	CLEAR, LAUNCH, EXIT, DRAWNODE
};

struct Path {
	Position* nextPosition;
	double length;
	double pheromone;
};

class Position : Node
{
public:
	Path pathToNext;
};

#endif