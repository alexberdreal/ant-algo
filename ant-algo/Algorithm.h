#ifndef ALGORITHM
#define ALGORITHM

#include "Core.h"

using namespace core;

namespace Algo {

	inline std::atomic_bool toTerminate = false;

	// ������� ����������� �������� from ---> to
	[[nodiscard]] Node* findNext(const Node& node, std::vector<unsigned>& eaten);

	// ��������� ���������� ��������� �� ������ road
	void updatePheromone(const std::vector<unsigned>& route, bool extra) noexcept;

	// ������� state ��������� 
	void reset() noexcept;

	// �������� ���������
	void start();

}

#endif
