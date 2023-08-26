#include <bits/stdc++.h>
#include <unordered_set>
using namespace std ;

typedef pair<string,int> P ;
struct Order {
    bool operator()(P const& a, P const& b) const {
        if (a.second != b.second) return a.second > b.second;
        int n = a.first.size();
        int m = b.first.size();
        int k = min(n, m);
        for (int i = 0; i < k; i++) {
            if (a.first[i] != b.first[i]) return a.first[i] < b.first[i];
        }
        return n < m;
    }
};

class TrieNode {
public:
    vector<TrieNode*> children;
    int isEnd;
    TrieNode() {
        isEnd = 0;
        children = vector<TrieNode*>(256, nullptr);
    }
};

class Trie {
public:
    TrieNode* root;
    Trie() {
        root = new TrieNode();
    }
    int char2int(char c) {
        return int(c);
    }
    char int2char(int num) {
        return char(num);
    }
    void insert(string s) {
        TrieNode* curr = root;
        for (auto c : s) {
            int cNum = char2int(c);
            if (curr->children[cNum] == nullptr) curr->children[cNum] = new TrieNode();
            curr = curr->children[cNum];
        }
        curr->isEnd++;
    }
    vector<string> find(string s) {
        priority_queue<P, vector<P>, Order> q;
        vector<string> out;
        TrieNode* curr = root;
        for (auto c : s) {
            int cNum = char2int(c);
            if (curr->children[cNum] == nullptr) return out;
            curr = curr->children[cNum];
        }
        string currAccum = s;
        dfs(curr, q, currAccum);
        while (!q.empty()) {
            out.push_back(q.top().first);
            q.pop();
        }
        reverse(out.begin(), out.end());
        return out;
    }
    void dfs(TrieNode* node, priority_queue<P, vector<P>, Order>& q, string& currAccum) {
        if (node->isEnd > 0) {
            q.push(make_pair(currAccum, node->isEnd));
            if (q.size() > 3) q.pop();
        }
        for (int i = 0; i < 27; i++) {
            if (node->children[i] != nullptr) {
                currAccum.push_back(int2char(i));
                dfs(node->children[i], q, currAccum);
                currAccum.pop_back();
            }
        }
    }
};

class SearchAutoCompleteSystem {
public:
    Trie* trie;
    string currString;
    SearchAutoCompleteSystem(vector<string>& sentences, vector<int>& times) {
        trie = new Trie();
        int n = sentences.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < times[i]; j++) {
                trie->insert(sentences[i]);
            }
        }
    }
    
    vector<string> input(char c) {
        if (c == '#') {
            trie->insert(currString);
            currString = "";
            return vector<string>();
        }
        currString.push_back(c);
        return trie->find(currString);
    }
};

int main() {
    fstream f ;
    f.open("cache.txt",ios::in);
    vector<string> sentences ;
    unordered_map<string,int> m ;
    vector<int> times ;
    while(!f.eof()) {
        string s ;
        int fq ; 
        f>>s>>fq ;
        m[s]=fq ;
        sentences.push_back(s);
        times.push_back(fq);
    }
    f.close();
    SearchAutoCompleteSystem* System = new SearchAutoCompleteSystem(sentences,times);
    char c ; 
    string terms="" ;
    cout<<"Enter Word " ;
    while(true) {
        cin>>c ;
        system("clear");
        if(c=='#') break ;
        terms+=c ;
        vector<string> ans = System->input(c);
        cout<<"Showing Results for "<<terms<<endl ;
        for(auto &t : ans) cout<<t<<endl ;
    }
    m[terms]++ ;
    f.open("cache.txt",ios::out);
    f<<sentences.size()<<endl ;
    for(auto &p : m) {
        f<<p.first<<" "<<p.second<<endl ;
    }
    f.close();
    return 0 ;
}
