/**
* Author: T_Zhehang
* Date: 18-3-15
*/


//5.1 有两个32位整数n和m，将m的二进制数位插入到n的二进制的第j到第i位
//测试用例：1024，19，2，6
//返回：1100
int binInsert(int n, int m, int j, int i) {
    // write code here
    int allone = ~0;
    int left = allone << i;
    int right = ~(allone << (j-1));
    n = n & (left | right);
    m = m << j;
    return m | n;
}

//5. 2有一个介于0和1之间的实数，类型为double，返回它的二进制表示。如果该数字无法精确地用32位以内的二进制表示，返回“Error”。
string printBin(double num) {
    // write code here
    string result = "0.";
    double base_2 = 0.5;
    double base_10 = 0.1;
    for(int i = 0; i < 32; i++){
        if( num >= base_2 ){
            num = num - base_2;
            result.push_back('1');
        }else{
            result.push_back('0');
        }
        base_2 /= 2;
        base_10 /= 10;
        if(num == 0)
            return result;
    }
    return "Error";

}

//5.3 有一个正整数，找出其二进制表示中1的个数相同、且大小最接近的那两个数。
int getOneNum(int x){

    int n = 0;
    while(x != 0){
        x = x & (x-1);
        n++;
    }
    return n;
}

vector<int> getCloseNumber(int x) {
    // write code here
    int n = getOneNum(x);
    int larger = x + 1;
    for( ; getOneNum(larger) != n; larger++);
    int smaller = x - 1;
    for( ; getOneNum(smaller) != n; smaller--);

    return vector<int>{smaller, larger};
}

//5.4 确定需要改变几个位，才能将整数A转变成整数B。
int calcCost(int A, int B) {
    // write code here
    int c = A ^ B;
    int n = 0;
    while(c != 0){
        c = c & (c-1);
        n++;
    }
    return n;
}

//5.6 交换一个数的二进制的奇数位和偶数位
int exchangeOddEven(int x) {
    // write code here
    int a = 0xaaaaaaaa;
    int b = 0x55555555;
    return ((x & a) >> 1) | ((x & b) << 1);
}

