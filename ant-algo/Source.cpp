#define _CRT_SECURE_NO_WARNINGS
#include "Algorithm.h"
#include "Visualization.h"
#include <thread> 
#include <Windows.h>
using namespace core;

void colonyNode();														// ������������� �������
void prepareConsole();

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Rus");
	prepareConsole();
	Visual::prepareVisual();											// �������������� ����������� �������

	srand(time(NULL));

	while (true) {

		colonyNode();													// �������������� ������� 

		Visual::setState(AppState::state_started);				// 1 ��������� - ������ ����������

		Visual::setState(AppState::state_nodes);				// 2 ��������� - ����� ��������� ����

		Visual::setState(AppState::state_ants);					// 3 ��������� - ����� ���-�� ��������

		for (size_t i = 0; i < nodes.size(); ++i) {
			nodes[i].initPaths();										// ������������ ���� ����� ������ �����
		}

		std::thread th(Algo::start);									// ��������� ��������
		Visual::setState(AppState::state_execution);			// 4 ��������� - ��������� ���������	
		
		//  ---------------- ������ ������ ���� -----------------
		
		if (Visual::showCmd) Visual::cmdStateChanged();					// ���� ��������			
		Algo::toTerminate.store(true);									// ���� ������ ���������, ��� ���� �����������
		algoSpeed = 0;													// ������ ��� � ����, ����� ��������
		if (th.joinable()) th.join();									// ���� ���� ����������
		Algo::toTerminate.store(false);									// ��������� ��������������� � ����������
		system("CLS");													// �������� ����			
		Algo::reset();													// �������� ������ ���������
	}
}

void colonyNode() {
	nodes.emplace_back();
}

void prepareConsole() {
	HWND cmd = GetConsoleWindow();										// �������� ���������� �������
	SetWindowPos(cmd, NULL, 0, 0, 300, 500, NULL);						// ��������� ��������� � ������� �������
	Visual::cmdStateChanged();											// �������� �������
}