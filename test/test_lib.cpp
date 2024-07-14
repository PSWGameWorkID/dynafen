extern "C" int multiply(int a, int b);
extern "C" void set(int a);
extern "C" int get(void);
extern "C" void do_nothing(void);

static int set_data = 0;

int multiply(int a, int b)
{
    return a * b;
}

void set(int a)
{
    set_data = a * 2;
}

int get(void)
{
    return set_data;
}

void do_nothing(void)
{
    // Do nothing
}