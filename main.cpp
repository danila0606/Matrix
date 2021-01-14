#include "Matrix.h"
#include <gtest/gtest.h>
#include <fstream>

using namespace linal;


/*void* operator new[] (size_t size) {

    void* p = malloc(size);
    printf("Allocated %p, %zu elems\n",p, size);
    return p;
}
void operator delete[] (void* p) noexcept {

    printf("deleted %p \n", p);
    free(p);
}

int b = 0;

class A {
    int a;
public:
    A() : a(0) {};
    A(int x) : a(x) {};

    A& operator = (const A& rhs) {
        if (b == 3)
            throw std::invalid_argument("3th elem\n");
        else
            b++;

        a = rhs.a;
    }

    ~A() {
        printf("A del, %d\n", a);
    };

    int getA() const {return a;};

};

std::ostream& operator << (std::ostream& os, const A& rhs) {
    os<< rhs.getA();
    return os;
}*/

int main(int argc, char* argv[]) {

#ifdef GTESTS
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#endif

    try {

        /*linal::Matrix<A> m {{1, 2, 3}, {2, 5}};
        std::cout<<m;*/
        linal::Matrix<double> m;
        std::cin>>m;

        double res = m.determinantGaus();

        std::cout<<std::round(res)<<std::endl;

    } catch (std::exception& e) {

        std::cerr<<e.what()<<std::endl;
    }
    return 0;
}