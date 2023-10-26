#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Node {
public:
    Node* links[256];
    int frequency;

    Node() {
        frequency = 0;
        for (int i = 0; i < 256; i++) {
            links[i] = nullptr;
        }
    }

    bool contains(int index) {
        return links[index] != nullptr;
    }

    void put(int index, Node* node) {
        links[index] = node;
    }

    Node* get(int index) {
        return links[index];
    }

    void updateFrequency(int times) {
        frequency += times;
    }
};

int char2int(char ch) {
    return static_cast<int>(ch);
}

char int2char(int i) {
    return static_cast<char>(i);
}

class Trie {
public:
    Node* root;

    Trie() {
        root = new Node();
    }

    void insert(string &word, int times) {
        Node* node = root;
        for (char c : word) {
            int index = char2int(c);

            if (!node->contains(index)) {
                node->put(index, new Node());
            }

            node = node->get(index);
        }
        node->updateFrequency(times);
    }

   void dfs(Node* node, string currString, vector<pair<int, string>>& possibleSentences) {
    if (node->frequency != 0) {
        possibleSentences.push_back({ node->frequency, currString });
    }

    for (int i = 0; i < 256; i++) {
        if (node->contains(i)) {
            Node* nextNode = node->get(i);
            char nextChar = int2char(i);
            string nextString = currString + nextChar; // Create a new string for each branch
            dfs(nextNode, nextString, possibleSentences);
        }
    }
}

private:

 ~Trie() {
        deleteNodes(root);
    }

    void deleteNodes(Node* node) {
        if (node == nullptr) {
            return;
        }
 
        for (int i = 0; i < 256; i++) {
            if (node->contains(i)) {
                deleteNodes(node->get(i));
            }
        }

        delete node;
    }

};

bool comparator(const pair<int, string>& p1, const pair<int, string>& p2) {
    if (p1.first > p2.first) return true;
    else if (p1.first < p2.first) return false;
    else {
        return p1.second < p2.second;
    }
}

vector<string> Top3sentences(vector<pair<int, string>>& possibleSentences) {
    vector<string> ans;
    sort(possibleSentences.begin(), possibleSentences.end(), comparator);

    int size = possibleSentences.size();

    for (int hot = 0; hot < 3 && hot < size; hot++) {
        ans.push_back(possibleSentences[hot].second);
    }

    return ans;
}

class AutocompleteSystem {
public:
    string currString;
    Trie* t;
    Node* currNode;

    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {
        currString = "";
        t = new Trie();
        currNode = t->root;

        for (size_t i = 0; i < sentences.size(); i++) {
            t->insert(sentences[i], times[i]);
        }
    }

    vector<string> input(char c) {
        vector<pair<int, string>> possibleSentences;

        if (c == '#') {
            t->insert(currString, 1);
            currString = "";
            currNode = t->root; // Reset the current node to the root.
            return vector<string>();
        }

        currString.push_back(c);
        if (currNode == nullptr || !currNode->contains(char2int(c))) {
            currNode = nullptr;
            return vector<string>();
        }
        currNode = currNode->get(char2int(c)); // Update the current node based on the input character.
        t->dfs(currNode, currString, possibleSentences);

        return Top3sentences(possibleSentences);

    }

};

int main() {
    ifstream inputFile; // Open the input file
    inputFile.open("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    vector<string> sentences;
    vector<int> times;

    // Read sentences and times from the file
    int numSentences;
    inputFile >> numSentences;
    inputFile.ignore();

    for (int i = 0; i < numSentences; ++i) {
        string sentence;
        //getline is used to take sentences as input instead of just words.
       getline(inputFile, sentence,'\n');
        sentences.push_back(sentence);
    }
    

    for (int i = 0; i < numSentences; ++i) {
        int time;
        inputFile >> time;
        times.push_back(time);
    }

    // Creating an instance of AutocompleteSystem
    AutocompleteSystem autocompleteSystem(sentences, times);

    // Process input from the file
    char c;
    while (inputFile >> c) {

        vector<string> result = autocompleteSystem.input(c);

        // Displaying the autocomplete suggestions
       int count=1;
        for (const string& suggestion : result) {
            cout << "Suggestion " <<count<<" : "<< suggestion << endl;
            count++;
        }
    }

    // Close the input file
    inputFile.close();

    return 0;
}
