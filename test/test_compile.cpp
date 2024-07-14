#include <dynafen.hxx>

rdynafen<int, int, int> multiply("./libtestlib.so", "multiply");
vdynafen<int> set("./libtestlib.so", "set");
rdynafen<int> get("./libtestlib.so", "set");
vdynafen do_nothing("./libtestlib.so", "do_nothing");

bool test_1()
{
    int e = multiply(2, 2);
    return e == 4;
}

bool test_2()
{
    set(4);
    return true;
}

bool test_3()
{
    int e = get();
    return e == (4 * 2);
}

bool test_4()
{
    do_nothing();
    return true;
}

int main()
{
    return !(test_1() && test_2() && test_3() && test_4());
}