#ifndef GENERAL
#define GENERAL
#include <vector>
#include <map>
#include <random>
#include <cmath>
#include <mutex>
#include <time.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>

constexpr double M_PI = 3.14159265358979323846;

inline std::atomic_int algoSpeed = 95;

namespace core {
	template <class T, class R, class K>
	bool mapContainsKey(std::map<T, R>& map, K key) {
		if (map.find(key) == map.end()) return false;
		return true;
	}

	template <class T, class R, class K>
	bool mapContainsKey(std::multimap<T, R>& map, K key) {
		if (map.find(key) == map.end()) return false;
		return true;
	}

	// считает длину в пиксел€х от ј(х1, у1) до ¬(х2, у2)
	double findLength(double x1, double y1, double x2, double y2);

	struct Path {                                               // —труктура, представл€юща€ тропу								
		double length;											// ƒлина тропы (в пиксел€х)			
		double pheromone;										//  оличество феромона на тропе
	};

	// ~~~~~~~~~~~~~~~~~~ Node - класс, представл€ющий узел ~~~~~~~~~~~~~~~~~~


	class Node {
	private:
		const unsigned id;											// »дентификатор узла (id = 0, если муравейник)
		const bool isHome;											// явл€етс€ ли узел муравейником
		const double x, y;											// ѕоложение узла в пиксел€х
	public:
		std::map<unsigned, Path> paths;									// paths[i] - путь из this в Node, id которого равно i. »нициализируетс€ внутри конструктора
		
		Node();			//  онструктор дл€ муравейника

		Node(double x, double y, unsigned id);			//  онструктор дл€ узлов пищи

		void initPaths();

		bool operator==(const Node& toCompare);						// ѕерегруженный оператор сравнени€ == (сравниваем узлы по id)

		unsigned getId() const;											// √еттер id

		double getX() const { return x; }
		double getY() const { return y; }
	};

	inline std::vector<Node> nodes;									// inline дл€ weak-internal компоновки (везде, где подключаетс€																		Core.h единственный инстанс nodes)

	inline std::vector<std::vector<float>> routeVec;

	inline uint16_t numberOfAnts;

	enum class AppEvent
	{
		RESTART, LAUNCH, EXIT, DRAWNODE, FEED, CHOOSEANTS
	};

	struct BestPath {
		std::mutex mut;
		std::vector<unsigned> route;
		double len = 100000.0;
	};

	inline BestPath bestPath;

	enum class AppState {
		state_started,
		state_nodes,
		state_ants,
		state_execution
	};

	// ћуравей, который знает только о своей текущей позиции, пройденный путь и умеет обновл€ть текущую позицию
	class Ant {
	private:
		Node* curPos;								// указатель на текущий узел, где находитс€ муравей
		std::vector<uint16_t> nodeIds;					// маршрут муравь€
	public:
		double entireLength;						// пройденный путь
		void updateCurrentPos(Node* position);		// обновить текущий узел, где находитс€ муравей
	};

}

#endif