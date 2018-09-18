#include<stdio.h>
#include<math.h>

double t2_rr(double p)
{
     double l1=15,l2=15,t2;
    t2=2*atan(sqrt(((l1+l2)*(l1+l2)-p*p)/(p*p-(l1-l2)*(l1-l2))));
    t2=t2*180/3.14;
    t2=(float)10.5556*(t2)+600;
    return t2;

}
double t1_rr(double p,double t2)
{
    double l1=15,l2=15;
    double t1;
    t1=atan(l2*sin(t2)/(l1+l2*cos(t2)));
    t1=t1*180/3.14;
    t1=(float)10.5556*(t1)+600;
    return t1;
}
