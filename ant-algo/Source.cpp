#include "Algorithm.h"
#include <thread>

void fromStartToStop();

int main() {
	
	srand(time(NULL));
	
	// initNodes();                                      �������������� ���� 

	// for (size_t i = 0; i < nodes.size(); ++i) {
	//	nodes[i].initPaths();							 ������������ ���� ����� ������ �����
	// }
	
	// numberOfAnts = 6;								 ��������� ���������� ��������

	// Algo::start();									 ��������� ��������



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

		if (ev == AppEvent::FEED) break;						// ������� �� "��������� �������"

		if (ev == AppEvent::EXIT) exit(EXIT_SUCCESS);			// ����� �� ���������

	}

	//Visual::drawWindow(core::state_nodes);

	while (true) {

		//ev = Visual::waitForEvent();

		if (ev == AppEvent::DRAWNODE) {							// ������� �� ���� 
			// ������ ���������� ����� �����
		}

		if (ev == AppEvent::CHOOSEANTS) break;					// ������� �� "����������"

		if (ev == AppEvent::EXIT) exit(EXIT_SUCCESS);			// ����� �� ���������

	}

	//Visual::drawWindow(core::state_ants);

	while (true) {

		//ev = Visual::waitForEvent();

		if (ev == AppEvent::EXIT) exit(EXIT_SUCCESS);			// ����� �� ���������

		if (ev == AppEvent::LAUNCH) {							// ������ ��������� � ��������� ������.
			//Visual::drawWindow(state_execution);
			// ������ ��������� � ��������� ������
			break;
		}
	}

	while (true) {
		//ev = Visual::waitForEvent();

		if (ev == AppEvent::RESTART) {							// ������� ��������� (�� ������ ���������� �����!)
			Algo::reset();
		//	Visual::drawWindow(state_nodes);
			break;
		}

		if (ev == AppEvent::EXIT) exit(EXIT_SUCCESS);			// ����� �� ���������
	}

	fromStartToStop();											// ��������� ������ (����� AppEvent::RESTART)
}