#include <ceres/ceres.h>
#include <chrono>
#include <iostream>

using namespace std;

struct Functor {
    // HelloWorld(T x) : x_(x) {}

    template <typename T>
    bool operator()(const T* const x, T* residual) const {
        residual[0] = T(10) - x[0];
        return true;
    }
    // const T x_;
};

int main(int argc, char** argv) {
    // initial value
    double initial_x = 5.0;
    double x = initial_x;

    // create problem
    ceres::Problem problem;

    // set the model of AutoDiffCostFunction自动求导的模板参数<误差类型， 输出维度， 输入维度>
    ceres::CostFunction* helloWord_costFunction = new ceres::AutoDiffCostFunction<Functor, 1, 1>(new Functor);
    // add the residualBlock
    problem.AddResidualBlock(helloWord_costFunction, nullptr, &x);

    // run the solver
    ceres::Solver::Options options;
    options.linear_solver_type = ceres::DENSE_QR;
    options.minimizer_progress_to_stdout = true;
    ceres::Solver::Summary summary;
    ceres::Solve(options, &problem, &summary);

    cout << summary.BriefReport() << endl;
    cout << "x: " << initial_x << " -> " << x << endl;
    return 0;
}
