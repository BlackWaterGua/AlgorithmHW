#include<iostream>
#include<vector>
using namespace std;

#include <chrono>

typedef struct{
    char character;
    vector<int> index;
}word;
long long t;
chrono::time_point<std::chrono::high_resolution_clock> starting, ending;
vector<word> s1;

int main(){
    string inputS1, inputS2;
    cin >> inputS1 >> inputS2;
    starting = chrono::high_resolution_clock::now();
    for(int i=0;i<inputS1.length();i++){
        bool found = false;
        for(int j=0;j<s1.size();j++){
            if(inputS1.at(i) == s1.at(j).character){
                found = true;
                s1.at(j).index.insert(s1.at(j).index.begin(), i);
                break;
            }
        }
        if(found == false){
            word temp;
            temp.character = inputS1.at(i);
            temp.index.push_back(i);
            s1.push_back(temp);
        }
    }

    vector<int> LIS_element;
    for(int i=0;i<inputS2.length();i++){
        for(int j=0;j<s1.size();j++){
            if(inputS2.at(i) == s1.at(j).character){
                for(int k=0;k<s1.at(j).index.size();k++){
                    LIS_element.push_back(s1.at(j).index.at(k));
                }
                break;
            }
        }
    }

    vector<int> LIS;
    int maxLength = 0, max = LIS_element.at(0);
    vector<int> LIS_element_DP;
    for(int i=0;i<LIS_element.size();i++){
        int cur = LIS_element.at(i);
        if(i==0){
            LIS_element_DP.push_back(0);
            LIS.push_back(LIS_element.at(0));
        }
        else if(cur > LIS.back()){
            LIS.push_back(cur);
            LIS_element_DP.push_back(LIS.size()-1);
            maxLength = LIS.size()-1;
        }
        else{
            int temp = cur;
            int temp_small = 99999999;
            int temp_index = 0;
            for(int j=LIS.size()-1;j>=0;j--){
                if(LIS.at(j) >= temp && LIS.at(j) < temp_small){
                    temp_small = LIS.at(j);
                    temp_index = j;
                }
            }
            LIS.at(temp_index) = cur;
            LIS_element_DP.push_back(temp_index);
        }
    }

    vector<int> sIndex;
    for(int i=LIS_element_DP.size()-1;i>=0;i--){
        if(LIS_element_DP.at(i) == maxLength){
            sIndex.insert(sIndex.begin(), i);
            maxLength--;
        }
    }

    vector<int> printIndex;
    for(int i=0;i<sIndex.size();i++){
        int temp = LIS_element.at(sIndex.at(i));
        printIndex.push_back(temp);
    }

    for(int i=0;i<printIndex.size();i++){
        for(int j=0;j<s1.size();j++){
            bool found = false;
            for(int k=0;k<s1.at(j).index.size();k++){
                if(printIndex.at(i) ==s1.at(j).index.at(k)){
                    cout << s1.at(j).character;
                    break;
                }
            }
            if(found == true)
                break;
        }
    }

    cout << endl;
    ending = chrono::high_resolution_clock::now();
    t = t + chrono::duration_cast<std::chrono::nanoseconds>(ending - starting).count();
    cout << t << " s" << endl;
    return 0;
}
