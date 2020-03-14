// GPA_CalculatorConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
	vector <vector<double>
	{grade, credit_hours, effective_hours}
	{{ (A || 92) , 3.0 , 12.0},
	{ , , },
	{ , , }}
*/

#include <iostream>
#include <iomanip> // Required for std::setprecision()
#include <vector>
#include <cctype>
#include <string>

void menuDisplay(std::vector<std::vector<double>> classes) {
	if (classes.size() == 0)
		std::cout << "Currently there are no grades entered."
				<< "\nWoud you like to enter a grade?(Y/N)";
	else {
		std::cout << "The grades you have entered are:\n\t";
		for (auto element : classes) {
			std::cout << element.at(0) << " ";
		}
		std::cout << "\nWould you like to add another grade?(Y/N)";
	}
}

bool runCheck() {
	bool keep_running{ 1 }, valid_input{ 0 };
	char input{};

	std::cin >> input;
	input = toupper(input);
	do {
		switch (input) {
			case 'Y':
				keep_running = 1;
				valid_input = 1;
				break;
			case 'N':
				keep_running = 0;
				valid_input = 1;
				break;
			default:
				std::cout << "\nYou did not enter a valid answer.\nPlease enter Y or N.";
				std::cout << std::endl;
				valid_input = 0;
		}
	} while (valid_input == 0);
	return keep_running;
}

// Takes a user's input from the user as a string and converts it into a 
// char 
double eval_grade(std::string input){
	double grade_weight;

	if (input.compare("A") == 1)
		grade_weight = 4.0;
	else if (input.compare("B") == 1)
		grade_weight = 3.0;
	else if (input.compare("C") == 1)
		grade_weight = 2.0;
	else if (input.compare("D") == 1)
		grade_weight = 1.0;
	else if (input.compare("F") == 1)
		grade_weight = 0.0;
	else {
		double number_grade = std::stod(input);
		if (number_grade >= 90)
			grade_weight = 4.0;
		else if (number_grade >= 80)
			grade_weight = 3.0;
		else if (number_grade >= 70)
			grade_weight = 2.0;
		else if (number_grade >= 60)
			grade_weight = 1.0;
		else
			grade_weight = 0.0;
	}
	return grade_weight;
}

// {grade, grade_weight, class_weight, effective_hours}
std::vector <std::vector<double>> add_class(std::vector<std::vector<double>> classes) {
	std::cout << "Please enter a number grade you received in the class."
		//<< "\nEnter either a number grade or letter grade." letter grades ar not supported yet.
		<< "\nYour grade: ";
	
	std::string grade;
	std::cin >> grade;
	double grade_weight = eval_grade(grade);
	double number_grade = stod(grade);

	double class_weight;
	std::cout << "How many credit hours is your class worth?";
	std::cin >> class_weight;

	double effective_hours{ grade_weight * class_weight };
	std::vector<double> single_class{ number_grade, grade_weight, class_weight, effective_hours };
	classes.push_back(single_class);
	return classes;
}

double determineGPA(std::vector<std::vector<double>> classes) {
	double gpa{ 0.0 }, total_hours{ 0.0 }, total_eff_hours{ 0.0 };
	for (auto course : classes) {
		total_hours += course.at(2);
		total_eff_hours += course.at(3);
	}
	gpa = total_eff_hours / total_hours;
	return gpa;
}

void reportGPA(double gpa) {
	std::cout << "\nYour current GPA is " << std::setprecision(3) << gpa << std::endl;
}
void separator() {
	std::cout << "\n=======================================================\n" << std::endl;
}

int main()
{
	bool run{ 1 };
	double gpa{ 0.0 };
	std::vector<std::vector<double>> classes;
	do {
		menuDisplay(classes);
		run = runCheck();
		if (run == 1) {
			classes = add_class(classes);
			gpa = determineGPA(classes);
			reportGPA(gpa);
		}
		separator();
	} while (run == 1);
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
