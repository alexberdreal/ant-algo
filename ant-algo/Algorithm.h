#ifndef ALGORITHM
#define ALGORITHM

#include "Core.h"
#include "Visualization.h"

using namespace core;

namespace Algo {

	// Считает вероятность перехода from ---> to
	core::Node* findNext(Node* node) noexcept;				

	// Обновляет количество феромонов на дороге road
	void updatePheromone(Path& road) noexcept;

	// Очищает state программы 
	void reset();

	// Стартует программу
	void start();

}

#endif
