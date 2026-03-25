#include<iostream>
#include<cstdio>
#include"ODE.h"
#include<fstream>
#include<cmath>
#include<functional>

int main(){
    // PART A:
    
    double a = 0, b = 10;
    pp::vec y_init{0, 1};

    std::function<pp::vec(double, pp::vec)> pend = [=](double x, pp::vec y, double b = 0.3, double c = 7){
        pp::vec dydx(2);
        dydx[0] = y[1] + 0*x;
        dydx[1] = -b*y[1] - c*std::sin(y[0]);
        return dydx;
    };

    std::tuple<std::vector<double>, std::vector<pp::vec>> result = driver(pend, a, b, y_init);
    std::vector<double> xs = std::get<0>(result);
    std::vector<pp::vec> ys = std::get<1>(result);

    std::string outfile = "pend.txt";
    std::ofstream output_pend(outfile);
    for (int i = 0; i < (int)xs.size(); ++i){
        output_pend << xs[i] << ", " << ys[i][0] << "\n";
    }
    output_pend.close();

    y_init = pp::vec {10, 5};
    std::function<pp::vec(double, pp::vec)> lotkavolterra = [=](double x, pp::vec y, double a = 1.5, double b = 1, double c = 3, double d = 1){
        pp::vec dydx(2);
        dydx[0] = a*y[0] - b*y[0]*y[1] + 0*x;
        dydx[1] = -c*y[1] + d*y[0]*y[1];
        return dydx;
    };
    result = driver(lotkavolterra, a, b, y_init);
    xs = std::get<0>(result);
    ys = std::get<1>(result);

    outfile = "lot.txt";
    std::ofstream output_lot(outfile);
    for (int i = 0; i < (int)xs.size(); ++i){
        output_lot << xs[i] << ", " << ys[i][0] << ", " << ys[i][1] << "\n";
    }
    output_lot.close();


    // PART B:

    y_init = pp::vec {1, 0};
    matrix settings{{1, 0, 0}, {1, -0.5, 0}, {1, -0.5, 0.01}};

    auto makeOrbitfunc = [](double eps){
        return [eps](double x, pp::vec y){
            pp::vec dydx(2);
            dydx[0] = y[1] + 0*x;
            dydx[1] = 1 + eps*y[0]*y[0] - y[0];
            return dydx;
        };
    };

    std::vector<std::tuple<std::vector<double>, std::vector<pp::vec>>> results(3);
    std::vector<std::vector<double>> Xs(3);
    std::vector<std::vector<pp::vec>> Ys(3);
    for (int i = 0; i < settings.ncols; ++i){
        std::function<pp::vec(double, pp::vec)> plan = makeOrbitfunc(settings[i, 2]);
        std::cout << settings[i, 0] << " "  << settings[i, 1] << " " << settings[i, 2] << "\n";
        std::tuple<std::vector<double>, std::vector<pp::vec>> result = driver(plan, a, b, pp::vec{settings[i, 0], settings[i, 1]}, 0.01, 1e-6, 1e-6);
        std::vector<double> xs = std::get<0>(result);
        std::vector<pp::vec> ys = std::get<1>(result);
        results.push_back(result), Xs.push_back(xs), Ys.push_back(ys);
    }

    outfile = "orbit.txt";
    std::ofstream output_orbit(outfile);
    for (int j = 0; j < (int)Xs.size(); ++j){
        for (int i = 0; i < (int)Xs[j].size(); ++i){output_orbit << Xs[j][i] << ", " << Ys[j][i][0] << ", " << Ys[j][i][1] << "\n";}
        output_orbit << "\n \n";
    }
    output_orbit.close();

    // PART C

    b = 3;
    y_init = pp::vec{0.97000436, -0.24308753, -0.97000436, 0.24308753, 0, 0, 0.4662036850, 0.4323657300, 0.4662036850, 0.4323657300, -0.93240737, -0.86473146};

    std::function<pp::vec(double, pp::vec)> stable_orbit = [=](double x, pp::vec y){
        matrix dydx(2, 6);
        matrix my(2, 6);

        for (int i = 0; i < 6; ++i){
            my[i, 0] = y[2*i]; my[i, 1] = y[2*i + 1];}
        for (int i = 0; i < 3; ++i){
            pp::vec ri = my.get_row(i);
            pp::vec v = my.get_row(i + 3);
            dydx.set_row(i, v);
            pp::vec dv{0, 0};
            for (int j = 0; j < 3; ++j){
                
                if (j != i){
                    pp::vec dr = my.get_row(j) - ri;
                    double norm = dr.norm();
                    dv += dr/(norm*norm*norm);
                }
                
            }
            dydx.set_row(i + 3, dv);
        }
        return dydx.reshape(12, 1).get_row(0) + 0*x;
    };

    result = driver(stable_orbit, a, b, y_init, 0.01, 1e-6, 1e-6);
    xs = std::get<0>(result);
    ys = std::get<1>(result);

    outfile = "stable_orbit.txt";
    std::ofstream output_stable_orbit(outfile);
    for (int i = 0; i < (int)xs.size(); ++i){
        output_stable_orbit << xs[i];
        for (int j = 0; j < 12; ++j){output_stable_orbit << "\t " << ys[i][j];}
        output_stable_orbit << "\n";
    }
    output_stable_orbit.close();

    
    // std::function<pp::vec(double, pp::vec)> stable_orbit = [=](double x, pp::vec y){
    //     matrix dydx(2, 6);
    //     matrix my(2, 6);

    //     for (int i = 0; i < 6; ++i){my[i, 0] = y[2*i]; my[i, 1] = y[2*i + 1];}
    //     for (int i = 0; i < 3; ++i){
    //         pp::vec ri = my.get_row(i);
    //         dydx.set_row(2*i, ri);
    //         for (int j = 0; j < 3; ++j){
    //             pp::vec dv{0, 0};
    //             if (j != i){
    //                 pp::vec dr = my.get_row(j) - ri;
    //                 double norm = dr.norm();
    //                 dv += dr/(norm*norm*norm);
    //             }
    //             dydx.set_row(2*i + 1, dv);
    //         }
    //     }
    //     // std::cout << dydx.reshape(12, 1).get_row(1);
    //     return dydx.reshape(12, 1).get_row(1) + 0*x;
    // };

    // result = driver(stable_orbit, a, b, y_init);
    // xs = std::get<0>(result);
    // ys = std::get<1>(result);

    // outfile = "stable_orbit.txt";
    // std::ofstream output_stable_orbit(outfile);
    // for (int i = 0; i < (int)xs.size(); ++i){
    //     output_stable_orbit << xs[i];
    //     for (int j = 0; j < 12; ++j){output_stable_orbit << ", " << ys[i][0] << ", " << ys[i][1];}
    //     output_stable_orbit << "\n";
    // }
    // output_stable_orbit.close();
return 0;
}