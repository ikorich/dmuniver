#include "dmwindow.h"
#include "ui_dmwindow.h"

void DmWindow::on_doubleSpinBox_T3_valueChanged(double value)
{
    dT3 = value;
    viborMaterialaZubchatihKoles();
}

void DmWindow::on_doubleSpinBox_n3_valueChanged(double value)
{
    dn3 = value;
    viborMaterialaZubchatihKoles();
}

void DmWindow::on_doubleSpinBox_u3_valueChanged(double value)
{
    du3 = value;
    viborMaterialaZubchatihKoles();
}

void DmWindow::on_spinBox_Litje_valueChanged(int value)
{
    iLitje = value;
    viborMaterialaZubchatihKoles();
}

void DmWindow::on_spinBox_HB1_valueChanged(int value)
{
    iHB1 = value;
    viborMaterialaZubchatihKoles();
}

void DmWindow::on_spinBox_HB2_valueChanged(int value)
{
    iHB2 = value;
    viborMaterialaZubchatihKoles();
}

void DmWindow::on_comboBox_Sb1_currentIndexChanged(QString value)
{
    iSb1 = value.toInt();
    viborMaterialaZubchatihKoles();
}

void DmWindow::on_comboBox_Sb2_currentIndexChanged(QString value)
{
    iSb2 = value.toInt();
    viborMaterialaZubchatihKoles();
}

void DmWindow::viborMaterialaZubchatihKoles()
{
    DopustimieNapryajeniyaIzgiba();
}

void DmWindow::DopustimieNapryajeniyaIzgiba()
{



































#ifdef TAB_CONTROL
    if (checkTab5())
        ui->tabWidget->setTabEnabled(5, true);
    else ui->tabWidget->setTabEnabled(5, false);
#else
    checkTab6();
#endif
}

bool DmWindow::checkTab6()
{
    bool    noErrors = true;
    int     iTempVal1 = 0;
    int     iTempVal2 = 0;
    double  dTempVal1 = 0.0;
    double  dTempVal2 = 0.0;

    if (dT3 != dValT3 || dn3 != dValN3 || du3 != dValI3)
    {
        ui->label_CheckVvod5->setVisible(true);
        noErrors = false;
    } else ui->label_CheckVvod5->setVisible(false);

    if (iLitje == 45)
    {
        iTempVal1 = 235;
        iTempVal2 = 207;
    }
    else
    {
        iTempVal1 = 207;
        iTempVal2 = 163;
    }

    if (iHB1 >= iTempVal2 && iHB1 <= iTempVal1)
    {
        ui->label_checkHB1->setVisible(false);
    }
    else
    {
        ui->label_checkHB1->setVisible(true);
        noErrors = false;
    }

    if (iHB2 >= iTempVal2 && iHB2 <= iTempVal1)
    {
        ui->label_checkHB2->setVisible(false);
    }
    else
    {
        ui->label_checkHB2->setVisible(true);
        noErrors = false;
    }

    if (iLitje == 35)
    {
        iTempVal1 = 500;
        iTempVal2 = 270;
    }
    else if (iLitje == 40)
    {
        iTempVal1 = 520;
        iTempVal2 = 295;
    }
    else if (iLitje == 45)
    {
        iTempVal1 = 680;
        iTempVal2 = 440;
    }

    if (iSb1 != iTempVal1)
    {
        ui->label_checkSb1->setVisible(true);
        noErrors = false;
    }
    else ui->label_checkSb1->setVisible(false);

    if (iSb2 != iTempVal2)
    {
        ui->label_checkSb2->setVisible(true);
        noErrors = false;
    }
    else ui->label_checkSb2->setVisible(false);









    return noErrors;
}
