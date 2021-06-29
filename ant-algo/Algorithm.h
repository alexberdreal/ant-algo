#ifndef ALGORITHM
#define ALGORITHM

#include "Core.h"

using namespace core;

namespace Algo {

	inline std::atomic_bool toTerminate = false;

	// Считает вероятность перехода from ---> to
	[[nodiscard]] Node* findNext(const Node& node, std::vector<unsigned>& eaten);

	// Обновляет количество феромонов на дороге road
	void updatePheromone(const std::vector<unsigned>& route, bool extra) noexcept;

	// Очищает state программы 
	void reset() noexcept;

	// Стартует программу
	void start();

}

#endif
