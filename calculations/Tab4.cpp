#include "dmwindow.h"
#include "ui_dmwindow.h"
#include "defines/table3.h"

void DmWindow::on_comboBox_Shesternya_currentIndexChanged(int index)
{
    iShesternya4Index = index;
    iSigmaT = svojstvaStali2[1][iShesternya4Index];
    if ((CurrentReductor == Reductor::CILINDRICHESKAYA_PRYMOZUBAYA || CurrentReductor == Reductor::CILINDRICHESKAYA_KOSOZUBAYA) && index != ui->comboBox_Koleso->currentIndex())
        ui->comboBox_Koleso->setCurrentIndex(index);
}

void DmWindow::on_comboBox_Koleso_currentIndexChanged(int index)
{
    iKoleso4Index = index;
    if ((CurrentReductor == Reductor::CILINDRICHESKAYA_PRYMOZUBAYA || CurrentReductor == Reductor::CILINDRICHESKAYA_KOSOZUBAYA) && index != ui->comboBox_Shesternya->currentIndex())
        ui->comboBox_Shesternya->setCurrentIndex(index);
}

void DmWindow::updateChisloCiclov(void)
{
    iHBcp1 = ui->spinBox_HVsr1->value();
    iHBcp2 = ui->spinBox_HVsr2->value();

    dNH01 = ROUND(30 * pow(iHBcp1, 2.4));
    dNH02 = ROUND(30 * pow(iHBcp2, 2.4));
    if (iHBcp1 == 0)
        ui->label_Nh01->setText("0");
    else
        ui->label_Nh01->setText(QString::number(dNH01, 'g', 10));
    if (iHBcp2 == 0)
        ui->label_Nh02->setText("0");
    else
        ui->label_Nh02->setText(QString::number(dNH02, 'g', 10));

    updateFactChisloCiclov();
}

void DmWindow::updateFactChisloCiclov(void)
{
    iC = ui->spinBox_C->value();

    ui->label_Nh01_2->setText(ui->label_Nh01->text());
    ui->label_Nh02_2->setText(ui->label_Nh02->text());

    iN1 = ROUND(60*dValN2*iC*iValLh);
    iN2 = ROUND(60*dValN3*iC*iValLh);

    ui->label_N1->setText(QString::number(iN1));
    ui->label_N2->setText(QString::number(iN2));

    if (iN1 > dNH01)
    {
        ui->label_OtnoshenieN1->setText(">");
        dKHL1 = 1;
    }
    else if (iN1 < dNH01)
    {
        ui->label_OtnoshenieN1->setText("<");
        dKHL1 = pow((double)iN1/dNH01, 0.16666666666);
        dKHL1 = ROUND3(dKHL1)
    }
    else
    {
        ui->label_OtnoshenieN1->setText("=");
        dKHL1 = 0;
    }
    ui->label_kHL1->setText(QString::number(dKHL1));

    if (iN2 > dNH02)
    {
        ui->label_OtnoshenieN2->setText(">");
        dKHL2 = 1;
    }
    else if (iN2 < dNH02)
    {
        ui->label_OtnoshenieN2->setText("<");
        dKHL2 = pow((double)iN2/dNH02, 0.16666666666);
        dKHL2 = ROUND3(dKHL2);
    }
    else
    {
        ui->label_OtnoshenieN2->setText("=");
        dKHL2 = 0;
    }
    ui->label_kHL2->setText(QString::number(dKHL2));

    updateKontaktnieNapryajenia();

}

void DmWindow::updateViborMateriala(void)
{
    dVs = 4.5*0.0001 * dValN3 * dValI2 * pow(dValT3, (1.0/3));
    dVs = ROUND2(dVs);
    ui->label_Vs->setText(QString::number(dVs) + tr("м/с"));

    updateKontaktnieNapryajenia();
}

void DmWindow::updateKontaktnieNapryajenia(void)
{
    if(CurrentReductor == Reductor::CILINDRICHESKAYA_PRYMOZUBAYA || CurrentReductor == Reductor::CILINDRICHESKAYA_KOSOZUBAYA || CurrentReductor == Reductor::KONICHESKAYA)
    {
        dSigmaH1 = ((2*iHBcp1+70)*dKHL1)/ui->doubleSpinBox_SH->value();
        dSigmaH1 = ROUND1(dSigmaH1);
        dSigmaH2 = ((2*iHBcp2+70)*dKHL2)/ui->doubleSpinBox_SH->value();
        dSigmaH2 = ROUND1(dSigmaH2);

        ui->label_SigmaH1->setText(tr("(2*") + QString::number(iHBcp1) + tr("+70)*") + QString::number(dKHL1) + tr("/") + ui->doubleSpinBox_SH->text() + tr("=") + QString::number(dSigmaH1) + tr(" МПа"));
        ui->label_SigmaH2->setText(tr("(2*") + QString::number(iHBcp2) + tr("+70)*") + QString::number(dKHL2) + tr("/") + ui->doubleSpinBox_SH->text() + tr("=") + QString::number(dSigmaH2) + tr(" МПа"));

        if (CurrentReductor == Reductor::CILINDRICHESKAYA_PRYMOZUBAYA || CurrentReductor == Reductor::KONICHESKAYA)
        {
            dSigmaH3 = (dSigmaH1 <= dSigmaH2 ? dSigmaH1 : dSigmaH2);
        }
        else if (CurrentReductor == Reductor::CILINDRICHESKAYA_KOSOZUBAYA)
        {
            dSigmaH3 = (dSigmaH1 + dSigmaH2) * 0.45;
        }
        else dSigmaH3 = 0;

        ui->label_SigmaH3->setText(QString::number(dSigmaH3));
    }
    else
    {
        dSigmaH2 = 300.0 - 25.0 * dVs;
        dSigmaH2 = ROUND1(dSigmaH2);

        ui->label_SigmaH2_2->setText(QString::number(dSigmaH2));
    }

    updateNapryajenieIzgiba();
}

void DmWindow::updateNapryajenieIzgiba(void)
{
    if (CurrentReductor == Reductor::CILINDRICHESKAYA_PRYMOZUBAYA || CurrentReductor == Reductor::CILINDRICHESKAYA_KOSOZUBAYA || CurrentReductor == Reductor::KONICHESKAYA)
    {
        if (iN1 > 4000000)
        {
            dKFL1 = 1;
        }
        else
        {
            dKFL1 = pow((4000000.0/(double)iN1), 0.16666666666);
            dKFL1 = ROUND3(dKFL1);
        }
        ui->label_kFL1->setText(QString::number(dKFL1));

        if (iN2 > 4000000)
        {
            dKFL2 = 1;
        }
        else
        {
            dKFL2 = pow((4000000.0/(double)iN2), 0.16666666666);
            dKFL2 = ROUND3(dKFL2);
        }
        ui->label_kFL2->setText(QString::number(dKFL2));

        dSigmaF1 = 1.8 * iHBcp1 * dKFL1 / ui->doubleSpinBox_SF->value();
        dSigmaF1 = ROUND1(dSigmaF1);

        dSigmaF2 = 1.8 * iHBcp2 * dKFL2 / ui->doubleSpinBox_SF->value();
        dSigmaF2 = ROUND1(dSigmaF2);

        ui->label_SigmaF1->setText(tr("1.8*") + QString::number(iHBcp1) + tr("*") + QString::number(dKFL1) + tr("/") + ui->doubleSpinBox_SF->text() + tr("=") + QString::number(dSigmaF1) + tr("МПа"));
        ui->label_SigmaF2->setText(tr("1.8*") + QString::number(iHBcp2) + tr("*") + QString::number(dKFL2) + tr("/") + ui->doubleSpinBox_SF->text() + tr("=") + QString::number(dSigmaF2) + tr(" МПа"));
    }
    else
    {
        iSigmab = ui->comboBox_Sb->currentText().toInt();
        iSigmat = ui->comboBox_St->currentText().toInt();

        iN2fe = ROUND(60 * iValLh * dValN3);
        dKFL1 = pow((1000000.0/iN2fe), (1.0/9));
        dKFL1 = ROUND2(dKFL1);
        dSigmaF2 = (0.25 * iSigmat + 0.08 * iSigmab) * dKFL1;
        dSigmaF2 = ROUND2(dSigmaF2);

        ui->label_N2fe->setText(QString::number(iN2fe));
        ui->label_Kfl->setText(QString::number(dKFL1));
        ui->label_SigmaF2_2->setText(QString::number(dSigmaF2));
    }

#ifdef TAB_CONTROL
    if (checkTab4())
        ui->tabWidget->setTabEnabled(4, true);
    else ui->tabWidget->setTabEnabled(4, false);
#else
    checkTab4();
#endif
}

bool DmWindow::checkTab4(void)
{
    bool noErrors = true;

    if(CurrentReductor == Reductor::CILINDRICHESKAYA_PRYMOZUBAYA || CurrentReductor == Reductor::CILINDRICHESKAYA_KOSOZUBAYA || CurrentReductor == Reductor::KONICHESKAYA)
    {
        if (iHBcp1 < 200 || iHBcp1 > 350 )
        {
            ui->label_CheckHBcp1->setVisible(true);
            noErrors = false;
        } else ui->label_CheckHBcp1->setVisible(false);

        if (iHBcp2 < 200 || iHBcp2 > 350 )
        {
            ui->label_CheckHBcp2->setVisible(true);
            noErrors = false;
        } else ui->label_CheckHBcp2->setVisible(false);
    }
    else if(CurrentReductor == Reductor::CHERVYACHNAYA)
    {
        if (dVs > 5)
        {
            if (ui->comboBox_Venec->currentIndex() > 1)
            {
                ui->label_checkVenec->setVisible(true);
                noErrors = false;
            } else ui->label_checkVenec->setVisible(false);
        }
        else
        {
            if (ui->comboBox_Venec->currentIndex() < 2)
            {
                ui->label_checkVenec->setVisible(true);
                noErrors = false;
            } else ui->label_checkVenec->setVisible(false);
        }

        if (iSigmab >= svojstvaStali[ui->comboBox_Venec->currentIndex()][0] && iSigmab <= svojstvaStali[ui->comboBox_Venec->currentIndex()][1])
        {
            ui->label_checkSb->setVisible(false);
        } else {
            noErrors = false;
            ui->label_checkSb->setVisible(true);
        }
        if (iSigmat >= svojstvaStali[ui->comboBox_Venec->currentIndex()][2] && iSigmat <= svojstvaStali[ui->comboBox_Venec->currentIndex()][3])
        {
            ui->label_checkSt->setVisible(false);
        } else {
            noErrors = false;
            ui->label_checkSt->setVisible(true);
        }
    }

    return noErrors;
}
