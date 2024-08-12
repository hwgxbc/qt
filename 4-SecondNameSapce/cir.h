#ifndef CIR_H
#define CIR_H

namespace cir {
    double PI = 3.141592653;
    //获取圆形周长的函数
    double getLenthOfCircle(double radius){
        return 2*PI*radius;
    }
    //获取圆形面积的函数
    double getAifCircle(double radius){
        return PI*radius*radius;
    }
}

#endif // CIR_H
