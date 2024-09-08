export module Point;

export namespace jod {
struct Point {
    Point Translate(int dx, int dy) {
        return {x + dx, y + dy};
    }

    int x {0};
    int y {0};
};
}