#include"../include/unit_test/unit_suites.h"
#include"../include/rsa_threadpool/rsa_threadpool.h"
using namespace boost;

BOOST_AUTO_TEST_SUITE(test_suite1)

BOOST_AUTO_TEST_CASE(rsa_threadpool_test){
    BOOST_CHECK(rsa_threadpool(111)==111);
}
BOOST_AUTO_TEST_SUITE_END()
