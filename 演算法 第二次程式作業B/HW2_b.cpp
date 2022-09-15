#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<vector<int>> arrays;    //save data
int amount = 0;    //save amount of numbers
int height = 0;    //save the height of arrays
vector<int> full;    //reveal the array's full status

//this is use for adjust full status for merging use
void adjustFull(){
    full.at(0)++;
    for(int i=0;i<full.size();i++){
        if(full.at(i) > 1){
            full.at(i+1)++;
            full.at(i) = 0;
        }
    }
}

void newArray(int heightTemp){
    int temp = pow(2, height);
    vector<int> arrTemp;
    for(int i=0;i<temp;i++)
    {
        arrTemp.push_back(0);
    }
    arrays.push_back(arrTemp);
}

int binarySearch(int searchNum){
    int found = 0;
    for(int i=0;i<full.size();i++){
        if(found == 1)
            break;
        int left = 0, right = arrays[i].size()-1;
        int mid = (left + right)/2;
        while(left <= right)
        {
            mid = (left + right)/2;
            if(arrays[i][mid] == searchNum)
            {
                found = 1;
                cout << "[" << i << "]" << "[" << mid << "]" << endl;
                break;
            }
            else if(arrays[i][mid] < searchNum)
            {
                left = mid+1;
            }
            else
            {
                right = mid-1;
            }
        }
    }
    if(found == 1){
        return 1;
    }
    else{
        return 0;
    }
}

void merge(vector<int>& A, vector<int>& B, vector<int>& mergedArray)
{
    int indexA = 0, indexB = 0;
    while(indexA != A.size() && indexB != B.size())
    {
        if(A[indexA]<B[indexB])
        {
            mergedArray.push_back(A[indexA]);
            A[indexA] = 0;
            indexA++;
        }
        else
        {
            mergedArray.push_back(B[indexB]);
            indexB++;
        }
    }
    while(indexA != A.size())
    {
        mergedArray.push_back(A[indexA]);
        A[indexA] = 0;
        indexA++;
    }
    while(indexB != B.size())
    {
        mergedArray.push_back(B[indexB]);
        indexB++;
    }
}

//not only sort, when sort we also add the new int into arrays
void sort(int n){
    //tmp is use for merge two array, arrays[i] and the array contain previous array and new int.
    vector<int> tmp;
    tmp.push_back(n);
    int i=0;
    while(full.at(i)==1){   //we only merge the line who has numbers
        vector<int> tempArray;
        merge(arrays[i], tmp, tempArray);
        tmp = tempArray;    // when the merge end we need to turn back merged array to tmp for merging next line.
        i++;
    }
    arrays[i] = tmp;    //take the merge result in empty array
}

//this is use for watching the result
void printArray(){
    for(int i=0;i<arrays.size();i++){
        for(int j=0;j<arrays.at(i).size();j++){
            cout << arrays[i][j] << " ";
            if(j==arrays.at(i).size()-1)
                cout << endl;
        }
    }
}

void insert(int n){
    //when the amount = 2^height, means that we have to create a array
    int temp = pow(2, height);
    amount++;
    if(amount == temp){
        //when we need to create an array, the height, full need to increase storage space
        newArray(height++);
        full.push_back(0);
        sort(n);
        adjustFull();
    }
    else{
        sort(n);
        adjustFull();
    }
    // printArray();
}

int main()
{
    //input phase
    vector<int> input;    //save the numbers which are used for operation
    string inputString;
    getline(cin, inputString);    //get whole line
    string inputTemp="";    //use for change string to int
    for(int i=0;i<inputString.length();i++){
        //the last number is no ' ' behind, take it as a exception
        if(i == inputString.length()-1){
            inputTemp += inputString.at(i);
            int temp = stoi(inputTemp);
            input.push_back(temp);
        }
        //we get a nuber when meet ' '
        else if(inputString.at(i) == ' ' ){
            int temp = stoi(inputTemp);
            input.push_back(temp);
            inputTemp = "";
        }
        //take the char in inputTemp for change
        else if(inputString.at(i)!= ' '){
            inputTemp += inputString.at(i);
        }
    }

    //find and insert
    for(int i=0;i<input.size();i++){
        //if not found then insert
        int found = binarySearch(input[i]);
        if(found == 0)
        {
            insert(input[i]);
        }
    }
    return 0;
}
