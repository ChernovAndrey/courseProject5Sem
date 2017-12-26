//
// Created by andrey on 08.11.17.
//

#ifndef COURSEPROJECT5SEM_QUICKMATH_H
#define COURSEPROJECT5SEM_QUICKMATH_H

#include <cmath>
#include <cassert>

class QuickMath {
private:
    QuickMath() = default;

public:
    template<typename T>
    static T powNatural(T x, int k) // возведение x в степень k
    {
        if(k==1) return x;
        if(k==0) return 1;
        T res = 1.0;
        while (k) {
            if (k & 1)
                res *= x;
            x *= x;
            k >>= 1;
        }
        return res;
    }


    static float powInverse(float x, int q) { //equal pow(x,1/q)
        int i = *(int *) &x;
        float p = 1.0f/q;
        //i = static_cast<int>(0x3f7a3bea + (1.0f/q) * (i - 0x3f7a3bea));
        i = 1064975338 + p*(i - 1064975338);
        float y = *(float *) &i;
       // std::cout<<x<<" | "<<(pow(y,q)-x)<<std::endl;
        float p1 = 1.0f-p;
        float px= p*x;
        int q1 =q-1;
        y = p1 * y + px/powNatural(y, q1);
        return  p1* y + px/powNatural(y, q1);
    }
//
//
//    static float powInverse2(float x, int q) { //equal pow(x,1/q) // второй с корнем
//        int i = *(int *) &x;
//        float p = 1.0f/q;
//        //i = static_cast<int>(0x3f7a3bea + (1.0f/q) * (i - 0x3f7a3bea));
//        i = 1064975338 + p*(i - 1064975338);
//        float y = *(float *) &i;
//
//        //y= y *(q-2 + sqrtf(-1.0f+ 2.0f*(x*(1.0f-p)/powNatural(y,q) + p))) / (q - 1);
//        return y *(q-2 + sqrtf(-1.0f+ 2.0f*( x*(1.0f-p)/powNatural(y,q) + p ))) / (q - 1);
//    }

    static double powInverse2(double x, int q) { //equal pow(x,1/q) // второй с корнем
        double p = 1.0d/q;
        long i = *(long *) &x;
        i = (0x3FEF47724901B800 + p*(i - 0x3FEF47724901B800));
        double y = *(double *) &i;

        //y= y *(q-2 + sqrtf(-1.0f+ 2.0f*(x*(1.0f-p)/powNatural(y,q) + p))) / (q - 1);
        return y *(q-2 + sqrt(-1.0d+ 2.0d*( x*(1.0d-p)/powNatural(y,q) + p ))) / (q - 1);
    }



    static float powInverse2(float x, int q) { //equal pow(x,1/q)
        int i = *(int *) &x;
        i = static_cast<int>(0x3f7a3bea + (1.0f / q) * (i - 0x3f7a3bea));//не очень как то
        float y = *(float *) &i;

        //  y = (1-1.0/q)*y+(1.0/q)*x/powNatural(y,q-1);
        float a = powNatural(y, q - 2);
        float b = a * y;//powNatural(y,q-1)
        float c = b * y;//powNatural(y,q)
        float cx = c - x;
        float d = ((q - 1) * a * cx) / (b * b * q);
        return y - (cx) / (q * b) * (1 + 0.5f * d);
    }

    template<typename T>
    static T quickPow2(T x, int n, int m) {//equial pow(x,n/m)
        //   return powNatural(powInverse2(x,m),n);
        if(n<m) return powInverse2(powNatural(x,n), m);
        return powNatural(x,n/m)*powInverse2(powNatural(x,n%m), m);
    }

    template<typename T>
    static T quickPow(T x, int n, int m) {//equial pow(x,n/m)
        if(n<m) return powInverse(powNatural(x,n), m);
        return powNatural(x,n/m)*powInverse(powNatural(x,n%m), m);
    }


    template<typename T>
    static T quickPow2m(T x, int n, int m){
        T res=x;
        assert(m%2==0);
        while(m != 1){
            res=sqrt(res);
            m >>= 1;
       }
       return powNatural(res,n);
    }


};


#endif //COURSEPROJECT5SEM_QUICKMATH_H
