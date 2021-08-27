#include <stdio.h>
#include <math.h>
#include <cmath>
#include <assert.h>


const double EPSILON = 0.001; ///< Shows double error. Determinated by math.

///Set of states of solveSquare
enum solveStatus
{
    NO_ROOTS = 0,      ///<Shows that there are no roots
    ONE_ROOT = 1,      ///<Shows that there are 1 root
    TWO_ROOTS = 2,     ///<Shows that there are 2 roots
    INFINITE_ROOTS = 3 ///<Shows that there are infinite roots
};

/**
    For tests solveSquare

    @param [in] testNum - shows test's number
    @param [in] a - quadratic coefficient
    @param [in] b - quadratic coefficient
    @param [in] c - quadratic coefficient
    @param [in] x1ref - expected the 1st root
    @param [in] x2ref - expected the 2nd root
    @param [in] nRootsref - expected number of roots

    @return Test status: succes/failure

*/

int UnitTest (int testNum, double a, double b, double c, double x1ref, double x2ref, int nRootsref);

/**
    Solve a quadratic equation ax2 + bx + c = 0

    @param [in]   a - quadratic coefficient
    @param [in]   b - quadratic coefficient
    @param [in]   c - quadratic coefficient
    @param [out] x1 - the 1st root
    @param [out] x2 - the 2nd root

    @return Number of roots: 0 / 1 / 2 / infinite

*/

int solveSquare (double a, double b, double c,
                 double* x1, double* x2);

/**
    Solve a linear equation kx + b = 0

    @param [in] k - linear coefficient
    @param [in] b - linear coefficient

    @return Linear root

*/

double solveLinear (double k, double b);

/**
    Checks equality of doubles

    @param [in] value    - the 1st number
    @param [in] valueref - the 2nd number

    @return Result: true/false

    @warning If both numbers are NAN then return TRUE!

*/

int isEqual (double value, double valueref);

/**
    Start UnitTest

    @return Number of the succesful tests

*/

int RunUnitTest ();

/**
    Checks if a number is NAN

    @param [in] value - number

    @return Result: true/false

*/

int isNAN (double value);

/**
    Checks if  adouble is NULL

    @param [in] value - number

    @return Result: true/false

*/

int IsZero (double value);

int main (void)
{
    printf ("Enter a, b, c in ax2 + bx + c = 0\n");

    float a = NAN, b = NAN, c = NAN;

    if (scanf ("%g %g %g", &a, &b, &c) != 3)
      {
      printf ("Bad value\n");
      return 0;
      }

    double x1 = NAN, x2 = NAN;

    int nRoots = solveSquare (a, b, c, &x1, &x2);

    switch (nRoots)
      {
      case NO_ROOTS :
        printf ("No roots\n");
        break;

      case ONE_ROOT :
        printf ("x = %g\n", x1);
        break;

      case TWO_ROOTS :
        printf ("x1 = %g, x2 = %g\n", x1, x2);
        break;

      case INFINITE_ROOTS :
        printf ("Any numbers\n");
        break;

      default:
        printf ("main (void) : ERROR : nRoots = %d\n", nRoots);
        return 1;
      }

    int nRight = RunUnitTest ();
    printf ("%d", nRight);

    return 0;
}


int solveSquare (double a, double b, double c,
                 double* x1, double* x2)
{
    assert (std::isfinite (a));
    assert (std::isfinite (b));
    assert (std::isfinite (c));

    assert (x1 != 0 );
    assert (x2 != 0 );
    assert (x1 != x2);

    *x1 = NAN, *x2 = NAN;

    if (IsZero (a))
    {
        if (IsZero (b))
        {
        if (IsZero (c))
            return 3;
        else
            return 0;
        }
        else // if (b != 0)
        {
        *x1 = solveLinear (b, c);
        return 1;
        }
    }

    else // if (a != 0)
    {
        double d = b*b - 4*a*c;

        if (IsZero (d))
        {
            *x1 = -b / (2*a);
            return 1;
        }
        else if (d < 0)
        {
            return 0;
        }
        else
        {
            *x1 = (-b - sqrt (d)) / (2*a);
            *x2 = (-b + sqrt (d)) / (2*a);

            return 2;
        }
    }
}


double solveLinear (double k, double b)
{
    return -b / k;
}


int IsZero (double value)
{
    return (fabs (value) < EPSILON);
}


int UnitTest (int testNum, double a, double b, double c, double x1ref, double x2ref, int nRootsref)
{
    double x1 = NAN, x2 = NAN;

    int nRoots = solveSquare (a, b, c, &x1, &x2);

    if (isEqual (nRoots, nRootsref) && ((isEqual (x1, x1ref) && isEqual (x2, x2ref)) || (isEqual (x1, x2ref) && isEqual (x2, x1ref))))
    {
        printf ("Test #%d - Success\n", testNum);
        return 1;
    }
    else
    {
        printf("Test #%d - FAILED:\n"
               "         %3d, %3g, %3g\n"
               "Expected %3d, %3g, %3g\n",
               testNum, nRoots, x1, x2, nRootsref, x1ref, x2ref);
        return 0;
    }
}


int isEqual (double value, double valueref)
{
    if ((isNAN (value)) && (isNAN (valueref))) return 1;
    return (fabs (value - valueref) < EPSILON);
}


int RunUnitTest ()
{
    int k = 0;

    if (UnitTest (1, 1, 5, -6, -6, 1, 2)) ++k;
    if (UnitTest (2, 1, 2, 1, -1, NAN, 1)) ++k;
    if (UnitTest (3, 50, 6, 30, NAN, NAN, 0)) ++k;
    if (UnitTest (4, 0, 6, 30, -5, NAN, 1)) ++k;
    if (UnitTest (5, 0, 0, 30, NAN, NAN, 0)) ++k;
    if (UnitTest (6, 0, 0, 0, NAN, NAN, 3)) ++k;
    if (UnitTest (7, 1, 17, -18, -18, 1, 2)) ++k;
    if (UnitTest (8, 2, -9, 7, 3.5, 1, 2)) ++k;
    if (UnitTest (9, 3, -11, 4, 0.4093, 3.2573, 2)) ++k;
    if (UnitTest (10, 1, 4, 4, -2, NAN, 1)) ++k;

    printf ("Nomber of succesful test:\n");
    return k;
}


int isNAN (double value)
{
    return (value != value);
}
