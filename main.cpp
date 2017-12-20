#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <iomanip>
#include "QuickMath.hpp"
#include "Grid/Grid.h"
#include "Grid/UniformGrid.h"
#include "LeastSquare.h"

using namespace std;
using number = double;
int N = 100000000;
const int n =1;
const int m=4;
const number p =(1.0/m)*n;



vector<number> createRandomVector() {
    srand(static_cast<unsigned int>(time(0)));
    vector<number> v;
    number r = static_cast <number> (rand()) / static_cast <number> (RAND_MAX);
    for (int i = 0; i < N; i++) v.push_back(static_cast <number> (rand()) / static_cast <number> (10000000));
    return v;
}



void evaluateDiff(const vector<number> &v1, const vector<number> &v2, int &nMax,number &max){
    for(int i=0;i<v1.size();i++){
        number diff=abs(v1[i]-v2[i]);
        if(max<diff) {
            nMax=i;
            max=diff;
        }
     //   cout<<diff<<" ";
    }

}


pair<vector<number>,number> evaluateQuick(const vector<number> &v,int n, int m, number (*f)(number,int, int)){
    vector<number> res(v.size());
    clock_t startQ = clock();
    for (int i = 0; i < v.size(); i++) {
        res[i]=f(v[i],n,m);
        //    vApprox[i]=QuickMath::quickAppr(v[i],(1.0*n)/m,true);
    }
    clock_t endQ = clock();
    number secondsQ = (number) (endQ - startQ) / CLOCKS_PER_SEC;
    return make_pair(res,secondsQ);
}

number powExpLog(number x, int n, int m){
    return exp(p*log(x));
}

//for number K=3FEF47724901B800
int main() {

    vector<number> v = createRandomVector();

    vector<number> vApprox(v.size());
    vector<number> vApprox2(v.size());
    vector<number> vApprox2m(v.size());
    vector<number> vAccur(v.size());

    //number p = 1.0/3;


//    clock_t startQ = clock();
//    for (int i = 0; i < v.size(); i++) {
//        vApprox[i]=QuickMath::quickPow(v[i],n,m);
//    //    vApprox[i]=QuickMath::quickAppr(v[i],(1.0*n)/m,true);
//    }
//    clock_t endQ = clock();
//    number secondsQ = (number) (endQ - startQ) / CLOCKS_PER_SEC;
    number secondsQ;
    tie(vApprox,secondsQ)= evaluateQuick(v,n,m,QuickMath::quickPow);  //холостой прогон
    tie(vApprox,secondsQ)= evaluateQuick(v,n,m,QuickMath::quickPow);


//    clock_t startQ2 = clock();
//    for (int i = 0; i < v.size(); i++) {
//        vApprox2[i]=QuickMath::quickPow2(v[i],n,m);
//        //    vApprox[i]=QuickMath::quickAppr(v[i],(1.0*n)/m,true);
//    }
//    clock_t endQ2 = clock();
//    number secondsQ2 = (number) (endQ2 - startQ2) / CLOCKS_PER_SEC;
    number secondsQ2;
    tie(vApprox2,secondsQ2)= evaluateQuick(v,n,m,QuickMath::quickPow2);

    number secondsQ2m;
    if(m%2==0) tie(vApprox2m,secondsQ2m)= evaluateQuick(v,n,m,QuickMath::quickPow2m);



    clock_t startS = clock();
    for (int i = 0; i < v.size(); i++) {
    vAccur[i]= pow(v[i],(1.0f*n/m));
    }
    clock_t endS = clock();
    number secondsS = (number) (endS - startS) / CLOCKS_PER_SEC;

    cout << "quick:" << secondsQ << endl;
    cout<<"quick2:"<<secondsQ2<<endl;
    if (m%2==0) cout<<"quick2m:"<<secondsQ2m<<endl;
    cout << "standard:" << secondsS << endl;

    cout<<endl<<endl;

   /* for(int i=0;i<vAccur.size();i++){
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
    cout << endl;*/

    number max =0;
    number max2 =0;
    number max2m =0;
    int nMax=0;
    int nMax2=0;
    int nMax2m=0;

    evaluateDiff(vAccur,vApprox,nMax,max);
    cout<<endl;

    evaluateDiff(vAccur,vApprox2,nMax2,max2);
    cout << endl;

    if(m%2==0) {
        evaluateDiff(vAccur, vApprox2m, nMax2m, max2m);
        cout << endl;
    }

    cout<<"maxDiff="<<max<<endl;
    cout<<"relative error="<<max/vAccur[nMax]<<endl;
    cout<<"killer elements:"<<vAccur[nMax]<<" "<<vApprox[nMax]<<endl;
    cout<<endl;

    cout<<"maxDiff2="<<max2<<endl;
    cout<<"relative error 2="<<max2/vAccur[nMax2]<<endl;
    cout<<"killer elements2:"<<vAccur[nMax2]<<" "<<vApprox2[nMax2]<<endl;
    cout<<endl;

    if(m%2==0) {
        cout<<"maxDiff2m="<<max2m<<endl;
        cout<<"relative error 2m="<<max2m/vAccur[nMax2m]<<endl;
        cout<<"killer elements2m:"<<vAccur[nMax2m]<<" "<<vApprox2m[nMax2m]<<endl;
        cout<<endl;
    }

    return 0;
}