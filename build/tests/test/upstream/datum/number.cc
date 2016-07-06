// auto-generated by yaml_to_cxx.py from test/upstream/datum/number.yaml
#include "testlib.h"
void test_upstream_datum_number() {
    enter_section("test_upstream_datum_number: Tests of conversion to and from the RQL number type");
    TEST_EQ(maybe_run(R::expr(1), *conn), (1));
    TEST_EQ(maybe_run(R::expr(-1), *conn), (-1));
    TEST_EQ(maybe_run(R::expr(0), *conn), (0));
    TEST_EQ(maybe_run(R::expr(1.0), *conn), (1.0));
    TEST_EQ(maybe_run(R::expr(1.5), *conn), (1.5));
    TEST_EQ(maybe_run(R::expr(-0.5), *conn), (-0.5));
    TEST_EQ(maybe_run(R::expr(67498.89278), *conn), (67498.89278));
    TEST_EQ(maybe_run(R::expr(1234567890), *conn), (1234567890));
    TEST_EQ(maybe_run(R::expr(-73850380122423), *conn), (-73850380122423));
    TEST_EQ(maybe_run(R::expr(1234567890123456789012345678901234567890.0), *conn), (double(1234567890123456789012345678901234567890.0)));
    TEST_EQ(maybe_run(R::expr(123.45678901234568), *conn), (123.45678901234568));
    TEST_EQ(maybe_run(R::expr(1).type_of(), *conn), ("NUMBER"));
    TEST_EQ(maybe_run(R::expr(1).coerce_to("string"), *conn), ("1"));
    TEST_EQ(maybe_run(R::expr(1).coerce_to("number"), *conn), (1));
    TEST_EQ(maybe_run(R::expr(1.0), *conn), (int(1)));
    TEST_EQ(maybe_run(R::expr(45), *conn), (int(45)));
    TEST_EQ(maybe_run(R::expr(1.2), *conn), (double(1.2)));
    exit_section();
}