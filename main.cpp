#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <cmath>
#include <sstream>
#include <iomanip>
#include "QuickMath.hpp"

using namespace std;
int n = 10000;




vector<float> createRandomVector() {
    srand(static_cast<unsigned int>(time(0)));
    vector<float> v;
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    for (int i = 0; i < n; i++) v.push_back(static_cast <float> (rand()) / static_cast <float> (10000000));
    return v;
}



int main() {
    vector<float> v = createRandomVector();

    vector<float> vApprox(v.size());
    vector<float> vAccur(v.size());


  //  float p = 1.0/3;

    int n=5;
    int m =3;
    clock_t startQ = clock();
    for (int i = 0; i < v.size(); i++) {
        vApprox[i]=QuickMath::quickPow(v[i],n,m);
    }
    clock_t endQ = clock();
    double secondsQ = (double) (endQ - startQ) / CLOCKS_PER_SEC;


    clock_t startS = clock();
    for (int i = 0; i < v.size(); i++) {
     vAccur[i]= pow(v[i], (1.0*n)/m);
    }

    clock_t endS = clock();
    double secondsS = (double) (endS - startS) / CLOCKS_PER_SEC;
    cout << "quick:" << secondsQ << endl;
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

    float max =0;
    int nMax=0;
    for(int i=0;i<vAccur.size();i++){
        float diff=abs(vAccur[i]-vApprox[i]);
        if(max<diff) {
            nMax=i;
            max=diff;
        }
        cout<<diff<<" ";
    }
    cout << endl;
    cout<<"maxDiff="<<max<<endl;
    cout<<"killer elements:"<<vAccur[nMax]<<" "<<vApprox[nMax]<<endl;
}