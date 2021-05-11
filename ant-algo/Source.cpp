#include "Algorithm.h"
#include <thread>

void fromStartToStop();

int main() {
	
	srand(time(NULL));
	
	// initNodes();                                      инициализируем узлы 

	// for (size_t i = 0; i < nodes.size(); ++i) {
	//	nodes[i].initPaths();							 прокладываем пути между каждым узлом
	// }
	
	// numberOfAnts = 6;								 указываем количество муравьев

	// Algo::start();									 запускаем алгоритм



	//Visual::drawWindow(core::state_started);

	//fromStartToStop();

}

void initNodes() {
	nodes.push_back(Node());
	nodes.push_back(Node(40, 20, 1));
	nodes.push_back(Node(100, 130, 2));
	nodes.push_back(Node(600, 50, 3));
	nodes.push_back(Node(230, 50, 4));
	nodes.push_back(Node(64, 100, 5));
	nodes.push_back(Node(69, 10, 6));
	nodes.push_back(Node(90, 0, 7));
}



void fromStartToStop() {
	AppEvent ev = AppEvent::CHOOSEANTS;

	while (true) {

	//	ev = Visual::waitForEvent();

		if (ev == AppEvent::FEED) break;						// Нажатие на "Покормить муравья"

		if (ev == AppEvent::EXIT) exit(EXIT_SUCCESS);			// Выход из программы

	}

	//Visual::drawWindow(core::state_nodes);

	while (true) {

		//ev = Visual::waitForEvent();

		if (ev == AppEvent::DRAWNODE) {							// Нажатие на поле 
			// логика добавления новых узлов
		}

		if (ev == AppEvent::CHOOSEANTS) break;					// Нажатие на "Продолжить"

		if (ev == AppEvent::EXIT) exit(EXIT_SUCCESS);			// Выход из программы

	}

	//Visual::drawWindow(core::state_ants);

	while (true) {

		//ev = Visual::waitForEvent();

		if (ev == AppEvent::EXIT) exit(EXIT_SUCCESS);			// Выход из программы

		if (ev == AppEvent::LAUNCH) {							// Запуск алгоритма В ОТДЕЛЬНОМ потоке.
			//Visual::drawWindow(state_execution);
			// запуск алгоритма в отдельном потоке
			break;
		}
	}

	while (true) {
		//ev = Visual::waitForEvent();

		if (ev == AppEvent::RESTART) {							// Рестарт программы (не забыть освободить поток!)
			Algo::reset();
		//	Visual::drawWindow(state_nodes);
			break;
		}

		if (ev == AppEvent::EXIT) exit(EXIT_SUCCESS);			// Выход из программы
	}

	fromStartToStop();											// Выполнить заново (после AppEvent::RESTART)
}