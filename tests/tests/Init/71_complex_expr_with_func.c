int multPlus(int a, int b) {
    a = a + 8;
    b = b + a;
    return a * b;
}

int sumPlus(int a, int b) {
    a = a + 3;
    b = b - a;
    return a + b;
}

int main() {
    int a = 4;
    int b = 12;
    int c = (1 + 3) * ((4 + 5) * 4) + (multPlus(a + 4, 4) - 7 * sumPlus(b, 34));
}