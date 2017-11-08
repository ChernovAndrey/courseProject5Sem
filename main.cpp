#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <cmath>
#include <sstream>
#include <iomanip>

using namespace std;
int n = 10000;


template<typename T>
std::string int_to_hex(T i) {
    stringstream stream;
    stream << "0x"
           << setfill('0') << std::setw(sizeof(T) * 2)
           << hex << i;
    return stream.str();
}

void standard(vector<float> v, double p) {
    clock_t start = clock();
    for (int i = 0; i < n; i++) {
        double x = pow(v[i], p);
        cout << x << " ";
    }
    cout << endl;
    clock_t end = clock();
    double seconds = (double) (end - start) / CLOCKS_PER_SEC;
    cout << "duration=" << seconds << endl;

}


float quickAppr(float x, float p,bool flagApprox=true) {
    // float xhalf = 0.5f * v[j];

    int i = *(int *) &x;
    i = static_cast<int>(0x3f7a3bea + p * (i - 0x3f7a3bea));
    float y = *(float *) &i;
  if(flagApprox) {
       float q = 1.0/p;
       return (1 - p) * y + p*(x/quickAppr(y,q-1,false));
    }
    return y;
}



float powNatural(float x, int k) // возведение t в степень k
{
    float res = 1.0;
    while (k)
    {
        if (k & 1)
            res *= x;
        x *= x;
        k >>= 1;
    }
    return res;
}

float powInverse(float x, int q) { //equal pow(x,1/q)
    int i = *(int *) &x;
    i = static_cast<int>(0x3f7a3bea + (1.0/q) * (i - 0x3f7a3bea));
    float y = *(float *) &i;
    // return y;

    //for p =1/3
    y = (1-1.0/q)*y+(1.0/q)*x/powNatural(y,q-1);
    return (1-1.0/q)*y+(1.0/q)*x/powNatural(y,q-1);
}


float quickOneThird(float x, double p) {
    // float xhalf = 0.5f * v[j];

    int i = *(int *) &x;
    i = static_cast<int>(0x3f7a3bea + p * (i - 0x3f7a3bea));
    float y = *(float *) &i;
   // return y;

    //for p =1/3
    return 0.6666667*y+0.3333333*x/(y*y);
}

float FastSqr(float x) {
    //  float xhalf = 0.5f * x;
    int i = *(int *) &x;  // представим биты float в виде целого числа
    i = -0x3f7a4e20 + (i << 1);  // какого черта здесь происходит ?
    x = *(float *) &i;
    //   x = x*(1.5f-(xhalf*x*x));
    return x;
}


/*from wiki*/
float Q_rsqrt(float number) {
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y = number;
    i = *(long *) &y;                       // evil floating point bit level hacking
    i = 0x5f3759df - (i >> 1);               // what the fuck?
    y = *(float *) &i;
    y = y * (threehalfs - (x2 * y * y));   // 1st iteration
//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

    return y;
}


vector<float> createRandomVector() {
    srand(static_cast<unsigned int>(time(0)));
    vector<float> v;
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    for (int i = 0; i < n; i++) v.push_back(static_cast <float> (rand()) / static_cast <float> (10000000));
    return v;
}

float quickPow(float x, int n, int m){//equial pow(x,n/m)
   // return powNatural(powInverse(x,m),n);
    return powInverse(powNatural(x,n),m);
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
        vApprox[i]=quickPow(v[i],n,m);
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