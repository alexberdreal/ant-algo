#define _CRT_SECURE_NO_WARNINGS
#include "Algorithm.h"
#include "Visualization.h"
#include <thread> 

void fromStartToStop();

void initNodes();

int main(int argc, char* argv[]) {
	Visual::prepareVisual();
	initNodes();
	if (argc > 1)
	for (int i = 1; i < argc; i += 2) {
		if (!strcmp(argv[i], "-t")) {
			FILE* file = fopen(argv[i + 1], "r");
			nodes.push_back(Node());
			size_t i = 1;
			while (!feof(file)) {
				double x, y;
				printf("added %u\n", i);
				fscanf(file, "%lf", &x);
				fscanf(file, "%lf", &y);
				nodes.push_back(Node(x, y, i++));
			}
			numberOfAnts = 6;
			for (int i = 0; i < nodes.size(); ++i) {
				printf("here");
				nodes[i].initPaths();
			}
		}
		else {
			printf("This flag doesn't exist\n");
		}
	}

	srand(time(NULL));
	
	// initNodes();                                      инициализируем узлы 

	// for (size_t i = 0; i < nodes.size(); ++i) {
	//	nodes[i].initPaths();							 прокладываем пути между каждым узлом
	// }
	
	// numberOfAnts = 6;								 указываем количество муравьев

	 //Algo::start();									 //запускаем алгоритм



	Visual::drawWindow(core::state_started);

	//fromStartToStop();

}

void initNodes() {
	nodes.push_back(Node());
	nodes.push_back(Node(240, 220, 1));
	nodes.push_back(Node(300, 130, 2));
	nodes.push_back(Node(600, 290, 3));
	nodes.push_back(Node(930, 350, 4));
	nodes.push_back(Node(654, 400, 5));
	nodes.push_back(Node(249, 210, 6));
	nodes.push_back(Node(790, 270, 7));
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