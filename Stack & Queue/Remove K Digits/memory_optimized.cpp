class Solution {
public:
    string removeKdigits(string num, int k) {
        if (k == num.length()) {
            return "0";
        }

        string ret;
        for (char digit : num) {
            while (!ret.empty() && ret.back() > digit && k > 0) {
                ret.pop_back();
                k--;
            }
            if (!ret.empty() || digit != '0') {
                ret.push_back(digit);
            }
        }

        while (!ret.empty() && k > 0) {
            ret.pop_back();
            k--;
        }

        return ret.empty() ? "0" : ret;
    }
};
