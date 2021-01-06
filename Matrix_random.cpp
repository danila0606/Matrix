#include "Matrix.h"

namespace  linal {
    void RandomFill(Matrix<int> &m, int d1, int d2) {

        unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
        std::default_random_engine eng(seed);

        std::uniform_int_distribution<int> distr(d1, d2);

        for (int i = 0; i < m.GetRows(); i++) {
            for (int j = 0; j < m.GetColumns(); j++)
                m.at(i, j) = distr(eng);
        }

    }

    void RandomFill(Matrix<double> &m, int d1, int d2) {

        unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
        std::default_random_engine eng(seed);

        std::uniform_real_distribution<double> distr(d1, d2);

        for (int i = 0; i < m.GetRows(); i++) {
            for (int j = 0; j < m.GetColumns(); j++)
                m.at(i, j) = distr(eng);
        }

    }

}
