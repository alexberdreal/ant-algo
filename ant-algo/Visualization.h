#ifndef VISUALIZATION
#define VISUALIZATION

#include "Core.h"

// ��� �������� ����� � Source.cpp
static double tempX, tempY; 

namespace Visual {

	// ��������� �������� ���� � ��� ����������� �����������
	void drawWindow(const core::AppState& state);

	// ���������� ���������� ������ ����
	void updateStatistics();

	// ��������� ������ ����� (����������� � ����)
	void drawNode(double x, double y);

	// ��������� ���� A(x1, y1) --> B(x2, y2)
	void drawPath(double x1, double y1, double x2, double y2);

	// ��������� ������� ����� �� ��������� A(x1,y1) --> B(x2,y2)
	void updatePheromones(double x1, double y1, double x2, double y2); 

	// �������� �������
	core::AppEvent waitForEvent();

	// ������� ����, �������� ����������
	void clean();
}

#endif