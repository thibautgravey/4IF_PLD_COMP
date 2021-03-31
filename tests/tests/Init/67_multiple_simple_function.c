int sum1(int a, int b) {
    return a + b + 3;
}

int sum2(int a, int b) {
    return a + b + 8;
}

int sum3(int b, int c) {
    return sum1(b, 5) + sum2(c, 6);
}

int main() {
    return sum3(56, 45);
}