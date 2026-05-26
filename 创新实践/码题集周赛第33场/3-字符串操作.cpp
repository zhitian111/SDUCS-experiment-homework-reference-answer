#include <iostream>
#include <string>
using namespace std;
 

int main(){
    int k;
    cin >>k;
    for (int loop = 0; loop < k ; loop ++){
        string s1,s2;
        cin >> s1  >> s2;

        bool swap_flag =false;

        for (int i = 0;i< s1.size();i++){
            if (swap_flag){
                break;
            }
            int index=-1;
            char tem = s1[i];
            for (int j = 0;j<s2.size();j++)
            {
                if (s2[j] < tem){
                    index=j;
                    tem = s2[j];
                }
            }
            if (index != -1){
                s2[index] = s1[i];
                s1[i] = tem;
                swap_flag = true;
            }
        }
        cout << s1 << "\n" << s2 << "\n";    
    }
    return 0;
}