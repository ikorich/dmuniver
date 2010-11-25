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

void DmWindow::on_comboBox_Sb_2_currentIndexChanged(QString value)
{
    iSb2 = value.toInt();
    viborMaterialaZubchatihKoles();
}

void DmWindow::on_comboBox_St_2_currentIndexChanged(QString value)
{
    iSt2 = value.toInt();
    viborMaterialaZubchatihKoles();
}

void DmWindow::on_doubleSpinBox_SF_2_valueChanged(double value)
{
    dSF = value;
}

void DmWindow::viborMaterialaZubchatihKoles(void)
{
    DopustimieNapryajeniyaIzgiba();
}

void DmWindow::DopustimieNapryajeniyaIzgiba(void)
{
    dSf1 = 1.8 * iHB1;
    dSf1 = ROUND1(dSf1);

    dSf2 = 1.8 * iHB2;
    dSf2 = ROUND1(dSf2);

    ui->label_sF01->setText(QString::number(dSf1));
    ui->label_sF02->setText(QString::number(dSf2));

    iN1FE = 60 * dn3 * iValLh;
    ui->label_N1FE->setText(QString::number(iN1FE));

    iN2FE = iN1FE / du3;
    ui->label_N2FE->setText(QString::number(iN2FE));

    dSff1 = dSf1 / dSF;
    dSff1 = ROUND1(dSff1);

    dSff2 = dSf2 / dSF;
    dSff2 = ROUND1(dSff2);

    ui->label_SFF1->setText(QString::number(dSff1));
    ui->label_SFF2->setText(QString::number(dSff2));

    chisloZubjev2();
}

void DmWindow::chisloZubjev2(void)
{




















#ifdef TAB_CONTROL
    if (checkTab5())
        ui->tabWidget->setTabEnabled(5, true);
    else ui->tabWidget->setTabEnabled(5, false);
#else
    checkTab6();
#endif
}

bool DmWindow::checkTab6(void)
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

    if (iSb2 != iTempVal1)
    {
        ui->label_checkSb1->setVisible(true);
        noErrors = false;
    }
    else ui->label_checkSb1->setVisible(false);

    if (iSt2 != iTempVal2)
    {
        ui->label_checkSb2->setVisible(true);
        noErrors = false;
    }
    else ui->label_checkSb2->setVisible(false);









    return noErrors;
}
