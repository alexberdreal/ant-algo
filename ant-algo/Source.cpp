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
	
	// initNodes();                                      �������������� ���� 

	// for (size_t i = 0; i < nodes.size(); ++i) {
	//	nodes[i].initPaths();							 ������������ ���� ����� ������ �����
	// }
	
	// numberOfAnts = 6;								 ��������� ���������� ��������

	 //Algo::start();									 //��������� ��������



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