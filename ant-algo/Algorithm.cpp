#include "Algorithm.h"

namespace Algo {

	core::Node* findNext(const Node& node, std::vector<unsigned>& eaten) noexcept {
		if (eaten.size() == nodes.size()) {
			eaten.push_back(0);
			routeVec.push_back({ (float)node.getX(), (float)node.getY(), (float)nodes[0].getX(), (float)nodes[0].getY() });
			return &nodes[0];
		}
		double r = (rand() % 100) / 100.0;
		std::multimap<double, unsigned> m;
		double sum = 0;

		for (auto it = node.paths.begin(); it != node.paths.end(); ++it) {
			if (std::find(eaten.begin(), eaten.end(), it->first) == eaten.end()) {
				sum += pow(it->second.pheromone, 2) / it->second.length;
			}
		}	
		double res = 0;
		for (auto it = node.paths.begin(); it != node.paths.end(); ++it) {
			if (std::find(eaten.begin(), eaten.end(), it->first) == eaten.end()) {
				res = pow(it->second.pheromone, 2) / it->second.length / sum;
				m.insert(std::make_pair(res, it->first));
			}
		}

		double t = 0;
		for (auto& el : m) {
			t += el.first;
			if (r <= t) {
				eaten.push_back(el.second);
				routeVec.push_back({ (float)node.getX(), (float)node.getY(), (float)nodes[el.second].getX(), (float)nodes[el.second].getY() });
				return &nodes[el.second];
			}
		}
		return nullptr;
	};

	void updatePheromone(const std::vector<unsigned>& route, bool extra = false) noexcept {
		if (!extra) {
			double sum = 0;
			//std::cout << "Start:" << std::endl;
			//for (size_t i = 0; i < route.size() - 1; ++i) {
				//	std::cout << route[i] << " ph:  " << nodes[route[i]].paths[route[i + 1]].pheromone << "  len:  " << nodes[route[i]].paths[route[i + 1]].length << std::endl;
			//}
			for (size_t i = 0; i < route.size() - 1; ++i) {
				sum += nodes[route[i]].paths[route[i + 1]].length;
				nodes[route[i]].paths[route[i + 1]].pheromone *= 0.6;
			}
			std::cout << "sum: " << sum << std::endl;
			for (size_t i = 0; i < route.size() - 1; ++i) {
				nodes[route[i]].paths[route[i + 1]].pheromone += 40 / sum;
				//std::cout << "After: " << nodes[route[i]].paths[route[i + 1]].pheromone << std::endl;
			}
		}
		else {
			for (size_t i = 0; i < route.size() - 1; ++i) {
				nodes[route[i]].paths[route[i + 1]].pheromone += 0.4;
			}
		}

	};

	void reset() {
		
	};

	void start() {
		mut.lock();
		std::vector<std::vector<unsigned>> routes;
		std::vector<unsigned> vec;
		int c = 1;
		while (true) {
			Node* current;
			for (int i = 0; i < numberOfAnts; ++i) {
				current = &nodes[0];
				vec.push_back(0);
				while (vec.size() != nodes.size() + 1) {
					current = findNext(*current, vec);
					 mut.unlock();
					std::this_thread::sleep_for(std::chrono::milliseconds(300));
					mut.lock();
					if (current == nullptr) throw std::runtime_error("The next node is not defined");
				}
				for (auto it = vec.begin(); it != vec.end(); ++it) {		// Весь путь одного муравья
					std::cout << *it << ' ';
				}
				std::cout << std::endl;
				routes.push_back(vec);
				vec.clear();
				routeVec.clear();
			}
			for (size_t i = 0; i < routes.size(); ++i) {
				Algo::updatePheromone(routes[i]);
			}
			int minL = 10000000;
			int minR = 0;
			for (size_t i = 0; i < routes.size(); ++i) {
				int curs = 0;
				for (size_t j = 0; j < routes[i].size() - 1; ++j) {
					curs += nodes[routes[i].at(j)].paths[routes[i].at(j + 1)].length;
				}
				if (curs < minL) {
					minL = curs;
					minR = i;
				}
			}
			std::cout << "MINR " << minR;
			Algo::updatePheromone(routes[minR], true);

			routes.clear();
			std::cout << "///////////////// ITERATION " << c << std::endl;
			c++;
			
		}
	};
}