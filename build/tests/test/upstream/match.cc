// auto-generated by yaml_to_cxx.py from test/upstream/match.yaml
#include "testlib.h"
void test_upstream_match() {
    enter_section("test_upstream_match: Tests for match");
    temp_table tbl_table;
    R::Query tbl = tbl_table.table();
    TEST_EQ(maybe_run(R::expr("abcdefg").match("a(b.e)|b(c.e)"), *conn), (R::Object{{"str", "bcde"}, {"groups", R::Array{R::Nil(), R::Object{{"start", 2}, {"str", "cde"}, {"end", 5}}}}, {"start", 1}, {"end", 5}}));
    TEST_EQ(maybe_run(R::expr("abcdefg").match("a(b.e)|B(c.e)"), *conn), (R::Nil()));
    TEST_EQ(maybe_run(R::expr("abcdefg").match("(?i)a(b.e)|B(c.e)"), *conn), (R::Object{{"str", "bcde"}, {"groups", R::Array{R::Nil(), R::Object{{"start", 2}, {"str", "cde"}, {"end", 5}}}}, {"start", 1}, {"end", 5}}));
    TEST_EQ(maybe_run(R::expr(R::array("aba", "aca", "ada", "aea")).filter([=](R::Var row){ return (*row).match("a(.)a")["groups"][0]["str"].match("[cd]"); }), *conn), (R::Array{"aca", "ada"}));
    TEST_EQ(maybe_run(tbl.insert(R::array(R::object("id", 0, "a", "abc"), R::object("id", 1, "a", "ab"), R::object("id", 2, "a", "bc"))), *conn), (R::Object{{"deleted", 0}, {"replaced", 0}, {"unchanged", 0}, {"errors", 0}, {"skipped", 0}, {"inserted", 3}}));
    TEST_EQ(maybe_run(tbl.filter([=](R::Var row){ return (*row)["a"].match("b"); }).order_by("id"), *conn), (R::Array{R::Object{{"id", 0}, {"a", "abc"}}, R::Object{{"id", 1}, {"a", "ab"}}, R::Object{{"id", 2}, {"a", "bc"}}}));
    TEST_EQ(maybe_run(tbl.filter([=](R::Var row){ return (*row)["a"].match("ab"); }).order_by("id"), *conn), (R::Array{R::Object{{"id", 0}, {"a", "abc"}}, R::Object{{"id", 1}, {"a", "ab"}}}));
    TEST_EQ(maybe_run(tbl.filter([=](R::Var row){ return (*row)["a"].match("ab$"); }).order_by("id"), *conn), (R::Array{R::Object{{"id", 1}, {"a", "ab"}}}));
    TEST_EQ(maybe_run(tbl.filter([=](R::Var row){ return (*row)["a"].match("^b$"); }).order_by("id"), *conn), (R::Array{}));
    TEST_EQ(maybe_run(R::expr("").match("ab\\9"), *conn), (err("ReqlQueryLogicError", "Error in regexp `ab\\9` (portion `\\9`): invalid escape sequence: \\9", R::Array{})));
    exit_section();
}