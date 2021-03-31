int toto(int a) {
    return a + 5;
}

int main() {
    int a;
    int b;
    b = 2 * 3 + (5 + (a = toto(3)));
    return a + b;
}
