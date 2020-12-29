class Point{
private:
    double x, y;

public:
    Point();
    Point(double another_point_x, double another_point_y);
    Point(const Point& another_point);

    double get_x() const;
    double get_y() const;

    friend class FigureDEGF;
};