#include<iostream>
#include<vector>
using namespace std;

#include <chrono>
chrono::time_point<std::chrono::high_resolution_clock> starting, ending;
long long t;
vector<char> s1;
vector<char> s2;
vector<vector<int>> map;    //紀錄長度
vector<vector<int>> previous;   //紀錄每格長度來源
vector<char> LCS;   //找到的LCS

void mapAdjust(){
    for(int j=1;j<s2.size();j++){
        for(int i=1;i<s1.size();i++){
            if(s1[i]==s2[j]){
                    map[j][i] = map[j-1][i-1] + 1;
                    previous[j][i] =  0;    //左上
            }
            else{
                if(map[j-1][i] >= map[j][i-1]){
                    map[j][i] = map[j-1][i];
                    previous[j][i] =  1;    //上
                }
                else{
                    map[j][i] = map[j][i-1];
                    previous[j][i] =  2;    //左
                }
            }
        }
    }
}

void getLCS(int j, int i){
    if(i == 0 || j == 0) return;
    if(previous[j][i] == 0){
        LCS.insert(LCS.begin(), s1[i]);
        getLCS(j-1, i-1);
    }
    else if(previous[j][i] == 1)    //上
        getLCS(j-1, i);
    else if(previous[j][i] == 2)    //左
        getLCS(j, i-1);
}

int main()
{
    // cout << "test" << endl;
    s1.push_back('0');
    s2.push_back('0');
    string inputS1, inputS2;
    cin >> inputS1 >> inputS2;
    starting = chrono::high_resolution_clock::now(); // start timing
    for(int i=0;i<inputS1.length();i++){
        s1.push_back(inputS1.at(i));
    }
    for(int i=0;i<inputS2.length();i++){
        s2.push_back(inputS2.at(i));
    }

    vector<int> inputTemp;
    for(int i=0;i<=inputS1.length();i++){
        inputTemp.push_back(0);
    }
    for(int i=0;i<=inputS2.length();i++){
        map.push_back(inputTemp);
    }

    previous = map;

    mapAdjust();

    // for(int j=0;j<s2.size();j++){
    //     for(int i=0;i<s1.size();i++){
    //         cout << map[j][i];
    //     }
    //     cout << endl;
    // }
    // for(int j=0;j<s2.size();j++){
    //     for(int i=0;i<s1.size();i++){
    //         cout << previous[j][i];
    //     }
    //     cout << endl;
    // }

    getLCS(s2.size()-1, s1.size()-1);

    for(int i=0;i<LCS.size();i++){
        cout << LCS[i];
    }
    cout << endl;

    ending = chrono::high_resolution_clock::now();
    t = t + chrono::duration_cast<std::chrono::nanoseconds>(ending - starting).count();
    cout << t << " s" << endl;
    return 0;
}
