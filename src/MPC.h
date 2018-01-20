#ifndef MPC_H
#define MPC_H

#include <vector>
#include "Eigen-3.3/Eigen/Core"

using namespace std;

struct state_vec {
	std::vector<double> x;
	std::vector<double> y;
	std::vector<double> psi;
	std::vector<double> v;
	std::vector<double> delta;
	std::vector<double> a;
};

class MPC {
 public:
  MPC();

  virtual ~MPC();

  // Solve the model given an initial state and polynomial coefficients.
  // Return the first actuatotions.
  //vector<double> Solve(Eigen::VectorXd state, Eigen::VectorXd coeffs);
  state_vec Solve(Eigen::VectorXd state, Eigen::VectorXd coeffs);
};

#endif /* MPC_H */
