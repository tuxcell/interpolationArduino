/*
* interpolation.h
*
* interpolation - An interpolation library for Arduino.
* Author: Jose Gama 2015

*
* This library is free software; you can redistribute it
* and/or modify it under the terms of the GNU Lesser
* General Public License as published by the Free Software
* Foundation; either version 3 of the License, or (at
* your option) any later version.
*
* This library is distributed in the hope that it will
* be useful, but WITHOUT ANY WARRANTY; without even the
* implied warranty of MERCHANTABILITY or FITNESS FOR A
* PARTICULAR PURPOSE.  See the GNU Lesser General Public
* License for more details.
*
* You should have received a copy of the GNU Lesser
* General Public License along with this library; if not,
* write to the Free Software Foundation, Inc.,
* 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*
*/
#include "interpolation.h"

interpolation::interpolation(void) {
    _valInterp = 0;
    _lenXY = 0;
}
interpolation::interpolation( double x[], double y[], int lenXY){
    _x = x;_y = y;_lenXY = lenXY;
    _valInterp = 0;
}
interpolation::interpolation( double x[], double y[], int lenXY, double  valInterp){
    _x = x;_y = y;_lenXY = lenXY;
    _valInterp = valInterp;
}

void interpolation::valueI( double valInterp ) {
    _valInterp = valInterp;
}
void interpolation::valuelenXY( int lenXY ) {
    _lenXY = lenXY;
}
void interpolation::valueX( double x[]) {
    _x = x;
}
void interpolation::valueY( double y[]) {
    _y = y;
}
void interpolation::valueXM( double XM[]) {
    _XM = XM;
}
void interpolation::valueZ( double Z[]) {
    _Z = Z;
}
double interpolation::LinearInterpolate() {return(LinearInterp( _x, _y, _lenXY, _valInterp));}
double interpolation::CosineInterpolate() {return(CosineInterp( _x, _y, _lenXY, _valInterp));}
double interpolation::CubicInterpolate() {return(CubicInterp( _x, _y, _lenXY, _valInterp));}
double interpolation::LagrangeInterpolate() {return(LagrangeInterp( _x, _y, _lenXY, _valInterp));}
double interpolation::QuadraticInterpolate() {return(QuadraticInterp( _x, _y, _lenXY, _valInterp));}
double interpolation::AkimaInterpolate() {return(AkimaInterp( _x, _y, _XM, _Z, _lenXY, _valInterp));}


double interpolation::LinearInterp( double* x, double* y, int n, double p )
{
    //http://paulbourke.net/miscellaneous/interpolation/
    int i;
    double mu;
    for( i = 0; i < n-1; i++ )
    {
        if (( x[i] <= p && x[i+1] >= p )||( x[i] >= p && x[i+1] <= p ))
        {
            mu=(p - x[i])/(x[i] - x[i+1]);
            if (mu<0) mu=-mu;
            return(y[i]*(1-mu)+y[i+1]*mu);
        }
    }
    return 0; // Not in Range
}

double interpolation::CosineInterp (double* x, double* y, int n, double p )
{
    int i;
    double mu, mu2;
    for( i = 0; i < n-1; i++ )
    {
        if (( x[i] <= p && x[i+1] >= p )||( x[i] >= p && x[i+1] <= p ))
        {
            mu=(p - x[i])/(x[i] - x[i+1]);
            if (mu<0) mu=-mu;
            mu2 = (1.0-cos(3.1415926535897*mu))/2.0;
            return(y[i]*(1.0-mu2)+y[i+1]*mu2);
        }
    }
    return 0; // Not in Range
}

double interpolation::CubicInterp(double* x, double* y, int n, double p )
{
    int i;
    double a0,a1,a2,a3,mu, mu2;
    for( i = 0; i < n-1; i++ )
    {
        if (( x[i] <= p && x[i+1] >= p )||( x[i] >= p && x[i+1] <= p ))
        {
            mu=(p - x[i])/(x[i] - x[i+1]);
            if (mu<0) mu=-mu;
            mu2 = mu*mu;
            a0 = y[i+2] - y[i+1] - y[i-1] + y[i];
            a1 = y[i-1] - y[i] - a0;
            a2 = y[i+1] - y[i-1];
            a3 = y[i];
            return(a0*mu*mu2+a1*mu2+a2*mu+a3);
        }
    }
    return 0; // Not in Range
}

double interpolation::LagrangeInterp( double* x, double* y, int n, double p )
{
    //http://www.dailyfreecode.com/code/lagranges-interpolation-method-finding-2376.aspx
    int i, j, k;
    double t, r=0;
    for(i=0;i<n;i++)
    {
        t = 1;
        k = i;
        for(j=0;j<n;j++)
        {
            if(k==j)
            {
                continue;
            }
            else
            {
                t = t * ((p-x[j])/(x[k]-x[j]));
            }
        }
        r+=y[i]*t;
    }
    return r; // Not in Range
}

double interpolation::QuadraticInterp(double* x, double* y, int n, double p )
{
    //view-source:http://www.johndcook.com/quadratic_interpolator.html
    int i;
    double xi2, k;
    for( i = 0; i < n-1; i++ )
    {
        if (( x[i] <= p && x[i+1] >= p )||( x[i] >= p && x[i+1] <= p ))
        {
            if (i<(n-3)) xi2=x[i+2]; else xi2=0;
                k  = y[i]*(p - x[i+1])*(p - xi2)/((x[i] - x[i+1])*(x[i] - xi2));
            k += y[i+1]*(p - x[i])*(p - xi2)/((x[i+1] - x[i])*(x[i+1] - xi2));
            k += y[i+2]*(p - x[i])*(p - x[i+1])/((xi2 - x[i])*(xi2 - x[i+1]));
            return(k);
        }
    }
    return 0; // Not in Range
}

double interpolation::AkimaInterp( double* x, double* y,  double* XM, double* Z, int n, double p )  {
    //http://jean-pierre.moreau.pagesperso-orange.fr/Cplus/akima_cpp.txt
    int i;
    double a,b,r;
    //special case p=0
    if (p==0.0) {
        return(0);
    }
    //Check to see if interpolation point is correct
    if (p<x[1] || p>=x[n-3]) {
        return(-330);
    }
    x[0]=2.0*x[1]-x[2];
    //Calculate Akima coefficients, a and b
    for (i=1; i<n; i++)
        //Shift i to i+2
    XM[i+2]=(y[i+1]-y[i])/(x[i+1]-x[i]);
    XM[n+2]=2.0*XM[n+1]-XM[n];
    XM[n+3]=2.0*XM[n+2]-XM[n+1];
    XM[2]=2.0*XM[3]-XM[4];
    XM[1]=2.0*XM[2]-XM[3];
    for (i=1; i<n+1; i++)  {
        a=fabs(XM[i+3]-XM[i+2]);
        b=fabs(XM[i+1]-XM[i]);
        if (a+b==0) Z[i]=(a*XM[i+1]+b*XM[i+2])/(a+b); else Z[i]=(XM[i+2]+XM[i+1])/2.0;
        }
    //Find relevant table interval
    i=0;
    while (p>x[i]) i++;
    i--;
    
    //Begin interpolation
    b=x[i+1]-x[i];
    a=p-x[i];
    r=y[i]+Z[i]*a+(3.0*XM[i+2]-2.0*Z[i]-Z[i+1])*a*a/b;
    r=r+(Z[i]+Z[i+1]-2.0*XM[i+2])*a*a*a/(b*b);
    return(r);
}
