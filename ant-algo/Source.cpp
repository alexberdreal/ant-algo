#define _CRT_SECURE_NO_WARNINGS
#include "Algorithm.h"
#include "Visualization.h"
#include <thread> 
#include <Windows.h>

void colonyNode();														// ������������� �������

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Rus");
	HWND cmd = GetConsoleWindow();										// �������� ���������� �������
	SetWindowPos(cmd, NULL, 0, 0, 300, 500, NULL);						// ��������� ��������� � ������� �������
	Visual::cmdStateChanged();											// �������� �������
	
	Visual::prepareVisual();											// �������������� ����������� �������

	if (argc > 1)														// �����
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

		colonyNode();													// �������������� ������� 

		Visual::drawWindow(core::AppState::state_started);				// 1 ��������� - ������ ����������

		Visual::drawWindow(core::AppState::state_nodes);				// 2 ��������� - ����� ��������� ����

		Visual::drawWindow(core::AppState::state_ants);					// 3 ��������� - ����� ���-�� ��������
		for (size_t i = 0; i < nodes.size(); ++i) {
			nodes[i].initPaths();										// ������������ ���� ����� ������ �����
		}

		std::thread th(Algo::start);									// ��������� ��������
		Visual::drawWindow(core::AppState::state_execution);			// 4 ��������� - ��������� ���������	
		
		//  ---------------- ������ ������ ���� -----------------
		
		if (Visual::showCmd) Visual::cmdStateChanged();					// ���� ��������			
		Algo::toTerminate.store(true);									// ���� ������ ���������, ��� ���� ������������
		algoSpeed = 0;													// ������ ��� � ����, ����� ��������
		if (th.joinable()) th.join();									// ���� ���� ����������
		Algo::toTerminate.store(false);									// ��������� ��������������� � ����������
		system("CLS");													// �������� ����			
		Algo::reset();													// �������� ������ ���������
	}

}

void colonyNode() {
	nodes.push_back(Node());
}
