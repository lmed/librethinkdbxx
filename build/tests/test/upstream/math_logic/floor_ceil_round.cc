// auto-generated by yaml_to_cxx.py from test/upstream/math_logic/floor_ceil_round.yaml
#include "testlib.h"
void test_upstream_math_logic_floor_ceil_round() {
    enter_section("test_upstream_math_logic_floor_ceil_round: tests for `floor`, `ceil`, and `round`, tests inspired by the Python test suite");
    TEST_EQ(maybe_run(R::floor(1.0).type_of(), *conn), ("NUMBER"));
    TEST_EQ(maybe_run(R::floor(1.0), *conn), (1.0));
    TEST_EQ(maybe_run(R::expr(1.0).floor(), *conn), (1.0));
    TEST_EQ(maybe_run(R::floor(0.5), *conn), (0.0));
    TEST_EQ(maybe_run(R::floor(1.0), *conn), (1.0));
    TEST_EQ(maybe_run(R::floor(1.5), *conn), (1.0));
    TEST_EQ(maybe_run(R::floor(-0.5), *conn), (-1.0));
    TEST_EQ(maybe_run(R::floor(-1.0), *conn), (-1.0));
    TEST_EQ(maybe_run(R::floor(-1.5), *conn), (-2.0));
    TEST_EQ(maybe_run(R::expr("X").floor(), *conn), (err("ReqlQueryLogicError", "Expected type NUMBER but found STRING.", R::Array{})));
    TEST_EQ(maybe_run(R::ceil(1.0).type_of(), *conn), ("NUMBER"));
    TEST_EQ(maybe_run(R::ceil(1.0), *conn), (1.0));
    TEST_EQ(maybe_run(R::expr(1.0).ceil(), *conn), (1.0));
    TEST_EQ(maybe_run(R::ceil(0.5), *conn), (1.0));
    TEST_EQ(maybe_run(R::ceil(1.0), *conn), (1.0));
    TEST_EQ(maybe_run(R::ceil(1.5), *conn), (2.0));
    TEST_EQ(maybe_run(R::ceil(-0.5), *conn), (0.0));
    TEST_EQ(maybe_run(R::ceil(-1.0), *conn), (-1.0));
    TEST_EQ(maybe_run(R::ceil(-1.5), *conn), (-1.0));
    TEST_EQ(maybe_run(R::expr("X").ceil(), *conn), (err("ReqlQueryLogicError", "Expected type NUMBER but found STRING.", R::Array{})));
    TEST_EQ(maybe_run(R::round(1.0).type_of(), *conn), ("NUMBER"));
    TEST_EQ(maybe_run(R::round(1.0), *conn), (1.0));
    TEST_EQ(maybe_run(R::expr(1.0).round(), *conn), (1.0));
    TEST_EQ(maybe_run(R::round(0.5), *conn), (1.0));
    TEST_EQ(maybe_run(R::round(-0.5), *conn), (-1.0));
    TEST_EQ(maybe_run(R::round(0.0), *conn), (0.0));
    TEST_EQ(maybe_run(R::round(1.0), *conn), (1.0));
    TEST_EQ(maybe_run(R::round(10.0), *conn), (10.0));
    TEST_EQ(maybe_run(R::round(1000000000.0), *conn), (1000000000.0));
    TEST_EQ(maybe_run(R::round(1e+20), *conn), (1e+20));
    TEST_EQ(maybe_run(R::round(-1.0), *conn), (-1.0));
    TEST_EQ(maybe_run(R::round(-10.0), *conn), (-10.0));
    TEST_EQ(maybe_run(R::round(-1000000000.0), *conn), (-1000000000.0));
    TEST_EQ(maybe_run(R::round(-1e+20), *conn), (-1e+20));
    TEST_EQ(maybe_run(R::round(0.1), *conn), (0.0));
    TEST_EQ(maybe_run(R::round(1.1), *conn), (1.0));
    TEST_EQ(maybe_run(R::round(10.1), *conn), (10.0));
    TEST_EQ(maybe_run(R::round(1000000000.1), *conn), (1000000000.0));
    TEST_EQ(maybe_run(R::round(-1.1), *conn), (-1.0));
    TEST_EQ(maybe_run(R::round(-10.1), *conn), (-10.0));
    TEST_EQ(maybe_run(R::round(-1000000000.1), *conn), (-1000000000.0));
    TEST_EQ(maybe_run(R::round(0.9), *conn), (1.0));
    TEST_EQ(maybe_run(R::round(9.9), *conn), (10.0));
    TEST_EQ(maybe_run(R::round(999999999.9), *conn), (1000000000.0));
    TEST_EQ(maybe_run(R::round(-0.9), *conn), (-1.0));
    TEST_EQ(maybe_run(R::round(-9.9), *conn), (-10.0));
    TEST_EQ(maybe_run(R::round(-999999999.9), *conn), (-1000000000.0));
    TEST_EQ(maybe_run(R::expr("X").round(), *conn), (err("ReqlQueryLogicError", "Expected type NUMBER but found STRING.", R::Array{})));
    exit_section();
}