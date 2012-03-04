#include "dmwindow.h"
#include "ui_dmwindow.h"
#include "defines/table5.h"

#pragma mark ============ Peredacha Cilindricheskaya =================

void DmWindow::viborMaterialaZubchatihKoles(void)
{
    dT3 = ui->doubleSpinBox_T3->value();
    dn3 = ui->doubleSpinBox_n3->value();
    du3 = ui->doubleSpinBox_u3->value();
    iLitje = ui->spinBox_Litje->value();
    iHB1 = ui->spinBox_HB1->value();
    iHB2 = ui->spinBox_HB2->value();
    iSb2 = ui->comboBox_Sb_2->currentText().toInt();
    iSt2 = ui->comboBox_St_2->currentText().toInt();
    dSF = ui->comboBox_SF_2->currentText().toDouble();
    iz1 = ui->comboBox_z1->currentText().toInt();

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

    iu = iz1 * du3;
    ui->label_u->setText(QString::number(iu));

    iz2 = iu;
    ui->label_z2_2->setText(QString::number(iz2));

    KoefficientShiriniVenca();
}

void DmWindow::KoefficientShiriniVenca(void)
{
    dPsibd3 = ROUND1(ui->doubleSpinBox_psibd->value());

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
    dm = ui->comboBox_m_2->currentText().toDouble();

    dmm3 = 14.0 * pow(((dT3 * 1.0 * dYF61) / (dPsibd3 * iz1 * iz1 * (dYF1SF1 == dYF2SF2 ? dSff1 : dSff2))) , 0.333333333);
    dmm3 = ROUND2(dmm3);

    ui->label_mm_2->setText(QString::number(dmm3));

    OsnovnieGeometricheskieRazmeri();
}

void DmWindow::OsnovnieGeometricheskieRazmeri(void)
{
    dd61 = iz1 * dm;
    dd61 = ROUND2(dd61);
    ui->label_d1_2->setText(QString::number(iz1) + tr(" * ") + QString::number(dm) + tr(" = ") + QString::number(dd61));

    dd62 = iz2 * dm;
    dd62 = ROUND2(dd62);
    ui->label_d2_2->setText(QString::number(iz2) + tr(" * ") + QString::number(dm) + tr(" = ") + QString::number(dd62));

    dda61 = dd61 + 2.0 * dm;
    dda61 = ROUND1(dda61);
    ui->label_da1_2->setText(QString::number(dd61) + tr(" + 2 * ") + QString::number(dm) + tr(" = ") + QString::number(dda61));

    dda62 = dd62 + 2.0 * dm;
    dda62 = ROUND1(dda62);
    ui->label_da2_2->setText(QString::number(dd62) + tr(" + 2 * ") + QString::number(dm) + tr(" = ") + QString::number(dda61));

    ddf61 = dd61 - 2.5 * dm;
    ddf61 = ROUND1(ddf61);
    ui->label_df1_2->setText(QString::number(dd61) + tr(" - 2.5 * ") + QString::number(dm) + tr(" = ") + QString::number(ddf61));

    ddf62 = dd62 - 2.5 * dm;
    ddf62 = ROUND1(ddf62);
    ui->label_df2_2->setText(QString::number(dd62) + tr(" - 2.5 * ") + QString::number(dm) + tr(" = ") + QString::number(ddf61));

    ib62 = ROUND((dPsibd3 * dd61));
    ib61 = ib62 + 3;

    ui->label_b2_2->setText(QString::number(ib62));
    ui->label_b1_2->setText(QString::number(ib61));

    OkrujnayaSkorostIStepenTochnostiPeredachi();
}

void DmWindow::OkrujnayaSkorostIStepenTochnostiPeredachi(void)
{
    iStepenTochnostiPeredachi = ui->spinBox_StepenTochnostiPeredachi->value();

    dV61 = PI * dd61 * dn3 / 60000;
    dV61 = ROUND2(dV61);
    ui->label_V_2->setText(QString::number(dV61));

    SilaVZaceplenii();
}

void DmWindow::SilaVZaceplenii(void)
{
    dFt12 = 2.0 * dT3 * 1000 / dd61;
    dFt12 = ROUND1(dFt12);
    ui->label_Ft12->setText(QString::number(dFt12));

    dFa1 = dFt12 * tan(20.0 * (PI / 180)); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    dFa1 = ROUND1(dFa1);
    ui->label_Fa1->setText(QString::number(dFa1));

    ProverkaaNaVinoslivostPoNapryjeniyamIzgiba();
}

void DmWindow::ProverkaaNaVinoslivostPoNapryjeniyamIzgiba(void)
{

    ui->label_StepenTochnostiPeredachi->setText(QString::number(iStepenTochnostiPeredachi));

    dSigmaF61 = (2000.0 * dT3 * 1.0 * dKFV61 * dYF61)/(dm * dd61 * ib61);
    dSigmaF61 = ROUND2(dSigmaF61);
    dSigmaF62 = (2000.0 * dT3 * 1.0 * dKFV61 * dYF62)/(dm * dd61 * ib62);
    dSigmaF62 = ROUND2(dSigmaF62);

    ui->label_sigmaF1->setText(QString::number(dSigmaF61));
    ui->label_sigmaF2->setText(QString::number(dSigmaF62));

    ui->label_sigmaF1_2->setText(QString::number(dSigmaF61));
    ui->label_sigmaF2_2->setText(QString::number(dSigmaF62));

    ui->label_sigmaFF1->setText(QString::number(dSff1));
    ui->label_sigmaFF2->setText(QString::number(dSff2));

    if (dSigmaF61 < dSff1)
    {
        ui->label_otnoshenieSigmaF1SigmaFF1->setText(tr("<"));
    }
    else
    {
        ui->label_otnoshenieSigmaF1SigmaFF1->setText(tr(">"));
    }

    if (dSigmaF62 < dSff2)
    {
        ui->label_otnoshenieSigmaF2SigmaFF2->setText(tr("<"));
    }
    else
    {
        ui->label_otnoshenieSigmaF2SigmaFF2->setText(tr(">"));
    }

    proverkaNaProchnost();
}

void DmWindow::proverkaNaProchnost(void)
{
    dSigmaFmax61 = dSigmaF61 * dTmaxTnom2;
    dSigmaFmax61 = ROUND1(dSigmaFmax61);

    dSigmaFmax62 = dSigmaF62 * dTmaxTnom2;
    dSigmaFmax62 = ROUND1(dSigmaFmax62);

    ui->label_SigmaFmax1->setText(QString::number(dSigmaFmax61));
    ui->label_SigmaFmax2->setText(QString::number(dSigmaFmax62));

    dSigmaFFmax61 = 4.8 * iHB1 / dSF;
    dSigmaFFmax61 = ROUND1(dSigmaFFmax61);

    dSigmaFFmax62 = 4.8 * iHB2 / dSF;
    dSigmaFFmax62 = ROUND1(dSigmaFFmax62);

    ui->label_SigmaFFmax1->setText(QString::number(dSigmaFFmax61));
    ui->label_SigmaFFmax2->setText(QString::number(dSigmaFFmax62));

    if (dSigmaFmax61 < dSigmaFFmax61)
    {
        ui->labelOtnoshenieSigmaFmax1->setText(tr("<"));
    }
    else
    {
        ui->labelOtnoshenieSigmaFmax1->setText(tr(">"));
    }

    if (dSigmaFmax62 < dSigmaFFmax62)
    {
        ui->labelOtnoshenieSigmaFmax2->setText(tr("<"));
    }
    else
    {
        ui->labelOtnoshenieSigmaFmax2->setText(tr(">"));
    }

    proverkaNaKontaktnujuProchnost();
}

void DmWindow::proverkaNaKontaktnujuProchnost(void)
{
    dKHV61 = dKFV61;
    dSigmaH = 426.0 * sqrt(((dFt12 * 1.0 * dKHBeta * dKFV61 * (du3 + 1)) / (dd61 * ib61 * du3)));
    dSigmaH = ROUND2(dSigmaH);

    ui->label_SigmaH->setText(QString::number(dSigmaH));

    dSigmaHmax61 = dSigmaH * sqrt(dTmaxTnom2);
    dSigmaHmax61 = ROUND1(dSigmaHmax61);

    ui->label_SigmaHmax->setText(QString::number(dSigmaHmax61));

    dSigmaHHmax61 = 2.8 * iSt2;
    dSigmaHHmax61 = ROUND1(dSigmaHHmax61);

    ui->label_SigmaHmax->setText(QString::number(dSigmaHHmax61));

    if (dSigmaHmax61 < dSigmaHHmax61)
    {
        ui->label_OtnoshenieSigmaHmax_2->setText(tr("<"));
    }
    else
    {
        ui->label_OtnoshenieSigmaHmax_2->setText(tr(">"));
    }

#ifdef TAB_CONTROL
    if (checkTab6())
        ui->tabWidget->setTabEnabled(5, true);
    else ui->tabWidget->setTabEnabled(5, false);
#else
    checkTab6();
#endif
}

#pragma mark ============ Peredacha Cepnayav =================

void DmWindow::ChisloZubjevZvezdochki(void)
{
    dT3 = ui->doubleSpinBox_T3_2->value();
    dn3 = ui->doubleSpinBox_n3_2->value();
    du3 = ui->doubleSpinBox_u3_2->value();

    iz1 = ROUND(31.0 - 2.0 * du3);
    ui->label_z1_5->setText(QString::number(iz1));

    iz2 = ROUND(du3 * iz1);
    ui->label_z2_5->setText(QString::number(iz2));

    OrientirovochnoeZnachenieDopustimogoDavleniyaVSharnirahCepi();
}

void DmWindow::OrientirovochnoeZnachenieDopustimogoDavleniyaVSharnirahCepi(void)
{
    dqq = ui->doubleSpinBox_q->value();

    KoefficientEkspluatacii();
}

void DmWindow::KoefficientEkspluatacii(void)
{
    dK1 = ui->comboBox_K1->currentText().toDouble();
    dK2 = ui->comboBox_K2->currentText().toDouble();
    dK3 = ui->comboBox_K3->currentText().toDouble();
    dK4 = ui->comboBox_K4->currentText().toDouble();
    dK5 = ui->comboBox_K5->currentText().toDouble();
    dK6 = ui->comboBox_K6->currentText().toDouble();

    dKe = dK1 * dK2 * dK3 * dK4 * dK5 * dK6;
    dKe = ROUND2(dKe);
    ui->label_Ke->setText(QString::number(dKe));

    ShagCepiIzRaschetaIznostoikostiEeSharniriv();
}

void DmWindow::ShagCepiIzRaschetaIznostoikostiEeSharniriv(void)
{
    dKt = ui->doubleSpinBox_Kt->value();

    dpp = 28.0 * pow((dT3 * dKe / (dqq * iz1 * dKt)) , 0.333333333);
    dpp = ROUND1(dpp);

    ui->label_p->setText(QString::number(dpp));

    TypCepi();
}

void DmWindow::TypCepi(void)
{
    iTypCepi = ui->comboBox_Cep->currentIndex();
    dp = ui->comboBox_p->currentText().toDouble();

    int shift = iTypCepi == TypCepi::ODNORYADNAYA ? ui->comboBox_p->currentIndex() : 2*ui->comboBox_p->currentIndex();
    ui->label_oboznachenie->setText(tr(ParametriRolikovihCepey[shift][4]));

    iFp = ui->spinBox_Fp->value();
    dm = ui->doubleSpinBox_m->value();
    iA = ui->spinBox_A->value();

    DiametriZvezdochki();
}

void DmWindow::DiametriZvezdochki(void)
{
    dd61 = dp / sin((180.0/iz1)*(PI/180.0));
    dd61 = ROUND1(dd61);
    ui->label_d1_3->setText(QString::number(dd61));

    dd62 = dp / sin((180.0/iz2)*(PI/180.0));
    dd62 = ROUND1(dd62);
    ui->label_d2_3->setText(QString::number(dd62));

    dKz1 = atan(180.0/iz1) * (180 / PI);
    dKz1 = ROUND3(dKz1);
    ui->label_KZ1->setText(QString::number(dKz1));

    dKz2 = atan(180.0/iz2) * (180 / PI);
    dKz2 = ROUND3(dKz2);
    ui->label_KZ2->setText(QString::number(dKz2));

    int shift = iTypCepi == TypCepi::ODNORYADNAYA ? ui->comboBox_p->currentIndex() : 2*ui->comboBox_p->currentIndex();
    QString dr = ParametriRolikovihCepey[shift][5];
    ddr = dr.toDouble();
    ui->label_dr->setText(QString::number(ddr));

    dLambda = dp / ddr;
    dLambda = ROUND1(dLambda);

    ui->label_Lyambda->setText(QString::number(dLambda));

    dDe1 = dp * (0.6 + dKz1 - 0.31/dLambda);
    dDe1 = ROUND1(dDe1);
    ui->label_De1->setText(QString::number(dDe1));

    dDe2 = dp * (0.6 + dKz2 - 0.31/dLambda);
    dDe2 = ROUND1(dDe2);
    ui->label_De2->setText(QString::number(dDe2));

    dDi1 = dd61 - (ddr - 0.175 * sqrt(dd61));
    dDi1 = ROUND1(dDi1);
    ui->label_Di1->setText(QString::number(dDi1));

    dDi2 = dd62 - (ddr - 0.175 * sqrt(dd62));
    dDi1 = ROUND1(dDi1);
    ui->label_Di2->setText(QString::number(dDi2));

    ShirinaZuba();
}

void DmWindow::ShirinaZuba(void)
{
    int shift = iTypCepi == TypCepi::ODNORYADNAYA ? ui->comboBox_p->currentIndex() : 2*ui->comboBox_p->currentIndex();
    QString b3 = ParametriRolikovihCepey[shift][6];
    db3 = b3.toDouble();
    ui->label_b3->setText(QString::number(db3));

    dbc = 0.93 * db3 - 0.15;
    dbc = ROUND1(dbc);

    ui->label_bc->setText(QString::number(dbc));

    SkoroctCepi();
}

void DmWindow::SkoroctCepi(void)
{
    dVc = dp * iz1 * dn3 / 60000.0;
    dVc = ROUND1(dVc);

    ui->label_Vc->setText(QString::number(dp) + "*" + QString::number(iz1) + "*" + QString::number(dn3) + "/(60*1000) = " + QString::number(dVc));

    MejosevoeRastoyanie();
}

void DmWindow::MejosevoeRastoyanie(void)
{
    double da;

    da = 35.0 * dp;
    da = ROUND(da);
    da = da / 10;
    da = ROUND(da);
    ia = da * 10;

    ui->label_a->setText(QString::number(ia));

    RasstoyanieDliniCepiVShagah();
}

void DmWindow::RasstoyanieDliniCepiVShagah(void)
{
    //lc = 2*a/р+(z1+z2)/2+((z2-z1)/2p)2(р/a) =
    dlcc = 2.0 * ia / dp + (1.0*(iz1+iz2))/2 + pow(((1.0*(iz2-iz1))/(2.0*PI)), 2.0) * (dp/ia);
    dlcc = ROUND1(dlcc);

    ui->label_lcc->setText("2*" + QString::number(ia) + "/" + QString::number(dp) + "+(" + QString::number(iz1) + "+" + QString::number(iz2) + ")/2+(("
                          + QString::number(iz2) + "-" + QString::number(iz1) + tr(")/2*π)<span style=\" font-size:14pt; vertical-align:super;\">2</span>*(")
                          + QString::number(dp) + "/" + QString::number(ia) + ")=" + QString::number(dlcc));

    ilc = ROUND(dlcc);
    ui->label_lc->setText(QString::number(ilc));

    FacticheskoeMejosevoeRastoyanie();
}

void DmWindow::FacticheskoeMejosevoeRastoyanie(void)
{
    da = (dp/4)*(1.0*ilc - 0.5*(iz1+iz2)+sqrt(pow((1.0*ilc - 0.5*(iz1+iz2)), 2.0)-8.0*pow((iz1+iz2),2.0)/pow((2.0*PI),2.0)));
    da = ROUND1(da);
    ui->label_a_2->setText(QString::number(da));

    OkrujnoeUslovie();
}

void DmWindow::OkrujnoeUslovie(void)
{
    dFt12 = (2.0*dT3*1000)/dd61;
    dFt12 = ROUND1(dFt12);
    ui->label_Ft_2->setText(QString::number(dFt12));

    RaschetnayaStreleRasstoyaniya();
}

void DmWindow::RaschetnayaStreleRasstoyaniya(void)
{
    dy = 0.02 * da;
    ui->label_y->setText("0.02*" + QString::number(da) + "=" + QString::number(dy));

    NashalnoeNapryajenie();
}

void DmWindow::NashalnoeNapryajenie(void)
{
    iKf = ui->comboBox_Kf->currentText().toDouble();

    int shift = iTypCepi == TypCepi::ODNORYADNAYA ? ui->comboBox_p->currentIndex() : 2*ui->comboBox_p->currentIndex();
    QString m = ParametriRolikovihCepey[shift][2];
    dm = m.toDouble();

    dFo = 9.81 * iKf * dm * da / 1000;
    ui->label_FO->setText("9.81*" + QString::number(iKf)+ "*" + QString::number(dm) + "*" + QString::number(da) + "/1000=" + QString::number(dFo));

    NatyajenieCepiOtDejstviyaCentorbejnojSili();
}

void DmWindow::NatyajenieCepiOtDejstviyaCentorbejnojSili(void)
{
    dFv = dm * dVc * dVc;
    dFv = ROUND1(dFv);
    ui->label_Fv->setText(QString::number(dFv));

    ProverochnijRaschetPeredachiNaVinoslivost();
}

void DmWindow::ProverochnijRaschetPeredachiNaVinoslivost(void)
{
    dq = dFt12 * dKe / (dKt*iA);
    dq = ROUND1(dq);
    ui->label_q->setText(QString::number(dq));

    dqqq = ui->doubleSpinBox_q_2->value();

    if (dq > dqqq)
    {
        ui->label_Otnoshenieq->setText(">");
    }
    else
    {
        ui->label_Otnoshenieq->setText("<");
    }

    ProverochnijRaschetCepiNaStaticheskuyuProchnost();
}

void DmWindow::ProverochnijRaschetCepiNaStaticheskuyuProchnost(void)
{
    dS = iFp / (dFt12 + dFv + dFo);
    dS = ROUND1(dS);
    ui->label_S->setText(QString::number(dS));

    dS = ui->spinBox_S->value();

    if (dS > dSS)
    {
        ui->label_OtnoshenieS->setText(">");
    }
    else
    {
        ui->label_OtnoshenieS->setText("≤");
    }

    RaschetnayaNAgruzkaNAValiPeredachi();
}

void DmWindow::RaschetnayaNAgruzkaNAValiPeredachi(void)
{
    dR = 1.15 * dFt12;
    dR = ROUND1(dR);
    ui->label_R->setText(QString::number(dR));

#ifdef TAB_CONTROL
    if (checkTab6())
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

    if (CurrentPeredacha == Peredacha::CILINDRICHESKAYA)
    {
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
            if (dmm3 >= raschetnoeZnachenieModulay[i])
            {
                dTempVal1 = raschetnoeZnachenieModulay[i+1] - dmm3;
                dTempVal2 = dmm3 - raschetnoeZnachenieModulay[i];
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

        if (dV61 <= 2)
        {
            iTempVal1 = 9;
        }
        else if (dV61 <= 6)
        {
            iTempVal1 = 8;
        }
        else if (dV61 <= 10)
        {
            iTempVal1 = 7;
        }
        else if (dV61 <= 15)
        {
            iTempVal1 = 6;
        }
        else
        {
            iTempVal1 = 5;
        }

        if (iStepenTochnostiPeredachi != iTempVal1)
        {
            ui->label_checkStepenTochnosti->setVisible(true);
            noErrors = false;
        }
        else ui->label_checkStepenTochnosti->setVisible(false);

        if(iStepenTochnostiPeredachi >=6 && iStepenTochnostiPeredachi <= 9)
        {
            if (dV61 < 1)
            {
                dTempVal1 = 1.1;
            }
            else
            {
                if(dV61 < 1.5)
                {
                    iTempVal1 = 0;
                }
                else if(dV61 < 2.5)
                {
                    iTempVal1 = 1;
                }
                else if(dV61 >= 2.5 && dV61 < 4.5)
                {
                    iTempVal1 = 2;
                }
                else if(dV61 >= 4.5 && dV61 < 6.5)
                {
                    iTempVal1 = 3;
                }
                else if(dV61 >= 6.5 && dV61 < 8.5)
                {
                    iTempVal1 = 4;
                }
                else if(dV61 >= 8.5)
                {
                    iTempVal1 = 5;
                }

                dTempVal1 = KoeficientKFV2[iStepenTochnostiPeredachi-6][iTempVal1];
            }
        }
        else dTempVal1 = -1.0;

        if (dKFV61 != iTempVal1)
        {
            ui->label_checkKfv->setVisible(true);
            noErrors = false;
        }
        else ui->label_checkKfv->setVisible(false);

        if (dSigmaF61 < dSff1 && dSigmaF62 < dSff2)
        {
            ui->label_checksigmaF1F2->setText(tr("<span style=\" color:#ff0000;\">Условие выносливости на изгиб выполняется.</span>"));
        }
        else
        {
            ui->label_checksigmaF1F2->setText(tr("<span style=\" color:#ff0000;\">Условие  выносливости на изгиб не выполняется, пожалуйста уточните!</span>"));
            noErrors = false;
        }

        if (dSigmaFmax61 < dSigmaFFmax61 && dSigmaFmax62 < dSigmaFFmax62)
        {
            ui->label_checkSigmaFmax12->setText(tr("<span style=\" color:#ff0000;\">Условие контактной выносливости выполняется.</span>"));
        }
        else
        {
            ui->label_checkSigmaFmax12->setText(tr("<span style=\" color:#ff0000;\">Условие контактной выносливости не выполняется, пожалуйста уточните!</span>"));
            noErrors = false;
        }

        if (dSigmaHmax61 < dSigmaHHmax61)
        {
            ui->label_checkSigmaHmax->setText(tr("<span style=\" color:#ff0000;\">Условие контактной выносливости выполняется.</span>"));
        }
        else
        {
            ui->label_checkSigmaHmax->setText(tr("<span style=\" color:#ff0000;\">Условие контактной выносливости не выполняется, пожалуйста уточните!</span>"));
            noErrors = false;
        }
    }
    else if (CurrentPeredacha == Peredacha::CEPNAYA)
    {
        if (dT3 != dValT3 || dn3 != dValN3 || du3 != dValI3)
        {
            ui->label_CheckVvod5_2->setVisible(true);
            noErrors = false;
        } else ui->label_CheckVvod5_2->setVisible(false);

        if ((dKt == 1.0 && ui->comboBox_Cep->currentIndex() != 0) || (dKt == 1.7 && ui->comboBox_Cep->currentIndex() != 1))
        {
            ui->label_checkCep->setVisible(true);
            noErrors = false;
        } else ui->label_checkCep->setVisible(false);

        if (dp > dpp*0.8 && dp < dpp*1.4)
        {
            ui->label_checkp->setVisible(false);
        } else {
            ui->label_checkp->setVisible(true);
            noErrors = false;
        }

        if ((dKt == 1.0 && ui->comboBox_Cep->currentIndex() != TypCepi::ODNORYADNAYA) || (dKt == 1.7 && ui->comboBox_Cep->currentIndex() != TypCepi::DVUHRYADNAYA))
        {
            ui->label_checkTipCepi->setVisible(true);
            noErrors = false;
        } else ui->label_checkTipCepi->setVisible(false);

        int shift = iTypCepi == TypCepi::ODNORYADNAYA ? ui->comboBox_p->currentIndex() : 2*ui->comboBox_p->currentIndex();
        QString __iFp = ParametriRolikovihCepey[shift][3];
        int _iFp = __iFp.toInt();

        QString __dm = ParametriRolikovihCepey[shift][2];
        double _dm = __dm.toDouble();

        QString __iA = ParametriRolikovihCepey[shift][1];
        int _iA = __iA.toInt();

        if (_iFp != iFp || _dm != dm || _iA != iA)
        {
            ui->label_checkTipCepi->setVisible(true);
            noErrors = false;
        } else ui->label_checkTipCepi->setVisible(false);

        if (dq > dqqq)
        {
            ui->label_checkq->setText(tr("<span style=\" color:#ff0000;\">Условие не выполняется!</span>"));
            noErrors = false;
        }
        else
        {
            ui->label_checkq->setText(tr("<span style=\" color:#ff0000;\">Условие выполняется</span>"));
        }

        if (dS < dSS)
        {
            ui->label_checkS->setText(tr("<span style=\" color:#ff0000;\">Прочность не обеспечивается, пожалуйста проверте!</span>"));
            noErrors = false;
        }
        else
        {
            ui->label_checkS->setText(tr("<span style=\" color:#ff0000;\">Прочность обеспечивается</span>"));
        }
    }

    return noErrors;
}
