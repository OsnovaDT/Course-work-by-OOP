#include <iostream>
#include <ctime>

#include "Figure.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;


double rand_for_double(double start, double stop){
	return start + (rand() % static_cast<unsigned int>((stop - start) * 1000)) / 1000.;
}


FigureDEGF::FigureDEGF(){
	show_main_menu();
}


FigureDEGF::FigureDEGF(Point d, Point e, Point g, Point f){
	this->d = Point(d);
	this->e = Point(e);
	this->g = Point(g);
	this->f = Point(f);
}


FigureDEGF::FigureDEGF(const FigureDEGF& rect){
	this->d = Point(rect.d);
	this->e = Point(rect.e);
	this->g = Point(rect.g);
	this->f = Point(rect.f);
}


bool FigureDEGF::is_figure_degf(){
	bool x_condition = (g.get_x() < f.get_x()) && (f.get_x() < e.get_x()) && (e.get_x() < d.get_x()) && (e.get_x() - f.get_x() == d.get_x() - e.get_x());
	bool y_condition = (g.get_y() > f.get_y()) && (e.get_y() > g.get_y()) && (d.get_y() == f.get_y()) && (e.get_x() - f.get_x() == e.get_y() - f.get_y());

	return  x_condition && y_condition;
}


double FigureDEGF::get_degf_square(){
	// Counting square of gef by Heron's formula
	double ge = sqrt(pow(e.get_x() - g.get_x(), 2) + pow(e.get_y() - g.get_y(), 2));
	double gf = sqrt(pow(f.get_x() - g.get_x(), 2) + pow(g.get_y() - f.get_y(), 2));
	double ef = sqrt(pow(e.get_x() - f.get_x(), 2) + pow(e.get_y() - f.get_y(), 2));

	double gef_half_P = (ge + gf + ef) / 2;

	double gef_S = sqrt(gef_half_P * (gef_half_P - ge) * (gef_half_P - gf) * (gef_half_P - ef));

	// Counting square of feo
	double feo_S = pow(e.get_x() - f.get_x(), 2) / 2;

	// Counting square of eod
	double eod_S = 3.14 * pow(d.get_x() - e.get_x(), 2) / 4;

	return gef_S + feo_S + eod_S;
}


double FigureDEGF::get_monte_carlo_square(int N, int& M){
	double k_ge = (e.get_y() - g.get_y()) / (e.get_x() - g.get_x());
	double b_ge = g.get_y() - g.get_x() * (e.get_y() - g.get_y()) / (e.get_x() - g.get_x());

	double k_gf = (f.get_y() - g.get_y()) / (f.get_x() - g.get_x());
	double b_gf = g.get_y() - g.get_x() * (f.get_y() - g.get_y()) / (f.get_x() - g.get_x());

	for (int i = 0; i < N; i++)
	{
		double x = (rand_for_double(0, 1) * (d.get_x() - g.get_x())) + g.get_x();
		double y = (rand_for_double(0, 1) * (e.get_y() - f.get_y())) + f.get_y();

		bool is_point_in_gefo = (y <= (k_ge * x + b_ge) && ((x < f.get_x() && y >= (k_gf * x + b_gf)) || (x >= f.get_x() && x <= e.get_x())));
		bool is_point_in_eod = (x >= e.get_x()) && (y <= sqrt(pow(e.get_x() - f.get_x(), 2) - pow(x - e.get_x(), 2)) + f.get_y());

		if (is_point_in_gefo || is_point_in_eod)
			M++;
	}
	return double(M) / double(N) * (d.get_x() - g.get_x()) * (e.get_y() - f.get_y());
}


void FigureDEGF::set_point_coordinates(char point_name, Point& point){
	cout << "Координата x для точки " << point_name << ": ";
	string x;
	cin >> x;

	cout << "Координата y для точки " << point_name << ": ";
	string y;
	cin >> y;

	point.x = atof(x.c_str());
	point.y = atof(y.c_str());
}


void FigureDEGF::set_all_points_coordinates(){
	while (!is_figure_degf())
	{
		set_point_coordinates('d', d);
		set_point_coordinates('e', e);
		set_point_coordinates('g', g);
		set_point_coordinates('f', f);

		if (!is_figure_degf())
			cout << "Введённые координаты не соответствую фигуре degf!\n";
	}
}


void FigureDEGF::print_results_for_square(){
	double degf_S = get_degf_square();
	cout << "\nТочная площадь фигуры degf = " << degf_S << "\n\n";

	cout << "Результаты нахождения площади методом Монте-Карло:" << endl;

	for (int i = 0; i < 5; i++)
	{
		int start_time = clock();
		int M = 0;
		
		double degf_monte_carlo_S = get_monte_carlo_square(int(pow(10, 3 + i)), M);

		int end_time = clock();

		double inaccuracy = abs(1 - degf_monte_carlo_S / degf_S) * 100;

		cout << i + 1 << ") Площадь = " << degf_monte_carlo_S << "\tПогрешность = " << inaccuracy << "%" << endl;
		cout << "Время = " << end_time - start_time << " мс\tN = 10^" << (3 + i) << "\tM = " << M << "\n\n";
	}
}


void FigureDEGF::show_menu_for_input_data() {
	string user_choice;

	while (true) {
		cout << "1 - Применить значения по умолчанию\n2 - Ввести значения\n3 - Выход\n\nВаш выбор: ";
		cin >> user_choice;

		if (user_choice == "1") {
			system("cls");

			d = Point(35, 10);
			e = Point(25, 20);
			g = Point(5, 15);
			f = Point(15, 10);

			print_results_for_square();
		}

		else if (user_choice == "2") {
			system("cls");

			d = Point(0, 0);
			e = Point(0, 0);
			g = Point(0, 0);
			f = Point(0, 0);

			set_all_points_coordinates();
			print_results_for_square();
		}

		else if (user_choice == "3")
			exit(1);

		else {
			system("cls");
			cout << "Такого варианта нет" << endl;
		}
	}
}


void FigureDEGF::show_main_menu(){
	string user_choice;

	while (true) {
		cout << "1 - Вычислить площадь\n2 - Выход\n\nВаш выбор: ";
		cin >> user_choice;

		if (user_choice == "1") {
			system("cls");
			show_menu_for_input_data();
		}

		else if (user_choice == "2") 
			exit(1);

		else {
			system("cls");
			cout << "Такого варианта нет" << endl;
		}
	}
}