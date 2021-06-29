#define _CRT_SECURE_NO_WARNINGS
#include "Algorithm.h"
#include "Visualization.h"
#include <thread> 
#include <Windows.h>
using namespace core;

void colonyNode();														// инициализация колонии
void prepareConsole();

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Rus");
	prepareConsole();
	Visual::prepareVisual();											// инициализируем графические объекты

	srand(time(NULL));

	while (true) {

		colonyNode();													// инициализируем колонию 

		Visual::setState(AppState::state_started);				// 1 состояние - запуск приложения

		Visual::setState(AppState::state_nodes);				// 2 состояние - выбор положения пищи

		Visual::setState(AppState::state_ants);					// 3 состояние - выбор кол-ва муравьев

		for (size_t i = 0; i < nodes.size(); ++i) {
			nodes[i].initPaths();										// прокладываем пути между каждым узлом
		}

		std::thread th(Algo::start);									// запускаем алгоритм
		Visual::setState(AppState::state_execution);			// 4 состояние - отрисовка алгоритма	
		
		//  ---------------- Нажата кнопка СТОП -----------------
		
		if (Visual::showCmd) Visual::cmdStateChanged();					// Логи спрятать			
		Algo::toTerminate.store(true);									// Дать сигнал алгоритму, что пора завершаться
		algoSpeed = 0;													// Помочь ему в этом, убрав задержку
		if (th.joinable()) th.join();									// Ждем пока завершится
		Algo::toTerminate.store(false);									// Перестаем сигнализировать о завершении
		system("CLS");													// Очистить логи			
		Algo::reset();													// Обнулить данные программы
	}
}

void colonyNode() {
	nodes.emplace_back();
}

void prepareConsole() {
	HWND cmd = GetConsoleWindow();										// получаем дескриптор консоли
	SetWindowPos(cmd, NULL, 0, 0, 300, 500, NULL);						// указываем положение и размеры консоли
	Visual::cmdStateChanged();											// скрываем консоль
}