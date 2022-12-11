#include "test-utils.h"

bool randomSolveTest(Solver* solver, unsigned size, unsigned distance) {
	// shuffling vector guarantees that we will get distinct toggles
	// thus the actual distance is equal to the desired distance
	const unsigned num_toggles = (size - 2) * (size - 2);
	vector<unsigned> toggles(num_toggles);
	for (unsigned i = 0; i < num_toggles; i++) {
		toggles[i] = i;
	}
	random_shuffle(toggles.begin(), toggles.end());
	Board initial(size);
	Board goal(initial);
	for (unsigned i = 0; i < distance; i++) {
		unsigned row = toggles[i] / (size - 2);
		unsigned col = toggles[i] % (size - 2);
		goal.toggle(row, col);
	}
	solver->loadFromBoards(initial, goal);
	vector<Board> solution = solver->solve();
	// solution must exists
	if (solution.empty()) {
		return false;
	}
	// solution must start at initial and end at goal
	if (solution.front() != initial || solution.back() != goal) {
		return false;
	}
	// steps of the solution must actually be neighbors
	for (unsigned i = 0; i < solution.size() - 1; i++) {
		vector<Board> neighbors = solver->getNeighbors(solution[i]);
		if (find(neighbors.begin(), neighbors.end(), solution[i + 1]) == neighbors.end()) {
			return false;
		}
	}
	return true;
}