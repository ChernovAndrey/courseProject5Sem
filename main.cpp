#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <cmath>
#include <sstream>
#include <iomanip>
#include "QuickMath.hpp"

using namespace std;
using number = float;
int n = 10000;




vector<number> createRandomVector() {
    srand(static_cast<unsigned int>(time(0)));
    vector<number> v;
    number r = static_cast <number> (rand()) / static_cast <number> (RAND_MAX);
    for (int i = 0; i < n; i++) v.push_back(static_cast <number> (rand()) / static_cast <number> (10000000));
    return v;
}



void printDiff(const vector<number> &v1, const vector<number> &v2, int &nMax,number &max){
    for(int i=0;i<v1.size();i++){
        number diff=abs(v1[i]-v2[i]);
        if(max<diff) {
            nMax=i;
            max=diff;
        }
        cout<<diff<<" ";
    }

}

//for number K=3FEF47724901B800
int main() {
    vector<number> v = createRandomVector();

    vector<number> vApprox(v.size());
    vector<number> vApprox2(v.size());
    vector<number> vAccur(v.size());

    //number p = 1.0/3;

    int n=2;
    int m =3;
    clock_t startQ = clock();
    for (int i = 0; i < v.size(); i++) {
        vApprox[i]=QuickMath::quickPow(v[i],n,m);
    //    vApprox[i]=QuickMath::quickAppr(v[i],(1.0*n)/m,true);
    }
    clock_t endQ = clock();
    number secondsQ = (number) (endQ - startQ) / CLOCKS_PER_SEC;


    clock_t startQ2 = clock();
    for (int i = 0; i < v.size(); i++) {
        vApprox2[i]=QuickMath::quickPow2(v[i],n,m);
        //    vApprox[i]=QuickMath::quickAppr(v[i],(1.0*n)/m,true);
    }
    clock_t endQ2 = clock();
    number secondsQ2 = (number) (endQ2 - startQ2) / CLOCKS_PER_SEC;



    clock_t startS = clock();
    for (int i = 0; i < v.size(); i++) {
     vAccur[i]= pow(v[i], (1.0*n)/m);
    }

    clock_t endS = clock();
    number secondsS = (number) (endS - startS) / CLOCKS_PER_SEC;
    cout << "quick:" << secondsQ << endl;
    cout<<"quick2:"<<secondsQ2<<endl;
    cout << "standard:" << secondsS << endl;

    cout<<endl<<endl;

    for(int i=0;i<vAccur.size();i++){
        cout<<vAccur[i]<<" ";
    }
    cout <<endl;


    for(int i=0;i<vAccur.size();i++){
        cout<<vApprox[i]<<" ";
    }
    cout << endl;

    for(int i=0;i<vApprox2.size();i++){
        cout<<vApprox2[i]<<" ";
    }
    cout << endl;

    number max =0;
    number max2 =0;
    int nMax=0;
    int nMax2=0;

    cout<<"1:"<<endl;
    printDiff(vAccur,vApprox,nMax,max);
    cout<<endl;
    cout<<"2:"<<endl;
    printDiff(vAccur,vApprox2,nMax2,max2);
    cout << endl;
    cout<<"maxDiff="<<max<<endl;
    cout<<"maxDiff2="<<max2<<endl;
    cout<<"killer elements:"<<vAccur[nMax]<<" "<<vApprox[nMax]<<endl;
    cout<<"killer elements2:"<<vAccur[nMax2]<<" "<<vApprox[nMax2]<<endl;
    return 0;
}