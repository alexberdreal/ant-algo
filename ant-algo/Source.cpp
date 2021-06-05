#define _CRT_SECURE_NO_WARNINGS
#include "Algorithm.h"
#include "Visualization.h"
#include <thread> 
#include <Windows.h>

void initNodes();

int main(int argc, char* argv[]) {
	HWND cmd = GetConsoleWindow();						// получаем дескриптор консоли
	SetWindowPos(cmd, NULL, 0, 0, 300, 500, NULL);		// указываем положение и размеры консоли
	Visual::cmdStateChanged();							// скрываем консоль
	
	Visual::prepareVisual();							// инициализируем графические объекты

	if (argc > 1)										// тесты
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


	// Visual::drawWindow(core::state_started);

	// Visual::drawWindow(core::state_nodes);
	// Visual::drawWindow(core::state_ants);


	while (true) {

		numberOfAnts = 6;									// указываем количество муравьев

		initNodes();										// инициализируем узлы 

		Visual::drawWindow(state_started);

		for (size_t i = 0; i < nodes.size(); ++i) {
			nodes[i].initPaths();							// прокладываем пути между каждым узлом
		}
		//Visual::drawWindow(state_nodes);
		//Visual::drawWindow(state_ants);

		std::thread th(Algo::start);									 //запускаем алгоритм
		Visual::drawWindow(state_execution);
		if (Visual::showCmd) Visual::cmdStateChanged();
		Algo::toTerminate.store(true);
		algoSpeed = 0;
		if (th.joinable()) th.join();
		Algo::toTerminate.store(false);
		system("CLS");
		Algo::reset();
	}

}

void initNodes() {
	nodes.push_back(Node());
}
