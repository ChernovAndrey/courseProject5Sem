//
// Created by andrey on 08.11.17.
//

#ifndef COURSEPROJECT5SEM_QUICKMATH_H
#define COURSEPROJECT5SEM_QUICKMATH_H


class  QuickMath {
private:
    QuickMath() = default;

public:


    static float quickAppr(float x, float p,bool flagApprox=true) {
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



    static float powNatural(float x, int k) // возведение x в степень k
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

    static float powInverse(float x, int q) { //equal pow(x,1/q)
        int i = *(int *) &x;
        i = static_cast<int>(0x3f7a3bea + (1.0/q) * (i - 0x3f7a3bea));
        float y = *(float *) &i;
        // return y;

        //for p =1/3
        y = (1-1.0/q)*y+(1.0/q)*x/powNatural(y,q-1);
        return (1-1.0/q)*y+(1.0/q)*x/powNatural(y,q-1);
    }


    static float quickOneThird(float x, double p) {
        // float xhalf = 0.5f * v[j];

        int i = *(int *) &x;
        i = static_cast<int>(0x3f7a3bea + p * (i - 0x3f7a3bea));
        float y = *(float *) &i;
        // return y;

        //for p =1/3
        return 0.6666667*y+0.3333333*x/(y*y);
    }


/*from wikipedia Quake 3*/
    static float Q_rsqrt(float number) {
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

    static float quickPow(float x, int n, int m){//equial pow(x,n/m)
        // return powNatural(powInverse(x,m),n);
        return powInverse(powNatural(x,n),m);
    }

};


#endif //COURSEPROJECT5SEM_QUICKMATH_H
