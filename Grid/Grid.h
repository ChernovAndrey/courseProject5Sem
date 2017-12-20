//
// Created by andrey on 20.10.17.
//

#ifndef LAB3_GRID_H
#define LAB3_GRID_H


#include <tuple>
#include "iostream"
#include <vector>
#include "cmath"
using namespace std;
class Grid {
protected:
    double a;
    double b;
    int n;

    vector<double> xValues{};
    vector<double> fxValues{};

    double getValueFunc(double x){
        return log2(1+x);
    }

    virtual double getXi(double a, double b, int n,double h , int i)=0;
public:
    Grid(double a, double b, int n):a(a),b(b),n(n){
        xValues=  vector<double>(static_cast<unsigned long>(n));
        fxValues=  vector<double>(static_cast<unsigned long>(n));
    }

    pair<vector<double>, vector<double>> get(){
        double h = (b-a)/(n-1);
        xValues[0]=a;
        fxValues[0]=getValueFunc(a);

        for(int i=1;i<n-1;i++){
            xValues[i]= getXi(a,b,n,h,i);
            fxValues[i]=this->getValueFunc(xValues[i]);
        }

        xValues[n-1]=b;
        fxValues[n-1]=getValueFunc(b);

        return  make_pair(xValues,fxValues);
    }
    void print(){
        cout<<"x:"<<endl;
        for (double i : xValues) {
            cout<< i <<'\t';
        }

        cout<<endl;

        cout<<"f(x):"<<endl;
        for (double i : fxValues) {
            cout<< i <<'\t';
        }

        cout<<endl;
    }

};


#endif //LAB3_GRID_H
