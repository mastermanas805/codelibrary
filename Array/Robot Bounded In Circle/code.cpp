// https://leetcode.com/problems/robot-bounded-in-circle/


class Solution {
public:
    bool isRobotBounded(string instructions) {
        int x = 0, y = 0, dir = 0;
        for (int i = 0; i < 4; ++i) {
            for (auto& c : instructions) {
                if (c == 'G') {
                    if (dir == 0) y++;
                    else if (dir == 90) x++;
                    else if (dir == 270) x--;
                    else y--;
                } else if (c == 'L') 
                    dir = dir - 90 < 0 ? 270 : dir - 90;
                else 
                    dir = dir + 90 >= 360 ? 0 : dir + 90;
            }
            if (x == 0 && y == 0) return true;
        }
        return false;
    }
};