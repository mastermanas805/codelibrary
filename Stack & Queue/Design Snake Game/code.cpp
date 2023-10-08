// https://leetcode.com/problems/design-snake-game/

class SnakeGame {
public:
    vector<vector<bool>> matrix;
    queue<pair<int,int>> food, moves;
    int size = 1;
    SnakeGame(int width, int height, vector<vector<int>>& food) {
        matrix = vector<vector<bool>>(height,vector<bool>(width, false));

        matrix[0][0] = 1;
        moves.push({0,0});

        for(auto i: food)
            this->food.push({i[0], i[1]});
    }
    
    int move(string direction) {
        pair<int,int> p = moves.back(), tail = moves.front();
        switch(direction[0]){
            case 'L':
                p.second--;
                break;
            case 'R':
                p.second++;
                break;
            case 'U':
                p.first--;
                break;
            case 'D':
                p.first++;
                break;
        }

        matrix[tail.first][tail.second] = 0;
        
        // snake runs out of bounds of rows
        if(p.first < 0 || p.first >= matrix.size()){
            return -1;
        }

        // snake runs out of bounds of columns
        if(p.second < 0 || p.second >= matrix[0].size()){
            return -1;
        }

        // snake runs into itself
        if(matrix[p.first][p.second] == 1){
            return -1;
        }

        matrix[p.first][p.second] = 1;

        if(!this->food.empty() && this->food.front() == p){
            this->size++;
            food.pop();
            matrix[tail.first][tail.second] = 1;
        }else{
            moves.pop();
        }

        moves.push(p);

        return  this->size-1;

    }
};

/**
 * Your SnakeGame object will be instantiated and called as such:
 * SnakeGame* obj = new SnakeGame(width, height, food);
 * int param_1 = obj->move(direction);
 */