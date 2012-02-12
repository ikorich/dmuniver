#include "dmwindow.h"
#include "ui_dmwindow.h"
#include "defines/table4.h"

#pragma mark ============ Reductor Cilindricheskij =================

void DmWindow::KoefficientShirini(void)
{
    dT2 = ROUND2(ui->doubleSpinBox_T2->value());
    dn2 = ROUND1(ui->doubleSpinBox_n2->value());
    du2 = ROUND2(ui->doubleSpinBox_u2->value());
    dTmaxTnom2 = ROUND2(ui->doubleSpinBox_TmaxTnom->value());

    dPsiba = ui->comboBox_Psiba->currentText().toDouble();

    dPsibd = 0.5 * dPsiba * (du2 + 1);
    dPsibd = ROUND2(dPsibd);

    ui->label_Psibd0->setText(tr("0.5*") + QString::number(dPsiba) + tr("*(") + QString::number(du2) + tr(")=") + QString::number(dPsibd) );

    updateMejOsevoeRastoyanie();
}

void DmWindow::updateMejOsevoeRastoyanie(void)
{
    dKHBeta = ui->comboBox_KHBeta->currentText().toDouble();
    daw2 = ui->comboBox_aw->currentText().toDouble();

    dKa = GetVspomogatelniyKoeficient();
    ui->label_Ka->setText(QString::number(dKa));

    daw = dKa * (du2 + 1) * pow((dT2 * dKHBeta / (dSigmaH1 * dSigmaH1 * du2 * dPsiba)) , 0.333333333);
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
    dmm = ui->comboBox_m->currentText().toDouble();

    dmm1 = ROUND2(0.01 * daw2);
    dmm2 = ROUND2(0.02 * daw2);

    ui->label_mm->setText(QString::number(dmm1) + tr("...") + QString::number(dmm2) + tr(" мм"));
    UgolNaklonaZubjev();
}

void DmWindow::UgolNaklonaZubjev(void)
{
    dbb = ui->doubleSpinBox_Beta->value();

    /*if (CurrentPeredacha == Peredacha::CILINDRICHESKAYA)
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

    ui->label_bb->setText(QString::number(dbb) + tr("°"));*/

    ChisloZubjev();
}

void DmWindow::ChisloZubjev(void)
{
    dZsum = 2.0 * daw2 * cos(dbb * (PI / 180)) / dmm;
    dZsum = ROUND2(dZsum);

    iZsum = ROUND(dZsum);

    ui->label_Zsumm1->setText(tr("2*") + QString::number(daw2) + tr("*cos(") + QString::number(dbb) + tr("°)/") + QString::number(dmm) + tr("=")  + QString::number(dZsum));
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

    ui->label_beta->setText(QString::number(dBeta) + tr("°"));

    FacticheskoePeredatochnoeOtnoshenie();
}

void DmWindow::FacticheskoePeredatochnoeOtnoshenie(void)
{
    dUf = ROUND1((double)iZ2 / iZ1);

    ui->label_uf->setText(QString::number(iZ2) + tr(" / ") + QString::number(iZ1) + tr(" = ") + QString::number(dUf));


    dUf2 = (fabs(du2 - dUf)) / du2 * 100;
    dUf2 = ROUND2(dUf2);

    ui->label_formulaUf->setText(tr("(") + QString::number(dValI2) + tr(" - ") + QString::number(dUf) + tr(") / ") + QString::number(dValI2) + tr(" = ") + QString::number(dUf2) + tr(" %"));

    OsnovnojGeometricheskijObjom();
}

void DmWindow::OsnovnojGeometricheskijObjom(void)
{
    dd1 = iZ1 * dmm / cos(dBeta * (PI / 180));
    dd1 = ROUND1(dd1);

    ui->label_d1->setText(QString::number(iZ1) + tr(" * ") + QString::number(dmm) + tr(" /cos(") + QString::number(dBeta) + tr("°) = ") + QString::number(dd1));

    dd2 = iZ2 * dmm / cos(dBeta * (PI / 180));
    dd2 = ROUND1(dd2);

    ui->label_d2->setText(QString::number(iZ2) + tr(" * ") + QString::number(dmm) + tr(" /cos(") + QString::number(dBeta) + tr("°) = ") + QString::number(dd2));

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
    iNaznachenie = ui->spinBox_StepenPeredachi->value();
    iZm = ui->comboBox_Zm->currentText().toInt();
    dKHV = ui->doubleSpinBox_Khv->value();

    dPsibd2 = (double)ib1 / dd1;
    dPsibd2 = ROUND2(dPsibd2);

    ui->label_Psibd->setText(QString::number(ib1) + tr(" / ") + QString::number(dd1) + tr(" = ") + QString::number(dPsibd2));

    dV = PI * dn2 * dd1 / 60000;
    dV = ROUND1(dV);

    ui->label_V->setText(tr(" 3.14 *  ") + QString::number(dn2) + tr(" * ") + QString::number(dd1) + tr(" / 60000 = ") + QString::number(dV));

    dEtaAlpha = (1.88 - 3.2 * ( 1.0 / iZ1 + 1.0 / iZ2 )) * cos(dBeta * (PI / 180));
    dEtaAlpha = ROUND2(dEtaAlpha);

    ui->label_EtaAlpha->setText(tr("[1.88 - 3.2 * (1 / ") + QString::number(iZ1) + tr(" + 1 / ")  + QString::number(iZ2) + tr(")] * cos(") + QString::number(dBeta) + tr("°) = ") + QString::number(dEtaAlpha));

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

    dSigmaHmax = dSigmaH51 * sqrt(dTmaxTnom2);
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

    dFr = dFt * tan(20.0 * (PI / 180)) / cos(dBeta * (PI / 180));
    dFr = ROUND1(dFr);

    ui->label_Fr->setText(QString::number(dFt) + tr(" * tg(20°) / cos(") + QString::number(dBeta) + tr("°) = ") + QString::number(dFr) + tr(" H"));

    dFa = dFt * tan(dBeta * (PI / 180));
    dFa = ROUND1(dFa);

    ui->label_Fa->setText(QString::number(dFt) + tr(" * tg(") + QString::number(dBeta) + tr("°) = ") + QString::number(dFa) + tr(" H"));

    ProverkaNaVinoslivostPoNapryajeniyuIzgiba();
}

void DmWindow::ProverkaNaVinoslivostPoNapryajeniyuIzgiba(void)
{
    dKFBeta = ROUND2(ui->comboBox_Kfbeta->currentText().toDouble());
    dKFV = ROUND2(ui->doubleSpinBox_Kfv->value());

    ui->label_StepenPeredachi->setText(QString::number(iNaznachenie));

    if (CurrentReductor == Reductor::CILINDRICHESKAYA_PRYMOZUBAYA)
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

    iSigmaFmax1 = ROUND(dSigmaF51 * dTmaxTnom2);
    iSigmaFmax2 = ROUND(dSigmaF52 * dTmaxTnom2);

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

#pragma mark ============ Reductor Konicheskij ==================

void DmWindow::KoefficientShiriniZubchastihVencov(void)
{
     dT2 = ROUND2(ui->doubleSpinBox_T2_2->value());
     dn2 = ROUND1(ui->doubleSpinBox_n2_2->value());
     du2 = ROUND2(ui->doubleSpinBox_u2_2->value());
     dTmaxTnom2 = ROUND2(ui->doubleSpinBox_TmaxTnom_2->value());

     dKbe = ROUND2(ui->doubleSpinBox_Kbe->value());

     KoefficientNeravnomernosti();
}

void DmWindow::KoefficientNeravnomernosti(void)
{
    dKbeu = (dKbe * du2) / (2.0 - dKbe);
    dKbeu = ROUND2(dKbeu);

    ui->label_Kbeu->setText(QString::number(dKbe) + " * " + QString::number(du2) + " / (2 - " + QString::number(dKbe) + ") = " + QString::number(dKbeu));

    iPodshipnikTupe = ui->comboBox_Podshipnik->currentIndex();

    dKHBeta = ui->comboBox_Khb->currentText().toDouble();
    dKHBeta = ROUND2(dKHBeta);

    PredvaritelnoeZnachenieVneshnegoDelitelnogoDiametraKolesa();
}

void DmWindow::PredvaritelnoeZnachenieVneshnegoDelitelnogoDiametraKolesa(void)
{
    dddl = 1000.0 * pow(((dT2 * dKHBeta * du2 * du2) / (dKbe * (1.0 - dKbe) * dSigmaH3 * dSigmaH3 )) , 0.333333333);
    dddl = ROUND2(dddl);
    ui->label_dl2->setText(QString::number(dddl));

    ChisloZubjevKolesa();
}

void DmWindow::ChisloZubjevKolesa(void)
{
    iZ1 = ui->spinBox_z1->value();

    double dZ2_2 = du2 * iZ1;
    dZ2_2 = ROUND1(dZ2_2);

    iZ2 = ROUND(dZ2_2);

    ui->label_z2_3->setText(QString::number(dZ2_2));
    ui->label_z2_4->setText(QString::number(iZ2));

    VneshnijOkrujnojModul();
}

void DmWindow::VneshnijOkrujnojModul(void)
{
    dmll = dddl / iZ2;
    dmll = ROUND2(dmll);

    ui->label_mll->setText(QString::number(dddl) + " / " + QString::number(iZ2) + " = " + QString::number(dmll));

    dml = ui->comboBox_ml->currentText().toDouble();

    VneshnieDelitelnieDiametriKoles();
}

void DmWindow::VneshnieDelitelnieDiametriKoles(void)
{
    idl1 = iZ1 * dml;
    ui->label_dl1->setText(QString::number(iZ1) + " * " + QString::number(dml) + " = " + QString::number(idl1));

    idl2 = iZ2 * dml;
    ui->label_dl2_2->setText(QString::number(iZ2) + " * " + QString::number(dml) + " = " + QString::number(idl2));

    VneshnieKonusnoeRastoyanie();
}

void DmWindow::VneshnieKonusnoeRastoyanie(void)
{
    dRl = 0.5 * dml * sqrt((iZ1*iZ1 + iZ2*iZ2));
    dRl = ROUND2(dRl);
    ui->label_Rl->setText(QString::number(dRl));

    ShirinaZubchatihVencov();
}

void DmWindow::ShirinaZubchatihVencov(void)
{
    db = dRl * dKbe;
    db = ROUND1(db);
    ui->label_b->setText(QString::number(db));

    SrednijModul();
}

void DmWindow::SrednijModul(void)
{
    dmm = dml * (1.0 - 0.5 * dKbe);
    dmm = ROUND3(dmm);

    ui->label_mm_3->setText(QString::number(dmm));

    SrednieDelitelnieDeametriKolesa();
}

void DmWindow::SrednieDelitelnieDeametriKolesa(void)
{
    ddm1 = dmm * iZ1;
    ddm1 = ROUND2(ddm1);
    ui->label_dm1->setText(QString::number(ddm1));

    ddm2 = dmm * iZ2;
    ddm2 = ROUND2(ddm2);
    ui->label_dm2->setText(QString::number(ddm2));

    UgliPriVershinahDelitelnihKonusovKoles();
}

void DmWindow::UgliPriVershinahDelitelnihKonusovKoles(void)
{
    dBeta1 = atan((double)iZ1/iZ2) * (180 / PI);
    dBeta1 = ROUND2(dBeta1);

    ui->label_beta1->setText(QString::number(dBeta1));

    dBeta2 = 90.0 - dBeta1;
    dBeta2 = ROUND2(dBeta2);

    ui->label_beta2->setText(QString::number(dBeta2));

    SilaVZaceplenii2();
}

void DmWindow::SilaVZaceplenii2(void)
{
    dFt12_5 = 2.0 * dT2 * 1000 / ddm1;
    dFt12_5 = ROUND2(dFt12_5);
    ui->label_Ft12_2->setText(QString::number(dFt12_5) + " H");

    dFr1_5 = dFt12_5 * tan(20.0 * (PI / 180)) * cos(dBeta1 * (PI / 180));
    dFr1_5 = dFa2_5 = ROUND2(dFr1_5);

    ui->label_Fr1->setText(QString::number(dFr1_5));

    dFa1_5 = dFt12_5 * tan(20.0 * (PI / 180)) * sin(dBeta1* (PI / 180));
    dFa1_5 = dFr2_5 = ROUND2(dFa1_5);

    ui->label_Fa1_2->setText(QString::number(dFa1_5));

    OkrujnayaSkorostStepenTochnostiPeredach();
}

void DmWindow::OkrujnayaSkorostStepenTochnostiPeredach(void)
{
    dV = PI * dn2 * ddm1 / 60000.0;
    dV = ROUND2(dV);

    ui->label_V_3->setText("3.14*" + QString::number(dn2) + "*" + QString::number(ddm1) + "/(60*1000) = " + QString::number(dV));

    iNaznachenie = ui->spinBox_StepenTochnostiPeredachi_2->value();

    ProverochnijRaschetNaKontaktnujuVinoslivost();
}

void DmWindow::ProverochnijRaschetNaKontaktnujuVinoslivost(void)
{
    iZm = ui->comboBox_Zm_2->currentText().toInt();
    dZh = 1.76;

    dEtaAlpha = (1.88 - 3.2 * ( 1.0 / iZ1 + 1.0 / iZ2 ));
    dEtaAlpha = ROUND2(dEtaAlpha);

    ui->label_EpsilonAlpha->setText(tr("1.88 - 3.2 * (1 / ") + QString::number(iZ1) + tr(" + 1 / ")  + QString::number(iZ2) + tr(") = ") + QString::number(dEtaAlpha));

    dZe = pow(((4.0 / dEtaAlpha) / 3), 0.5);
    dZe = ROUND2(dZe);
    ui->label_Ze_2->setText(QString::number(dZe));

    dKHV = ui->doubleSpinBox_KHV->value();
    dKHV = ROUND2(dKHV);

    dSigmaH51 = dZh * iZm * dZe * sqrt(dFt12_5 * dKHBeta * dKHV * sqrt(du2 * du2 + 1) / (0.85 * ddm1 * db * du2));
    dSigmaH51 = ROUND2(dSigmaH51);

    ui->label_SigmaH_2->setText(QString::number(dSigmaH51));
    ui->label_SigmaH_3->setText(QString::number(dSigmaH51));
    ui->label_SigmaH_4->setText(QString::number(dSigmaH3));

    if (dSigmaF51 < dSigmaH3)
    {
        ui->label_OtnoshenieSigmaH->setText("<");
    }
    else ui->label_OtnoshenieSigmaH->setText(">");

    ui->label_StepenTochnosti->setText(QString::number(iNaznachenie));

    dSigmaHmax = dSigmaH3 * sqrt(dTmaxTnom2);
    dSigmaHmax = ROUND1(dSigmaHmax);
    ui->label_SigmaHmax_2->setText(QString::number(dSigmaHmax));

    dSigmaHHmax = 2.8 * iSigmaT;
    dSigmaHHmax = ROUND1(dSigmaHHmax);
    ui->label_SigmaHmax_3->setText(QString::number(dSigmaHHmax));

    if (dSigmaHmax < dSigmaHHmax)
    {
        ui->label_OtnoshenieSigmaHmax_3->setText("<");
    }
    else ui->label_OtnoshenieSigmaHmax_3->setText(">");

    ProverkaNaVinoslivostPoNapryjeniyuIzgiba();
}

void DmWindow::ProverkaNaVinoslivostPoNapryjeniyuIzgiba(void)
{
    dKFBeta = ROUND2(ui->comboBox_KFBeta->currentText().toDouble());
    dKFV = ROUND2(ui->doubleSpinBox_KFv->value());

    ui->label_StepenTochnosti_2->setText(QString::number(iNaznachenie));

    dZV1 = (double)iZ1 / pow(cos(dBeta1 * (PI / 180)), 3);
    dZV1 = ROUND1(dZV1);
    ui->label_ZV1->setText(QString::number(dZV1));

    dZV2 = (double)iZ2 / pow (cos(dBeta2 * (PI / 180)), 3);
    dZV2 = ROUND1(dZV2);
    ui->label_ZV2->setText(QString::number(dZV2));

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

    ui->label_YF1_3->setText(QString::number(dYF1));
    ui->label_YF2_3->setText(QString::number(dYF2));

    dSigmaF51 = dFt12_5 * dKFBeta * dKFV * dYF1 / (0.85 * db * dmm);
    dSigmaF51 = ROUND2(dSigmaF51);
    ui->label_SigmaF1_2->setText(QString::number(dSigmaF51));
    ui->label_SigmaF1_3->setText(QString::number(dSigmaF51));

    dSigmaF52 = dFt12_5 * dKFBeta * dKFV * dYF1 / (0.85 * db * dmm);
    dSigmaF52 = ROUND2(dSigmaF52);
    ui->label_SigmaF2_3->setText(QString::number(dSigmaF52));
    ui->label_SigmaF2_5->setText(QString::number(dSigmaF52));

    ui->label_SigmaF1_5->setText(QString::number(dSigmaF1));
    ui->label_SigmaF2_6->setText(QString::number(dSigmaF2));

    if (dSigmaF51 < dSigmaF1)
    {
        ui->label_OtnoshenieSigmaF1->setText("<");
    }
    else ui->label_OtnoshenieSigmaF1->setText(">");

    if (dSigmaF52 < dSigmaF2)
    {
        ui->label_OtnoshenieSigmaF2->setText("<");
    }
    else ui->label_OtnoshenieSigmaF2->setText(">");

    dSigmaFmax1 = dSigmaF51 * dTmaxTnom2;
    dSigmaFmax1 = ROUND1(dSigmaFmax1);
    ui->label_SigmaFmax1_3->setText(QString::number(dSigmaFmax1));

    dSigmaFmax2 = dSigmaF52 * dTmaxTnom2;
    dSigmaFmax2 = ROUND1(dSigmaFmax2);
    ui->label_SigmaFmax2_3->setText(QString::number(dSigmaFmax2));

    dSigmaFFmax1 = 4.8 * iHBcp1;
    dSigmaFFmax1 = ROUND1(dSigmaFFmax1);
    ui->label_SigmaFmax1_4->setText(QString::number(dSigmaFFmax1));

    dSigmaFFmax2 = 4.8 * iHBcp2;
    dSigmaFFmax2 = ROUND1(dSigmaFFmax2);
    ui->label_SigmaFmax2_4->setText(QString::number(dSigmaFFmax2));

    if (dSigmaFmax1 < dSigmaFFmax1)
    {
        ui->label_OtnoshenieSigmaFmax1->setText("<");
    }
    else ui->label_OtnoshenieSigmaFmax1->setText(">");

    if (dSigmaFmax2 < dSigmaFFmax2)
    {
        ui->label_OtnoshenieSigmaFmax2->setText("<");
    }
    else ui->label_OtnoshenieSigmaFmax2->setText(">");

#ifdef TAB_CONTROL
    if (checkTab5())
        ui->tabWidget->setTabEnabled(5, true);
    else ui->tabWidget->setTabEnabled(5, false);
#else
    checkTab5();
#endif
}


#pragma mark =================== check ==========================

bool DmWindow::checkTab5(void)
{
    bool noErrors = true;

    if (CurrentReductor == Reductor::CILINDRICHESKAYA_PRYMOZUBAYA || CurrentReductor == Reductor::CILINDRICHESKAYA_KOSOZUBAYA) {
        if (dT2 != dValT2 || dn2 != dValN2 || du2 != dValI2 || dTmaxTnom1 != dTmaxTnom2)
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
    }
    else if (CurrentReductor == Reductor::KONICHESKAYA) {

        double tempValD = 0.0;
        int    tempValI = 0;

        if (dT2 != dValT2 || dn2 != dValN2 || du2 != dValI2 || dTmaxTnom1 != dTmaxTnom2)
        {
            ui->label_CheckT2_2->setVisible(true);
            noErrors = false;
        } else ui->label_CheckT2_2->setVisible(false);

        tempValD = ROUND1(dKbeu);
        tempValI = tempValD * 10 - 1;
        if (tempValI < 0)
            tempValI = 0;
        else if (tempValI > 7)
            tempValI = 7;

        if(dKHBeta != KoeficientKHBeta[0 + 2 * iPodshipnikTupe][tempValI])
        {
            ui->label_CheckKhb->setVisible(true);
            noErrors = false;
        } else ui->label_CheckKhb->setVisible(false);

        tempValD = dmll - dml;
        tempValD = (tempValD > 0) ? tempValD : -tempValD;
        if ( tempValD > 1.0 )
        {
            ui->label_checkml->setVisible(true);
            noErrors = false;
        } else ui->label_checkml->setVisible(false);

        if ( db > (dml*10) )
        {
            ui->label_checkb->setText(tr("<span style=\" font-size:14pt; color:#ff0000;\">&gt; 10 m</span><span style=\" font-size:14pt; color:#ff0000; vertical-align:sub;\">e</span><span style=\" font-size:14pt; color:#ff0000;\">&gt; 10 m</span> Уточните!</span>"));
            noErrors = false;
        } else ui->label_checkb->setText(tr("<span style=\" font-size:14pt; color:#ff0000;\">&lt; 10 m</span><span style=\" font-size:14pt; color:#ff0000; vertical-align:sub;\">e</span>"));

        if (dV <= 2.0)
            tempValI = 9;
        else if (dV <= 6.0)
            tempValI = 8;
        else if (dV <= 10.0)
            tempValI = 7;
        else if (dV <= 15.0)
            tempValI = 6;
        else
            tempValI = 5;

        if(iNaznachenie != tempValI)
        {
            ui->label_checkStepenTochnostiPeredachi->setVisible(true);
            noErrors = false;
        } else ui->label_checkStepenTochnostiPeredachi->setVisible(false);

        if((iNaznachenie >=6 && iNaznachenie <= 9) || CurrentPeredacha == Peredacha::CILINDRICHESKAYA)
        {
            if (dV < 1)
            {
                tempValI = 1;
            }
            else
            {
                if(dV < 1.5)
                {
                    tempValI = 0;
                }
                else if(dV < 2.5)
                {
                    tempValI = 1;
                }
                else if(dV >= 2.5 && dV < 4.5)
                {
                    tempValI = 2;
                }
                else if(dV >= 4.5 && dV < 6.5)
                {
                    tempValI = 3;
                }
                else if(dV >= 6.5 && dV < 8.5)
                {
                    tempValI = 4;
                }
                else if(dV >= 8.5)
                {
                    tempValI = 5;
                }

                tempValD = KoeficientKHV[iNaznachenie-6][static_cast<int>(tempValI)];
            }

        }
        else tempValD = -1.0;

        if (dKHV != tempValD)
        {
            ui->label_checkKHV_2->setVisible(true);
            noErrors = false;
        } else ui->label_checkKHV_2->setVisible(false);

        if (dSigmaH51 > dSigmaH1)
        {
            ui->label_checkSigmaH->setText(tr("<span style=\" color:#ff0000;\">Условие контактной выносливости не выполняется, пожалуйста уточните!</span>"));
            noErrors = false;
        } else ui->label_checkSigmaH->setText(tr("<span style=\" color:#ff0000;\">Условие контактной выносливости выполняется.</span>"));

        if (dSigmaHmax > dSigmaHHmax)
        {
            ui->label_checkSigmaHmax_3->setText(tr("<span style=\" color:#ff0000;\">Условие  не выполняется, пожалуйста уточните!</span>"));
            noErrors = false;
        } else ui->label_checkSigmaHmax_3->setText(tr("<span style=\" color:#ff0000;\">Условие  выполняется.</span>"));

        tempValD = ROUND1(dKbeu);
        tempValI = tempValD * 10 - 1;
        if (tempValI < 0)
            tempValI = 0;
        else if (tempValI > 7)
            tempValI = 7;

        if(dKFBeta != KoeficientKHBeta[1 + 2 * iPodshipnikTupe][tempValI])
        {
            ui->label_checkKFBeta->setVisible(true);
            noErrors = false;
        } else ui->label_checkKFBeta->setVisible(false);

        if(iNaznachenie >=6 && iNaznachenie <= 9)
        {
            tempValI = ROUND(dV) - 1;

            if (tempValI < 0)
            {
                tempValI = 0;
            }
            else if (tempValI > 5)
            {
                tempValI = 5;
            }

            tempValD = KoeficientKFV[iNaznachenie-6][tempValI];

        }
        else tempValD = -1.0;

        if (dKFV != tempValD)
        {
            ui->label_checkKFV->setVisible(true);
            noErrors = false;
        } else ui->label_checkKFV->setVisible(false);

        if (dSigmaF51 > dSigmaF1 || dSigmaF52 > dSigmaF2)
        {
            ui->label_checkSigmaF1->setText(tr("<span style=\" color:#ff0000;\">Условие  выносливости на изгиб не выполняется, пожалуйста уточните!</span>"));
            noErrors = false;
        } else ui->label_checkSigmaF1->setText(tr("<span style=\" color:#ff0000;\">Условие выносливости на изгиб выполняется.</span>"));

        if (iSigmaFmax1 < iSigmaFFmax1 || iSigmaFmax2 < iSigmaFFmax2)
        {
            ui->label_checkSigmaFmax1->setText(tr("<span style=\" color:#ff0000;\">Условие  выносливости не выполняется, пожалуйста уточните!</span>"));
            noErrors = false;
        } else ui->label_checkSigmaFmax1->setText(tr("<span style=\" color:#ff0000;\">Условие выносливости выполняется.</span>"));
    }

    return noErrors;
}

double DmWindow::GetVspomogatelniyKoeficient()
{
    double _dKa = 0.0;

    if (CurrentReductor == Reductor::CILINDRICHESKAYA_PRYMOZUBAYA)
        _dKa = 490;

    else if (CurrentReductor == Reductor::CILINDRICHESKAYA_KOSOZUBAYA)
        _dKa = 430;

    return _dKa;
}
