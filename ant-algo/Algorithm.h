#ifndef ALGORITHM
#define ALGORITHM

#include "Core.h"
#include "Visualization.h"

using namespace core;

namespace Algo {

	// Считает вероятность перехода from ---> to
	core::Node* findNext(const Node& node, std::vector<unsigned>& eaten) noexcept;

	// Обновляет количество феромонов на дороге road
	void updatePheromone(const std::vector<unsigned>& route, bool extra) noexcept;

	// Очищает state программы 
	void reset();

	// Стартует программу
	void start();

}

#endif
