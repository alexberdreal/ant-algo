#ifndef GENERAL
#define GENERAL
#include <vector>
#include <string>

namespace core {


	// ������� ����� � �������� �� �(�1, �1) �� �(�2, �2)
	double findLength(double x1, double y1, double x2, double y2);

	struct Path {                                               // ���������, �������������� �����								
		double length;											// ����� ����� (� ��������)			
		double pheromone;										// ���������� �������� �� �����
	};

	// ~~~~~~~~~~~~~~~~~~ Node - �����, �������������� ���� ~~~~~~~~~~~~~~~~~~


	class Node {
	private:
		const uint16_t id;											// ������������� ����
		const bool isHome;											// �������� �� ���� ������������
		const double x, y;											// ��������� ���� � ��������
	public:
		std::vector<Path> paths;
		Node();
		Node(double x, double y, bool isHome, uint16_t id);
		bool operator==(const Node& toCompare);						// ������������� �������� ��������� == (���������� ���� �� id)
		uint16_t getId();
	};

	inline std::vector<Node> nodes;									// inline ��� weak-internal ���������� (�����, ��� ������������ Core.h ������������ ������� nodes)

	inline uint16_t numberOfAnts;

	enum class AppEvent
	{
		RESTART, LAUNCH, EXIT, DRAWNODE, FEED, CHOOSEANTS
	};

	struct AppState {
		bool toDrawField;
		bool isFieldTouchable;
		bool hasFeedBtn;
		std::string infoText;
		bool hasExecutionBtn;
		bool hasStopBtn;
		bool hasContinueBtn;
		bool hasTextField;
	};

	inline AppState state_started{ true, false, true, "���� ��� ����������", false, false, false, false };
	inline AppState state_nodes{ false, true, false, "����������� ��� ��� ��������", false, false, true, false };
	inline AppState state_ants{ false, false, false, "������� ���������� ��������", false, false, true, true };
	inline AppState state_execution{ false, false, false, "", true, true, false, false };

	// �������, ������� ����� ������ � ����� ������� �������, ���������� ���� � ����� ��������� ������� �������
	class Ant {
	private:
		Node* curPos;								// ��������� �� ������� ����, ��� ��������� �������
		std::vector<uint16_t> nodeIds;					// ������� �������
	public:
		double entireLength;						// ���������� ����
		void updateCurrentPos(Node* position);		// �������� ������� ����, ��� ��������� �������
	};

}

#endif