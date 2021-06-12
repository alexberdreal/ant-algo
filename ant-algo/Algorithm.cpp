#include "Algorithm.h"

namespace Algo {

	// ����� ���������� ������ ��� ������� 
	core::Node* findNext(const Node& node, std::vector<unsigned>& eaten) noexcept {																			
		if (eaten.size() == nodes.size()) {																														// ������������ � �����������, ���� ���� ���������
			eaten.push_back(0);
			routeVec.push_back({ (float)node.getX(), (float)node.getY(), (float)nodes[0].getX(), (float)nodes[0].getY() });
			return &nodes[0];
		}
		double r = (rand() % 100) / 100.0;																														// ���������� ��������� �����
		std::multimap<double, unsigned> m;																														// ��������� {�����������: id ����}
		double sum = 0;																																			// ��� * �� (����������� �� �������)

		for (auto it = node.paths.begin(); it != node.paths.end(); ++it) {																	
			if (std::find(eaten.begin(), eaten.end(), it->first) == eaten.end()) {
				sum += pow(it->second.pheromone, 3) / it->second.length;																						// ������� �����������
			}
		}	
		double res = 0;																																		
		for (auto it = node.paths.begin(); it != node.paths.end(); ++it) {
			if (std::find(eaten.begin(), eaten.end(), it->first) == eaten.end()) {																				// ���� ���� ��� �� �������
				res = pow(it->second.pheromone, 3) / it->second.length / sum;																					// �������� ����������� �������� node --> it->second
				m.insert(std::make_pair(res, it->first));																										// ��������� ��� ����������� � ��������� {�����������: id ����}
			}
		}

		double t = 0;																																			
		for (auto& el : m) {																																	
			t += el.first;																																		// ����������� �������� ����������� (0-1)
			if (r <= t) {																																		// |--t1--------t2----------r--t--------|, ��� t1, t2 = t �� ���������� ���������
				eaten.push_back(el.second);																														// �������� ���� ��� ���������
				routeVec.push_back({ (float)node.getX(), (float)node.getY(), (float)nodes[el.second].getX(), (float)nodes[el.second].getY() });					// ��������� ���� � ������� ������� (��� ������������)
				return &nodes[el.second];																														// ���������� ��������� ����
			}
		}
		return nullptr;																																			// ���� ��������� ����� �� ������ - ������� nullptr � ���������� ��� ������� �-�
	};

	// �������� ������� ��� ���������� ����
	void updatePheromone(const std::vector<unsigned>& route, bool extra = false) noexcept {																		// extra - ���� ��� �������� ��������
		if (!extra) {
			double sum = 0;
			for (size_t i = 0; i < route.size() - 1; ++i) {
				sum += nodes[route[i]].paths[route[i + 1]].length;																								// ���� ����� ����� ����
				nodes[route[i]].paths[route[i + 1]].pheromone *= 0.6;																							// �������� ���������� ���-�� �������� �� ����.���������
			}
				std::cout << "�����: " << sum << std::endl;																										// ����
				for (size_t i = 0; i < route.size() - 1; ++i) {																									
				nodes[route[i]].paths[route[i + 1]].pheromone += 40 / sum;																						// �� ������ ����� ����� ��������� �������
			}
		}
		else {
			for (size_t i = 0; i < route.size() - 1; ++i) {
				nodes[route[i]].paths[route[i + 1]].pheromone += 0.4;																							// ������� ������� ������ ��������� ���-�� ��������� ��������
			}
		}

	};

	// �������� ��������� ��������� (��� ��������� core::AppState::state_started)
	void reset() {
		numberOfAnts = 0;																																		// �������� ���
		nodes.clear();																																			// ����� ���
		routeVec.clear();																																		// ������� ������� �������
		algoSpeed.store(95);																																	// �������� ��������� ���������
		core::bestPath.len = 100000.0;																															// ���������� ����� �����������
		core::bestPath.route.clear();																															// ������ ���� �����������
	};

	// ��������� ��������
	void start() {
		std::vector<std::vector<unsigned>> routes;																												// ������ �� ��������� ��������� ��������
		std::vector<unsigned> vec;																																// ������� �������� ������� (�� id)
		int c = 1;																																				// ������� ��������
		while (true) {
			if (toTerminate.load()) return;																														// ���� main ����� ������� ���������� ������ ��������� - ��������� �����
				Node* current;																																	// ������� ����
			for (int i = 0; i < numberOfAnts; ++i) {																											// ��� ���� ��������
				current = &nodes[0];																															// �������� � �����������
				vec.push_back(0);																																// ������� ���������� ��� ��������� ����� � �������
				while (vec.size() != nodes.size() + 1) {																										// ���� ������� �� ����� ����� ���-�� ���� ����� ���� ���� �� ����������� � �����
					current = findNext(*current, vec);																											// ���� ���� ������� �������
					std::this_thread::sleep_for(std::chrono::milliseconds(algoSpeed.load()));																	// ������ ��������
					if (current == nullptr) throw std::runtime_error("The next node is not defined");															// ������������� ������ �� findNext
				}
				for (auto it = vec.begin(); it != vec.end(); ++it) {																							// ���� ���� ������ �������
					std::cout << *it << ' ';																													// ����
				}
				std::cout << std::endl;																									
				routes.push_back(vec);																															// ��������� ������� ������� �� ��� ��������
				vec.clear();																																	// ������� ������� ������� (�� id ����� ��� ���������)
				routeVec.clear();																																// ������� ������� ������� (�� ��������� ����� ��� ������������) 
			}
			for (size_t i = 0; i < routes.size(); ++i) {																										
				Algo::updatePheromone(routes[i]);																												// ��������� �������� �� ������ ������� ����������
			}
			double minL = 10000000.f;																															// ����������� ���������� ������ ��������
			int minR = 0;																																		// ����� �������, ������������ ���������� �������
			for (size_t i = 0; i < routes.size(); ++i) {
				double curs = 0;																																// ����� �������� ���������� �������
				for (size_t j = 0; j < routes[i].size() - 1; ++j) {																					
					curs += nodes[routes[i].at(j)].paths[routes[i].at(j + 1)].length;																		    // ������� ��������� �����	
				}
				if (curs < minL) {																																// ��������� ���������� ����
					minL = curs;
					minR = i;
				}
			}

			core::bestPath.mut.lock();																															// ��������� ������� ������� ���� ��� �������� ������ main ������
			std::cout << "������ �����: " << minL << std::endl;																									// ����
			if (core::bestPath.len > minL) {																													// �������� ������ main ������ ����� ��������� � ���������
				core::bestPath.len = minL;
				core::bestPath.route = routes[minR];
			}
			core::bestPath.mut.unlock();																														// ������������ �������
			Algo::updatePheromone(routes[minR], true);																											// �������� �������� ������� �� ����� �������� �������

			routes.clear();																																		// ������� �������� ���� ��������
			std::cout << "////// �������� " << c << std::endl;																									// ����
			c++;																																				// ��������� ��������
			
		}
	};
}