#include "ladder.h"
#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <queue>
#include <stack>

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    if(begin_word == end_word) {
        error(begin_word, end_word, "The words are the same");
        return {};
    }
    if(word_list.count(end_word) == 0) {
        error(begin_word, " ", "The begin word is not a valid word");
        return {};
    }
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while(!ladder_queue.empty()){
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        for(auto word : word_list){
            if(is_adjacent(last_word, word)){
                if (visited.count(word) == 0) {
                    visited.insert(word); 
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word)
                        return new_ladder;
                    ladder_queue.push(new_ladder);
                }
                
            }
        }
    }
    return {};
}



bool is_adjacent(const string& word1, const string& word2){
    size_t word1_len = word1.size();
    size_t word2_len = word2.size();
    string word_test = word1;

    if(word1_len == word2_len){
        for(int i = 0; i < word1_len; i++){
            if(word1[i] != word2[i]){
                word_test[i] = word2[i];
                return word_test == word2;
            }
        }
    } else if((word1_len - 1) == word2_len){
        for(int i = 0; i < word1_len; i++){
            if(word1[i] != word2[i]){
                word_test.erase(i, 1);
                return word_test == word2;
            }
        }
    } else if((word1_len + 1) == word2_len){
        for(int i = 0; i < word2_len; i++){
            if(word1[i] != word2[i]){
                word_test = word1.substr(0, i) + word2[i] + word1.substr(i);
                return word_test == word2;
            }
        }
    } else {
        return false;
    }
    
    return word1 == word2;
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(file_name);

    if(!file)
        error(file_name, "could not find file: ", "failed to open");
    
    string word;
    while( file >> word){
        word_list.insert(word);
    }
    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    
    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); i++) {
        cout << ladder[i] << " ";
    }
    cout << endl;
}

bool verify_word_ladder(const vector<string>& ladder) {
    if (ladder.size() < 2) return false;  // Must have at least two words

    for (size_t i = 1; i < ladder.size(); i++) {
        if (!is_adjacent(ladder[i - 1], ladder[i])) {
            return false;  // Two words in the ladder are not adjacent
        }
    }
    return true;
}

void error(string word1, string word2, string msg) {
    cerr << msg << word2 << word1 << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.size(), len2 = str2.size();
    
    if (std::abs(len1 - len2) > d) return false;


    std::vector<std::vector<int>> dp(len1 + 1, std::vector<int>(len2 + 1, 0));

    for (int i = 0; i <= len1; ++i) dp[i][0] = i;
    for (int j = 0; j <= len2; ++j) dp[0][j] = j;

    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];  
            } else {
                dp[i][j] = std::min({dp[i - 1][j] + 1,     
                                     dp[i][j - 1] + 1,     
                                     dp[i - 1][j - 1] + 1}
                                   );
            }
        }
    }

    return dp[len1][len2] <= d;
}