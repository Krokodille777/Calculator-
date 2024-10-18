#include <iostream>
#include <cmath>
#include <string>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>

using namespace std;

class Calculator {
public:
    // Метод для сложения
    double add(double a, double b) {
        return a + b;
    }
    
    // Метод для вычитания
    double sub(double a, double b) {
        return a - b;
    }
    
    // Метод для умножения
    double mul(double a, double b) {
        return a * b;
    }
    
    // Метод для деления
    double div(double a, double b) {
        if (b != 0) {
            return a / b;
        } else {
            std::cout << "Error: Division by zero is not allowed!" << std::endl;
            return NAN; // Возвращаем Not-A-Number, если деление на ноль
        }
    }
    // Метод для возведения в степень
    double pow(double a, double b) {
        return std::pow(a, b);  // Используем std::pow
    }
    // Метод для квадратного корня
    double sqrt(double a) {
        if (a >= 0) {
            return std::sqrt(a);  // Используем std::sqrt
        } else {
            std::cout << "Error: Square root of a negative number is not allowed!" << std::endl;
            return NAN;
        }
    }
    // Метод для кубического корня
    double cbrt(double a) {
        return std::cbrt(a);  // Используем std::cbrt
    }
    
    // Метод для выполнения операции на основе оператора
    double calculate(double a, double b, const std::string& op) {
        if (op == "+") {
            return add(a, b);
        } else if (op == "-") {
            return sub(a, b);
        } else if (op == "*") {
            return mul(a, b);
        } else if (op == "/") {
            return div(a, b);
        } else if (op == "pow") {
            return pow(a, b);
        } else {
            std::cout << "Error: Invalid operator or wrong operation with two operands!" << std::endl;
            return NAN;
        }
    }
    // Метод для выполнения операций с одним аргументом
    double calculate(double a, const std::string& op) {
        if (op == "sqrt") {
            return sqrt(a);
        } else if (op == "cbrt") {
            return cbrt(a);
        } else {
            std::cout << "Error: Invalid operator for single operand!" << std::endl;
            return NAN;
        }
    }
};

class CalculatorUI : public Fl_Window {
private:
    Calculator calc;
    Fl_Input *input1, *input2;
    Fl_Output *output;
    Fl_Button *add_button, *sub_button, *mul_button, *div_button, *pow_button, *sqrt_button, *cbrt_button;

public:
    CalculatorUI() : Fl_Window(300, 400, "Calculator") {
        input1 = new Fl_Input(10, 10, 130, 30, "Number 1:");
        input2 = new Fl_Input(160, 10, 130, 30, "Number 2:");
        output = new Fl_Output(10, 50, 280, 30, "Result:");
        create_buttons();
    }

    void create_buttons() {
        add_button = new Fl_Button(10, 100, 60, 30, "+");
        sub_button = new Fl_Button(80, 100, 60, 30, "-");
        mul_button = new Fl_Button(150, 100, 60, 30, "*");
        div_button = new Fl_Button(220, 100, 60, 30, "/");
        pow_button = new Fl_Button(10, 140, 60, 30, "pow");
        sqrt_button = new Fl_Button(80, 140, 60, 30, "sqrt");
        cbrt_button = new Fl_Button(150, 140, 60, 30, "cbrt");

        add_button->callback(button_callback, (void*)"+");
        sub_button->callback(button_callback, (void*)"-");
        mul_button->callback(button_callback, (void*)"*");
        div_button->callback(button_callback, (void*)"/");
        pow_button->callback(button_callback, (void*)"pow");
        sqrt_button->callback(button_callback, (void*)"sqrt");
        cbrt_button->callback(button_callback, (void*)"cbrt");
    }

    static void button_callback(Fl_Widget* widget, void* data) {
        CalculatorUI* ui = (CalculatorUI*)widget->window();
        const char* op = (const char*)data;
        double a = atof(ui->input1->value());
        double b = atof(ui->input2->value());
        double result;

        if (strcmp(op, "sqrt") == 0 || strcmp(op, "cbrt") == 0) {
            result = ui->calc.calculate(a, op);
        } else {
            result = ui->calc.calculate(a, b, op);
        }

        char buffer[50];
        snprintf(buffer, sizeof(buffer), "%.2f", result);
        ui->output->value(buffer);
    }
};

int main() {
    CalculatorUI* calc_ui = new CalculatorUI();
    calc_ui->show();
    return Fl::run();
}