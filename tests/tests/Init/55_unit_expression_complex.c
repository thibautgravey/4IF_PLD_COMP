int main() {
    int x = 0, y = !x;
    int g = -(-(y + 30));
    int h = !!g;
    return h + g + y;
}
