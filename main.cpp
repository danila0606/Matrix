#include "Matrix.h"
#include <gtest/gtest.h>
#include <fstream>

using namespace linal;

int main(int argc, char* argv[]) {

#ifdef GTESTS
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#endif

    try {

        linal::Matrix<double> m;
        std::cin>>m;

        double res = m.determinantGaus();

        std::cout<<std::round(res)<<std::endl;

    } catch (std::exception& e) {

        std::cerr<<e.what()<<std::endl;
    }
    return 0;
}