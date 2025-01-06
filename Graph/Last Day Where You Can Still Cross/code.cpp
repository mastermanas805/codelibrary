#define key pair<int, int>
#define ff first
#define ss second
class Solution {
public:
    vector<key> moves = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        int l = 0, r = row * col - 1, mid;

        while (l <= r) {
            mid = (l + r) / 2;
            if (canCross(row, col, cells, mid)) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        return l;
    }

    bool canCross(int row, int col, vector<vector<int>>& cells, int mid) {
        vector<vector<int>> state(row, vector<int>(col, 0));
        for (int i = 0; i <= mid; i++) state[cells[i][0] - 1][cells[i][1] - 1] = 1;

        for (int i = 0; i < col; i++)
            if (canCross(row, col, state, {0, i})) return true; 

        return false;
    }

    bool canCross(int row, int col, vector<vector<int>>& cells, key src) {
        if (cells[src.ff][src.ss] == 1) return false;

        queue<key> q;
        q.push(src);
        cells[src.ff][src.ss] = 2; // Mark as visited

        while (!q.empty()) {
            key src = q.front();
            q.pop();
            if (src.ff == row - 1) return true; // Early exit
            for (key i : moves) {
                key dst = {i.ff + src.ff, i.ss + src.ss};
                if (dst.ff < 0 || dst.ff >= row ||
                    dst.ss < 0 || dst.ss >= col ||
                    cells[dst.ff][dst.ss] != 0) continue;
                q.push(dst);
                cells[dst.ff][dst.ss] = 2; // Mark as visited
            }
        }
        return false;
    }
};