#include "dmwindow.h"
#include "ui_dmwindow.h"
#include "defines/table1.h"

void DmWindow::updateKPDText(void)
{
    dValEta1 = ui->doubleSpinBox_nu1->value();
    dValEta2 = ui->doubleSpinBox_nu2->value();
    dValEta3 = ui->doubleSpinBox_nu3->value();
    dValEta = ROUND2(dValEta1 * dValEta2 * dValEta3);
    ui->label_KPD->setText(QString::number(dValEta1) + "*" + QString::number(dValEta2) + "*" + QString::number(dValEta3) + "=" + QString::number(dValEta));

    updatePValues();
}

void DmWindow::updatePValues(void)
{
    ui->label_P4->setText("");
    if (ui->doubleSpinBox_P->value() == 0)
    {
        if (iValFt > 0 && dValV > 0)
        {
            dValPiv = dValV * iValFt;
            ui->label_P4->setText(QString::number(iValFt) + tr("+") + QString::number(dValV) + tr("="));
        }
    }
    else dValPiv = ui->doubleSpinBox_P->value();

    ui->label_P4->setText(ui->label_P4->text() + QString::number(dValPiv));
    double tmp = dValPiv/dValEta;
    tmp = ROUND2(tmp);
    ui->label_Pl->setText(QString::number(dValPiv) + tr("/") + QString::number(dValEta) + tr("=") + QString::number(tmp));

    on_comboBox_Pnom_currentIndexChanged();
}

void DmWindow::updatePnomTable(void)
{
    int index = ui->comboBox_Pnom->currentIndex();
    for (int i = 0 ; i < ui->tableWidgetPnom->columnCount() ; i ++)
    {
        ui->tableWidgetPnom->setItem(0, i , new QTableWidgetItem(tr(sincOfRotationHertz750[index][i])));
        ui->tableWidgetPnom->setItem(1, i , new QTableWidgetItem(tr(sincOfRotationHertz1000[index][i])));
        ui->tableWidgetPnom->setItem(2, i , new QTableWidgetItem(tr(sincOfRotationHertz1500[index][i])));
        ui->tableWidgetPnom->setItem(3, i , new QTableWidgetItem(tr(sincOfRotationHertz3000[index][i])));
    }
}
void DmWindow::on_comboBox_Pnom_currentIndexChanged(void)
{
    updatePnomTable();
    updateNValues();
    updateIValues();
}

void DmWindow::updateTablePeredatochnoeOtnoshenie(void)
{
    ui->tableWidget_4Privoda->setItem(1, 0, new QTableWidgetItem(ui->comboBoxPrivodType->currentText()));
    ui->tableWidget_4Privoda->setItem(2, 0, new QTableWidgetItem(ui->comboBoxPeredacha1Type1->currentText()));
    ui->tableWidget_4Privoda->setItem(3, 0, new QTableWidgetItem(ui->comboBoxPeredacha3Type1->currentText()));

    for (int i = 2 ; i < ui->tableWidget_4Privoda->columnCount() ; i ++)
    {

        double val = ROUND2(ui->tableWidgetPnom->item(i-2, 3)->text().toDouble() / dValNiv);
        ui->tableWidget_4Privoda->setItem(0, i , new QTableWidgetItem(QString::number(val)));
        ui->tableWidget_4Privoda->setItem(1, i , new QTableWidgetItem(QString::number(ui->doubleSpinBox_i1->value())));
        ui->tableWidget_4Privoda->setItem(2, i , new QTableWidgetItem(ui->comboBox_i2->currentText()));
        val = ROUND2(ui->tableWidget_4Privoda->item(0, i)->text().toDouble()/(ui->tableWidget_4Privoda->item(1, i)->text().toDouble() * ui->tableWidget_4Privoda->item(2, i)->text().toDouble()));
        ui->tableWidget_4Privoda->setItem(3, i , new QTableWidgetItem(QString::number(val)));
    }
    on_spinBox_Variant2_valueChanged(ui->spinBox_Variant2->value());
}

void DmWindow::updateNValues(void)
{
    if (iValN > 0)
    {
        dValNiv = iValN;
        ui->label_n4_2->setText(QString::number(dValNiv));
    }
    else if (dValOmega > 0) {
        dValNiv = ROUND2(30 * dValOmega / PI);
        ui->label_n4_2->setText(tr("30*ω/π=")+QString::number(dValNiv));
    }
    else if (dValV > 0) {
        bool firstF = false;
        if (dValD <= 0 && dValP > 0 && dValZ > 0)
        {
            dValD = dValP/sin((180.0/dValZ)*(PI/180.0));
            firstF = true;
        }
        dValNiv = ROUND2((60.0 * dValV) / (PI*dValD));
        if (firstF){
            ui->label_n4_2->setText(tr("60*V/(π*(p/sin(180/z)))=")+QString::number(dValNiv));
        }
        else
        {
            ui->label_n4_2->setText(tr("60*V/(π*d)=")+QString::number(dValNiv));
        }
    }
    else {
        dValNiv = 0;
        ui->label_n4_2->setText("0");
    }
}

void DmWindow::updateIValues(void)
{
    ui->label_i1->setText( QString::number(predelI[0][0])+" .. "+QString::number(predelI[0][1]));
    int shift = CurrentReductor + 1;
    ui->label_i2->setText( QString::number(predelI[shift][0])+" .. "+QString::number(predelI[shift][1]));
    shift = 4 + ui->comboBoxPeredacha3Type1->currentIndex();
    ui->label_i3->setText( QString::number(predelI[shift][0])+" .. "+QString::number(predelI[shift][1]));

    ui->label_RemennayaPeredacha->setText(ui->comboBoxPrivodType->currentText());
    ui->label_Reductor->setText(ui->comboBoxPeredacha1Type1->currentText());
    ui->label_OtkritauaPeredacha->setText(ui->comboBoxPeredacha3Type1->currentText());

    ui->label_n4_3->setText(QString::number(dValNiv));

    updateTablePeredatochnoeOtnoshenie();
}


void DmWindow::on_spinBox_Variant2_valueChanged(int val)
{
    ui->label_i->setText(ui->tableWidget_4Privoda->item(0, val+1)->text());
    ui->label_i_1->setText(ui->tableWidget_4Privoda->item(1, val+1)->text());
    ui->label_i_2->setText(ui->tableWidget_4Privoda->item(2, val+1)->text());
    ui->label_i_3->setText(ui->tableWidget_4Privoda->item(3, val+1)->text());

    //round
    dValI2 = ui->label_i_2->text().toDouble();
    ui->label_i2_2->setText(QString::number(dValI2));
    ui->label_i3_2->setText(tr("нет расчета"));
    if (ui->comboBoxPeredacha3Type1->currentIndex() != 2)
    {
        double i3 = ui->label_i_3->text().toDouble();
        for (int i = LENGTH(roundI) - 2 ; i >= 0 ; i--)
        {
            if(i3 >= roundI[i])
            {
                double temp1 = roundI[i+1] - i3;
                double temp2 = i3 - roundI[i];

                if(temp1 < temp2)
                    dValI3 = roundI[i+1];
                else
                    dValI3 = roundI[i];
                ui->label_i3_2->setText(QString::number(dValI3));
                break;
            }
        }
    }
    dValI = ui->label_i->text().toDouble();
    dValI1 = dValI/(dValI2*dValI3) + 0.001;
    dValI1 = ROUND2(dValI1);
    ui->label_i1_2->setText(QString::number(dValI1));

    ui->label_Dvigatel_2->setText(ui->tableWidgetPnom->item(val-1, 1)->text());
    ui->label_nnom_2->setText(ui->tableWidgetPnom->item(val-1, 3)->text());
    ui->label_Pnom_2->setText(ui->tableWidgetPnom->item(val-1, 0)->text());
    dTmaxTnom = ui->tableWidgetPnom->item(val-1, 4)->text().toDouble();
    ui->label_TmaxTnom_2->setText(QString::number(dTmaxTnom));

    updateHarakteristiki();
}

void DmWindow::updateHarakteristiki(void)
{
    dValN1 = ui->label_nnom_2->text().toDouble();
    ui->label_n1->setText(QString::number(dValN1));
    dValN2 = ROUND1(dValN1 / dValI1);
    ui->label_n2->setText(QString::number(dValN1) + tr("/") + QString::number(dValI1) + tr("=") + QString::number(dValN2));
    dValN3 = ROUND1(dValN2 / dValI2);
    ui->label_n3->setText(QString::number(dValN2) + tr("/") + QString::number(dValI2) + tr("=") + QString::number(dValN3));
    dValN4 = ROUND1(dValN3 / dValI3);
    ui->label_n4->setText(QString::number(dValN3) + tr("/") + QString::number(dValI3) + tr("=") + QString::number(dValN4));

    dValP1 = ui->label_Pnom_2->text().toDouble();
    ui->label_P1->setText(QString::number(dValP1));
    dValP2 = ROUND1(dValP1 * dValEta1);
    ui->label_P2->setText(QString::number(dValP1) + tr("*") + QString::number(dValEta1) + tr("=") + QString::number(dValP2));
    dValP3 = ROUND1(dValP2 * dValEta2);
    ui->label_P3->setText(QString::number(dValP2) + tr("*") + QString::number(dValEta2) + tr("=") + QString::number(dValP3));
    dValP4 = ROUND1(dValP3 * dValEta3);
    ui->label_P4_2->setText(QString::number(dValP3) + tr("*") + QString::number(dValEta3) + tr("=") + QString::number(dValP4));

    dValOmega1 = ROUND1(PI * dValN1/ 30);
    dValOmega2 = ROUND1(PI * dValN2 / 30);
    dValOmega3 = ROUND1(PI * dValN3 / 30);
    dValOmega4 = ROUND1(PI * dValN4 / 30);
    ui->label_Omega1->setText(tr("3.14*") + QString::number(dValN1) + tr("/30=") + QString::number(dValOmega1));
    ui->label_Omega2->setText(tr("3.14*") + QString::number(dValN2) + tr("/30=") + QString::number(dValOmega2));
    ui->label_Omega3->setText(tr("3.14*") + QString::number(dValN3) + tr("/30=") + QString::number(dValOmega3));
    ui->label_Omega4->setText(tr("3.14*") + QString::number(dValN4) + tr("/30=") + QString::number(dValOmega4));

    dValT1 = ROUND2(9550 * dValP1 / dValN1);
    dValT2 = ROUND2(9550 * dValP2 / dValN2);
    dValT3 = ROUND2(9550 * dValP3 / dValN3);
    dValT4 = ROUND2(9550 * dValP4 / dValN4);
    ui->label_T1->setText(tr("9500*") + QString::number(dValP1) + tr("/") + QString::number(dValN1) + tr("=") + QString::number(dValT1));
    ui->label_T2->setText(tr("9500*") + QString::number(dValP2) + tr("/") + QString::number(dValN2) + tr("=") + QString::number(dValT2));
    ui->label_T3->setText(tr("9500*") + QString::number(dValP3) + tr("/") + QString::number(dValN3) + tr("=") + QString::number(dValT3));
    ui->label_T4->setText(tr("9500*") + QString::number(dValP4) + tr("/") + QString::number(dValN4) + tr("=") + QString::number(dValT4));

    ui->label_Harakteristiki->setText(tr("Тип двигателя: ") + ui->label_Dvigatel_2->text() + " ,     " +
                                      tr("P<span style=\" vertical-align:sub;\">ном</span>= ") + ui->label_Pnom_2->text() + tr(" кВт,    ") +
                                      tr("n<span style=\" vertical-align:sub;\">ном</span>= ") + ui->label_nnom_2->text() + tr(" об/мин"));

    ui->tableWidget_Charact1->setItem(0 , 0 , new QTableWidgetItem(ui->comboBoxPrivodType->currentText()));
    ui->tableWidget_Charact1->setItem(1 , 0 , new QTableWidgetItem(ui->comboBoxPeredacha1Type1->currentText()));
    ui->tableWidget_Charact1->setItem(2 , 0 , new QTableWidgetItem(ui->comboBoxPeredacha3Type1->currentText()));

    ui->tableWidget_Charact1->setItem(0 , 1 , new QTableWidgetItem(QString::number(dValI1)));
    ui->tableWidget_Charact1->setItem(1 , 1 , new QTableWidgetItem(QString::number(dValI2)));
    ui->tableWidget_Charact1->setItem(2 , 1 , new QTableWidgetItem(QString::number(dValI3)));

    ui->tableWidget_Charact1->setItem(0 , 2 , new QTableWidgetItem(QString::number(dValEta1)));
    ui->tableWidget_Charact1->setItem(1 , 2 , new QTableWidgetItem(QString::number(dValEta2)));
    ui->tableWidget_Charact1->setItem(2 , 2 , new QTableWidgetItem(QString::number(dValEta3)));

    ui->tableWidget_Charact2->setItem(0 , 0 , new QTableWidgetItem(QString::number(dValP1)));
    ui->tableWidget_Charact2->setItem(0 , 1 , new QTableWidgetItem(QString::number(dValP2)));
    ui->tableWidget_Charact2->setItem(0 , 2 , new QTableWidgetItem(QString::number(dValP3)));
    ui->tableWidget_Charact2->setItem(0 , 3 , new QTableWidgetItem(QString::number(dValP4)));

    ui->tableWidget_Charact2->setItem(1 , 0 , new QTableWidgetItem(QString::number(dValN1)));
    ui->tableWidget_Charact2->setItem(1 , 1 , new QTableWidgetItem(QString::number(dValN2)));
    ui->tableWidget_Charact2->setItem(1 , 2 , new QTableWidgetItem(QString::number(dValN3)));
    ui->tableWidget_Charact2->setItem(1 , 3 , new QTableWidgetItem(QString::number(dValN4)));

    ui->tableWidget_Charact2->setItem(2 , 0 , new QTableWidgetItem(QString::number(dValT1)));
    ui->tableWidget_Charact2->setItem(2 , 1 , new QTableWidgetItem(QString::number(dValT2)));
    ui->tableWidget_Charact2->setItem(2 , 2 , new QTableWidgetItem(QString::number(dValT3)));
    ui->tableWidget_Charact2->setItem(2 , 3 , new QTableWidgetItem(QString::number(dValT4)));

    ui->tableWidget_Charact2->setItem(3 , 0 , new QTableWidgetItem(QString::number(dValOmega1)));
    ui->tableWidget_Charact2->setItem(3 , 1 , new QTableWidgetItem(QString::number(dValOmega2)));
    ui->tableWidget_Charact2->setItem(3 , 2 , new QTableWidgetItem(QString::number(dValOmega3)));
    ui->tableWidget_Charact2->setItem(3 , 3 , new QTableWidgetItem(QString::number(dValOmega4)));

#ifdef TAB_CONTROL
    if (checkTab2())
        ui->tabWidget->setTabEnabled(2, true);
    else
        ui->tabWidget->setTabEnabled(2, false);
#else
    checkTab2();
#endif
}

bool DmWindow::checkTab2(void)
{
    bool noErrors = true;

    if ((dValEta1 >= predelEta[CurrentPrivod][0] && dValEta1 <= predelEta[CurrentPrivod][1]) &&
        (dValEta2 >= predelEta[ 2 + CurrentReductor][0] && dValEta2 <= predelEta[ 2 + CurrentReductor][1]) &&
        (dValEta3 >= predelEta[ 6 + CurrentPeredacha][0] && dValEta3 <= predelEta[ 6 + CurrentPeredacha][1]))
    {
        ui->label_CheckEta->setVisible(false);
    }
    else
    {
        ui->label_CheckEta->setVisible(true);
        noErrors = false;
    }

    double tempVal = 0;
    if(dValPiv == 0)
        tempVal = (dValV * iValFt / dValEta);
    else tempVal = (dValPiv / dValEta);

    for (uint i = 0 ; i < LENGTH(powerTable); i++)
    if (tempVal <= powerTable[i])
        {
            tempVal = powerTable[i];
            break;
        }

    double p = ui->comboBox_Pnom->currentText().toDouble();
    if (p != tempVal)
    {
        ui->label_CheckPnom->setVisible(true);
        noErrors = false;
    } else ui->label_CheckPnom->setVisible(false);

    tempVal = ROUND2(ui->doubleSpinBox_i1->value());
    if(tempVal < predelI[0][0] || tempVal > predelI[0][1])
    {
        ui->label_CheckI1->setVisible(true);
        noErrors = false;
    } else ui->label_CheckI1->setVisible(false);

    tempVal = ROUND2(ui->comboBox_i2->currentText().toDouble());
    int shift = CurrentReductor + 1;
    if(tempVal < predelI[shift][0] || tempVal > predelI[shift][1])
    {
        ui->label_CheckI2->setVisible(true);
        noErrors = false;
    } else ui->label_CheckI2->setVisible(false);

    shift = 4 + ui->comboBoxPeredacha3Type1->currentIndex();
    if(dValI3 < predelI[shift][0] || dValI3 > predelI[shift][1])
    {
        ui->label_CheckI3->setVisible(true);
        noErrors = false;
    } else  ui->label_CheckI3->setVisible(false);

    return noErrors;

}
