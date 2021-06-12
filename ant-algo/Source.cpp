#define _CRT_SECURE_NO_WARNINGS
#include "Algorithm.h"
#include "Visualization.h"
#include <thread> 
#include <Windows.h>

void colonyNode();														// инициализация колонии

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Rus");
	HWND cmd = GetConsoleWindow();										// получаем дескриптор консоли
	SetWindowPos(cmd, NULL, 0, 0, 300, 500, NULL);						// указываем положение и размеры консоли
	Visual::cmdStateChanged();											// скрываем консоль
	
	Visual::prepareVisual();											// инициализируем графические объекты

	if (argc > 1)														// тесты
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

	while (true) {

		colonyNode();													// инициализируем колонию 

		Visual::drawWindow(core::AppState::state_started);				// 1 состояние - запуск приложения

		Visual::drawWindow(core::AppState::state_nodes);				// 2 состояние - выбор положения пищи

		Visual::drawWindow(core::AppState::state_ants);					// 3 состояние - выбор кол-ва муравьев
		for (size_t i = 0; i < nodes.size(); ++i) {
			nodes[i].initPaths();										// прокладываем пути между каждым узлом
		}

		std::thread th(Algo::start);									// запускаем алгоритм
		Visual::drawWindow(core::AppState::state_execution);			// 4 состояние - отрисовка алгоритма	
		
		//  ---------------- Нажата кнопка СТОП -----------------
		
		if (Visual::showCmd) Visual::cmdStateChanged();					// Логи спрятать			
		Algo::toTerminate.store(true);									// Дать сигнал алгоритму, что пора заверишаться
		algoSpeed = 0;													// Помочь ему в этом, убрав задержку
		if (th.joinable()) th.join();									// Ждем пока завершится
		Algo::toTerminate.store(false);									// Перестаем сигнализировать о завершении
		system("CLS");													// Очистить логи			
		Algo::reset();													// Обнулить данные программы
	}

}

void colonyNode() {
	nodes.push_back(Node());
}
