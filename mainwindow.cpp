#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->l_result->setText("0");
    ui->l_memory->setText("");
    ui->l_formula->setText("");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetDigitKeyCallback(std::function<void (int)> cb) {
    digit_cb_ = cb;
}

void MainWindow::SetProcessOperationKeyCallback(std::function<void (Operation)> cb) {
    operation_cb_ = cb;
}

void MainWindow::SetProcessControlKeyCallback(std::function<void (ControlKey)> cb) {
    control_cb_ = cb;
}

void MainWindow::SetControllerCallback(std::function<void (ControllerType)> cb) {
    controller_cb_ = cb;
}

void MainWindow::SetInputText(const std::string &text) {
    QFont font = ui->l_result->font();
    ui->l_result->setStyleSheet("");
    ui->l_result->setFont(font);
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetErrorText(const std::string &text) {
    ui->l_result->setStyleSheet("color: red;");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetFormulaText(const std::string &text) {
    ui->l_formula->setText(QString::fromStdString(text));
}

void MainWindow::SetMemText(const std::string &text) {
    ui->l_memory->setText(QString::fromStdString(text));
}

void MainWindow::SetExtraKey(const std::optional<std::string> &key)
{
    ui->tb_extra->setVisible(key != std::nullopt);
    if (ui->cmb_controller->currentText() == "Rational") {
        ui->tb_extra->setText("/");
    }
    else {
        ui->tb_extra->setText(".");
    }
}

void MainWindow::on_btn_num_0_clicked() {
    digit_cb_(0);
}

void MainWindow::on_btn_num_1_clicked() {
    digit_cb_(1);
}

void MainWindow::on_btn_num_2_clicked() {
    digit_cb_(2);
}

void MainWindow::on_btn_num_3_clicked() {
    digit_cb_(3);
}

void MainWindow::on_btn_num_4_clicked() {
    digit_cb_(4);
}

void MainWindow::on_btn_num_5_clicked() {
    digit_cb_(5);
}

void MainWindow::on_btn_num_6_clicked() {
    digit_cb_(6);
}

void MainWindow::on_btn_num_7_clicked() {
    digit_cb_(7);
}

void MainWindow::on_btn_num_8_clicked() {
    digit_cb_(8);
}

void MainWindow::on_btn_num_9_clicked() {
    digit_cb_(9);
}

void MainWindow::on_btn_equal_clicked() {
    control_cb_(ControlKey::EQUALS);
}

void MainWindow::on_btn_plus_minus_clicked() {
    control_cb_(ControlKey::PLUS_MINUS);
}

void MainWindow::on_btn_backspace_clicked() {
    control_cb_(ControlKey::BACKSPACE);
}

void MainWindow::on_btn_mult_clicked() {
    operation_cb_(Operation::MULTIPLICATION);
}

void MainWindow::on_btn_sub_clicked() {
    operation_cb_(Operation::SUBTRACTION);
}

void MainWindow::on_btn_add_clicked() {
    operation_cb_(Operation::ADDITION);
}

void MainWindow::on_btn_pow_clicked() {
    operation_cb_(Operation::POWER);
}

void MainWindow::on_btn_div_clicked() {
    operation_cb_(Operation::DIVISION);
}

void MainWindow::on_btn_c_clicked() {
    control_cb_(ControlKey::CLEAR);
}

void MainWindow::on_btn_ms_clicked() {
    control_cb_(ControlKey::MEM_SAVE);
}

void MainWindow::on_btn_mc_clicked() {
    control_cb_(ControlKey::MEM_CLEAR);
}

void MainWindow::on_btn_mr_clicked() {
    control_cb_(ControlKey::MEM_LOAD);
}

void MainWindow::on_tb_extra_clicked() {
    control_cb_(ControlKey::EXTRA_KEY);
}

void MainWindow::on_cmb_controller_currentTextChanged(const QString &textType)
{
    ControllerType type = ControllerType::DOUBLE;
    if (textType == "double") {
        type = ControllerType::DOUBLE;
    }
    else if (textType == "float") {
        type = ControllerType::FLOAT;
    }
    else if (textType == "uint8_t") {
        type = ControllerType::UINT8_T;
    }
    else if (textType == "int") {
        type = ControllerType::INT;
    }
    else if (textType == "int64_t") {
        type = ControllerType::INT64_T;
    }
    else if (textType == "size_t") {
        type = ControllerType::SIZE_T;
    }
    else if (textType == "Rational") {
        type = ControllerType::RATIONAL;
    }

    controller_cb_(type);
}

