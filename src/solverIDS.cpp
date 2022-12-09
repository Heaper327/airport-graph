#include "solverIDS.h"
using namespace std;

vector<Board> SolverIDS::solve() {
    queue<Board> q;
    q.push(_initial);
    map<Board, Board> predecessor;
    unordered_map<string, int> visited;
    visited[_initial.print()] = 1;
    bool isfind = false;
    while (!q.empty()) {
        int q_size = q.size();
        for (int i = 0; i < q_size; i++) {
            Board cur = q.front();
            if (cur == _goal) {
                isfind = true;
                break;
            }
            for (const auto& neighbor: getNeighbors(cur)) {
                if (visited.find(neighbor.print()) == visited.end()) {
                    q.push(neighbor);
                    predecessor[neighbor] =cur;
                    visited[neighbor.print()] = 1;
                }
            }
            q.pop();
        }
        if (isfind) {
            break;
        }
    }
    return predToSolution(predecessor);
}


bool SolverIDS::search(unsigned remaining_depth, vector<Board>& path) {
    Board& cur = path.back();
    if (remaining_depth == 0) {
        // we only check if goal is reached when we exhaust our depth
        // because if goal is at a lower depth, it would have been found by previous iterations already
        if (cur == _goal) {
            return true;
        }
        return false;
    }
    for (const auto& neighbor: getNeighbors(cur)) {
        // cycle pruning
        if (find(path.begin(), path.end(), neighbor) != path.end()) {
            continue;
        }
        path.push_back(neighbor);
        if (search(remaining_depth - 1, path)) { 
            return true;
        }
        path.pop_back();
    }
    return false;  
}

vector<Board> SolverIDS::solve(int max_search_depth) { 
    for(int search_depth = 0; search_depth < max_search_depth; search_depth++) {
        vector<Board> path = {_initial};
        if (search(search_depth, path)) {
            return path;
        }
    }
    return vector<Board>{};
}