#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

QString RemoveTrailingZeroes(const QString &text) {
    for (qsizetype i = 0; i < text.size(); ++i) {
        if (text[i] != '0') {
            return text.mid(i);
        }
    }
    return "";
}

QString NormalizeNumber(const QString &text) {
    if (text.isEmpty()) {
        return "0";
    }
    if (text.startsWith('.')) {
        // Рекурсивный вызов.
        return NormalizeNumber("0" + text);
    }
    if (text.startsWith('-')) {
        // Рекурсивный вызов.
        return "-" + NormalizeNumber(text.mid(1));
    }
    if (text.startsWith('0') && !text.startsWith("0.")) {
        return NormalizeNumber(RemoveTrailingZeroes(text));
    }
    return text;
}


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->l_result->setText("0");
    ui->l_memory->setText("");
    ui->l_formula->setText("");

    SetText("0");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_btn_equal_clicked()
{
    if (current_operation_ != Operation::NO_OPERATION) {
        ui->l_formula->setText(QString("%1 %2 %3 =").arg(calculator_.GetNumber())
                                                    .arg(OpToString(current_operation_))
                                                    .arg(active_number_));

        switch (current_operation_) {
        case Operation::NO_OPERATION : break;
        case Operation::ADDITION : calculator_.Add(active_number_); break;
        case Operation::DIVISION : calculator_.Div(active_number_);break;
        case Operation::MULTIPLICATION : calculator_.Mul(active_number_);break;
        case Operation::POWER : calculator_.Pow(active_number_);break;
        case Operation::SUBTRACTION : calculator_.Sub(active_number_);break;
        }
        active_number_ = calculator_.GetNumber();
        ui->l_result->setText(QString::number(active_number_));
        input_number_.clear();
        current_operation_ = Operation::NO_OPERATION;
    }
}

void MainWindow::SetText(const QString &text)
{
    input_number_ = NormalizeNumber(text);
    active_number_ = input_number_.toDouble();
    ui->l_result->setText(input_number_);
}

void MainWindow::AddText(const QString &suffix)
{
    input_number_.append(suffix);
    SetText(input_number_);
}

void MainWindow::SetOperation(Operation op)
{
    if (current_operation_ == Operation::NO_OPERATION) {
        calculator_.Set(active_number_);
    }
    current_operation_ = op;
    ui->l_formula->setText(QString("%1 %2").arg(calculator_.GetNumber()).arg(OpToString(op)));
    input_number_.clear();
}

QString MainWindow::OpToString(Operation op) const
{
    switch(op) {
    case Operation::NO_OPERATION: return "";
    case Operation::ADDITION: return "+";
    case Operation::DIVISION: return "÷";
    case Operation::MULTIPLICATION: return "×";
    case Operation::SUBTRACTION: return "−";
    case Operation::POWER: return "^";
    }
    return QString();
}

void MainWindow::on_btn_num_0_clicked()
{
    AddText("0");
}

void MainWindow::on_btn_num_1_clicked()
{
    AddText("1");
}

void MainWindow::on_btn_num_2_clicked()
{
    AddText("2");
}

void MainWindow::on_btn_num_3_clicked()
{
    AddText("3");
}

void MainWindow::on_btn_num_4_clicked()
{
    AddText("4");
}

void MainWindow::on_btn_num_5_clicked()
{
    AddText("5");
}

void MainWindow::on_btn_num_6_clicked()
{
    AddText("6");
}

void MainWindow::on_btn_num_7_clicked()
{
    AddText("7");
}

void MainWindow::on_btn_num_8_clicked()
{
    AddText("8");
}

void MainWindow::on_btn_num_9_clicked()
{
    AddText("9");
}

void MainWindow::on_btn_point_clicked()
{
    if (!input_number_.contains(".")) {
        AddText(".");
    }
}

void MainWindow::on_btn_plus_minus_clicked()
{
    if (input_number_.isEmpty()) {
        SetText(QString::number(-active_number_));
   } else {
       if (input_number_.startsWith("-")) {
           input_number_ = input_number_.mid(1);
       } else {
           input_number_ = "-" + input_number_;
       }
       SetText(input_number_);
   }
}

void MainWindow::on_btn_backspace_clicked()
{
    input_number_.chop(1);
    SetText(input_number_);
}

void MainWindow::on_btn_mult_clicked()
{
    SetOperation(Operation::MULTIPLICATION);
}

void MainWindow::on_btn_sub_clicked()
{
    SetOperation(Operation::SUBTRACTION);
}

void MainWindow::on_btn_add_clicked()
{
    SetOperation(Operation::ADDITION);
}

void MainWindow::on_btn_pow_clicked()
{
    SetOperation(Operation::POWER);
}

void MainWindow::on_btn_div_clicked()
{
    SetOperation(Operation::DIVISION);
}

void MainWindow::on_btn_c_clicked()
{
    current_operation_ = Operation::NO_OPERATION;
    ui->l_formula->clear();
    SetText("0");
}

void MainWindow::on_btn_ms_clicked()
{
    save_number_ = active_number_;
    ui->l_memory->setText("M");
    wasSaving_ = true;
}

void MainWindow::on_btn_mc_clicked()
{
    save_number_ = 0;
    ui->l_memory->clear();
    wasSaving_ = false;
}

void MainWindow::on_btn_mr_clicked()
{
    if (wasSaving_) {
        active_number_ = save_number_;
        ui->l_result->setText(QString::number(active_number_));
        input_number_.clear();
        wasSaving_ = false;
    }
}

