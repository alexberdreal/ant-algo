#include "Algorithm.h"
#include <thread>

State state;

int main() {
	Visual::drawWindow();
	bool isLaunched = false;
	AppEvent ev;
	while (true) {
		ev = Visual::waitForEvent();
		Node node(0, 0, false, 0);
		switch (ev)
		{
		case AppEvent::DRAWNODE :
			state.addNode(node);
			break;
		case AppEvent::CLEAR :
			Visual::clean();
			break;
		case AppEvent::LAUNCH :
			//std::thread(Algo::start, NULL);
			break;
		case AppEvent::EXIT :
			exit(EXIT_SUCCESS);
			break;
		default:
			break;
		}
	}
}