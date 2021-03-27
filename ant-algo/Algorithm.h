#ifndef ALGORITHM
#define ALGORITHM

#include "Core.h"
#include "Visualization.h"

using namespace core;

namespace Algo {

	// ������� ����������� �������� from ---> to
	core::Node* findNext(Node* node) noexcept;				

	// ��������� ���������� ��������� �� ������ road
	void updatePheromone(Path& road) noexcept;

	// ������� state ��������� 
	void reset();

	// �������� ���������
	void start();

}

#endif
