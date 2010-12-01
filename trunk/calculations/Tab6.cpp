#include "dmwindow.h"
#include "ui_dmwindow.h"
#include "defines/table5.h"

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
    DopustimieNapryajeniyaIzgiba();
}

void DmWindow::on_comboBox_z1_currentIndexChanged(QString value)
{
    iz1 = value.toInt();
    chisloZubjev2();
}

void DmWindow::viborMaterialaZubchatihKoles(void)
{
    DopustimieNapryajeniyaIzgiba();
}

void DmWindow::on_doubleSpinBox_psibd_valueChanged(double value)
{
    dPsibd3 = ROUND1(value);
    KoefficientShiriniVenca();
}

void DmWindow::on_comboBox_m_2_currentIndexChanged(QString value)
{
    dm = value.toDouble();
    RaschetnoeZnachenieModulya();
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

    iu = iz1 * du3;
    ui->label_u->setText(QString::number(iu));

    iz2 = iu;
    ui->label_z2_2->setText(QString::number(iz2));

    KoefficientShiriniVenca();
}

void DmWindow::KoefficientShiriniVenca(void)
{
    EkvivalentnoeChisloZubjev();
}

void DmWindow::EkvivalentnoeChisloZubjev(void)
{
    izv1 = iz1;
    izv2 = iz2;

    ui->label_zv1_2->setText(QString::number(izv1));
    ui->label_zv2_2->setText(QString::number(izv2));

    for (int i = LENGTH(KoeficientYf2)-2 ; i >= 0; i--)
        if (izv1 >= KoeficientYf2[i][0])
        {
            double temp1 = KoeficientYf2[i+1][0] - izv1;
            double temp2 = izv1 - KoeficientYf2[i][0];
            if(temp1 < temp2)
                dYF61 = KoeficientYf2[i+1][1];
            else
                dYF61 = KoeficientYf2[i][1];
            break;
        }
    for (int i = LENGTH(KoeficientYf2)-2 ; i >= 0; i--)
        if (izv2 >= KoeficientYf2[i][0])
        {
            double temp1 = KoeficientYf2[i+1][0] - izv2;
            double temp2 = izv2 - KoeficientYf2[i][0];
            if(temp1 < temp2)
                dYF62 = KoeficientYf2[i+1][1];
            else
                dYF62 = KoeficientYf2[i][1];
            break;
        }

    ui->label_YF1_2->setText(QString::number(dYF61));
    ui->label_YF2_2->setText(QString::number(dYF62));

    ProektnijRascetPeredachi();
}

void DmWindow::ProektnijRascetPeredachi(void)
{
    dYF1SF1 = dYF61 / (dSf1 / dSF);
    dYF1SF1 = ROUND4(dYF1SF1);

    dYF2SF2 = dYF62 / (dSf2 / dSF);
    dYF2SF2 = ROUND4(dYF2SF2);

    ui->label_YF1SF1->setText(QString::number(dYF1SF1));
    ui->label_YF2SF2->setText(QString::number(dYF2SF2));

    RaschetnoeZnachenieModulya();
}

void DmWindow::RaschetnoeZnachenieModulya(void)
{
    dmm3 = 14.0 * pow(((dT3 * 1.0 * dYF61) / (dPsibd3 * izv1 * izv1 * (dYF1SF1 == dYF2SF2 ? dSff1 : dSff2))) , 0.333333333);
    dmm3 = ROUND2(dmm3);

    ui->label_mm_2->setText(QString::number(dmm3));



















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

    for (int i = LENGTH(raschetnoeZnachenieModulay)-2 ; i >= 0; i--)
        if (dm >= raschetnoeZnachenieModulay[i])
        {
            dTempVal1 = raschetnoeZnachenieModulay[i+1] - dm;
            dTempVal2 = dm - raschetnoeZnachenieModulay[i];
            if(dTempVal1 < dTempVal2)
                dTempVal1 = raschetnoeZnachenieModulay[i+1];
            else
                dTempVal1 = raschetnoeZnachenieModulay[i];
            break;
        }
    if (dTempVal1 != dm)
    {
        ui->label_checkm->setVisible(true);
        noErrors = false;
    }
    else ui->label_checkm->setVisible(false);






    return noErrors;
}
