//
//  Copyright (c) 2000-2002
//  Joerg Walter, Mathias Koch
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  GeNeSys mbH & Co. KG in producing this work.
//

#include "test1.hpp"

// Test matrix & vector expression templates
template<class V, class M, int N>
struct test_my_matrix_vector {
    typedef typename V::value_type value_type;

    template<class VP, class MP>
    void test_with (VP &v1, VP &v2, MP &m1) const {
        {
            // Rows and columns
            initialize_matrix (m1);
            for (int i = 0; i < N; ++ i) {
                v1 = ublas::row (m1, i);
                std::cout << "row (m, " << i << ") = " << v1 << std::endl;
                v1 = ublas::column (m1, i);
                std::cout << "column (m, " << i << ") = " << v1 << std::endl;
            }

            // Outer product
            initialize_vector (v1);
            initialize_vector (v2);
            m1 = ublas::outer_prod (v1, v2);
            std::cout << "outer_prod (v1, v2) = " << m1 << std::endl;

            // Matrix vector product
            initialize_matrix (m1);
            initialize_vector (v1);
            v2 = ublas::prod (m1, v1);
            std::cout << "prod (m1, v1) = " << v2 << std::endl;
            v2 = ublas::prod (v1, m1);
            std::cout << "prod (v1, m1) = " << v2 << std::endl;
        }
    }
    void operator () () const {
        {
            V v1 (N), v2 (N);
            M m1 (N, N);
            test_with (v1, v2, m1);

            ublas::matrix_row<M> mr1 (m1, 0), mr2 (m1, 1);
            test_with (mr1, mr2, m1);

            ublas::matrix_column<M> mc1 (m1, 0), mc2 (m1, 1);
            test_with (mc1, mc2, m1);

#ifdef USE_RANGE
            ublas::matrix_vector_range<M> mvr1 (m1, ublas::range (0, N), ublas::range (0, N)),
                                          mvr2 (m1, ublas::range (0, N), ublas::range (0, N));
            test_with (mvr1, mvr2, m1);
#endif

#ifdef USE_SLICE
            ublas::matrix_vector_slice<M> mvs1 (m1, ublas::slice (0, 1, N), ublas::slice (0, 1, N)),
                                          mvs2 (m1, ublas::slice (0, 1, N), ublas::slice (0, 1, N));
            test_with (mvs1, mvs2, m1);
#endif
        }
    }
};

// Test matrix & vector
void test_matrix_vector () {
    std::cout << "test_matrix_vector" << std::endl;

    std::cout << "mp_test_type, bounded_array" << std::endl;
    test_my_matrix_vector<ublas::vector<mp_test_type, ublas::bounded_array<mp_test_type, 3> >,
                          ublas::matrix<mp_test_type, ublas::row_major, ublas::bounded_array<mp_test_type, 3 * 3> >, 3> () ();
    std::cout << "mp_test_type, unbounded_array" << std::endl;
    test_my_matrix_vector<ublas::vector<mp_test_type, ublas::unbounded_array<mp_test_type> >,
                          ublas::matrix<mp_test_type, ublas::row_major, ublas::unbounded_array<mp_test_type> >, 3> () ();
    std::cout << "mp_test_type, std::vector" << std::endl;
    test_my_matrix_vector<ublas::vector<mp_test_type, std::vector<mp_test_type> >,
                          ublas::matrix<mp_test_type, ublas::row_major, std::vector<mp_test_type> >, 3> () ();
    std::cout << "mp_test_type, bounded" << std::endl;
    test_my_matrix_vector<ublas::bounded_vector<mp_test_type, 3>,
                          ublas::bounded_matrix<mp_test_type, 3, 3>, 3> () ();
    std::cout << "mp_test_type, bounded_array" << std::endl;
    test_my_matrix_vector<ublas::vector<mp_test_type, ublas::bounded_array<mp_test_type, 3> >,
                          ublas::vector_of_vector<mp_test_type, ublas::row_major, ublas::bounded_array<ublas::bounded_array<mp_test_type, 3>, 3 + 1> >, 3> () ();
    std::cout << "mp_test_type, unbounded_array" << std::endl;
    test_my_matrix_vector<ublas::vector<mp_test_type, ublas::unbounded_array<mp_test_type> >,
                          ublas::vector_of_vector<mp_test_type, ublas::row_major, ublas::unbounded_array<ublas::unbounded_array<mp_test_type> > >, 3> () ();
    std::cout << "mp_test_type, std::vector" << std::endl;
    /*
    // This fails with an internal std lib assersion, even when mp_test_type is double,
    // looks like a bug in the uBlas test code...
    test_my_matrix_vector<ublas::vector<mp_test_type, std::vector<mp_test_type> >,
                          ublas::vector_of_vector<mp_test_type, ublas::row_major, std::vector<std::vector<mp_test_type> > >, 3> () ();*/
}
