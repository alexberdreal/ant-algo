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

		if (ev == AppEvent::FEED) break;						// ������� �� "��������� �������"

		if (ev == AppEvent::EXIT) exit(EXIT_SUCCESS);			// ����� �� ���������

	}

	Visual::drawWindow(core::state_nodes);

	while (true) {

		ev = Visual::waitForEvent();

		if (ev == AppEvent::DRAWNODE) {							// ������� �� ���� 
			// ������ ���������� ����� �����
		}

		if (ev == AppEvent::CHOOSEANTS) break;					// ������� �� "����������"

		if (ev == AppEvent::EXIT) exit(EXIT_SUCCESS);			// ����� �� ���������

	}

	Visual::drawWindow(core::state_ants);

	while (true) {

		ev = Visual::waitForEvent();

		if (ev == AppEvent::EXIT) exit(EXIT_SUCCESS);			// ����� �� ���������

		if (ev == AppEvent::LAUNCH) {							// ������ ��������� � ��������� ������.
			Visual::drawWindow(state_execution);
			// ������ ��������� � ��������� ������
			break;
		}
	}

	while (true) {
		ev = Visual::waitForEvent();

		if (ev == AppEvent::RESTART) {							// ������� ��������� (�� ������ ���������� �����!)
			Algo::reset();
			Visual::drawWindow(state_nodes);
			break;
		}

		if (ev == AppEvent::EXIT) exit(EXIT_SUCCESS);			// ����� �� ���������
	}

	fromStartToStop();											// ��������� ������ (����� AppEvent::RESTART)
}