#include <iostream>
#include <vector>
#include <map>

using namespace std;
#define maxCharNum 256 //定義一行最多幾個char

void makeTrie(char* cursor, int currentNode);
vector<map<int, char>> patterns;
int nextNode = 0;//node的編號

int main() {

    int n;
    cin >> n;
    cin.ignore();//沒有這個的話getline會吃到\n

    while (n-->0){
        //把一整行讀進p，最多maxCharNum個字元，包含最後的'\0'
        char p[maxCharNum];
        cin.getline(p, maxCharNum);

        makeTrie(p, 0);
    }

    for (int i = 0; i < patterns.size(); ++i) {
        for (auto it = patterns[i].begin(); it != patterns[i].end(); ++it){
            cout << i << "->" << it->first << ':' << it->second << endl;
        }
    }

    return 0;
}

//用recursive的方式一個一個放進trie中
void makeTrie(char* cursor, int currentNode){
    /* cursor   -> 指向字元的指標
     * currentNode  -> vector的index(現在的node)
     * nextNode     -> 下一個要指到的node
     * */

    //recursive的終止條件，讀到空字元 = 字串結束
    if(*cursor == '\0')
        return;

    //如果pattern[currentNode]不存在，則放入空的map直到pattern[currentNode]
    while (patterns.size() < currentNode + 1){
        map<int, char> map1;
        patterns.push_back(map1);
    }

    //如果這個node底下還沒有分支
    if (patterns[currentNode].empty()) {
        //創一個分支指到nextNode
        patterns[currentNode].insert(pair<int, char>(++nextNode, *cursor));
        //cout << currentNode << "->" << nextNode << ":" << patterns[currentNode].at(nextNode) << endl;//for debugging
        //下一個字元，接在上面的node之後
        makeTrie(cursor+1, currentNode+1);
        return;
    }

    //如果這個node底下有分支了，檢查分支裡面是否有現在的字元
    for (auto &it : patterns[currentNode]) {
        if (it.second == *cursor){
            //如果有的話，則下一個字元接在它的node之後
            makeTrie(cursor+1, it.first);
            return;
        }
    }

    //會到這邊則代表這個node底下有分支且都不是現在的字元
    //直接創一個分支指到nextNode
    patterns[currentNode].insert(std::pair<int, char>(++nextNode, *cursor));
    //cout << currentNode << "->" << nextNode << ":" << patterns[currentNode].at(nextNode) << endl;//for debugging
    makeTrie(cursor+1, nextNode);
}
