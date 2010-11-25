#include "dmwindow.h"
#include "ui_dmwindow.h"
#include "defines/table2.h"

void DmWindow::updateLabelTextTab3(void)
{
    QString text1 = ui->comboBox_sechenieRemnya1->currentText() + tr(":");
    QString text2 = ui->comboBox_sechenieRemnya2->currentText() + tr(":");

    ui->label_RemenType0_1->setText(text1);
    ui->label_RemenType0_2->setText(text2);

    ui->label_RemenType1->setText(text1);
    ui->label_RemenType2->setText(text2);

    ui->label_RemenType1_2->setText(text1);
    ui->label_RemenType2_2->setText(text2);

    ui->label_RemenType1_3->setText(text1);
    ui->label_RemenType2_3->setText(text2);

    ui->label_RemenType1_4->setText(text1);
    ui->label_RemenType2_4->setText(text2);

    ui->label_RemenType1_5->setText(text1);
    ui->label_RemenType2_5->setText(text2);

    ui->label_RemenType1_6->setText(text1);
    ui->label_RemenType2_6->setText(text2);

    ui->label_RemenType1_7->setText(text1);
    ui->label_RemenType2_7->setText(text2);

    ui->label_RemenType1_8->setText(text1);
    ui->label_RemenType2_8->setText(text2);

    ui->label_RemenType1_9->setText(text1);
    ui->label_RemenType2_9->setText(text2);

    ui->label_RemenType1_10->setText(text1);
    ui->label_RemenType2_10->setText(text2);

    ui->label_RemenType1_11->setText(text1);
    ui->label_RemenType2_11->setText(text2);

    ui->label_RemenType1_12->setText(text1);
    ui->label_RemenType2_12->setText(text2);

    updateDiametrVedushegoShkiva();

}

void DmWindow::updateDiametrVedushegoShkiva(void)
{
    dVald11 = ui->comboBox_diametrRemnya1->currentText().toInt();
    dVald12 = ui->comboBox_diametrRemnya2->currentText().toInt();

    updateDiametrVedomogoShkiva();
}

void DmWindow::updateDiametrVedomogoShkiva(void)
{

    dValU = ROUND2(ui->doubleSpinBox_peredatochnoeOtnoshenie->value());

    ui->label_RaschetnoeZnachenie1->setText(QString::number(dVald11*dValU));
    ui->label_RaschetnoeZnachenie2->setText(QString::number(dVald12*dValU));

    dVald21 = ui->comboBox_standart1->currentText().toDouble();
    dVald22 = ui->comboBox_standart2->currentText().toDouble();

    updatePeredatochnoeChislo();

}

void DmWindow::updatePeredatochnoeChislo(void)
{
    dValXi = ui->doubleSpinBox_Xi->value();
    dValU1 = ROUND2(dVald21/(dVald11*(1.0 - dValXi)));
    ui->label_u1_1->setText(QString::number(dVald21) + tr("/(") + QString::number(dVald11) + tr("*(1-") + QString::number(dValXi) + tr("))=") + QString::number(dValU1));

    dValU2 = ROUND2(dVald22/(dVald12*(1.0 - ui->doubleSpinBox_Xi->value())));
    ui->label_u1_2->setText(QString::number(dVald22) + tr("/(") + QString::number(dVald12) + tr("*(1-") + QString::number(dValXi) + tr("))=") + QString::number(dValU2));

    updatePredMejosevoeRastoyanie();
}

void DmWindow::updatePredMejosevoeRastoyanie(void)
{
    uint i;

    for (i = 0 ; i < LENGTH(rastoyanieKlinovoyPeredachi); ++i)
        if (dValU <= rastoyanieKlinovoyPeredachi[i][0])
        {
            break;
        }

    dValaa1 = ROUND1(rastoyanieKlinovoyPeredachi[i][1] * dVald21);
    dValaa2 = ROUND1(rastoyanieKlinovoyPeredachi[i][1] * dVald22);

    ui->label_aa1->setText(QString::number(rastoyanieKlinovoyPeredachi[i][1]) + tr("*d<span style=\" vertical-align:sub;\">2</span>=") + QString::number(rastoyanieKlinovoyPeredachi[i][1]) + tr("*") + QString::number(dVald21) + tr("=") + QString::number(dValaa1));
    ui->label_aa2->setText(QString::number(rastoyanieKlinovoyPeredachi[i][1]) + tr("*d<span style=\" vertical-align:sub;\">2</span>=") + QString::number(rastoyanieKlinovoyPeredachi[i][1]) + tr("*") + QString::number(dVald22) + tr("=") + QString::number(dValaa2));

    updateDlinaRemnya();
}

void DmWindow::updateDlinaRemnya(void)
{
    dValll1 = (2 * dValaa1) + (PI * (dVald11 + dVald21) / 2) + (((dVald21 - dVald11) * (dVald21 - dVald11)) / (4 * dValaa1));
    dValll1 = ROUND1(dValll1);
    dValll2 = (2 * dValaa2) + (PI * (dVald12 + dVald22) / 2) + (((dVald22 - dVald12) * (dVald22 - dVald12)) / (4 * dValaa2));
    dValll2 = ROUND1(dValll2);

    ui->label_ll1->setText(tr("2*") + QString::number(dValaa1) + tr("+3.14*(") + QString::number(dVald11) + tr("+") + QString::number(dVald21) + tr(")/2+(")
                           + QString::number(dVald21) + tr("-") + QString::number(dVald11) + tr(")<span style=\" vertical-align:super;\">2</span>/4*") + QString::number(dValaa1)
                           + tr("=") + QString::number(dValll1));

    ui->label_ll2->setText(tr("2*") + QString::number(dValaa2) + tr("+3.14*(") + QString::number(dVald12) + tr("+") + QString::number(dVald22) + tr(")/2+(")
                           + QString::number(dVald22) + tr("-") + QString::number(dVald12) + tr(")<span style=\" vertical-align:super;\">2</span>/4*") + QString::number(dValaa2)
                           + tr("=") + QString::number(dValll2));

    updateStandartDlinaRemnya();
}

void DmWindow::updateStandartDlinaRemnya(void)
{
    dVall1 = ui->comboBox_L2->currentText().toDouble();
    dVall2 = ui->comboBox_L2_2->currentText().toDouble();

    updateMejosevoeRastoyanie();
}

void DmWindow::updateMejosevoeRastoyanie(void)
{
    dVala1 = ROUND1(dValaa1 + (abs(dVall1 - dValll1))/2);
    dVala2 = ROUND1(dValaa2 + (abs(dVall2 - dValll2))/2);

    ui->label_a1->setText(QString::number(dValaa1) + tr("+|") + QString::number(dVall1) + tr("-") + QString::number(dValll1) + tr("|/2=") + QString::number(dVala1));
    ui->label_a2->setText(QString::number(dValaa2) + tr("+|") + QString::number(dVall2) + tr("-") + QString::number(dValll2) + tr("|/2=") + QString::number(dVala2));

    updateSkorostRemney();
}

void DmWindow::updateSkorostRemney(void)
{
    dValV1 = ROUND2(PI * dVald11 * dValN1 / 60000.0);
    dValV2 = ROUND2(PI * dVald12 * dValN1 / 60000.0);

    ui->label_V1->setText(tr("3.14*") + QString::number(dVald11) + tr("*") + QString::number(dValN1) + tr("/60000=") + QString::number(dValV1));
    ui->label_V2->setText(tr("3.14*") + QString::number(dVald12) + tr("*") + QString::number(dValN1) + tr("/60000=") + QString::number(dValV2));

    updateDolgovechnostiRemney();
}

void DmWindow::updateDolgovechnostiRemney(void)
{
    dValNpr1 = ROUND2(dValV1 * 1000 / dVall1);
    dValNpr2 = ROUND2(dValV2 * 1000 / dVall2);

    ui->label_npr1->setText(QString::number(dValV1) + tr("*1000/") + QString::number(dVall1) + tr("=") + QString::number(dValNpr1));
    ui->label_npr2->setText(QString::number(dValV2) + tr("*1000/") + QString::number(dVall2) + tr("=") + QString::number(dValNpr2));

    updateUgolObhvataMinShkiva();
}

void DmWindow::updateUgolObhvataMinShkiva(void)
{
    dValAlpha1 = ROUND1(180 - (dVald21 - dVald11) * 57 / dVala1);
    dValAlpha2 = ROUND1(180 - (dVald22 - dVald12) * 57 / dVala2);

    ui->label_alpha1->setText(tr("180-(") + QString::number(dVald21) + tr("-") + QString::number(dVald11) + tr(")*57/") + QString::number(dVala1)
                              + tr("=") + QString::number(dValAlpha1));
    ui->label_alpha2->setText(tr("180-(") + QString::number(dVald22) + tr("-") + QString::number(dVald12) + tr(")*57/") + QString::number(dVala2)
                              + tr("=") + QString::number(dValAlpha2));

    updateMoshnostNaOdnomRemne();
}

void DmWindow::updateMoshnostNaOdnomRemne(void)
{
    for (int i = LENGTH(koeficientKp)-2 ; i >= 0; i--)
        if (dValU >= koeficientKp[i][0])
        {
            double temp1 = koeficientKp[i+1][0] - dValU;
            double temp2 = dValU - koeficientKp[i][0];
            if(temp1 < temp2)
                dValKp = koeficientKp[i+1][1];
            else
                dValKp = koeficientKp[i][1];
            break;
        }

    for (int i = LENGTH(koeficientCa)-2 ; i >= 0; i--)
        if (dValAlpha1 >= koeficientCa[i][0])
        {
            double temp1 = koeficientCa[i+1][0] - dValAlpha1;
            double temp2 = dValAlpha1 - koeficientCa[i][0];
            if(temp1 < temp2)
            {
                dValCa1 = koeficientCa[i+1][1];
                dVala12 = koeficientCa[i+1][0];
            }
            else
            {
                dValCa1 = koeficientCa[i][1];
                dVala12 = koeficientCa[i][0];
            }
            break;
        }
    for (int i = LENGTH(koeficientCa)-2 ; i >= 0; i--)
        if (dValAlpha2 >= koeficientCa[i][0])
        {
            double temp1 = koeficientCa[i+1][0] - dValAlpha2;
            double temp2 = dValAlpha2 - koeficientCa[i][0];
            if(temp1 < temp2)
            {
                dValCa2 = koeficientCa[i+1][1];
                dVala22 = koeficientCa[i+1][0];
            }
            else
            {
                dValCa2 = koeficientCa[i][1];
                dVala22 = koeficientCa[i][0];
            }
            break;
        }

    uint startPos1 = 0;
    uint startPos2 = 0;
    uint endPos1 = 0;
    uint endPos2 = 0;

    int index1 = ui->comboBox_sechenieRemnya1->currentIndex();
    int index2 = ui->comboBox_sechenieRemnya2->currentIndex();
    if (index1 == 3)
    {
        startPos1 = 1 + 5 * index1;
        endPos1   = 1 + 5 * index1 + 4;
    } else
    {
        startPos1 = 1 + 5 * index1;
        endPos1   = 1 + 5 * index1 + 5;
    }

    if (index2 == 3)
    {
        startPos2 = 1 + 5 * index2;
        endPos2   = 1 + 5 * index2 + 4;
    } else
    {
        startPos2 = 1 + 5 * index2;
        endPos2   = 1 + 5 * index2 + 5;
    }

    dValPo1 = getValPo(startPos1, endPos1, dVald11, dValV1);
    dValPo2 = getValPo(startPos2, endPos2, dVald12, dValV2);

    dVal_ll1 = ROUND2(dVall1 / diametrShkivov[ui->comboBox_sechenieRemnya1->currentIndex()][1]);
    dVal_ll2 = ROUND2(dVall2 / diametrShkivov[ui->comboBox_sechenieRemnya2->currentIndex()][1]);

    for (int i = LENGTH(koeficientCl)-2 ; i >= 0; i--)
        if (dVal_ll1 >= koeficientCl[i][0])
        {
            double temp1 = koeficientCl[i+1][0] - dVal_ll1;
            double temp2 = dVal_ll1 - koeficientCl[i][0];
            if(temp1 < temp2)
            {
                dValCl1 = koeficientCl[i+1][1];
            }
            else
            {
                dValCl1 = koeficientCl[i][1];
            }
            break;
        }

    for (int i = LENGTH(koeficientCl)-2 ; i >= 0; i--)
        if (dVal_ll2 >= koeficientCl[i][0])
        {
            double temp1 = koeficientCl[i+1][0] - dVal_ll2;
            double temp2 = dVal_ll2 - koeficientCl[i][0];
            if(temp1 < temp2)
            {
                dValCl2 = koeficientCl[i+1][1];
            }
            else
            {
                dValCl2 = koeficientCl[i][1];
            }
            break;
        }

    dVal_ll1 = ROUND1(dVal_ll1);
    dVal_ll2 = ROUND1(dVal_ll2);

    dValPPo1 = ROUND2(dValKp * dValPo1 * dValCa1 * dValCl1);
    dValPPo2 = ROUND2(dValKp * dValPo2 * dValCa2 * dValCl2);

    ui->tableWidgetSechenie->setItem(0, 0 , new QTableWidgetItem(ui->comboBox_sechenieRemnya1->currentText()));
    ui->tableWidgetSechenie->setItem(1, 0 , new QTableWidgetItem(ui->comboBox_sechenieRemnya2->currentText()));
    ui->tableWidgetSechenie->setItem(0, 1 , new QTableWidgetItem(QString::number(dValKp)));
    ui->tableWidgetSechenie->setItem(1, 1 , new QTableWidgetItem(QString::number(dValKp)));
    ui->tableWidgetSechenie->setItem(0, 2 , new QTableWidgetItem(QString::number(dValPo1)));
    ui->tableWidgetSechenie->setItem(1, 2 , new QTableWidgetItem(QString::number(dValPo2)));
    ui->tableWidgetSechenie->setItem(0, 3 , new QTableWidgetItem(QString::number(dValPPo1)));
    ui->tableWidgetSechenie->setItem(1, 3 , new QTableWidgetItem(QString::number(dValPPo2)));

    ui->label_a1_2->setText(QString::number(dVala12));
    ui->label_a1_3->setText(QString::number(dVala22));

    ui->label_ll01->setText(QString::number(dVal_ll1));
    ui->label_ll02->setText(QString::number(dVal_ll2));

    updateKolichestvoRemney();
}

void DmWindow::updateKolichestvoRemney(void)
{
    dValCp = ui->comboBox_Cp->currentText().toDouble();
    dValCz1 = ROUND2(ui->doubleSpinBox_Cz1->value());
    dValCz2 = ROUND2(ui->doubleSpinBox_Cz2->value());

    iValRemen1 = ROUND(dValP1/dValPPo1);
    iValRemen2 = ROUND(dValP1/dValPPo2);

    ui->label_zz1->setText(QString::number(iValRemen1));
    ui->label_zz2->setText(QString::number(iValRemen2));

    iValZp1 = ROUND(dValP1*dValCp/(dValPPo1*dValCz1));
    iValZp2 = ROUND(dValP1*dValCp/(dValPPo2*dValCz2));

    ui->label_Zp1->setText(QString::number(dValP1) + tr("*") + QString::number(dValCp) + tr("/(") + QString::number(dValPPo1) + tr("*") + QString::number(dValCz1) + tr(")=") + QString::number(iValZp1));
    ui->label_Zp2->setText(QString::number(dValP2) + tr("*") + QString::number(dValCp) + tr("/(") + QString::number(dValPPo2) + tr("*") + QString::number(dValCz2) + tr(")=") + QString::number(iValZp2));

    updateNatyajenieRemnya();
}

void DmWindow::updateNatyajenieRemnya(void)
{
    double Ca = 0;
    double V = 0;
    double z = 0;
    double Cl = 0;
    double q = ui->comboBox_q->currentText().toDouble();

    bool bTrueCheck = false;

    if (ui->comboBox_sechenieRemnya3->currentIndex() == ui->comboBox_sechenieRemnya1->currentIndex())
    {
        Ca = dValCa1;
        V  = dValV1;
        z  = iValZp1;
        Cl = dValCl1;

        bTrueCheck = true;
    }
    else if (ui->comboBox_sechenieRemnya3->currentIndex() == ui->comboBox_sechenieRemnya2->currentIndex())
    {
        Ca = dValCa2;
        V  = dValV2;
        z  = iValZp2;
        Cl = dValCl2;

        bTrueCheck = true;
    }
    
    if (bTrueCheck)
    {
        dValF0 = ((850.0 * dValP1 * Cl) / (z * V * Ca * dValCp)) + q * (V*V);
        dValF0 = ROUND1(dValF0);
    }
    else
    {
        dValF0 = 0;
    }

    ui->label_F0->setText(QString::number(dValF0));
    
    updateNagruzkaVala();
}

void DmWindow::updateNagruzkaVala(void)
{

    double z = 0;
    double a1 = 0;

    if (ui->comboBox_sechenieRemnya3->currentIndex() == ui->comboBox_sechenieRemnya1->currentIndex())
    {
        a1 = dValAlpha1;
        z  = iValZp1;
    }
    else if (ui->comboBox_sechenieRemnya3->currentIndex() == ui->comboBox_sechenieRemnya2->currentIndex())
    {
        a1 = dValAlpha2;
        z  = iValZp1;
    }

    dValRn = ROUND1(dValF0 * z * sin((a1/2.0)*(PI/180.0)));

    ui->label_Rn->setText(QString::number(dValRn));

    updateOsnovnieRazmeriShkivov();
}

void DmWindow::updateOsnovnieRazmeriShkivov(void)
{
    dValde1 = ROUND1(dVald11 + 2.0 * jolobStandart[ui->comboBox_sechenieRemnya1->currentIndex()][0]);
    dValde2 = ROUND1(dVald12 + 2.0 * jolobStandart[ui->comboBox_sechenieRemnya2->currentIndex()][0]);

    ui->label_de1->setText(QString::number(dVald11) + tr("+2*") + QString::number(jolobStandart[ui->comboBox_sechenieRemnya1->currentIndex()][0]) + tr("=") + QString::number(dValde1));
    ui->label_de2->setText(QString::number(dVald12) + tr("+2*") + QString::number(jolobStandart[ui->comboBox_sechenieRemnya2->currentIndex()][0]) + tr("=") + QString::number(dValde2));

    double z = 0;

    if (ui->comboBox_sechenieRemnya3->currentIndex() == ui->comboBox_sechenieRemnya1->currentIndex())
    {
        z  = iValZp1;
    }
    else if (ui->comboBox_sechenieRemnya3->currentIndex() == ui->comboBox_sechenieRemnya2->currentIndex())
    {
        z  = iValZp1;
    }

    dValM = ROUND2((z - 1)*jolobStandart[ui->comboBox_sechenieRemnya3->currentIndex()][2] + 2 * jolobStandart[ui->comboBox_sechenieRemnya3->currentIndex()][3]);
    ui->label_M->setText(QString::number(dValM));

#ifdef TAB_CONTROL
    if (checkTab3())
        ui->tabWidget->setTabEnabled(3, true);
    else ui->tabWidget->setTabEnabled(3, false);
#else
    checkTab3();
#endif

}

bool DmWindow::checkTab3(void)
{
    bool noErrors = true;
    double temp1 = ROUND2(ui->doubleSpinBox_moshnistNaVedushijVal->value());

    if(dValP1 != temp1 ||
       dValN1 != ui->spinBox_ChastotaVrasheniya->value() ||
       dValI1 != dValU)
    {
        ui->label_CheckInputValue->setVisible(true);
        noErrors = false;
    } else ui->label_CheckInputValue->setVisible(false);

    QString _text1;
    QString _text2;

    if (dValT1 < 30 )
    {
        _text1 = tr("О");
        _text2 = tr("А");
    }
    else if (dValT1 < 60 )
    {
        _text1 = tr("А");
        _text2 = tr("Б");
    }
    else if (dValT1 < 150 )
    {
        _text1 = tr("Б");
        _text2 = tr("В");
    }
    else
    {
        _text1 = tr("В");
        _text2 = tr("");
    }

    if (ui->comboBox_sechenieRemnya1->currentText() != _text1 || ui->comboBox_sechenieRemnya2->currentText() != _text2)
    {
        ui->label_Check_Remen->setVisible(true);
        noErrors = false;
    } else ui->label_Check_Remen->setVisible(false);

    if (dVald11 < diametrShkivov[ui->comboBox_sechenieRemnya1->currentIndex()][0]
        || dVald12 < diametrShkivov[ui->comboBox_sechenieRemnya2->currentIndex()][0])
    {
        ui->label_Check_VedushiyShkiv->setVisible(true);
        noErrors = false;
    } else ui->label_Check_VedushiyShkiv->setVisible(false);

    double tempVal = ui->label_RaschetnoeZnachenie1->text().toDouble();
    for (uint i = 0 ; i < LENGTH(standartShkiva); i++)
        if (tempVal <= standartShkiva[i])
        {
            tempVal = standartShkiva[i];
            break;
        }
    if (dVald21 < tempVal)
    {
        ui->label_Check_VedomiyShkiv1->setVisible(true);
        noErrors = false;
    } else ui->label_Check_VedomiyShkiv1->setVisible(false);

    tempVal = ui->label_RaschetnoeZnachenie2->text().toDouble();
    for (uint i = 0 ; i < LENGTH(standartShkiva); i++)
        if (tempVal <= standartShkiva[i])
        {
            tempVal = standartShkiva[i];
            break;
        }
    if (dVald22 < tempVal)
    {
        ui->label_Check_VedomiyShkiv2->setVisible(true);
        noErrors = false;
    } else ui->label_Check_VedomiyShkiv2->setVisible(false);

    tempVal = dValll1;
    for (int i = LENGTH(ryadKlinovihRemney)-2 ; i >= 0; i--)
        if (tempVal >= ryadKlinovihRemney[i])
        {
            double temp1 = ryadKlinovihRemney[i+1] - tempVal;
            double temp2 = tempVal - ryadKlinovihRemney[i];
            if(temp1 < temp2)
                tempVal = ryadKlinovihRemney[i+1];
            else
                tempVal = ryadKlinovihRemney[i];
            break;
        }
    if(dVall1 < tempVal)
    {
        ui->label_Check_StandartRemny1->setVisible(true);
        noErrors = false;
    } else ui->label_Check_StandartRemny1->setVisible(false);

    tempVal = dValll2;
    for (int i = LENGTH(ryadKlinovihRemney)-2 ; i >= 0; i--)
        if (tempVal >= ryadKlinovihRemney[i])
        {
            double temp1 = ryadKlinovihRemney[i+1] - tempVal;
            double temp2 = tempVal - ryadKlinovihRemney[i];
            if(temp1 < temp2)
                tempVal = ryadKlinovihRemney[i+1];
            else
                tempVal = ryadKlinovihRemney[i];
            break;
        }
    if(dVall2 < tempVal)
    {
        ui->label_Check_StandartRemny2->setVisible(true);
        noErrors = false;
    } else ui->label_Check_StandartRemny2->setVisible(false);

    if(dValNpr1 >= 15)
    {
        ui->label_Check_Uslovie11->setText(tr("<span style=\" color:#ff0000;\">- условие не выполняется</span>"));
        noErrors = false;
    } else ui->label_Check_Uslovie11->setText(tr("<span style=\" color:#ff0000;\">- условие выполняется</span>"));

    if(dValNpr2 >= 15)
    {
        ui->label_Check_Uslovie12->setText(tr("<span style=\" color:#ff0000;\">- условие не выполняется</span>"));
        noErrors = false;
    } else ui->label_Check_Uslovie12->setText(tr("<span style=\" color:#ff0000;\">- условие выполняется</span>"));

    if(dValAlpha1 <= 120)
    {
        ui->label_Check_Uslovie21->setText(tr("<span style=\" color:#ff0000;\">- условие не выполняется</span>"));
        noErrors = false;
    } else ui->label_Check_Uslovie21->setText(tr("<span style=\" color:#ff0000;\">- условие выполняется</span>"));

    if(dValAlpha1 <= 120)
    {
        ui->label_Check_Uslovie22->setText(tr("<span style=\" color:#ff0000;\">- условие не выполняется</span>"));
        noErrors = false;
    } else ui->label_Check_Uslovie22->setText(tr("<span style=\" color:#ff0000;\">- условие выполняется</span>"));

    if (ui->comboBox_Ca1->currentText().toDouble() != dValCa1)
    {
        ui->label_CheckCa1->setVisible(true);
        noErrors = false;
    } else ui->label_CheckCa1->setVisible(false);

    if (ui->comboBox_Ca2->currentText().toDouble() != dValCa2)
    {
        ui->label_CheckCa2->setVisible(true);
        noErrors = false;
    } else ui->label_CheckCa2->setVisible(false);

    if (ui->comboBox_Cl1->currentText().toDouble() != dValCl1)
    {
        ui->label_checkCl1->setVisible(true);
        noErrors = false;
    } else ui->label_checkCl1->setVisible(false);

    if (ui->comboBox_Cl2->currentText().toDouble() != dValCl2)
    {
        ui->label_checkCl2->setVisible(true);
        noErrors = false;
    } else ui->label_checkCl2->setVisible(false);

    if (iValRemen1 < 2)
        tempVal = 1.00;
    else if (iValRemen1 == 2)
        tempVal = 0.95;
    else if (iValRemen1 > 2)
        tempVal = 0.90;

    if (dValCz1 != tempVal)
    {
        ui->label_checkCz1->setVisible(true);
        noErrors = false;
    } else ui->label_checkCz1->setVisible(false);

    if (iValRemen2 < 2)
        tempVal = 1.00;
    else if (iValRemen2 == 2)
        tempVal = 0.95;
    else if (iValRemen2 > 2)
        tempVal = 0.90;

    if (dValCz2 != tempVal)
    {
        ui->label_checkCz2->setVisible(true);
        noErrors = false;
    } else ui->label_checkCz2->setVisible(false);

    if (iValZp1 > 5)
    {
        ui->label_checkZp1->setVisible(true);
    } else ui->label_checkZp1->setVisible(false);

    if (iValZp2 > 5)
    {
        ui->label_checkZp2->setVisible(true);
    } else ui->label_checkZp2->setVisible(false);

    if ((ui->comboBox_sechenieRemnya3->currentIndex() != ui->comboBox_sechenieRemnya1->currentIndex() && ui->comboBox_sechenieRemnya3->currentIndex() != ui->comboBox_sechenieRemnya2->currentIndex())
        || ((ui->comboBox_sechenieRemnya3->currentIndex() == ui->comboBox_sechenieRemnya1->currentIndex() && iValZp1 > 5))
        || ((ui->comboBox_sechenieRemnya3->currentIndex() == ui->comboBox_sechenieRemnya2->currentIndex()) && iValZp2 > 5))
    {
        ui->label_checkSechebie3->setVisible(true);
        noErrors = false;
    } else ui->label_checkSechebie3->setVisible(false);

    if (ui->comboBox_q->currentIndex() !=  ui->comboBox_sechenieRemnya3->currentIndex())
    {
        ui->label_checkQ->setVisible(true);
        noErrors = false;
    } else ui->label_checkQ->setVisible(false);


    return noErrors;

}

double DmWindow::getValPo(uint start, uint end, double d1, double v)
{
    double Po = 0;

    bool bExist = false;

    uint len = LENGTH(dopustimayaPrivedenayaMoshnost[0]);

    for (uint i = start ; i <= end ; i++)
    {
        if (d1 == dopustimayaPrivedenayaMoshnost[i][0])
        {
            for(uint j = 1 ; j < len ; j++)
            {
                if (v < dopustimayaPrivedenayaMoshnost[0][j])
                {
                    Po = dopustimayaPrivedenayaMoshnost[i][j];
                    bExist = true;

                    break;
                }
            }

            break;
        }
    }

    return Po;
}
