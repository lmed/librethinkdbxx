// auto-generated by yaml_to_cxx.py from test/upstream/regression/4462.yaml
#include "testlib.h"
void test_upstream_regression_4462() {
    enter_section("test_upstream_regression_4462: 4462 -- Coroutine stacks should not overflow during datum serialization");
    temp_table tbl_table;
    R::Query tbl = tbl_table.table();
    exit_section();
}