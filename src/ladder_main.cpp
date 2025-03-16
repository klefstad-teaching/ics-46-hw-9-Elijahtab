#include "ladder.h"
#include <iostream>
#include <string>

using namespace std;


int main() {
    set<string> word_list;
    load_words(word_list, "/Users/elijahtabachnik/Desktop/Github/School/ics-46-hw-9-Elijahtab/src/words.txt");
    vector<string> lad = generate_word_ladder("cat", "fuck", word_list);
    print_word_ladder(lad);
}
