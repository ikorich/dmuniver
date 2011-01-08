#include "dmwindow.h"
#include "ui_dmwindow.h"
#include "defines/table4.h"

void DmWindow::on_doubleSpinBox_T2_valueChanged(double value)
{
    dT2 = ROUND2(value);
    KoefficientShirini();
}

void DmWindow::on_doubleSpinBox_n2_valueChanged(double value)
{
    dn2 = ROUND1(value);
    KoefficientShirini();
}

void DmWindow::on_doubleSpinBox_u2_valueChanged(double value)
{
    du2 = ROUND2(value);
    KoefficientShirini();
}

void DmWindow::on_comboBox_Psiba_currentIndexChanged(QString value)
{
    dPsiba = value.toDouble();
    KoefficientShirini();
}

void DmWindow::on_comboBox_KHBeta_currentIndexChanged(QString value)
{
    dKHBeta = value.toDouble();
    updateMejOsevoeRastoyanie();
}

void DmWindow::on_comboBox_aw_currentIndexChanged(QString value)
{
    daw2 = value.toDouble();
    updateMejOsevoeRastoyanie();
}

void DmWindow::on_comboBox_m_currentIndexChanged(QString value)
{
    dmm = value.toDouble();
    ModulZacepleniya();
}

void DmWindow::on_spinBox_StepenPeredachi_valueChanged(int value)
{
    iNaznachenie = value;
    ProverkaNaKontaktnuyuVinoslivost();
}

void DmWindow::on_comboBox_Zm_currentIndexChanged(QString value)
{
    iZm = value.toInt();
    ProverkaNaKontaktnuyuVinoslivost();
}

void DmWindow::on_doubleSpinBox_Khv_valueChanged(double value)
{
    dKHV = value;
    ProverkaNaKontaktnuyuVinoslivost();
}

void DmWindow::on_comboBox_Kfbeta_currentIndexChanged(QString value)
{
    dKFBeta = value.toDouble();
    ProverkaNaVinoslivostPoNapryajeniyuIzgiba();
}

void DmWindow::on_doubleSpinBox_Kfv_valueChanged(double value)
{
    dKFV = ROUND2(value);
    ProverkaNaVinoslivostPoNapryajeniyuIzgiba();
}

void DmWindow::KoefficientShirini(void)
{    
    dPsibd = 0.5 * dPsiba * (du2 + 1);
    dPsibd = ROUND2(dPsibd);

    ui->label_Psibd0->setText(tr("0.5*") + QString::number(dPsiba) + tr("*(") + QString::number(du2) + tr(")=") + QString::number(dPsibd) );

    updateMejOsevoeRastoyanie();
}

void DmWindow::updateMejOsevoeRastoyanie(void)
{
    dKa = GetVspomogatelniyKoeficient();
    ui->label_Ka->setText(QString::number(dKa));

    daw = dKa * (du2 + 1) * pow((dT2 * dKHBeta * 1000.0 / (dSigmaH1 * dSigmaH1 * du2 * dPsiba)) , 0.333333333);
    daw = ROUND1(daw);

    ui->label_Aw->setText(QString::number(daw));

    ShirinaZubchatogoVenca();
}

void DmWindow::ShirinaZubchatogoVenca(void)
{
    ib2 = dPsiba * daw2;
    ui->label_b2->setText(QString::number(dPsiba) + tr("*") + QString::number(daw2) + tr("=") + QString::number(ib2) + tr(" мм") );

    ib1 = ib2 + 4;
    ui->label_b1->setText(QString::number(ib1) + tr(" мм") );

    ModulZacepleniya();
}

void DmWindow::ModulZacepleniya(void)
{
    dmm1 = ROUND2(0.01 * daw2);
    dmm2 = ROUND2(0.02 * daw2);

    ui->label_mm->setText(QString::number(dmm1) + tr("...") + QString::number(dmm2) + tr(" мм"));
    UgolNaklonaZubjev();
}

void DmWindow::UgolNaklonaZubjev(void)
{
    if (CurrentPeredacha == Peredacha::CILINDRICHESKAYA)
    {
        dbb = 0.0;
        ui->label_BetaBFormula->setVisible(false);
    }
    else
    {
        dbb = asin(3.5 * dmm / ib2) * (180.0/PI);
        ui->label_BetaBFormula->setVisible(true);
    }
    dbb = ROUND2(dbb);

    ui->label_bb->setText(QString::number(dbb));

    ChisloZubjev();
}

void DmWindow::ChisloZubjev(void)
{
    dZsum = 2.0 * daw2 * cos(dbb * (PI / 180)) / dmm;
    dZsum = ROUND2(dZsum);

    iZsum = ROUND(dZsum);

    ui->label_Zsumm1->setText(tr("2*") + QString::number(daw2) + tr("*cos(") + QString::number(dbb) + tr(")/") + QString::number(dmm) + tr("=")  + QString::number(dZsum));
    ui->label_Zsumm2->setText(QString::number(iZsum));

    dZ1 = (double)iZsum / (du2 + 1);
    dZ1 = ROUND2(dZ1);

    iZ1 = ROUND(dZ1);

    ui->label_z11->setText(QString::number(iZsum) + tr(" / (") + QString::number(du2) + tr(" + 1) = ") + QString::number(dZ1));
    ui->label_z12->setText(QString::number(iZ1));

    iZ2 = iZsum - iZ1;
    ui->label_z2->setText(QString::number(iZ2));

    FacticheskijUgolNaklona();
}

void DmWindow::FacticheskijUgolNaklona(void)
{
    if (CurrentPeredacha == Peredacha::CILINDRICHESKAYA)
    {
        dBeta = 0.0;
        ui->label_BetaFormula->setVisible(false);
    }
    else
    {
        dBeta = acos((double)iZsum * dmm / (2.0 * daw2)) * (180.0/PI);
        ui->label_BetaFormula->setVisible(true);
    }
    dBeta = ROUND1(dBeta);

    ui->label_beta->setText(QString::number(dBeta));

    FacticheskoePeredatochnoeOtnoshenie();
}
void DmWindow::FacticheskoePeredatochnoeOtnoshenie(void)
{
    dUf = ROUND1((double)iZ2 / iZ1);

    ui->label_uf->setText(QString::number(iZ2) + tr(" / ") + QString::number(iZ2) + tr(" = ") + QString::number(dUf));

    //че-то там не то в экселе

    dUf2 = (fabs(du2 - dUf)) / du2 * 100;
    dUf2 = ROUND2(dUf2);

    ui->label_formulaUf->setText(tr("(") + QString::number(dValI2) + tr(" - ") + QString::number(dUf) + tr(") / ") + QString::number(dValI2) + tr(" = ") + QString::number(dUf2) + tr(" %"));

    OsnovnojGeometricheskijObjom();
}

void DmWindow::OsnovnojGeometricheskijObjom(void)
{
    dd1 = iZ1 * dmm / cos(dBeta * (PI / 180));
    dd1 = ROUND1(dd1);

    ui->label_d1->setText(QString::number(iZ1) + tr(" * ") + QString::number(dmm) + tr(" /cos(") + QString::number(dBeta) + tr(") = ") + QString::number(dd1));

    dd2 = iZ2 * dmm / cos(dBeta * (PI / 180));
    dd2 = ROUND1(dd2);

    ui->label_d2->setText(QString::number(iZ2) + tr(" * ") + QString::number(dmm) + tr(" /cos(") + QString::number(dBeta) + tr(") = ") + QString::number(dd2));

    dda1 = dd1 + 2.0 * dmm;
    dda1 = ROUND1(dda1);

    ui->label_da1->setText(QString::number(dd1) + tr(" + 2 * ") + QString::number(dmm) + tr(" = ") + QString::number(dda1));

    dda2 = dd2 + 2.0 * dmm;
    dda2 = ROUND1(dda2);

    ui->label_da2->setText(QString::number(dd2) + tr(" + 2 * ") + QString::number(dmm) + tr(" = ") + QString::number(dda2));

    ddf1 = dd1 - 2.5 * dmm;
    ddf1 = ROUND1(ddf1);

    ui->label_df1->setText(QString::number(dd1) + tr(" - 2.5 * ") + QString::number(dmm) + tr(" = ") + QString::number(ddf1));

    ddf2 = dd2 - 2.5 * dmm;
    ddf2 = ROUND1(ddf2);

    ui->label_df2->setText(QString::number(dd2) + tr(" - 2.5 * ") + QString::number(dmm) + tr(" = ") + QString::number(ddf2));

    ProverkaNaKontaktnuyuVinoslivost();
}

void DmWindow::ProverkaNaKontaktnuyuVinoslivost(void)
{
    dPsibd2 = (double)ib1 / dd1;
    dPsibd2 = ROUND2(dPsibd2);

    ui->label_Psibd->setText(QString::number(ib1) + tr(" / ") + QString::number(dd1) + tr(" = ") + QString::number(dPsibd2));

    dV = PI * dn2 * dd1 / 60000;
    dV = ROUND1(dV);

    ui->label_V->setText(tr(" 3.14 *  ") + QString::number(dn2) + tr(" * ") + QString::number(dd1) + tr(" / 60000 = ") + QString::number(dV));

    dEtaAlpha = (1.88 - 3.2 * ( 1.0 / iZ1 + 1.0 / iZ2 )) * cos(dBeta * (PI / 180));
    dEtaAlpha = ROUND2(dEtaAlpha);

    ui->label_EtaAlpha->setText(tr("[1.88 - 3.2 * (1 / ") + QString::number(iZ1) + tr(" + 1 / ")  + QString::number(iZ2) + tr(")] * cos(") + QString::number(dBeta) + tr(") = ") + QString::number(dEtaAlpha));

    if (CurrentPeredacha == Peredacha::CILINDRICHESKAYA)
        dZh = 1.76;
    else dZh = 1.76 * cos(dBeta * (PI / 180));
    dZh = ROUND2(dZh);

    ui->label_Zh->setText(QString::number(dZh));

    if (CurrentReductor == Reductor::CILINDRICHESKAYA_PRYMOZUBAYA || CurrentPeredacha == Peredacha::CILINDRICHESKAYA)
    {
        dZe = pow(((4.0 - dEtaAlpha) / 3), 0.5);
    }
    else
    {
        dZe = pow(((1.0 / dEtaAlpha) / 3), 0.5);
    }
    dZe = ROUND2(dZe);

    ui->label_Ze->setText(QString::number(dZe));

    if(dV <= 2.5)
        dKHa = 1.05;
    else if(dV <= 5)
        dKHa = 1.09;
    else if(dV <= 10)
        dKHa = 1.13;

    ui->label_KHa->setText(QString::number(dKHa));

    ui->label_Zm->setText(QString::number(iNaznachenie));

    dSigmaH51 = dZh * iZm * dZe * sqrt(2000.0 * dT2 * dKHBeta * dKHV * (dUf + 1) / (dd1*dd1 * ib2 * dUf) );
    dSigmaH51 = ROUND2(dSigmaH51);

    ui->label_sigmaH1->setText(QString::number(dSigmaH51));
    ui->label_sigmaH2->setText(QString::number(dSigmaH51));
    ui->label_sigmaH->setText(QString::number(dSigmaH1));

    if (dSigmaH51 < dSigmaH1)
    {
        ui->label_OtnoshenieSigmaH1H2->setText(tr("<"));
    }
    else ui->label_OtnoshenieSigmaH1H2->setText(tr(">"));

    dSigmaHmax = dSigmaH51 * sqrt(dTmaxTnom);
    dSigmaHmax = ROUND(dSigmaHmax);

    ui->label_SigmaHmax1->setText(QString::number(dSigmaHmax));

    dSigmaHHmax = 2.8 * iSigmaT;
    dSigmaHHmax = ROUND(dSigmaHHmax);

    ui->label_SigmaHmax2->setText(QString::number(dSigmaHHmax));

    if (dSigmaHmax < dSigmaHHmax)
    {
        ui->label_OtnoshenieSigmaHmax->setText(tr("<"));
    }
    else ui->label_OtnoshenieSigmaHmax->setText(tr(">"));

    SilaDejstviyaVZaceplenii();
}

void DmWindow::SilaDejstviyaVZaceplenii(void)
{
    dFt = 2.0 * dT2 * 1000.0 / dd1;
    dFt = ROUND1(dFt);

    ui->label_Ft->setText(tr("2 * ") + QString::number(dT2) + tr(" * 1000 / ") + QString::number(dd1) + tr(" = ") + QString::number(dFt) + tr(" H"));

    dFr = dFt * tan(20.0 * (PI / 180)) / cos(dBeta * (PI / 180));;
    dFr = ROUND1(dFr);

    ui->label_Fr->setText(QString::number(dFt) + tr(" * tg(20) / cos(") + QString::number(dBeta) + tr(" = ") + QString::number(dFr) + tr(" H"));

    dFa = dFt * tan(dBeta * (PI / 180));
    dFa = ROUND1(dFa);

    ui->label_Fa->setText(QString::number(dFt) + tr(" * tg(") + QString::number(dBeta) + tr(") = ") + QString::number(dFa) + tr(" H"));

    ProverkaNaVinoslivostPoNapryajeniyuIzgiba();
}

void DmWindow::ProverkaNaVinoslivostPoNapryajeniyuIzgiba(void)
{
    ui->label_StepenPeredachi->setText(QString::number(iNaznachenie));

    if (CurrentReductor == Reductor::CILINDRICHESKAYA_PRYMOZUBAYA || CurrentPeredacha == Peredacha::CILINDRICHESKAYA)
    {
        dKFa = 1;
    }
    else
    {
        dKFa = (4.0 + (dEtaAlpha - 1) * (iNaznachenie - 5))/(4.0 * dEtaAlpha) ;
        dKFa = ROUND2(dKFa);
    }

    ui->label_KFa->setText(QString::number(dKFa));

    iZV1 = iZ1 * pow (cos(dBeta * (PI / 180)), 3);
    ui->label_zv1->setText(QString::number(iZV1));

    iZV2 = iZ2 * pow (cos(dBeta * (PI / 180)), 3);
    ui->label_zv2->setText(QString::number(iZV2));

    int tempVal1 = iZV1;
    int tempVal2 = iZV2;
    if (tempVal1 < 17)
        tempVal1 = 17;
    if (tempVal2 < 17)
        tempVal2 = 17;

    dYF1 = dYF2 = 0;
    for (int i = 0; i < LENGTH(KoeficientYf); ++i)
    {
        if (tempVal1 <= KoeficientYf[i][0] && dYF1 == 0)
        {
            dYF1 = KoeficientYf[i][1];
        }

        if (tempVal2 <= KoeficientYf[i][0] && dYF2 == 0)
        {
            dYF2 = KoeficientYf[i][1];
        }
    }

    ui->label_YF1->setText(QString::number(dYF1));
    ui->label_YF2->setText(QString::number(dYF2));

    if (CurrentReductor == Reductor::CILINDRICHESKAYA_PRYMOZUBAYA || CurrentPeredacha == Peredacha::CILINDRICHESKAYA)
    {
        dYb = 1;
    }
    else
    {
        dYb = (1.0 - dBeta) / 140 ;
        dYb = ROUND2(dYb);
    }

    ui->label_Yb->setText(QString::number(dYb));

    dSigmaF51 = dFt * dKFBeta * dKFV * dKFa * dYF1 * dYb / (dmm * ib1);
    dSigmaF51 = ROUND1(dSigmaF51);
    dSigmaF52 = dFt * dKFBeta * dKFV * dKFa * dYF2 * dYb / (dmm * ib2);
    dSigmaF52 = ROUND1(dSigmaF52);

    ui->label_SigmaF1_4->setText( QString::number(dFt) + tr("*") + QString::number(dKFBeta) + tr("*") + QString::number(dKFV) + tr("*") + QString::number(dKFa) + tr("*") + QString::number(dYF1) + tr("*") + QString::number(dYb) + tr("/(") + QString::number(ib1) + tr("*") + QString::number(dmm) + tr(")=") + QString::number(dSigmaF51));
    ui->label_SigmaF2_4->setText( QString::number(dFt) + tr("*") + QString::number(dKFBeta) + tr("*") + QString::number(dKFV) + tr("*") + QString::number(dKFa) + tr("*") + QString::number(dYF2) + tr("*") + QString::number(dYb) + tr("/(") + QString::number(ib2) + tr("*") + QString::number(dmm) + tr(")=") + QString::number(dSigmaF52));

    ui->label_SigmaF12->setText(QString::number(dSigmaF51));
    ui->label_SigmaF22->setText(QString::number(dSigmaF52));

    ui->label_SigmaModulF1->setText(QString::number(dSigmaF1));
    ui->label_SigmaModulF2->setText(QString::number(dSigmaF2));

    if (dSigmaF51 < dSigmaF1)
    {
        ui->label_OtnoshenieSigmaF1_2->setText("<");
    }
    else ui->label_OtnoshenieSigmaF1_2->setText(">");

    if (dSigmaF52 < dSigmaF2)
    {
        ui->label_OtnoshenieSigmaF2_2->setText("<");
    }
    else ui->label_OtnoshenieSigmaF2_2->setText(">");

    iSigmaFmax1 = ROUND(dSigmaF51 * dTmaxTnom);
    iSigmaFmax2 = ROUND(dSigmaF52 * dTmaxTnom);

    iSigmaFFmax1 = ROUND(4.8 * iHBcp1);
    iSigmaFFmax2 = ROUND(4.8 * iHBcp2);

    ui->label_SigmaFmax1_2->setText(QString::number(iSigmaFmax1));
    ui->label_SigmaFmax2_2->setText(QString::number(iSigmaFmax2));

    ui->label_ModulSigmaFmax1->setText(QString::number(iSigmaFFmax1));
    ui->label_ModulSigmaFmax2->setText(QString::number(iSigmaFFmax2));

    if (iSigmaFmax1 < iSigmaFFmax1)
    {
        ui->label_OtnoshenieSigmaFmax1_2->setText("<");
    }
    else ui->label_OtnoshenieSigmaFmax1_2->setText(">");

    if (iSigmaFmax2 < iSigmaFFmax2)
    {
        ui->label_OtnoshenieSigmaFmax2_2->setText("<");
    }
    else ui->label_OtnoshenieSigmaFmax2_2->setText(">");

    ProverkaPrigodnostiZagotovki();
}

void DmWindow::ProverkaPrigodnostiZagotovki()
{


    if (ui->comboBox_Shesternya->currentIndex() == 0)
        iDrped = 80;
    else if (ui->comboBox_Shesternya->currentIndex() == 1)
        iDrped = 125;
    else iDrped = 200;

    ui->label_Dpred->setText(QString::number(iDrped));

    dDzag = dda1 + 6;

    ui->label_Dzag->setText(QString::number(dDzag));

    if (dDzag < iDrped)
        ui->label_OtnoshenieDzag->setText(tr("<"));
    else ui->label_OtnoshenieDzag->setText(tr("<"));

    if (ui->comboBox_Koleso->currentIndex() == 0)
        iSrped = 50;
    else if (ui->comboBox_Koleso->currentIndex() == 1)
        iSrped = 80;
    else
        iSrped = 125;

    ui->label_Spred->setText(QString::number(iSrped));

    dCzag = 0.5 * ib2;
    dCzag = ROUND1(dCzag);

    ui->label_Czag->setText(QString::number(dCzag));

    iSzag1 = 8 * dmm;
    iSzag2 = ib2 + 4;

    ui->label_Szag2->setText(QString::number(iSzag1));
    ui->label_Szag3->setText(QString::number(iSzag2));

    if (iSzag1 < iSrped)
        ui->label_OtnoshenieSzag1->setText(tr("<"));
    else ui->label_OtnoshenieSzag1->setText(tr(">"));

    if (iSzag2 < iSrped)
        ui->label_OtnoshenieSzag2->setText(tr("<"));
    else ui->label_OtnoshenieSzag2->setText(tr(">"));

#ifdef TAB_CONTROL
    if (checkTab5())
        ui->tabWidget->setTabEnabled(5, true);
    else ui->tabWidget->setTabEnabled(5, false);
#else
    checkTab5();
#endif
}

bool DmWindow::checkTab5(void)
{
    bool noErrors = true;

    if (dT2 != dValT2 || dn2 != dValN2 || du2 != dValI2)
    {
        ui->label_CheckT2->setVisible(true);
        noErrors = false;
    } else ui->label_CheckT2->setVisible(false);


    double tempVal = 0.0;
    if (CurrentPeredacha == Peredacha::CILINDRICHESKAYA)
    {
        if (dPsibd >= 1.2)
        {
            tempVal = 1.07;
        }
        else if (dPsibd >= 0.8)
        {
            tempVal = 1.04;
        }
        else if (dPsibd >= 0.6)
        {
            tempVal = 1.03;
        }
        else if (dPsibd >= 0.4)
        {
            tempVal = 1.02;
        }
        else
        {
            tempVal = 1.01;
        }
    }

    if (dKHBeta != tempVal)
    {
        ui->label_CheckPsi->setVisible(true);
        noErrors = false;
    }
    else ui->label_CheckPsi->setVisible(false);

    for (int i = LENGTH(mejosevoeRastoyanie)-2 ; i >= 0; i--)
    {
        if (daw > mejosevoeRastoyanie[i])
        {
            tempVal = mejosevoeRastoyanie[i+1];
            break;
        }
        else if (daw == mejosevoeRastoyanie[i])
        {
            tempVal = daw;
            break;
        }
    }

    if(daw2 != tempVal)
    {
        ui->label_checkAw->setVisible(true);
        noErrors = false;
    } else ui->label_checkAw->setVisible(false);

    if (dmm >= dmm1 && dmm <= dmm2)
    {
        ui->label_checkM_2->setVisible(false);
    }
    else
    {
        ui->label_checkM_2->setVisible(true);
        noErrors = false;
    }

    if (dUf2 > 4.0)
    {
         ui->label_checkUf_2->setText(tr("<span style=\" color:#ff0000;\"> > 4%, что не допустимо.</span>"));
    }
    else ui->label_checkUf_2->setText(tr("<span style=\" color:#ff0000;\"> < 4%, что допустимо.</span>"));

    if(dV <= 2)
    {
        tempVal = 9;
    }
    else if(dV <= 6)
    {
        tempVal = 8;
    }
    else if(dV <= 10)
    {
        tempVal = 7;
    }
    else if(dV <= 15)
    {
        tempVal = 6;
    }
    else tempVal = 5;

    if (iNaznachenie != tempVal)
    {
        ui->label_checkNaznachenie->setVisible(true);
        noErrors = false;
    }
    else ui->label_checkNaznachenie->setVisible(false);

    if((iNaznachenie >=6 && iNaznachenie <= 9) || CurrentPeredacha == Peredacha::CILINDRICHESKAYA)
    {
        if (dV < 1)
        {
            tempVal = 1;
        }
        else
        {
            if(dV < 1.5)
            {
                tempVal = 0;
            }
            else if(dV < 2.5)
            {
                tempVal = 1;
            }
            else if(dV >= 2.5 && dV < 4.5)
            {
                tempVal = 2;
            }
            else if(dV >= 4.5 && dV < 6.5)
            {
                tempVal = 3;
            }
            else if(dV >= 6.5 && dV < 8.5)
            {
                tempVal = 4;
            }
            else if(dV >= 8.5)
            {
                tempVal = 5;
            }

            tempVal = KoeficientKHV[iNaznachenie-6][static_cast<int>(tempVal)];
        }

    }
    else tempVal = -1.0;

    if (dKHV != tempVal)
    {
        ui->label_checkKHV->setVisible(true);
        noErrors = false;
    } else ui->label_checkKHV->setVisible(false);

    if (ui->label_OtnoshenieSigmaH1H2->text() == tr(">"))
    {
        ui->label_checkSigmaH_2->setText(tr("<span style=\" color:#ff0000;\">Условие контактной выносливости не выполняется, пожалуйста уточните!</span>"));
        noErrors = false;
    } else ui->label_checkSigmaH_2->setText(tr("<span style=\" color:#ff0000;\">Условие контактной выносливости выполняется.</span>"));

    if (ui->label_OtnoshenieSigmaHmax->text() == tr(">"))
    {
        ui->label_checkSigmaHmax_2->setText(tr("<span style=\" color:#ff0000;\">Условие не выполняется, пожалуйста уточните!</span>"));
        noErrors = false;
    } else ui->label_checkSigmaHmax_2->setText(tr("<span style=\" color:#ff0000;\">Условие  выполняется.</span>"));

    if(dPsibd <= 0.2)
        tempVal = 1;
    else if(dPsibd <= 0.4)
        tempVal = 1.03;
    else if(dPsibd <= 0.6)
        tempVal = 1.05;
    else if(dPsibd <= 0.8)
        tempVal = 1.07;
    else if(dPsibd <= 1.2)
        tempVal = 1.14;
    else
        tempVal = -1;

    if (dKFBeta != tempVal)
    {
        ui->label_checkKFBeta_2->setVisible(true);
        noErrors = false;
    } else ui->label_checkKFBeta_2->setVisible(false);

    if(iNaznachenie >=6 && iNaznachenie <= 9)
    {
        if (dV < 1)
        {
            tempVal = 1;
        }
        else
        {
            if(dV < 1.5)
            {
                tempVal = 0;
            }
            else if(dV < 2.5)
            {
                tempVal = 1;
            }
            else if(dV >= 2.5 && dV < 4.5)
            {
                tempVal = 2;
            }
            else if(dV >= 4.5 && dV < 6.5)
            {
                tempVal = 3;
            }
            else if(dV >= 6.5 && dV < 8.5)
            {
                tempVal = 4;
            }
            else if(dV >= 8.5)
            {
                tempVal = 5;
            }

            tempVal = KoeficientKFV[iNaznachenie-6][static_cast<int>(tempVal)];
        }

    }
    else tempVal = -1.0;

    if (dKFV != tempVal)
    {
        ui->label_checkKFV_2->setVisible(true);
        noErrors = false;
    } else ui->label_checkKFV_2->setVisible(false);

    if (ui->label_OtnoshenieSigmaF1_2->text() == tr(">") && ui->label_OtnoshenieSigmaF2_2->text() == tr(">"))
    {
        ui->label_checkSigmaF1F2->setText(tr("<span style=\" color:#ff0000;\">Условие выносливости на изгиб не выполняется, пожалуйста уточните!</span>"));
        noErrors = false;
    } else ui->label_checkSigmaF1F2->setText(tr("<span style=\" color:#ff0000;\">Условие выносливости на изгиб выполняется.</span>"));

    if (ui->label_OtnoshenieSigmaFmax1_2->text() == tr(">") && ui->label_OtnoshenieSigmaFmax2_2->text() == tr(">"))
    {
        ui->label_checkSigmaF1F2max->setText(tr("<span style=\" color:#ff0000;\">Условие  выносливости не выполняется, пожалуйста уточните!</span>"));
        noErrors = false;
    } else ui->label_checkSigmaF1F2max->setText(tr("<span style=\" color:#ff0000;\">Условие выносливости выполняется.</span>"));

    if (dDzag > iDrped)
    {
        ui->label_checkDzag->setText(tr("<span style=\" color:#ff0000;\"> - заготовка  не  пригодна, уточните!</span>"));
        noErrors = false;
    }
    else ui->label_checkDzag->setText(tr("<span style=\" color:#ff0000;\"> - заготовка  пригодна.</span>"));

    if (iSzag1 > iSrped)
    {
        ui->label_checkSzag1->setText(tr("<span style=\" color:#ff0000;\"> - заготовка  не  пригодна, уточните!</span>"));
        noErrors = false;
    }
    else ui->label_checkSzag1->setText(tr("<span style=\" color:#ff0000;\"> - заготовка  пригодна.</span>"));

    if (iSzag2 > iSrped)
    {
        ui->label_checkSzag2->setText(tr("<span style=\" color:#ff0000;\"> - заготовка  не  пригодна, уточните!</span>"));
        noErrors = false;
    }
    else ui->label_checkSzag2->setText(tr("<span style=\" color:#ff0000;\"> - заготовка  пригодна.</span>"));

    return noErrors;
}

double DmWindow::GetVspomogatelniyKoeficient()
{
    double _dKa = 0.0;

    if (CurrentPeredacha == Peredacha::CILINDRICHESKAYA)
        _dKa = 49.5;

    return _dKa;
}
