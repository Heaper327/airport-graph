## Leading Question 

    Instead of analyzing a dataset, our final project revolves around the light bulb game. The game consists of a n-by-n square grid of light bulbs, all of which are off at the beginning of the game. At every turn, the player is allowed to toggle an 3x3 square of bulbs within the grid, turning on the ones that are off, and turning off the ones that are on. The goal of the player is to reach a specified configuration of light bulbs (all on, checker board pattern, etc.)
    
    Our objective is to find the shortest sequence of moves that solves the game, given a reasonably sized n-by-n board and a goal configuration. In addition, we will visualize our result by animating the execution of our moves on a board.
    
    To achieve our goal we will use a directed, unweighted graph to represent the game. Each node of the graph will represent a configuration of the board, and an edge connects node A to B iff configuration A can be transformed into configuration B through a single toggle operation. We will generate the graph from an the initial configuration at runtime using the rules of the game, and use iterative deepening DFS and A* algorithms to find an optimal solution.

## Dataset Acquisition

    As stated above, we will not be using an exisitng data set for our project. Instead, our graph will be generated at run time. Our graph will start with an initial node, representing the initial board with all bulbs off. Each time we query for the neighbors of a node, we will use a transition function to generate them and place them into the graph. The transition function will take an initial configuration, an operation, and outputs the resulting configuration. Therefore, our graph is generated as we explore it for the goal node.
    
    It is worth noting that our graph is only a subgraph of the whole state space of the game, whose nodes represent all possible configurations of the board, and whose edges represent all transitions between them. However, due to the immense size of the state space (a n-by-n game has 2^(2n) possible states), it is impractical to work with the whole state space graph. This is why we chose to only work on the small subgraph relevant to our purpose.

## Data Format

    The only input data we need are the size of the puzzle, n, and the goal configuration of the puzzle, a n-by-n boolean matrix (see data storage section). Therefore, we choose to use a text file as our input format. The first row of the file will contain n, and the next n rows will contain the rows of the goal configuration. Following is an example input:
    
    4
    1010
    0101
    1010
    0101
    
    We will generate the input files by hand

## Data Correction

    To parse our input file we are going to use the ifstream class in the STL. We will save n into an int variable and the goal configuration into our node dictionary (see data storage section).
    
    We will check n to ensure n > 0, check if the goal configuration is indeed n by n, and check whether all elements in the goal configuration are indeed boolean.  We will throw an error if the input does not pass the checks.

## Data Storage

    We will store our graph in an adjacancy list assisted by a dictionary.
    
    We will store the nodes of our graph in an <int, vector<vector<bool>>> dictionary (a hash table). Each node is an entry in the dictionary, with an int key serving as its ID and an n-by-n boolean matrix representing a state of the board (mat[i][j] represents whether the bulb at row i, column j is on)
    
    We will store the edges of our graph in a modified version of the adjacency list, a <int, vector<int>> dictionary. Each entry stores the neighbors of a node, where the key is the ID of the source node, and the vector value contains the IDs of the neighbors. 
    
    Since the number of possible operations (toggles) is fixed for a given board size, each node in our graph has the same fixed degree, which allows us to use a vector in the adj list.
    
    The exactly storage space we will need to store the graph is hard to tell, since our graph will be dynamically generated. However, notice that each node takes a constant amount of space in the dictionary and in the adj list. Therefore, if n were the number of nodes in the graph, we will need O(n) space.

## Algorithm 

    Due to the size of the graph, we will be implementing a DFS traversal iterator. The iterator will move through the graph and output the boards it visit. If the entire graph were to be traversed, the time and space complexity will be O(2^(n^2)). However, in practice we usually only need to traverse part of it.

    To reach the goal configuration will use is the A* algorithm. Since our graph can be potentially very large, we will experiment with multiple heuristics to improve our run time. Our naive heuristic function will return the hamming distance between the current board and the goal board. If this does not work, we will try a manhattan distance heuristic function. 
    
    The time and space complexity of A* heavily depends on our heuristic function. The branching factor (the # of possible moves) of our graph will be O(n^2). However, as our graph contains many cycles (performing the same operation twice on a board returns it to its original state, e.g.), the effective branching factor should be lower. The worst case scenario runtime and space is O((n^2)^d), where d is the distance between initial and goal node, but we expect better performance from our heuristics.
    
    For the traversal and search algorithm, we expect to output the path from the initial node to a goal state as a list of boards. The output will either be stored to a text file, displayed to command line as ASCII images, or converted to an animation similar to mp_floodfill.
    
## Timeline

    We have already clear the rule and the target of the code. So the first step is implement the structure and code of the project. This will take about ten days so we plan to finish it at about 11/15/2022. Then the next step is data correction and data storage, this will take about one week on 11/22/2022. After that two of the group member will focuse on the test case of the code and the other two need to finish the visualization of the graph, this will take one week on 11/29/2022. Finally, the last week allow us to prepare the final report and the presentation of our group.