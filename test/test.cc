#include <signal.h>

#include <cstdio>

#include <rethinkdb.h>

namespace R = RethinkDB;

R::OutputFileDescriptor out(1);

void test_json(const char* string) {
    printf("Round-trip %s: ", string);
    fflush(stdout);
    R::write_datum(R::read_datum(string), out);
    puts("");
}

void test_connect() {
    R::Connection conn = R::connect();
    printf("Waiting for result (1 + 2): ");
    fflush(stdout);
    write_datum((R::expr(1) + 2).run(conn), out);
    printf("\nWaiting for result (r.table('test').count()): ");
    fflush(stdout);
    write_datum(R::table("test").count().run(conn), out);
    puts("");
}

int main() {
    signal(SIGPIPE, SIG_IGN);
    try {
        test_connect();
        test_json("null");
        test_json("1.2");
        test_json("1.2e20");
        test_json("true");
        test_json("false");
        test_json("\"\"");
        test_json("\"\\u1234\"");
        test_json("\"\\\"\"");
        test_json("\"foobar\"");
        test_json("[]");
        test_json("[1]");
        test_json("[1,2,3,4]");
        test_json("{}");
        test_json("{\"a\":1}");
        test_json("{\"a\":1,\"b\":2,\"c\":3}");
    } catch (const R::Error& error) {
        printf("Tests failed: %s\n", error.message.c_str());
    }
}