#include<iostream>
#include<vector>
using namespace std;

int trackMap[100][100];
int trackMapM[100][100];
int eatWhoMax[100][100];
int eatWhoMin[100][100];

void ParentString(vector<string>&, int, int, int);
void MaxParent(string A)
{
    vector<int> num;
    vector<char> symbol;
    string tempinput = "";
    for(int i=0;i<A.length();i++)
    {
        if(i!=0 && (A.at(i) == '+' || A.at(i) == '*' || A.at(i) == '-'))
        {
            num.push_back(stoi(tempinput));
            tempinput = "";
            symbol.push_back(A.at(i));
            if(i!=A.length()-1 && A.at(i+1) == '-')
            {
                tempinput += A.at(i+1);
                i++;
            }
        }
        else if(i==A.length()-1)
        {
            tempinput += A.at(i);
            num.push_back(stoi(tempinput));
        }
        else
        {
            tempinput += A.at(i);
        }
    }

    int size = num.size();
    int max[size][size];
    int min[size][size];
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            max[i][j] = -99999999;
            min[i][j] = 99999999;
            eatWhoMax[i][j] = 0;
            eatWhoMin[i][j] = 0;
            trackMap[i][j] = 0;
            if (i == j)
            {
                max[i][j] = num[i];
                min[i][j] = num[i];
            }
        }
    }

    for (int s = 2; s <= size; s++)
    {
        for (int i = 0; i < size - s + 1; i++)
        {
            int j = i + s - 1;
            for (int k = i; k < j; k++)
            {
                int eatMax = 0;
                int eatMin = 0;
                int maxTmp=-99999999;
                int minTmp=99999999;
                if(symbol[k] == '+')
                {
                    int subMinTmp, subMaxTmp, subEatMax, subEatMin;
                    //4 type combination for min => +
                    subMinTmp = min[i][k] + min[k + 1][j];
                    if(subMinTmp < minTmp)
                    {
                        subEatMin = 3;
                        minTmp = subMinTmp;
                    }
                    subMinTmp = min[i][k] + max[k + 1][j];
                    if(subMinTmp < minTmp)
                    {
                        subEatMin = 4;
                        minTmp = subMinTmp;
                    }
                    subMinTmp = max[i][k] + max[k + 1][j];
                    if(subMinTmp < minTmp)
                    {
                        subEatMin = 1;
                        minTmp = subMinTmp;
                    }
                    subMinTmp = max[i][k] + min[k + 1][j];
                    if(subMinTmp < minTmp)
                    {
                        subEatMin = 2;
                        minTmp = subMinTmp;
                    }
                    eatMin = subEatMin;

                    // 4 type combination for max => +
                    subMaxTmp = max[i][k] + max[k + 1][j];
                    if(subMaxTmp > maxTmp)
                    {
                        subEatMax = 1;
                        maxTmp = subMaxTmp;
                    }
                    subMaxTmp = max[i][k] + min[k + 1][j];
                    if(subMaxTmp > maxTmp)
                    {
                        subEatMax = 2;
                        maxTmp = subMaxTmp;
                    }
                    subMaxTmp = min[i][k] + min[k + 1][j];
                    if(subMaxTmp > maxTmp)
                    {
                        subEatMax = 3;
                        maxTmp = subMaxTmp;
                    }
                    subMaxTmp = min[i][k] + max[k + 1][j];
                    if(subMaxTmp > maxTmp)
                    {
                        subEatMax = 4;
                        maxTmp = subMaxTmp;
                    }
                    eatMax = subEatMax;
                }
                else if(symbol[k] == '*')
                {
                    int subMinTmp, subMaxTmp, subEatMax, subEatMin;
                    //4 type combination for min => *
                    subMinTmp = min[i][k] * min[k + 1][j];
                    if(subMinTmp < minTmp)
                    {
                        subEatMin = 3;
                        minTmp = subMinTmp;
                    }
                    subMinTmp = min[i][k] * max[k + 1][j];
                    if(subMinTmp < minTmp)
                    {
                        subEatMin = 4;
                        minTmp = subMinTmp;
                    }
                    subMinTmp = max[i][k] * max[k + 1][j];
                    if(subMinTmp < minTmp)
                    {
                        subEatMin = 1;
                        minTmp = subMinTmp;
                    }
                    subMinTmp = max[i][k] * min[k + 1][j];
                    if(subMinTmp < minTmp)
                    {
                        subEatMin = 2;
                        minTmp = subMinTmp;
                    }
                    eatMin = subEatMin;

                    // 4 type combination for max => *
                    subMaxTmp = max[i][k] * max[k + 1][j];
                    if(subMaxTmp > maxTmp)
                    {
                        subEatMax = 1;
                        maxTmp = subMaxTmp;
                    }
                    subMaxTmp = max[i][k] * min[k + 1][j];
                    if(subMaxTmp > maxTmp)
                    {
                        subEatMax = 2;
                        maxTmp = subMaxTmp;
                    }
                    subMaxTmp = min[i][k] * min[k + 1][j];
                    if(subMaxTmp > maxTmp)
                    {
                        subEatMax = 3;
                        maxTmp = subMaxTmp;
                    }
                    subMaxTmp = min[i][k] * max[k + 1][j];
                    if(subMaxTmp > maxTmp)
                    {
                        subEatMax = 4;
                        maxTmp = subMaxTmp;
                    }
                    eatMax = subEatMax;
                }
                else if(symbol[k] == '-')
                {
                    int subMinTmp, subMaxTmp, subEatMax, subEatMin;
                    //4 type combination for min => -
                    subMinTmp = min[i][k] - min[k + 1][j];
                    if(subMinTmp < minTmp)
                    {
                        subEatMin = 3;
                        minTmp = subMinTmp;
                    }
                    subMinTmp = min[i][k] - max[k + 1][j];
                    if(subMinTmp < minTmp)
                    {
                        subEatMin = 4;
                        minTmp = subMinTmp;
                    }
                    subMinTmp = max[i][k] - max[k + 1][j];
                    if(subMinTmp < minTmp)
                    {
                        subEatMin = 1;
                        minTmp = subMinTmp;
                    }
                    subMinTmp = max[i][k] - min[k + 1][j];
                    if(subMinTmp < minTmp)
                    {
                        subEatMin = 2;
                        minTmp = subMinTmp;
                    }
                    eatMin = subEatMin;

                    // 4 type combination for max => -
                    subMaxTmp = max[i][k] - max[k + 1][j];
                    if(subMaxTmp > maxTmp)
                    {
                        subEatMax = 1;
                        maxTmp = subMaxTmp;
                    }
                    subMaxTmp = max[i][k] - min[k + 1][j];
                    if(subMaxTmp > maxTmp)
                    {
                        subEatMax = 2;
                        maxTmp = subMaxTmp;
                    }
                    subMaxTmp = min[i][k] - min[k + 1][j];
                    if(subMaxTmp > maxTmp)
                    {
                        subEatMax = 3;
                        maxTmp = subMaxTmp;
                    }
                    subMaxTmp = min[i][k] - max[k + 1][j];
                    if(subMaxTmp > maxTmp)
                    {
                        subEatMax = 4;
                        maxTmp = subMaxTmp;
                    }
                    eatMax = subEatMax;
                }
                if (maxTmp > max[i][j])
                {
                    max[i][j] = maxTmp;
                    trackMap[i][j] = k;
                    eatWhoMax[i][j] = eatMax;
                }
                if (minTmp < min[i][j])
                {
                    min[i][j] = minTmp;
                    trackMapM[i][j] = k;
                    eatWhoMin[i][j] = eatMin;
                }
            }
        }
    }

    vector<string> resultFormula;
    for(int i=0;i<num.size();i++)
    {
        string temp = to_string(num.at(i));
        resultFormula.push_back(temp);
    }
    ParentString(resultFormula,0, size-1, 1);   //由於一開始取最大，第3引數丟入1代表取最大
    //print out the final result
    for(int i=num.size()-1;i>0;i--)
    {
        string temp = "";
        temp += symbol.at(i-1);
        resultFormula.insert(resultFormula.begin()+i, temp);
    }
    for(int i=0;i<resultFormula.size();i++)
    {
        cout << resultFormula.at(i);
    }
    cout << endl;
}

void ParentString(vector<string> &resultFormula, int i, int j, int needBigSmall)
{
    int k;
    if(needBigSmall == 1)
        k = trackMap[i][j];
    else if(needBigSmall == 2)
        k = trackMapM[i][j];
    if(i==j)
        return;
    if(k!=i)
    {
        resultFormula.at(i) = "("+resultFormula.at(i);  // before i
        resultFormula.at(k) = resultFormula.at(k) +")"; //after k
    }
    if(k+1!=j)
    {
        resultFormula.at(k+1) = "(" + resultFormula.at(k+1);  //before k+1
        resultFormula.at(j) = resultFormula.at(j) + ")";  //after j
    }
    int left, right, head;
    if(needBigSmall == 1)
        head = eatWhoMax[i][j];
    else if(needBigSmall == 2)
        head = eatWhoMin[i][j];
    switch(head)
    {
        case 1:
            left = 1;
            right = 1;
            break;
        case 2:
            left = 1;
            right = 2;
            break;
        case 3:
            left = 2;
            right = 2;
            break;
        case 4:
            left = 2;
            right = 1;
            break;
    }
    ParentString(resultFormula, i, k, left);
    ParentString(resultFormula, k+1, j, right);
}

int main()
{
    string input;
    cin >> input;
    MaxParent(input);
    return 0;
}
