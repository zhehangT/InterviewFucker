/**
* Author: T_Zhehang 
* Date: 18-3-8
*/

//3.3 请实现一种数据结构SetOfStacks，由多个栈组成，其中每个栈的大小为size，当前一个栈填满时，新建一个栈。
//该数据结构应支持与普通栈相同的push和pop操作。
vector<vector<int> > setOfStacks(vector<vector<int> > ope, int size) {
    // write code here
    vector<vector<int> > ss;
    vector<int> tmp;

    for(int i = 0; i < ope.size(); i++){

        if(ope[i][0] == 1){
            if(tmp.size() < size){
                tmp.emplace_back(ope[i][1]);
            }else{
                ss.emplace_back(tmp);
                tmp.clear();
                tmp.emplace_back(ope[i][1]);
            }
        }else if(ope[i][0] == 2){
            if(tmp.size() > 0){
                tmp.pop_back();
            }else{
                tmp = ss[ss.size()-1];
                ss.pop_back();
                tmp.pop_back();
            }
        }
    }
    if(tmp.size() == 0)
        ss.pop_back();
    else
        ss.emplace_back(tmp);
    return ss;
}

//3.4
//按升序对栈进行排序（即最大元素位于栈顶），要求最多只能使用一个额外的栈存放临时数据，但不得将元素复制到别的数据结构中。
void pushVector(vector<int> &v, int value){
    auto iter = v.begin();
    v.insert(iter, value);
}

void popVector(vector<int> &v){
    auto iter = v.begin();
    v.erase(iter);
}

int topVector(vector<int> &v){
    return v[0];
}

vector<int> twoStacksSort(vector<int> numbers) {
    // write code here
    vector<int> results;
    int tmp;

    while(numbers.size() > 0){
        tmp = topVector(numbers);
        popVector(numbers);
        while(results.size() != 0 && topVector(results) > tmp){
            pushVector(numbers, topVector(results));
            popVector(results);
        }
        pushVector(results, tmp);
    }
    return results;
}

