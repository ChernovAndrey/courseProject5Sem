//
// Created by andrey on 03.12.17.
//

#ifndef COURSEPROJECT5SEM_LEASTSQUARE_H
#define COURSEPROJECT5SEM_LEASTSQUARE_H

#include <iostream>
#include <vector>
using namespace std;

class LeastSquare {
private:
    LeastSquare() = default;
public:
    static pair<double,double> approximate(pair<vector<double>,vector<double>> values){//return a and b
        vector<double> x=values.first;
        vector<double> y=values.second;
        unsigned long n = x.size();
        double sumXY = 0;
        double sumX = 0;
        double sumY = 0;
        double sumXX = 0;
        for(int i=0;i<n;i++){
            sumXY+=x[i]*y[i];
            sumX+=x[i];
            sumY+=y[i];
            sumXX+=x[i]*x[i];
        }
       // double a = (n*sumXY-sumX*sumY)/(n*sumXX-sumX*sumX);
        double a = 1.0;
        double b = (sumY-a*sumX)/n;
        cout<<"a="<<a<<endl;
        cout<<"b="<<b<<endl;
        return make_pair(a,b);
    }
};


#endif //COURSEPROJECT5SEM_LEASTSQUARE_H

