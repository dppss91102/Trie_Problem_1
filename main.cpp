#include <iostream>
#include <vector>
#include <map>

using namespace std;

void makeTrie(char* p, int cursor, int num);
vector<map<int, char>> patterns;
int nodeNum = 0;

int main() {

    int n;
    cin >> n;
    cin.ignore();

    while (n-->0){
        char p[256];
        cin.getline(p, 256);

        makeTrie(p, 0, 0);
    }

    for (int i = 0; i < patterns.size(); ++i) {
        for (auto it = patterns[i].begin(); it != patterns[i].end(); ++it){
            cout << i << "->" << it->first << ':' << it->second << endl;
        }
    }

    return 0;
}

void makeTrie(char* p, int cursor, int num){

    if(p[cursor] == '\0')
        return;

    while (patterns.size() < num + 1){
        map<int, char> map1;
        patterns.push_back(map1);
    }

    if (patterns[num].empty()) {
        patterns[num].insert(pair<int, char>(++nodeNum, p[cursor]));
        //cout << num << "->" << nodeNum << ":" << patterns[num].at(nodeNum) << endl;//for debugging
        makeTrie(p, cursor+1, num+1);
        return;
    }

    for (auto &it : patterns[num]) {
        if (it.second == p[cursor]){
            makeTrie(p, cursor+1, it.first);
            return;
        }
    }

    patterns[num].insert(std::pair<int, char>(++nodeNum, p[cursor]));
    //cout << num << "->" << nodeNum << ":" << patterns[num].at(nodeNum) << endl;//for debugging
    makeTrie(p, cursor+1, nodeNum);
}