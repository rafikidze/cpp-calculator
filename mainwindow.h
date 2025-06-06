#pragma once

#include "calculator.h"
#include "enums.h"
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

    void SetDigitKeyCallback(std::function<void(int key)> cb);
    void SetProcessOperationKeyCallback(std::function<void(Operation key)> cb);
    void SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb);
    void SetControllerCallback(std::function<void(ControllerType controller)> cb);

    void SetInputText(const std::string& text);
    void SetErrorText(const std::string& text);
    void SetFormulaText(const std::string& text);
    void SetMemText(const std::string& text);
    void SetExtraKey(const std::optional<std::string>& key);

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
    void on_tb_extra_clicked();
    void on_cmb_controller_currentTextChanged(const QString &textType);

private:


private:
    Ui::MainWindow* ui;
    QString input_number_;

    std::function<void(int)> digit_cb_;
    std::function<void(Operation key)> operation_cb_;
    std::function<void(ControlKey key)> control_cb_;
    std::function<void (ControllerType)> controller_cb_;

};
