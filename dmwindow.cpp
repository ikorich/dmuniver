#include "defines/var.h"
#include "dmwindow.h"
#include "ui_dmwindow.h"
#include <QFile>
#include <qtextstream.h>

DmWindow::DmWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DmWindow)
{
    ui->setupUi(this);
//Reset Value
    //Global
    CurrentPrivod = Privod::KLINNOREMENNAYA;
    CurrentReductor = Reductor::CILINDRICHESKAYA_PRYMOZUBAYA;
    CurrentPeredacha = Peredacha::CILINDRICHESKAYA;
    //Tab2
    dValPiv = dValV = dValOmega = dValOmega1 = dValOmega2 = dValOmega3 = dValOmega4 = dValD = dValP = dValZ = dTmaxTnom = 0.0;
    iValN = iValLh = iValLh = iValFt = 0;
    dValEta = dValEta1 = dValEta2 = dValEta3 = dValNiv = dValI = dValI1 = dValI2 = dValI3 = 0.0;
    dValN1 = dValN2 = dValN3 = dValN4 = dValP1 = dValP2 = dValP3 = dValP4 = dValT1 = dValT2 = dValT3 = dValT4 = 0.0;
    //Tab3
    dValXi = dVald11 = dVald12 = dVald21 = dVald22 = dValU = dValU1 = dValU2 = dValaa1 = dValaa2 = dVala1 = dVala2 = dVala12 = dVala22 = 0.0;
    dValll1 = dValll2 = dVall1 = dVall2 = dValV1 = dValV2 = dValNpr1 = dValNpr2 = dValAlpha1 = dValAlpha2 = dValKp = dValCa1 = dValCa2 = 0.0;
    dValPo1 = dValPo2 = dVal_ll1 = dVal_ll2 = dValCl1 = dValCl2 = dValPPo1 = dValPPo2 = dValCp = dValCz1 = dValCz2 = dValF0 = 0.0;
    dValRn = dValde1 = dValde2 = dValM = 0.0;
    iValRemen1 = iValRemen2 = iValZp1 = iValZp2 = 0;
    //Tab4
    iShesternya4Index = iKoleso4Index = iN1 = iN2 = iN2fe = 0;
    dNH01 = dNH02 = dKHL1 = dKHL2 = dSigmaH1 = dSigmaH2 = dSigmaH3 = dSigmaF1 = dSigmaF2 = dKFL1 = dKFL2 = dVs = 0.0;
    iSb = 230;
    iSt = 140;
    iSigmaT = 650;
    iHBcp1 = iHBcp2 = 250;
    iC = 1;
    //Tab5
    dT2 = dn2 = du2 = dPsiba = dPsibd = dKHBeta = daw = daw2 = dKa = dmm = dmm1 = dmm2 = dbb = dZsum = dZ1 = dBeta = dUf = dUf2 = 0.0;
    dd1 = dd2 = dda1 = dda2 = ddf1 = ddf2 = dPsibd2 = dV = dEtaAlpha = dZh = dZe = dKHa = dKHV = dSigmaH51 = dSigmaHmax = dSigmaHHmax = 0.0;
    dFt = dFr = dFa = dKFBeta = dKFV = dKFa = dYF1 = dYF2 = dYb = dSigmaF51 = dSigmaF52 = dDzag = dCzag = 0.0;
    ib1 = ib2 = iZsum = iZ1 = iZ2 = iNaznachenie = iZm = iZV1 = iZV2 = iDrped = iSrped = iSzag1 = iSzag2 = 20;
    //Tab6




//Tab 1
    connect(ui->doubleSpinBox_nu1,                      SIGNAL(valueChanged(double)),       this, SLOT(updateKPDText()));
    connect(ui->doubleSpinBox_nu2,                      SIGNAL(valueChanged(double)),       this, SLOT(updateKPDText()));
    connect(ui->doubleSpinBox_nu3,                      SIGNAL(valueChanged(double)),       this, SLOT(updateKPDText()));

    connect(ui->doubleSpinBox_i1,                       SIGNAL(valueChanged(double)),       this, SLOT(updateTablePeredatochnoeOtnoshenie()));
    connect(ui->comboBox_i2,                            SIGNAL(currentIndexChanged(int)),   this, SLOT(updateTablePeredatochnoeOtnoshenie()));
//Tab 2
    connect(ui->comboBox_sechenieRemnya1,               SIGNAL(currentIndexChanged(int)),   this, SLOT(updateLabelTextTab3()));
    connect(ui->comboBox_sechenieRemnya2,               SIGNAL(currentIndexChanged(int)),   this, SLOT(updateLabelTextTab3()));
    connect(ui->doubleSpinBox_moshnistNaVedushijVal,    SIGNAL(valueChanged(double)),       this, SLOT(updateLabelTextTab3()));
    connect(ui->spinBox_ChastotaVrasheniya,             SIGNAL(valueChanged(int)),          this, SLOT(updateLabelTextTab3()));
    connect(ui->doubleSpinBox_peredatochnoeOtnoshenie,  SIGNAL(valueChanged(double)),       this, SLOT(updateLabelTextTab3()));

    connect(ui->comboBox_diametrRemnya1,                SIGNAL(currentIndexChanged(int)),   this, SLOT(updateDiametrVedushegoShkiva()));
    connect(ui->comboBox_diametrRemnya2,                SIGNAL(currentIndexChanged(int)),   this, SLOT(updateDiametrVedushegoShkiva()));

    connect(ui->comboBox_standart1,                     SIGNAL(currentIndexChanged(int)),   this, SLOT(updateDiametrVedomogoShkiva()));
    connect(ui->comboBox_standart2,                     SIGNAL(currentIndexChanged(int)),   this, SLOT(updateDiametrVedomogoShkiva()));

    connect(ui->doubleSpinBox_Xi,                       SIGNAL(valueChanged(double)),       this, SLOT(updatePeredatochnoeChislo()));

    connect(ui->comboBox_L2,                            SIGNAL(currentIndexChanged(int)),   this, SLOT(updateStandartDlinaRemnya()));
    connect(ui->comboBox_L2_2,                          SIGNAL(currentIndexChanged(int)),   this, SLOT(updateStandartDlinaRemnya()));

    connect(ui->comboBox_Ca1,                           SIGNAL(currentIndexChanged(int)),   this, SLOT(updateMoshnostNaOdnomRemne()));
    connect(ui->comboBox_Ca2,                           SIGNAL(currentIndexChanged(int)),   this, SLOT(updateMoshnostNaOdnomRemne()));
    connect(ui->comboBox_Cl1,                           SIGNAL(currentIndexChanged(int)),   this, SLOT(updateMoshnostNaOdnomRemne()));
    connect(ui->comboBox_Cl2,                           SIGNAL(currentIndexChanged(int)),   this, SLOT(updateMoshnostNaOdnomRemne()));

    connect(ui->doubleSpinBox_Cz1,                      SIGNAL(valueChanged(double)),       this, SLOT(updateKolichestvoRemney()));
    connect(ui->doubleSpinBox_Cz2,                      SIGNAL(valueChanged(double)),       this, SLOT(updateKolichestvoRemney()));
    connect(ui->comboBox_Cp,                            SIGNAL(currentIndexChanged(int)),   this, SLOT(updateKolichestvoRemney()));
    connect(ui->comboBox_sechenieRemnya3,               SIGNAL(currentIndexChanged(int)),   this, SLOT(updateKolichestvoRemney()));

    connect(ui->comboBox_q,                             SIGNAL(currentIndexChanged(int)),   this, SLOT(updateNatyajenieRemnya()));


    //Tab 3
    connect(ui->spinBox_HVsr1,                         SIGNAL(valueChanged(int)),          this, SLOT(updateChisloCiclov()));
    connect(ui->spinBox_HVsr2,                         SIGNAL(valueChanged(int)),          this, SLOT(updateChisloCiclov()));
    connect(ui->spinBox_C,                             SIGNAL(valueChanged(int)),          this, SLOT(updateFactChisloCiclov()));
    connect(ui->doubleSpinBox_SH,                      SIGNAL(valueChanged(double)),       this, SLOT(updateKontaktnieNapryajenia()));
    connect(ui->doubleSpinBox_SF,                      SIGNAL(valueChanged(double)),       this, SLOT(updateNapryajenieIzgiba()));
    connect(ui->comboBox_Sb,                           SIGNAL(currentIndexChanged(int)),   this, SLOT(updateNapryajenieIzgiba()));
    connect(ui->comboBox_St,                           SIGNAL(currentIndexChanged(int)),   this, SLOT(updateNapryajenieIzgiba()));
    connect(ui->comboBox_Venec,                        SIGNAL(currentIndexChanged(int)),   this, SLOT(updateNapryajenieIzgiba()));

    //Tab 4
    connect(ui->doubleSpinBox_T2,                      SIGNAL(valueChanged(double)),       this, SLOT(KoefficientShirini()));
    connect(ui->doubleSpinBox_n2,                      SIGNAL(valueChanged(double)),       this, SLOT(KoefficientShirini()));
    connect(ui->doubleSpinBox_u2,                      SIGNAL(valueChanged(double)),       this, SLOT(KoefficientShirini()));

    on_spinBox_2_valueChanged(1);
    setPicture(ui->graphicsView_2 , ":/resources/shkiv.jpg");
#ifdef TAB_CONTROL
    for (uint i = 2 ; i < ui->tabWidget->count() ; i++)
    {
        ui->tabWidget->setTabEnabled(i, false);
    }
#endif
}

DmWindow::~DmWindow()
{
    delete ui;
}

void DmWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void DmWindow::on_tabWidget_currentChanged(int index)
{
    if (index == Tabs::TAB_2)
    {
        ui->labelPrivodType->setText(ui->comboBoxPrivodType->currentText());
        ui->labelPeredacha1Types->setText(ui->comboBoxPeredacha1Type1->currentText());
        ui->labelPeredacha2Types->setText(ui->comboBoxPeredacha3Type1->currentText());

        dValPiv = ui->doubleSpinBox_P->value();
        iValN = ui->spinBox_N->value();
        iValLh = ui->spinBox_LH->value();
        iValFt = ui->spinBox_Ft->value();
        dValV = ui->doubleSpinBox_V->value();
        dValOmega = ui->doubleSpinBox_Omega->value();
        dValD = ui->doubleSpinBox_D->value();
        dValP = ui->doubleSpinBox_p->value();
        dValZ = ui->doubleSpinBox_z->value();

        updateKPDText();

    }
    else if (index == Tabs::TAB_3)
    {
        updateLabelTextTab3();
    }
    else if (index == Tabs::TAB_4)
    {
        if (CurrentReductor == Reductor::CILINDRICHESKAYA_PRYMOZUBAYA || CurrentReductor == Reductor::CILINDRICHESKAYA_KOSOZUBAYA || CurrentReductor == Reductor::KONICHESKAYA)
        {
            ui->label_ViborMateriala->setText(tr("Выбор материала зубчатых колес. Вычисление допускаемых напряжений."));
            ui->frame_ViborMateriala1->setVisible(true);
            ui->frame_ViborMateriala2->setVisible(false);

            updateChisloCiclov();
        }
        else if (CurrentReductor == Reductor::CHERVYACHNAYA)
        {
            ui->label_ViborMateriala->setText(tr("Выбор материала. Определение допускаемых напряжений."));
            ui->frame_ViborMateriala1->setVisible(false);
            ui->frame_ViborMateriala2->setVisible(true);

            updateViborMateriala();
        }
    }
    else if (index == Tabs::TAB_5)
    {
        dT2 = ui->doubleSpinBox_T2->value();
        dn2 = ui->doubleSpinBox_n2->value();
        du2 = ui->doubleSpinBox_u2->value();

        KoefficientShirini();
    }
    else if (index == Tabs::TAB_6)
    {
        dT3 = ui->doubleSpinBox_T3->value();
        dn3 = ui->doubleSpinBox_n3->value();
        du3 = ui->doubleSpinBox_u3->value();

        viborMaterialaZubchatihKoles();
    }

}


void DmWindow::on_spinBox_2_valueChanged(int index)
{
    char buffer [256];
    sprintf (buffer, ":/resources/var%d.jpg", index);
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(QPixmap(buffer));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();

    uint col = ui->tableWidget_var->columnCount();
    uint row = ui->tableWidget_var->rowCount();

    for (uint i = 0 ; i < row; i++)
        for (uint j = 0 ; j < col; j++)
        {
            ui->tableWidget_var->setItem(i, j, new QTableWidgetItem(tr(table1Var[row*(index-1)+i][j])));//->setItem(i, j , new QTableWidgetItem());
        }

    col = ui->tableWidget_remark->columnCount();
    row = ui->tableWidget_remark->rowCount();

        for (uint i = 0 ; i < row; i++)
            for (uint j = 0 ; j < col; j++)
            {
                ui->tableWidget_remark->setItem(i, j, new QTableWidgetItem(tr(table2Var[row*(index-1)+i][j])));//->setItem(i, j , new QTableWidgetItem());
            }


    sprintf (buffer, ":/resources/var%d.txt", index);
    QFile file(buffer);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QString line;

    QTextStream in(&file);
    while (!in.atEnd()) {
         line = in.readLine();
    }

    ui->label_var->setText(line);
}

void DmWindow::setPicture(QGraphicsView *graphics, const char* buffer )
{
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(QPixmap(buffer));
    graphics->setBackgroundRole(QPalette::Window);
    graphics->setAutoFillBackground( true );
    graphics->setScene(scene);
    graphics->show();
}

void DmWindow::on_comboBoxPeredacha1Type1_currentIndexChanged(int index)
{
    if (index == 0)
        CurrentReductor = Reductor::CILINDRICHESKAYA_PRYMOZUBAYA;
    else if (index == 1)
        CurrentReductor = Reductor::CILINDRICHESKAYA_KOSOZUBAYA;
    else if (index == 2)
        CurrentReductor = Reductor::KONICHESKAYA;
    else if (index == 3)
        CurrentReductor = Reductor::CHERVYACHNAYA;
}

void DmWindow::on_comboBoxPeredacha3Type1_currentIndexChanged(int index)
{
    if (index == 0)
        CurrentPeredacha = Peredacha::CILINDRICHESKAYA;
    else if (index == 1)
        CurrentPeredacha = Peredacha::KONICHESKAYA;
    else if (index == 2)
        CurrentPeredacha = Peredacha::CEPNAYA;
}

void DmWindow::on_comboBoxPrivodType_currentIndexChanged(int index)
{
    if (index == 0)
        CurrentPrivod = Privod::KLINNOREMENNAYA;
    else if (index == 1)
        CurrentPrivod = Privod::PLOSKOREMENNAYA;
}


