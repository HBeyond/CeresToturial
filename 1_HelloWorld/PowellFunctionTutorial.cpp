#include <ceres/ceres.h>
#include <iostream>
#include "gflags/gflags.h"
#include "glog/logging.h"

using namespace std;
using ceres::AutoDiffCostFunction;
using ceres::CostFunction;
using ceres::Problem;
using ceres::Solver;
using ceres::Solve;

struct F1 {
    template <typename T>
    bool operator()(const T* const x1, const T* const x2, T* residual) const {
        residual[0] = x1[0] + T(10.0) * x2[0];
        return true;
    }
};

struct F2 {
    template <typename T>
    bool operator()(const T* const x3, const T* const x4, T* residual) const {
        residual[0] = T(sqrt(5.0)) * (x3[0] - x4[0]);
        return true;
    }
};

struct F3 {
    template <typename T>
    bool operator()(const T* const x2, const T* const x3, T* residual) const {
        residual[0] = (x2[0] - T(10.0) * x3[0]) * (x2[0] - T(10.0) * x3[0]);
        return true;
    }
};

struct F4 {
    template <typename T>
    bool operator()(const T* const x1, const T* const x4, T* residual) const {
        residual[0] = T(sqrt(10.0)) * (x1[0] - x4[0]) * (x1[0] - x4[0]);
        return true;
    }
};

DEFINE_string(minimizer, "trust_region", "Minimizer type to use, choices are: line_search & trust_region");

int main(int argc, char* argv[]) {
    google::InitGoogleLogging(argv[0]);
    google::ParseCommandLineFlags(&argc, &argv, true);
    LOG(INFO) << "Begin" << endl;

    double x1 = 3.0;
    double x2 = -1.0;
    double x3 = 0.0;
    double x4 = 1.0;

    Problem problem;

    CostFunction* costF1 = new AutoDiffCostFunction<F1, 1, 1, 1>(new F1);
    CostFunction* costF2 = new AutoDiffCostFunction<F2, 1, 1, 1>(new F2);
    CostFunction* costF3 = new AutoDiffCostFunction<F3, 1, 1, 1>(new F3);
    CostFunction* costF4 = new AutoDiffCostFunction<F4, 1, 1, 1>(new F4);

    problem.AddResidualBlock(costF1, nullptr, &x1, &x2);
    problem.AddResidualBlock(costF2, nullptr, &x3, &x4);
    problem.AddResidualBlock(costF3, nullptr, &x2, &x3);
    problem.AddResidualBlock(costF4, nullptr, &x1, &x4);

    Solver::Options options;
    LOG_IF(FATAL, !ceres::StringToMinimizerType(FLAGS_minimizer, &options.minimizer_type))
        << "Invalid minimizer: " << FLAGS_minimizer << ", valid options are: trust_region and line_search.";
    options.max_num_iterations = 100;
    options.linear_solver_type = ceres::DENSE_QR;
    options.minimizer_progress_to_stdout = true;
    std::cout << "Initial x1 = " << x1 << ", x2 = " << x2 << ", x3 = " << x3 << ", x4 = " << x4 << "\n";
    // Run the solver!
    Solver::Summary summary;
    Solve(options, &problem, &summary);
    std::cout << summary.FullReport() << "\n";
    std::cout << "Final x1 = " << x1 << ", x2 = " << x2 << ", x3 = " << x3 << ", x4 = " << x4 << "\n";
    return 0;
}
