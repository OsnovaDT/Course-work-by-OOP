#include "Point.h"

Point::Point(){
    x = 0, y = 0;
}

Point::Point(double another_point_x, double another_point_y){
    x = another_point_x;
    y = another_point_y;
}

Point::Point(const Point& another_point){
    x = another_point.x;
    y = another_point.y;
}

double Point::get_x() const{
    return x;
}

double Point::get_y() const{
    return y;
}