#define M 5
#define C 5
#define MAP(val, m, c) val *m + c

int main(int argc, char *argv[])
{
    int x = 2;
    int y = MAP(x, M, C);
    return 0;
}