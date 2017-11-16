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
            return (1 - p) * y + p*(x/quickAppr(y, static_cast<float>(q - 1.0), false));
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

    static double powNatural(double x, int k) // возведение x в степень k
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

        y = (1-1.0/q)*y+(1.0/q)*x/powNatural(y,q-1);
        return (1-1.0/q)*y+(1.0/q)*x/powNatural(y,q-1);
    }

    static float powInverse2(float x, int q) { //equal pow(x,1/q)
        int i = *(int *) &x;
        i = static_cast<int>(0x3f7a3bea + (1.0/q) * (i - 0x3f7a3bea));//не очень как то
        float y = *(float *) &i;

      //  y = (1-1.0/q)*y+(1.0/q)*x/powNatural(y,q-1);
        float a = powNatural(y,q-2);
        float b = a*y;//powNatural(y,q-1)
        float c = b*y;//powNatural(y,q)
        float cx= c - x;
        float d = ((q-1)*a*cx)/(b*b*q);
        return y-(cx)/(q*b)*(1+0.5*d);
    }


    static double powInverse(double x, int q) { //equal pow(x,1/q)
        long i = *(long *) &x;
        i = static_cast<long>(0x3FEF47724901B800 + (1.0 / q) * (i - 0x3FEF47724901B800));
        double y = *(double*) &i;

        y = (1-1.0/q)*y+(1.0/q)*x/powNatural(y,q-1);
        return (1-1.0/q)*y+(1.0/q)*x/powNatural(y,q-1);
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
  /*      clock_t start = clock();
        float a = powNatural(x,n);
        clock_t end = clock();
        float seconds = (float) (end - start) / CLOCKS_PER_SEC;

      clock_t start2 = clock();
        float res = powNatural(x,n);
        clock_t end2 = clock();
        float seconds2 = (float) (end2 - start2) / CLOCKS_PER_SEC;
         std::cout<<"timeInv:"<<seconds<<std::endl;
         std::cout<<"timeNat:"<<seconds2<<std::endl;
        return res;*/

        return powInverse(powNatural(x,n),m);
    }

    static float quickPow2(float x, int n, int m){//equial pow(x,n/m)
      //   return powNatural(powInverse2(x,m),n);
        return powInverse2(powNatural(x,n),m);
    }


    static double quickPow(double x, int n, int m){//equial pow(x,n/m)
        // return powNatural(powInverse(x,m),n);
        return powInverse(powNatural(x,n),m);
    }

};


#endif //COURSEPROJECT5SEM_QUICKMATH_H
