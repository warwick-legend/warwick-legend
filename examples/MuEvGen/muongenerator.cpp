#include <random>
#include <cmath>
#include <iostream>

class MuEnergy {
  // data members
  private:
   double bpar; // fixed parameter; Mei, Hime, Preprint astro-ph/0512125, Eq.8
   double gammaMu; // "
   double epsMu;   // "
   double depth;   // laboratory depth [km.w.e.] to be set

  public:
   MuEnergy(double d) : bpar(0.4), 
                        gammaMu(3.77),
                        epsMu(693.0),
                        depth(d) {} // default constructor, fix parameter values
   ~MuEnergy() {}

   double operator() (double x) {   // energy distribution function
     double dummy = (x + epsMu * (1.0 - std::exp(-bpar * depth)));
     double result = std::exp(-bpar * depth * (gammaMu - 1.0)) * std::pow(dummy, -gammaMu);
     return result;
   }
};

class MuAngle {
  // data members
  private:
   double i1, i2, L1, L2; // fixed parameter; Mei, Hime, Preprint astro-ph/0512125, Eq.3/4
   double depth;   // laboratory depth [km.w.e.] to be set

  public:
   MuAngle(double d) : i1(8.6e-6),
                       i2(0.44e-6),
                       L1(0.45),
                       L2(0.87),
                       depth(d) {} // default constructor, fix parameter values
   ~MuAngle() {}

   double operator() (double x) {   // cos(theta) distribution function
     double costheta = x;
     double sec = 1.0e5; // inverse smallest cos theta
     if (costheta>1.0e-5)
       sec = 1.0/costheta; // exclude horizontal costheta = 0
     double dummy = depth * sec / L1;
     double dummy2= depth * sec / L2;
     double result = (i1 * std::exp(-dummy) + i2 * std::exp(-dummy2)) * sec;
     return result;
   }
};


int main() {
  typedef std::piecewise_linear_distribution<double> pld_type;

  int nw = 100; // number of bins
  double lower_bound = 1.0;    // energy interval lower bound [GeV]
  double upper_bound = 3000.0; // upper bound [GeV]
  double nearhorizontal = 1.0e-5;
  double fullcosangle = 1.0;

  double depth = 5.89; // Sudbury laboratory [km.w.e]

  // custom probability distributions
  std::random_device rd;
  std::ranlux24 generator(rd()); // explicit generator
  pld_type ed(nw, lower_bound, upper_bound, MuEnergy(depth) );
  pld_type cosd(nw, nearhorizontal, fullcosangle, MuAngle(depth) );

  // output, compare fig.6 in paper
  std::cout << "energy intervals: " << std::endl;
  for (double val : ed.intervals()) std::cout << val << " ";
  std::cout << std::endl;
  std::cout << "energy densities: " << std::endl;
  for (double val : ed.densities()) std::cout << val << " ";
  std::cout << std::endl;
  std::cout << "energy value: " << ed(generator) << std::endl;

  // output angle, compare fig. 7 in paper
  std::cout << "angle intervals: " << std::endl;
  for (double val : cosd.intervals()) std::cout << val << " ";
  std::cout << std::endl;
  std::cout << "angle densities: " << std::endl;
  for (double val : cosd.densities()) std::cout << val << " ";
  std::cout << std::endl;

  // momentum vector
  double px, py, pz;
  double sintheta, sinphi, costheta, cosphi;

  costheta = cosd(generator); // get a random number
  sintheta = std::sqrt(1. - costheta*costheta);

  std::uniform_real_distribution<> rndm(0.0, 1.0); // azimuth angle
  double twopi = 2.0 * std::acos(-1.0);
  double phi = twopi * rndm(generator);  
  sinphi = std::sin(phi);
  cosphi = std::cos(phi);
  
  px = -sintheta * cosphi;
  py = -sintheta * sinphi;
  pz = -costheta;  // default downwards: pz = -1.0

  std::cout << "cos angle value: " << costheta << std::endl;
  std::cout << "vector components: " << std::endl;
  std::cout << px << ", " << py << ", " << pz << std::endl;
  return 0;
}

