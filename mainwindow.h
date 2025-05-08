#pragma once

#include "calculator.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    enum class Operation {
        NO_OPERATION,
        ADDITION,
        SUBTRACTION,
        MULTIPLICATION,
        DIVISION,
        POWER
    };

private slots:
    void on_btn_equal_clicked();
    void on_btn_num_0_clicked();
    void on_btn_num_1_clicked();
    void on_btn_num_2_clicked();
    void on_btn_num_3_clicked();
    void on_btn_num_4_clicked();
    void on_btn_num_5_clicked();
    void on_btn_num_6_clicked();
    void on_btn_num_7_clicked();
    void on_btn_num_8_clicked();
    void on_btn_num_9_clicked();
    void on_btn_point_clicked();
    void on_btn_plus_minus_clicked();
    void on_btn_backspace_clicked();
    void on_btn_mult_clicked();
    void on_btn_sub_clicked();
    void on_btn_add_clicked();
    void on_btn_pow_clicked();
    void on_btn_div_clicked();
    void on_btn_c_clicked();
    void on_btn_ms_clicked();
    void on_btn_mc_clicked();
    void on_btn_mr_clicked();

private:
    void SetText(const QString& text);
    void AddText(const QString& suffix);
    void SetOperation(Operation op);
    QString OpToString(Operation op) const;

private:
    Ui::MainWindow* ui;
    Calculator calculator_;
    QString input_number_;
    double active_number_ = 0;
    double save_number_ = 0;
    bool wasSaving_ = false;
    Operation current_operation_ = Operation::NO_OPERATION;
};
