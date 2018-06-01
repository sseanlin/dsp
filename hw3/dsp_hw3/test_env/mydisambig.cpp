#include <cstring>
#include <unordered_map>
#include <vector>
#include <string>
#include <utility>
#include <limits>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Ngram.h"

using namespace std;

typedef vector<string> Path;

double bigranProb(Ngram &lm, Vocab &vocab, string &now, string &last) {
    VocabIndex i_now = vocab.getIndex(now.c_str());
    VocabIndex i_last = vocab.getIndex(last.c_str());
    
    i_now = i_now == Vocab_None ? Vocab_Unknown : i_now;
    i_last = i_last == Vocab_None ? Vocab_Unknown : i_last;
    
    VocabIndex context[] = {i_last, Vocab_None};
    return lm.wordProb(i_now, context);
}

int main(int argc, char *argv[]) {
    char *map_filename, *text_filename, *lm_filename;
    int order = 2;
    for (int i = 1; i <= 8; i += 2) {
        if (strcmp(argv[i], "-map") == 0)
            map_filename = argv[i + 1];
        else if (strcmp(argv[i], "-text") == 0)
            text_filename = argv[i + 1];
        else if (strcmp(argv[i], "-lm") == 0)
            lm_filename = argv[i + 1];
        else if (strcmp(argv[i], "-order") == 0)
            order = atoi(argv[i + 1]);
        else {
            fprintf(stderr, "command error\n");
            exit(EXIT_FAILURE);
        }
    }
    
    unordered_map<string, vector<string>> zy_map;
    ifstream map_fs(map_filename);
    string line;
    while(getline(map_fs, line)) {
        istringstream ss(line);
        string key, character;
        getline(ss, key, ' ');
        while(getline(ss, character, ' ')) {
            if(!character.empty()) zy_map[key].push_back(character);
        }
    }
    
    Vocab vocab;
    Ngram lm(vocab, order);
    File lmfile(lm_filename, "r");
    lm.read(lmfile);
    lmfile.close();
    
    ifstream text(text_filename);
    string line;
    while(getline(text, line)) {
        vector<Path> last_paths;
        vector<double> last_probs;
        Path initial;
        initial.push_back("<s>"); 
        last_paths.push_back(initial);
        last_probs.push_back(0.0);
        istringstream ss(line);
        string character;
        while(getline(ss, character, ' ')) {
            if(character.empty()) continue;
            vector<string> &candidates = zy_map[character];
            vector<Path> now_paths(candidates.size());
            vector<double> now_probs(candidates.size());
            for(int i = 0; i < candidates.size(); ++i) {
                string &now = candidates[i];
                int max_j = 0;
                double max_prob = numeric_limits<double>::lowest();
                for(int j = 0; j < last_paths.size(); ++j) {
                    string &last = last_paths[j].back();
                    double prob = last_prob[j] + bigramProb(lm, vocab, now, last);
                    if(prob > max_prob) {
                        max_j = j;
                        max_prob = prob;
                    }
                }
                now_probs[i] = max_prob;
                now_paths[i] = last_path[max_j];
                now_paths[i].push_back(now);
            }
            last_paths = move(now_paths);
            last_prob = move(now_prob);
        }
        int max_i = 0;
        double max_prob = numeric_limits<double>::lowest();
        for(int i = 0; i < last_paths.size(); ++i) {
            if(last_prob[i] > max_prob) {
                max_i = i;
                max_prob = last_prob[i];
            }
        }
        for(string character : last_paths[max_i]) {
            cout << character << " ";
        }
        cout << "</s>" << endl;
    } 
}
