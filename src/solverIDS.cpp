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


bool SolverIDS::limited_dfs(int max_depth, int cur_depth,  const Board& cur_stat, const Board& target_stat,  unordered_map<string, int>& visited, map<Board, Board>& predecessor) {

    if (cur_depth > max_depth) {
        return false;
    }
    else if (visited[cur_stat.print()] == 1) {
        return false;
    }
    else {
        visited[cur_stat.print()] = 1;
        if (cur_stat == target_stat) {
            return true;
        }
        else {
            for (const auto& neighbor: getNeighbors(cur_stat)) {
                predecessor[neighbor] =cur_stat;
                if (limited_dfs(max_depth, cur_depth + 1, neighbor, target_stat, visited, predecessor)) { 
                    return true;
                }        
            }
            return false;
        }    
    }

}

vector<Board> SolverIDS::solve(int max_search_depth) { 
    bool find = false;
    for(int search_depth = 0; search_depth < max_search_depth; search_depth++) {
        map<Board, Board> predecessor;
        unordered_map<string, int> visited;
        find = this->limited_dfs(search_depth, 0, _initial, _goal, visited, predecessor);
        if (find) {
            return predToSolution(predecessor);
        }
    }
    return vector<Board>{};
}