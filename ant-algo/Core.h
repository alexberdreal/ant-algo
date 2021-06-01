#ifndef GENERAL
#define GENERAL
#include <vector>
#include <map>
#include <random>
#include <cmath>
#include <time.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <mutex>
#include <thread>

constexpr double M_PI = 3.14159265358979323846;

inline std::mutex mut;

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

	// считает длину в пикселях от А(х1, у1) до В(х2, у2)
	double findLength(double x1, double y1, double x2, double y2);

	struct Path {                                               // Структура, представляющая тропу								
		double length;											// Длина тропы (в пикселях)			
		double pheromone;										// Количество феромона на тропе
	};

	// ~~~~~~~~~~~~~~~~~~ Node - класс, представляющий узел ~~~~~~~~~~~~~~~~~~


	class Node {
	private:
		const unsigned id;											// Идентификатор узла (id = 0, если муравейник)
		const bool isHome;											// Является ли узел муравейником
		const double x, y;											// Положение узла в пикселях
	public:
		std::map<unsigned, Path> paths;									// paths[i] - путь из this в Node, id которого равно i. Инициализируется внутри конструктора
		
		Node();			// Конструктор для муравейника

		Node(double x, double y, unsigned id);			// Конструктор для узлов пищи

		void initPaths();

		bool operator==(const Node& toCompare);						// Перегруженный оператор сравнения == (сравниваем узлы по id)

		unsigned getId() const;											// Геттер id

		double getX() const { return x; }
		double getY() const { return y; }
	};

	inline std::vector<Node> nodes;									// inline для weak-internal компоновки (везде, где подключается																		Core.h единственный инстанс nodes)

	inline std::vector<std::vector<float>> routeVec;

	inline uint16_t numberOfAnts;

	enum class AppEvent
	{
		RESTART, LAUNCH, EXIT, DRAWNODE, FEED, CHOOSEANTS
	};

	struct AppState {
		bool toDrawField;
		bool isFieldTouchable;
		bool hasFeedBtn;
		std::string infoText;
		bool hasExecutionBtn;
		bool hasStopBtn;
		bool hasContinueBtn;
		bool hasTextField;
	};

	inline const AppState state_started{ true, false, true, "Окно для информации", false, false, false, false };
	inline AppState state_nodes{ false, true, false, "Расположите еду для муравьёв", false, false, true, false };
	inline AppState state_ants{ false, false, false, "Введите количество муравьев", false, false, true, true };
	inline AppState state_execution{ false, false, false, "", true, true, false, false };

	// Муравей, который знает только о своей текущей позиции, пройденный путь и умеет обновлять текущую позицию
	class Ant {
	private:
		Node* curPos;								// указатель на текущий узел, где находится муравей
		std::vector<uint16_t> nodeIds;					// маршрут муравья
	public:
		double entireLength;						// пройденный путь
		void updateCurrentPos(Node* position);		// обновить текущий узел, где находится муравей
	};

}

#endif