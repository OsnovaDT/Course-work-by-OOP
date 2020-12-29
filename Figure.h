#include <iostream>

#include "Point.h"

using std::string;

class FigureDEGF
{
private:
	Point d, e, g, f;

public:
	FigureDEGF();
	FigureDEGF(Point d, Point e, Point g, Point f);
	FigureDEGF(const FigureDEGF& figure_degf);

	bool is_figure_degf();

	double get_degf_square();
	double get_monte_carlo_square(int N, int& M);

	void print_results_for_square();

private:
	void set_point_coordinates(char point_name, Point& point);
	void set_all_points_coordinates();
	void show_main_menu();
	void show_menu_for_input_data();
};