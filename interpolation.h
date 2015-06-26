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
#ifndef interpolation_h
#define interpolation_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include <Arduino.h>
#else
    #include <WProgram.h>
#endif

class interpolation
{
    public:
    // constructor
    interpolation( void );
    interpolation( double x[], double y[], int lenXY);
    interpolation( double x[], double y[], int lenXY, double  valInterp);
    
    void valueI( double valInterp );
    void valuelenXY( int lenXY );
    void valueX( double x[]);
    void valueY( double y[]);
    void valueXM( double XM[]);
    void valueZ( double Z[]);
    double LinearInterpolate();
    double CosineInterpolate();
    double CubicInterpolate();
    double LagrangeInterpolate();
    double QuadraticInterpolate();
    double AkimaInterpolate();
    
    private:
    double* _x;
    double* _y;
    double* _XM;
    double* _Z;
    int _lenXY;
    double _valInterp;
    
    double LinearInterp( double x[], double y[], int n, double p );
    double CosineInterp( double x[], double y[], int n, double p );
    double CubicInterp( double x[], double y[], int n, double p );
    double LagrangeInterp( double x[], double y[], int n, double p );
    double QuadraticInterp( double x[], double y[], int n, double p );
    double AkimaInterp( double x[], double y[],  double XM[], double Z[], int n, double p );
    
};

#endif