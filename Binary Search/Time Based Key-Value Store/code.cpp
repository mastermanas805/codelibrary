// https://leetcode.com/problems/time-based-key-value-store/

class Values {
    private:
        std::vector<int> timestamps;
        std::map<int, std::string> mp;
    
        int getTimestamp(int i) const {
            return timestamps[i];
        }
    
        int lessThanEqualTo(int timestamp) const {
            auto it = std::lower_bound(timestamps.begin(), timestamps.end(), timestamp);
            if (it == timestamps.begin()) {
                return -1;
            }
            --it;
            return std::distance(timestamps.begin(), it);
        }
    
    public:
        void set(const std::string& value, int timestamp) {
            auto it = std::lower_bound(timestamps.begin(), timestamps.end(), timestamp);
            timestamps.insert(it, timestamp);
            mp[timestamp] = value;
        }
    
        std::string get(int timestamp) const {
            if (mp.empty()) {
                return "";
            }
    
            auto it = mp.find(timestamp);
            if (it != mp.end()) {
                return it->second;
            }
    
            int index = lessThanEqualTo(timestamp);
            if (index < 0) {
                return "";
            }
            return mp.at(getTimestamp(index));
        }
    };
    
    class TimeMap {
    public:
        std::map<std::string, std::unique_ptr<Values>> mp;
    
        void set(const std::string& key, const std::string& value, int timestamp) {
            if (mp.find(key) == mp.end()) {
                mp.emplace(key, std::make_unique<Values>());
            }
            mp[key]->set(value, timestamp);
        }
    
        std::string get(const std::string& key, int timestamp) const {
            auto it = mp.find(key);
            if (it != mp.end()) {
                return it->second->get(timestamp);
            }
            return "";
        }
    };