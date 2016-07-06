// auto-generated by yaml_to_cxx.py from test/upstream/datum/object.yaml
#include "testlib.h"
void test_upstream_datum_object() {
    enter_section("test_upstream_datum_object: Tests conversion to and from the RQL object type");
    TEST_EQ(maybe_run(R::expr(R::object()), *conn), (R::Object{}));
    TEST_EQ(maybe_run(R::expr(R::object("a", 1)), *conn), (R::Object{{"a", 1}}));
    TEST_EQ(maybe_run(R::expr(R::object("a", 1, "b", "two", "c", true)), *conn), (R::Object{{"a", 1}, {"b", "two"}, {"c", true}}));
    TEST_EQ(maybe_run(R::expr(R::object("a", R::expr(1))), *conn), (R::Object{{"a", 1}}));
    TEST_EQ(maybe_run(R::expr(R::object("a", R::object("b", R::array(R::object("c", 2), "a", 4)))), *conn), (R::Object{{"a", R::Object{{"b", R::Array{R::Object{{"c", 2}}, "a", 4}}}}}));
    TEST_EQ(maybe_run(R::expr(R::object("a", 1)).type_of(), *conn), ("OBJECT"));
    TEST_EQ(maybe_run(R::expr(R::object("a", 1)).coerce_to("string"), *conn), ("{\"a\":1}"));
    TEST_EQ(maybe_run(R::expr(R::object("a", 1)).coerce_to("object"), *conn), (R::Object{{"a", 1}}));
    TEST_EQ(maybe_run(R::expr(R::object("a", 1)).coerce_to("array"), *conn), (R::Array{R::Array{"a", 1}}));
    TEST_EQ(maybe_run(R::object(), *conn), (R::Object{}));
    TEST_EQ(maybe_run(R::object("a", 1, "b", 2), *conn), (R::Object{{"a", 1}, {"b", 2}}));
    TEST_EQ(maybe_run(R::object(R::expr("c") + "d", 3), *conn), (R::Object{{"cd", 3}}));
    TEST_EQ(maybe_run(R::object("o", "d", "d"), *conn), (err("ReqlQueryLogicError", "OBJECT expects an even number of arguments (but found 3).", R::Array{})));
    TEST_EQ(maybe_run(R::object(1, 1), *conn), (err("ReqlQueryLogicError", "Expected type STRING but found NUMBER.", R::Array{})));
    TEST_EQ(maybe_run(R::object("e", 4, "e", 5), *conn), (err("ReqlQueryLogicError", "Duplicate key \"e\" in object.  (got 4 and 5 as values)", R::Array{})));
    TEST_EQ(maybe_run(R::object("g", R::db("test")), *conn), (err("ReqlQueryLogicError", "Expected type DATUM but found DATABASE:", R::Array{})));
    exit_section();
}