// auto-generated by yaml_to_cxx.py from test/upstream/mutation/insert.yaml
#include "testlib.h"
void test_upstream_mutation_insert() {
    enter_section("test_upstream_mutation_insert: Tests insertion into tables");
    temp_table tbl_table;
    R::Query tbl = tbl_table.table();
    TEST_EQ(maybe_run(R::db("test").table_create("test2"), *conn), (partial(R::Object{{"tables_created", 1}})));
    TEST_DO(auto tbl2 = (R::db("test").table("test2")));
    TEST_EQ(maybe_run(tbl.insert(R::object("id", 0, "a", 0)), *conn), (R::Object{{"deleted", 0}, {"replaced", 0}, {"unchanged", 0}, {"errors", 0}, {"skipped", 0}, {"inserted", 1}}));
    TEST_EQ(maybe_run(tbl.count(), *conn), (1));
    TEST_EQ(maybe_run(tbl.insert(R::object("id", 1, "a", 1), R::OptArgs{{"durability", R::expr("hard")}}), *conn), (R::Object{{"deleted", 0}, {"replaced", 0}, {"unchanged", 0}, {"errors", 0}, {"skipped", 0}, {"inserted", 1}}));
    TEST_EQ(maybe_run(tbl.count(), *conn), (2));
    TEST_EQ(maybe_run(tbl.insert(R::object("id", 2, "a", 2), R::OptArgs{{"durability", R::expr("soft")}}), *conn), (R::Object{{"deleted", 0}, {"replaced", 0}, {"unchanged", 0}, {"errors", 0}, {"skipped", 0}, {"inserted", 1}}));
    TEST_EQ(maybe_run(tbl.count(), *conn), (3));
    TEST_EQ(maybe_run(tbl.insert(R::object("id", 3, "a", 3), R::OptArgs{{"durability", R::expr("wrong")}}), *conn), (err("ReqlQueryLogicError", "Durability option `wrong` unrecognized (options are \"hard\" and \"soft\").", R::Array{0})));
    TEST_EQ(maybe_run(tbl.count(), *conn), (3));
    TEST_EQ(maybe_run(tbl.get(2).delete_(), *conn), (R::Object{{"deleted", 1}, {"replaced", 0}, {"unchanged", 0}, {"errors", 0}, {"skipped", 0}, {"inserted", 0}}));
    TEST_EQ(maybe_run(tbl.insert(R::array(R::object("id", 2, "a", 2), R::object("id", 3, "a", 3))), *conn), (R::Object{{"deleted", 0}, {"replaced", 0}, {"unchanged", 0}, {"errors", 0}, {"skipped", 0}, {"inserted", 2}}));
    TEST_EQ(maybe_run(tbl2.insert(tbl), *conn), (R::Object{{"deleted", 0}, {"replaced", 0}, {"unchanged", 0}, {"errors", 0}, {"skipped", 0}, {"inserted", 4}}));
    TEST_EQ(maybe_run(tbl.insert(R::object("id", 2, "b", 20)), *conn), (R::Object{{"first_error", "Duplicate primary key `id`:\x0a{\x0a\x09\"a\":\x09\x32,\x0a\x09\"id\":\x09\x32\x0a}\x0a{\x0a\x09\"b\":\x09\x32\x30,\x0a\x09\"id\":\x09\x32\x0a}"}, {"deleted", 0}, {"replaced", 0}, {"unchanged", 0}, {"errors", 1}, {"skipped", 0}, {"inserted", 0}}));
    TEST_EQ(maybe_run(tbl.insert(R::object("id", 2, "b", 20), R::OptArgs{{"conflict", R::expr("error")}}), *conn), (R::Object{{"first_error", "Duplicate primary key `id`:\x0a{\x0a\x09\"a\":\x09\x32,\x0a\x09\"id\":\x09\x32\x0a}\x0a{\x0a\x09\"b\":\x09\x32\x30,\x0a\x09\"id\":\x09\x32\x0a}"}, {"deleted", 0}, {"replaced", 0}, {"unchanged", 0}, {"errors", 1}, {"skipped", 0}, {"inserted", 0}}));
    TEST_EQ(maybe_run(tbl.insert(R::object("id", 15, "b", 20), R::OptArgs{{"conflict", R::expr("error")}}), *conn), (R::Object{{"deleted", 0}, {"replaced", 0}, {"unchanged", 0}, {"errors", 0}, {"skipped", 0}, {"inserted", 1}}));
    TEST_EQ(maybe_run(tbl.get(15), *conn), (R::Object{{"id", 15}, {"b", 20}}));
    TEST_EQ(maybe_run(tbl.insert(R::object("id", 2, "b", 20), R::OptArgs{{"conflict", R::expr("replace")}}), *conn), (R::Object{{"deleted", 0}, {"replaced", 1}, {"unchanged", 0}, {"errors", 0}, {"skipped", 0}, {"inserted", 0}}));
    TEST_EQ(maybe_run(tbl.get(2), *conn), (R::Object{{"id", 2}, {"b", 20}}));
    TEST_EQ(maybe_run(tbl.insert(R::object("id", 20, "b", 20), R::OptArgs{{"conflict", R::expr("replace")}}), *conn), (R::Object{{"deleted", 0}, {"replaced", 0}, {"unchanged", 0}, {"errors", 0}, {"skipped", 0}, {"inserted", 1}}));
    TEST_EQ(maybe_run(tbl.get(20), *conn), (R::Object{{"id", 20}, {"b", 20}}));
    TEST_EQ(maybe_run(tbl.insert(R::object("id", 2, "c", 30), R::OptArgs{{"conflict", R::expr("update")}}), *conn), (R::Object{{"deleted", 0}, {"replaced", 1}, {"unchanged", 0}, {"errors", 0}, {"skipped", 0}, {"inserted", 0}}));
    TEST_EQ(maybe_run(tbl.get(2), *conn), (R::Object{{"id", 2}, {"b", 20}, {"c", 30}}));
    TEST_EQ(maybe_run(tbl.insert(R::object("id", 30, "b", 20), R::OptArgs{{"conflict", R::expr("update")}}), *conn), (R::Object{{"deleted", 0}, {"replaced", 0}, {"unchanged", 0}, {"errors", 0}, {"skipped", 0}, {"inserted", 1}}));
    TEST_EQ(maybe_run(tbl.get(30), *conn), (R::Object{{"id", 30}, {"b", 20}}));
    TEST_EQ(maybe_run(tbl.insert(R::object("id", 3, "a", 3), R::OptArgs{{"conflict", R::expr("wrong")}}), *conn), (err("ReqlQueryLogicError", "Conflict option `wrong` unrecognized (options are \"error\", \"replace\" and \"update\").", R::Array{0})));
    TEST_DO(auto tblpkey = (R::db("test").table("testpkey")));
    TEST_EQ(maybe_run(R::db("test").table_create("testpkey", R::OptArgs{{"primary_key", R::expr("foo")}}), *conn), (partial(R::Object{{"tables_created", 1}})));
    TEST_EQ(maybe_run(tblpkey.insert(R::object()), *conn), (R::Object{{"deleted", 0}, {"replaced", 0}, {"generated_keys", arrlen(1, uuid())}, {"unchanged", 0}, {"errors", 0}, {"skipped", 0}, {"inserted", 1}}));
    TEST_EQ(maybe_run(tblpkey, *conn), (R::Array{R::Object{{"foo", uuid()}}}));
    TEST_EQ(maybe_run(tblpkey.insert(R::object("b", 20), R::OptArgs{{"conflict", R::expr("replace")}}), *conn), (R::Object{{"deleted", 0}, {"replaced", 0}, {"generated_keys", arrlen(1, uuid())}, {"unchanged", 0}, {"errors", 0}, {"skipped", 0}, {"inserted", 1}}));
    TEST_EQ(maybe_run(tblpkey.insert(R::object("b", 20), R::OptArgs{{"conflict", R::expr("update")}}), *conn), (R::Object{{"deleted", 0}, {"replaced", 0}, {"generated_keys", arrlen(1, uuid())}, {"unchanged", 0}, {"errors", 0}, {"skipped", 0}, {"inserted", 1}}));
    TEST_EQ(maybe_run(R::db("test").table_drop("testpkey"), *conn), (partial(R::Object{{"tables_dropped", 1}})));
    TEST_EQ(maybe_run(tbl.for_each([=](R::Var row){ return tbl2.insert((*row).merge(R::object("id", (*row)["id"] + 100))); }), *conn), (R::Object{{"deleted", 0}, {"replaced", 0}, {"unchanged", 0}, {"errors", 0}, {"skipped", 0}, {"inserted", 7}}));
    TEST_EQ(maybe_run(tbl.insert(R::object("value", R::minval)), *conn), (partial(R::Object{{"errors", 1}, {"first_error", "`r.minval` and `r.maxval` cannot be written to disk."}})));
    TEST_EQ(maybe_run(tbl.insert(R::object("value", R::maxval)), *conn), (partial(R::Object{{"errors", 1}, {"first_error", "`r.minval` and `r.maxval` cannot be written to disk."}})));
    TEST_EQ(maybe_run(tbl.insert(R::array(R::object("id", 666), R::object("id", 666)), R::OptArgs{{"return_changes", R::expr("always")}}), *conn), (R::Object{{"changes", R::Array{R::Object{{"new_val", R::Object{{"id", 666}}}, {"old_val", R::Nil()}}, R::Object{{"error", "Duplicate primary key `id`:\x0a{\x0a\x09\"id\":\x09\x36\x36\x36\x0a}\x0a{\x0a\x09\"id\":\x09\x36\x36\x36\x0a}"}, {"new_val", R::Object{{"id", 666}}}, {"old_val", R::Object{{"id", 666}}}}}}, {"deleted", 0}, {"errors", 1}, {"first_error", "Duplicate primary key `id`:\x0a{\x0a\x09\"id\":\x09\x36\x36\x36\x0a}\x0a{\x0a\x09\"id\":\x09\x36\x36\x36\x0a}"}, {"inserted", 1}, {"replaced", 0}, {"skipped", 0}, {"unchanged", 0}}));
    TEST_EQ(maybe_run(tbl.insert(R::range(1, 100).map([=](R::Var i){ return R::object("id", R::expr(100) + *i, "ordered-num", *i); }), R::OptArgs{{"return_changes", R::expr("always")}}), *conn), (partial(R::Object{{"changes", R::range(1, 100).map([=](R::Var i){ return R::object("old_val", R::Nil(), "new_val", R::object("id", R::expr(100) + *i, "ordered-num", *i)); })}})));
    TEST_EQ(maybe_run(tbl.insert(R::range(1, 100).map([=](R::Var i){ return R::object("id", R::array(1, "blah", R::expr(200) + *i), "ordered-num", *i); }), R::OptArgs{{"return_changes", R::expr("always")}}), *conn), (partial(R::Object{{"changes", R::range(1, 100).map([=](R::Var i){ return R::object("old_val", R::Nil(), "new_val", R::object("id", R::array(1, "blah", R::expr(200) + *i), "ordered-num", *i)); })}})));
    TEST_EQ(maybe_run(tbl.insert(R::range(1, 100).map([=](R::Var i){ return R::object("id", R::array(1, "blah", R::expr(300) + *i), "ordered-num", *i); }), R::OptArgs{{"return_changes", R::expr(true)}}), *conn), (partial(R::Object{{"changes", R::range(1, 100).map([=](R::Var i){ return R::object("old_val", R::Nil(), "new_val", R::object("id", R::array(1, "blah", R::expr(300) + *i), "ordered-num", *i)); })}})));
    TEST_EQ(maybe_run(tbl.insert(R::range(1, 100).map([=](R::Var i){ return R::object("id", R::expr(100) + *i, "ordered-num", *i); }), R::OptArgs{{"return_changes", R::expr("always")}}), *conn), (partial(R::Object{{"changes", R::range(1, 100).map([=](R::Var i){ return R::object("old_val", R::object("id", R::expr(100) + *i, "ordered-num", *i), "new_val", R::object("id", R::expr(100) + *i, "ordered-num", *i), "error", (((((((R::expr("Duplicate primary key `id`:\x0a{\x0a\x09\"id\":\x09") + str(R::expr(100) + *i)) + ",\x0a\x09\"ordered-num\":\x09") + str(*i)) + "\x0a}\x0a{\x0a\x09\"id\":\x09") + str(R::expr(100) + *i)) + ",\x0a\x09\"ordered-num\":\x09") + str(*i)) + "\x0a}"); })}})));
    TEST_EQ(maybe_run(tbl.insert(R::array(R::object("id", 123), R::object("id", repeat("a", 500)), R::object("id", 321)), R::OptArgs{{"return_changes", R::expr("always")}}), *conn), (R::Object{{"changes", R::Array{R::Object{{"error", "Duplicate primary key `id`:\x0a{\x0a\x09\"id\":\x09\x31\x32\x33,\x0a\x09\"ordered-num\":\x09\x32\x33\x0a}\x0a{\x0a\x09\"id\":\x09\x31\x32\x33\x0a}"}, {"new_val", R::Object{{"id", 123}, {"ordered-num", 23}}}, {"old_val", R::Object{{"id", 123}, {"ordered-num", 23}}}}, R::Object{{"error", "Primary key too long (max 127 characters): \"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\""}, {"new_val", R::Nil()}, {"old_val", R::Nil()}}, R::Object{{"new_val", R::Object{{"id", 321}}}, {"old_val", R::Nil()}}}}, {"deleted", 0}, {"errors", 2}, {"first_error", "Primary key too long (max 127 characters): \"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\""}, {"inserted", 1}, {"replaced", 0}, {"skipped", 0}, {"unchanged", 0}}));
    TEST_EQ(maybe_run(tbl.insert(R::range(1, 100).map([=](R::Var i){ return R::object("id", R::expr(100) + *i, "ordered-num", *i); }), R::OptArgs{{"return_changes", R::expr(true)}}), *conn), (partial(R::Object{{"changes", R::Array{}}})));
    TEST_EQ(maybe_run(tbl.insert(R::object("a", R::minval), R::OptArgs{{"return_changes", R::expr("always")}}), *conn), (partial(R::Object{{"changes", R::Array{R::Object{{"old_val", R::Nil()}, {"new_val", R::Nil()}, {"error", "`r.minval` and `r.maxval` cannot be written to disk."}}}}})));
    TEST_EQ(maybe_run(tbl.insert(R::object("id", 42, "foo", 1, "bar", 1)), *conn), (partial(R::Object{{"inserted", 1}})));
    TEST_EQ(maybe_run(tbl.insert(R::object("id", 42, "foo", 5, "bar", 5), R::OptArgs{{"conflict", R::expr([=](R::Var id, R::Var old_row, R::Var new_row){ return (*old_row).merge((*new_row).pluck("bar")); })}}), *conn), (partial(R::Object{{"replaced", 1}})));
    TEST_EQ(maybe_run(tbl.get(42), *conn), (R::Object{{"id", 42}, {"foo", 1}, {"bar", 5}}));
    TEST_EQ(maybe_run(tbl.insert(R::object("id", 42, "foo", 1, "bar", 1), R::OptArgs{{"conflict", R::expr([=](R::Var a, R::Var b, R::Var c){ return R::expr(2); })}}), *conn), (partial(R::Object{{"first_error", "Inserted value must be an OBJECT (got NUMBER):\x0a\x32"}})));
    TEST_EQ(maybe_run(tbl.insert(R::object("id", 42), R::OptArgs{{"conflict", R::expr([=](R::Var a, R::Var b){ return *a; })}}), *conn), (err("ReqlQueryLogicError", "The conflict function passed to `insert` should expect 3 arguments.")));
    TEST_EQ(maybe_run(tbl.insert(R::object("id", 42), R::OptArgs{{"conflict", R::expr([=](R::Var a, R::Var b, R::Var c){ return tbl.get(42); })}}), *conn), (err("ReqlQueryLogicError", "The conflict function passed to `insert` must be deterministic.")));
    TEST_EQ(maybe_run(tbl.insert(R::object("id", 42), R::OptArgs{{"conflict", R::expr([=](R::Var a, R::Var b, R::Var c){ return R::object("id", 42, "num", "424"); })}}), *conn), (partial(R::Object{{"replaced", 1}})));
    TEST_EQ(maybe_run(tbl.get(42), *conn), (R::Object{{"id", 42}, {"num", "424"}}));
    TEST_EQ(maybe_run(R::minval, *conn), (err("ReqlQueryLogicError", "Cannot convert `r.minval` to JSON.")));
    TEST_EQ(maybe_run(R::maxval, *conn), (err("ReqlQueryLogicError", "Cannot convert `r.maxval` to JSON.")));
    TEST_EQ(maybe_run(R::db("test").table_drop("test2"), *conn), (partial(R::Object{{"tables_dropped", 1}})));
    exit_section();
}