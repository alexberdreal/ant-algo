#ifndef ALGORITHM
#define ALGORITHM

#include "Core.h"
#include "Visualization.h"

namespace Algo {

	// ������� ����������� �������� from ---> to
	void findNext(Node& node) noexcept;

	// ��������� ���������� ��������� �� ������ road
	void updatePheromone(Path& road) noexcept;

	// ������� ����� ���� �� Node(�1, �1) �� Node(�2, �2)
	double calcLength(double x1, double y1, double x2, double y2) noexcept;

	void reset();

	void start();

}

#endif
