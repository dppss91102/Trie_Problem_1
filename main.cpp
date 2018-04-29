#include <iostream>
#include <vector>
#include <map>

using namespace std;

void makeTrie(char* p, int cursor, int num);
vector<map<int, char>> patterns;
int nodeNum = 0;//node的編號

int main() {

    int n;
    cin >> n;
    cin.ignore();//沒有這個的話getline會吃到\n

    while (n-->0){
        //把一整行讀進p，最多256個字元
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

//用recursive的方式一個一個放進trie中
void makeTrie(char* p, int cursor, int num){//p -> 字串，cursor -> 指向字元的指標，num -> vector的index

    //recursive的終止條件，讀到空字元 = 字串結束
    if(p[cursor] == '\0')
        return;

    //如果pattern[num]不存在，則放入空的map直到pattern[num]
    while (patterns.size() < num + 1){
        map<int, char> map1;
        patterns.push_back(map1);
    }

    //如果這個node底下還沒有分支
    if (patterns[num].empty()) {
        //創一個分支到nodeNum
        patterns[num].insert(pair<int, char>(++nodeNum, p[cursor]));
        //cout << num << "->" << nodeNum << ":" << patterns[num].at(nodeNum) << endl;//for debugging
        //下一個字元，接在上面的node之後
        makeTrie(p, cursor+1, num+1);
        return;
    }

    //如果這個node底下有分支了，檢查分支裡面是否有現在的字元
    for (auto &it : patterns[num]) {
        if (it.second == p[cursor]){
            //如果有的話，則下一個字元接在它的node之後
            makeTrie(p, cursor+1, it.first);
            return;
        }
    }

    //會到這邊則代表這個node底下有分支且都不是現在的字元
    //直接創一個分支到nodeNum
    patterns[num].insert(std::pair<int, char>(++nodeNum, p[cursor]));
    //cout << num << "->" << nodeNum << ":" << patterns[num].at(nodeNum) << endl;//for debugging
    makeTrie(p, cursor+1, nodeNum);
}
