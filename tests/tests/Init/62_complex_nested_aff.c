int main() {
    int test1;
    int test2 = 4;
    int test3;
    int res = test1 = 5 + 2 * (test3 = test2 * 4);
    return res + test1 + test2 + test3;
}