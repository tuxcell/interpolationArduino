// interpolation - An interpolation library for Arduino.
// test code
// Author: Jose Gama 2015

#include <Arduino.h>
#include "interpolation.h"

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    double y[14]={150, 140, 130, 120, 110, 100,  90,  80,  70,  60,  50,  40,  30,  20},
    x[14]={0.37, 0.40, 0.43, 0.46, 0.50, 0.55, 0.61, 0.68, 0.78, 0.91, 1.09, 1.35, 1.79, 2.66};
    double XM[18];
    double Z[15];
    interpolation test;
    test.valueX(x);
    test.valueY(y);
    test.valueXM(XM); // For Akima interpolation
    test.valueZ(Z); // For Akima interpolation
    test.valuelenXY(14);
    Serial.println("Interpolation");
    Serial.println("Value Linear Cosine Cubic Lagrange Quadratic Akima");
    for (int c=0;c<=7;c++){
        test.valueI(c * 0.5);
        Serial.print(c * 0.5);Serial.print(" : ");
        Serial.print(test.LinearInterpolate());Serial.print("   ");
        Serial.print(test.CosineInterpolate());Serial.print("   ");
        Serial.print(test.CubicInterpolate());Serial.print("   ");
        Serial.print(test.LagrangeInterpolate());Serial.print("   ");
        Serial.print(test.QuadraticInterpolate());Serial.print("   ");
        Serial.println(test.AkimaInterpolate());
    }
    
    delay(10000);
}
