#include <iostream>
#include "ceres/ceres.h"
#include "glog/logging.h"

using namespace std;
using ceres::CostFunction;
using ceres::NumericDiffCostFunction;
using ceres::CENTRAL;
using ceres::Problem;
using ceres::Solver;
using ceres::Solve;

struct Functor {
    bool operator()(const double* const x, double* residual) const {
        residual[0] = 10.0 - x[0];
        return true;
    }
};

int main(int argc, char** argv) {
    // google::InitGoogleLogging(argv[0]);

    double initial_x = 5.0;
    double x = initial_x;

    Problem problem;

    CostFunction* helloWrold_ND_costFun = new NumericDiffCostFunction<Functor, CENTRAL, 1, 1>(new Functor);
    problem.AddResidualBlock(helloWrold_ND_costFun, nullptr, &x);

    Solver::Options options;
    options.linear_solver_type = ceres::DENSE_QR;
    options.minimizer_progress_to_stdout = true;

    Solver::Summary summary;
    Solve(options, &problem, &summary);

    cout << summary.BriefReport() << endl;
    cout << "x: " << initial_x << " -> " << x << endl;

    return 0;
}
