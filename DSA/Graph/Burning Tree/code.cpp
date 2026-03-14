#include<bits/stdc++.h>
using namespace std;
// Node structure
struct Node {
    int data;
    Node *left, *right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};


// Helper function to build tree from level-order string
Node* buildTree(string str) {
    if (str.length() == 0 || str[0] == 'N') return nullptr;
    vector<string> ip;
    istringstream iss(str);
    for (string str; iss >> str; ) ip.push_back(str);

    Node* root = new Node(stoi(ip[0]));
    queue<Node*> q;
    q.push(root);

    int i = 1;
    while (!q.empty() && i < ip.size()) {
        Node* curr = q.front();
        q.pop();

        if (ip[i] != "N") {
            curr->left = new Node(stoi(ip[i]));
            q.push(curr->left);
        }
        i++;
        if (i >= ip.size()) break;
        if (ip[i] != "N") {
            curr->right = new Node(stoi(ip[i]));
            q.push(curr->right);
        }
        i++;
    }
    return root;
}


#include<bits/stdc++.h>

using namespace std;

class Solution{
	unordered_map<int, Node*> parent;
	Node* newRoot = nullptr;
	public:
		bool fillParents(Node* root, Node* parentNode, int start) {
			if(root == nullptr) return 0;

			if(root->data == start) {
				newRoot = root;
				parent[root->data] = parentNode;
				return true;
			}

			if(fillParents(root->left, root, start)) {
				parent[root->data] = parentNode;
				return true;
			}

			if(fillParents(root->right, root, start)) {
				parent[root->data] = parentNode;
				return true;
			}
		}

		int minTime(Node* root, int start){
            bool nodeExists = fillParents(root, nullptr, start);
			if(!nodeExists) 
				return 0;
			
			queue<pair<Node*, Node*>> q;
			q.push({newRoot, nullptr});
			int level = -1;
			while(!q.empty()) {
                level++;
				int sz = q.size();
				while(sz--) {
					pair<Node*, Node*> front = q.front();
					q.pop();

					if(parent.find(front.first->data) != parent.end() 
						&& parent[front.first->data] != front.second
                        && parent[front.first->data] != nullptr) {
							q.push({parent[front.first->data], front.first});
					}

					if(front.first->left!= nullptr && front.first->left != front.second)
						q.push({front.first->left, front.first});
					
					if(front.first->right!= nullptr && front.first->right != front.second)
						q.push({front.first->right, front.first});
				}
			}

			return level;

		}	
};


int main() {
    // Input format based on your image: 1 2 3 4 5 6 7
    string treeInput = "1 2 3 4 5 6 7";
    int target = 4; // Example target node

    Node* root = buildTree(treeInput);
    Solution sol;
    
    int result = sol.minTime(root, target);
    
    cout << "Minimum time to burn the tree starting from " << target << " is: " << result << endl;

    return 0;
}