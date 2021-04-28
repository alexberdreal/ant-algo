#ifndef ALGORITHM
#define ALGORITHM

#include "Core.h"
#include "Visualization.h"

using namespace core;

namespace Algo {

	// ������� ����������� �������� from ---> to
	core::Node* findNext(const Node& node, std::vector<unsigned>& eaten) noexcept;

	// ��������� ���������� ��������� �� ������ road
	void updatePheromone(const std::vector<unsigned>& route, bool extra) noexcept;

	// ������� state ��������� 
	void reset();

	// �������� ���������
	void start();

}

#endif
