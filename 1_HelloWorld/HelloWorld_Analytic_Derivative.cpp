#include <ceres/ceres.h>
#include <glog/logging.h>
#include <iostream>

using namespace std;
using ceres::CostFunction;
using ceres::SizedCostFunction;
using ceres::Problem;
using ceres::Solver;
using ceres::Solve;

// A CostFunction implementing analytically derivatives for the
// function f(x) = 10 - x.
class QuadraticCostFunction : public SizedCostFunction<1 /* number of residuals */, 1 /* size of first parameter */> {
   public:
    virtual ~QuadraticCostFunction() {}
    virtual bool Evaluate(double const* const* parameters, double* residuals, double** jacobians) const {
        double x = parameters[0][0];
        // f(x) = 10 - x.
        residuals[0] = 10 - x;
        // f'(x) = -1. Since there's only 1 parameter and that parameter
        // has 1 dimension, there is only 1 element to fill in the
        // jacobians.
        //
        // Since the Evaluate function can be called with the jacobians
        // pointer equal to NULL, the Evaluate function must check to see
        // if jacobians need to be computed.
        //
        // For this simple problem it is overkill to check if jacobians[0]
        // is NULL, but in general when writing more complex
        // CostFunctions, it is possible that Ceres may only demand the
        // derivatives w.r.t. a subset of the parameter blocks.
        if (jacobians != NULL && jacobians[0] != NULL) {
            jacobians[0][0] = -1;
        }
        return true;
    }
};

int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);
    double initial_x = 5.0;
    double x = initial_x;

    Problem problem;

    CostFunction* helloWorld_AD_costFun = new QuadraticCostFunction;
    problem.AddResidualBlock(helloWorld_AD_costFun, nullptr, &x);

    Solver::Options options;
    // options.linear_solver_type =
    options.minimizer_progress_to_stdout = true;

    Solver::Summary summary;
    Solve(options, &problem, &summary);

    cout << summary.BriefReport() << endl;
    cout << "x: " << initial_x << " -> " << x << endl;
}
