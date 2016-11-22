#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "rand.h"

/*-------------  UNIFORM [0, 1) RANDOM NUMBER GENERATOR  -------------*/
double uniform(void)
  {
	return drand48();
  }


/*-------------  UNIFORM (0, 1) RANDOM NUMBER GENERATOR  -------------*/
double uniform_pos(void)
{
	double g;

	g = uniform();
	while (g == 0.0)
		g = uniform();

	return g;
}


/*--------------------------  SET SEED  --------------------------*/
void seed( long int n)
    { /* set seed to n  */
	srand48(n);
    }

/*------------  UNIFORM [a, b) RANDOM VARIATE GENERATOR  -------------*/
double uniform_ab(double a, double b)
    { /* 'uniform' returns a psuedo-random variate from a uniform     */
      /* distribution with lower bound a and upper bound b.           */
      if (a>b)  printf("uniform Argument Error: a > b\n");
      return(a+(b-a)*uniform());
    }

/*--------------------  RANDOM INTEGER GENERATOR  --------------------*/
int uniform_int(int i, int n)
    { /* 'random' returns an integer equiprobably selected from the   */
      /* set of integers i, i+1, i+2, . . , n.                        */
      if (i>n)  printf("random Argument Error: i > n\n");
      n-=i; n=(n+1.0)*uniform();
      return(i+n);
    }

/*--------------  EXPONENTIAL RANDOM VARIATE GENERATOR  --------------*/
/* The exponential distribution has the form

   p(x) dx = exp(-x/landa) dx/landa

   for x = 0 ... +infty 
*/


double exponential(double landa)
{ 
	/* 'exponential' returns a psuedo-random variate from a negative     */
      	/* exponential distribution with mean 1/landa.                        */

 	double u = uniform_pos();	
	double mean = 1.0 / landa;


 	return -mean * log(u);
}

/*----------------  ERLANG RANDOM VARIATE GENERATOR  -----------------*/
double erlang(double x, double s)
    { /* 'erlang' returns a psuedo-random variate from an erlang      */
      /* distribution with mean x and standard deviation s.           */
      int i,k; double z;
      if (s>x)  printf("erlang Argument Error: s > x\n");
      z=x/s; k=(int)z*z;
      z=1.0; for (i=0; i<k; i++) z*=uniform_pos();
      return(-(x/k)*log(z));
    }

/*-----------  HYPEREXPONENTIAL RANDOM VARIATE GENERATION  -----------*/
double hyperx(double x, double s)
    { /* 'hyperx' returns a psuedo-random variate from Morse's two-   */
      /* stage hyperexponential distribution with mean x and standard */
      /* deviation s, s>x.  */
      double cv,z,p;
      if (s<=x)  printf("hyperx Argument Error: s not > x\n");
      cv=s/x; z=cv*cv; p=0.5*(1.0-sqrt((z-1.0)/(z+1.0)));
      z=(uniform_pos()>p)? (x/(1.0-p)):(x/p);
      return(-0.5*z*log(uniform_pos()));
    }

/*-----------------  NORMAL RANDOM VARIATE GENERATOR  ----------------*/
double normal(double x, double s)
    { /* 'normal' returns a psuedo-random variate from a normal dis-  */
      /* tribution with mean x and standard deviation s.              */
      double v1,v2,w,z1; static double z2=0.0;
      if (z2!=0.0)
         {z1=z2; z2=0.0;}  /* use value from previous call */
        else
          {
            do
              {v1=2.0*uniform_pos()-1.0; v2=2.0*uniform_pos()-1.0; w=v1*v1+v2*v2;}
            while (w>=1.0);
            w=sqrt((-2.0*log(w))/w); z1=v1*w; z2=v2*w;
          }
      return(x+z1*s);
  }

/*---------- LOGNORMAL RANDOM VARIATE GENERATOR ------------*/
double ran_lognormal(double p, double u)
{
	return exp(normal(u, p));
}

/* The Weibull distribution has the form,

   p(x) dx = (k/a) (x/a)^(k-1) exp(-(x/a)^k) dx

   k = shape
  a = landa = scale
 */

double ran_weibull ( const double k, const double a)
{
  double x = uniform_pos ();

  double z = pow (-log (x), 1 / k);

  return a * z;
}



/* The Gamma distribution 

   k = shape
   b = teta = scale

   p(x) dx = {1 / \Gamma(k) b^a } x^{k-1} e^{-x/b} dx

   for x>0.  If X and Y are independent gamma-distributed random
   variables of order a1 and a2 with the same scale parameter b, then
   X+Y has gamma distribution of order a1+a2.

   The algorithms below are from Knuth, vol 2, 2nd ed, p. 129. */

double ran_gamma (const double k, const double b)
{
  /* assume a > 0 */
   unsigned int na = floor (k);

  if (k == na)
    {
      return b * ran_gamma_int (na);
    }
  else if (na == 0)
    {
      return b * gamma_frac (k);
    }
  else
    {
      return b * (ran_gamma_int (na) + gamma_frac (k - na)) ;
    }
}

double ran_gamma_int (const unsigned int a)
{
  if (a < 12)
    {
      unsigned int i;
      double prod = 1;

      for (i = 0; i < a; i++)
        {
          prod *= uniform_pos ();
        }

      /* Note: for 12 iterations we are safe against underflow, since
         the smallest positive random number is O(2^-32). This means
         the smallest possible product is 2^(-12*32) = 10^-116 which
         is within the range of double precision. */

      return -log (prod);
    }
  else
    {
      return gamma_large ((double) a);
    }
}

double gamma_large (const double a)
{
  /* Works only if a > 1, and is most efficient if a is large

     This algorithm, reported in Knuth, is attributed to Ahrens.  A
     faster one, we are told, can be found in: J. H. Ahrens and
     U. Dieter, Computing 12 (1974) 223-246 begin_of_the_skype_highlighting              12 (1974) 223-246      end_of_the_skype_highlighting.  */

  double sqa, x, y, v;
  sqa = sqrt (2 * a - 1);
  do
    {
      do
        {
          y = tan (M_PI * uniform ());
          x = sqa * y + a - 1;
        }
      while (x <= 0);
      v = uniform ();
    }
  while (v > (1 + y * y) * exp ((a - 1) * log (x / (a - 1)) - sqa * y));

  return x;
}

double gamma_frac (const double a)
{
  /* This is exercise 16 from Knuth; see page 135, and the solution is
     on page 551.  */

  double p, q, x, u, v;
  p = M_E / (a + M_E);
  do
    {
      u = uniform ();
      v = uniform_pos ();

      if (u < p)
        {
          x = exp ((1 / a) * log (v));
          q = exp (-x);
        }
      else
        {
          x = 1 - log (v);
          q = exp ((a - 1) * log (x));
        }
    }
  while (uniform () >= q);

  return x;
}

double ran_distri(char num, double a, double b){
	switch((int)num){
		case 0:
			return ran_weibull(a, b); 
		case 1:
			return ran_gamma(a, b);
		case 2:
			return ran_lognormal(a, b);
		case 3:
			return normal(a, b);
		case 4:
			return hyperx(a, b);
		case 5:
			return exponential(a);
		case 6:	
			return 1;
		case 7:
			return 0;
		default:
			// ERROR
			printf("You've chosen an incorrect random distribution\n");
			return -1;
			
	}
	return 0;
}


