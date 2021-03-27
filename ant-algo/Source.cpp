#include "Algorithm.h"
#include <thread>

void fromStartToStop();

int main() {

	Visual::drawWindow(core::state_started);

	fromStartToStop();

}



void fromStartToStop() {
	AppEvent ev;

	while (true) {

		ev = Visual::waitForEvent();

		if (ev == AppEvent::FEED) break;						// Нажатие на "Покормить муравья"

		if (ev == AppEvent::EXIT) exit(EXIT_SUCCESS);			// Выход из программы

	}

	Visual::drawWindow(core::state_nodes);

	while (true) {

		ev = Visual::waitForEvent();

		if (ev == AppEvent::DRAWNODE) {							// Нажатие на поле 
			// логика добавления новых узлов
		}

		if (ev == AppEvent::CHOOSEANTS) break;					// Нажатие на "Продолжить"

		if (ev == AppEvent::EXIT) exit(EXIT_SUCCESS);			// Выход из программы

	}

	Visual::drawWindow(core::state_ants);

	while (true) {

		ev = Visual::waitForEvent();

		if (ev == AppEvent::EXIT) exit(EXIT_SUCCESS);			// Выход из программы

		if (ev == AppEvent::LAUNCH) {							// Запуск алгоритма В ОТДЕЛЬНОМ потоке.
			Visual::drawWindow(state_execution);
			// запуск алгоритма в отдельном потоке
			break;
		}
	}

	while (true) {
		ev = Visual::waitForEvent();

		if (ev == AppEvent::RESTART) {							// Рестарт программы (не забыть освободить поток!)
			Algo::reset();
			Visual::drawWindow(state_nodes);
			break;
		}

		if (ev == AppEvent::EXIT) exit(EXIT_SUCCESS);			// Выход из программы
	}

	fromStartToStop();											// Выполнить заново (после AppEvent::RESTART)
}