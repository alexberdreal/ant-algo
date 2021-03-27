#ifndef GENERAL
#define GENERAL
#include <vector>
#include <string>

namespace core {


	// считает длину в пикселях от А(х1, у1) до В(х2, у2)
	double findLength(double x1, double y1, double x2, double y2);

	struct Path {                                               // Структура, представляющая тропу								
		double length;											// Длина тропы (в пикселях)			
		double pheromone;										// Количество феромона на тропе
	};

	// ~~~~~~~~~~~~~~~~~~ Node - класс, представляющий узел ~~~~~~~~~~~~~~~~~~


	class Node {
	private:
		const uint16_t id;											// Идентификатор узла
		const bool isHome;											// Является ли узел муравейником
		const double x, y;											// Положение узла в пикселях
	public:
		std::vector<Path> paths;
		Node();
		Node(double x, double y, bool isHome, uint16_t id);
		bool operator==(const Node& toCompare);						// Перегруженный оператор сравнения == (сравниваем узлы по id)
		uint16_t getId();
	};

	inline std::vector<Node> nodes;									// inline для weak-internal компоновки (везде, где подключается Core.h единственный инстанс nodes)

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

	inline AppState state_started{ true, false, true, "Окно для информации", false, false, false, false };
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