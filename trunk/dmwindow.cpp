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
//Set Default Value
    //Tab2
    dValPiv = dValV = dValOmega = dValOmega1 = dValOmega2 = dValOmega3 = dValOmega4 = dValD = dValP = dValZ = dTmaxTnom1 = dTmaxTnom2 = 0.0;
    iValN = iValLh = iValLh = iValFt = 0;
    dValEta = dValEta1 = dValEta2 = dValEta3 = dValNiv = dValI = dValI1 = dValI2 = dValI3 = dPnom = 0.0;
    dValN1 = dValN2 = dValN3 = dValN4 = dValP1 = dValP2 = dValP3 = dValP4 = dValT1 = dValT2 = dValT3 = dValT4 = 0.0;
    //Tab3
    dValXi = dVald11 = dVald12 = dVald21 = dVald22 = dValU = dValU1 = dValU2 = dValaa1 = dValaa2 = dVala1 = dVala2 = dVala12 = dVala22 = 0.0;
    dValll1 = dValll2 = dVall1 = dVall2 = dValV1 = dValV2 = dValNpr1 = dValNpr2 = dValAlpha1 = dValAlpha2 = dValKp = dValCa1 = dValCa2 = 0.0;
    dValPo1 = dValPo2 = dVal_ll1 = dVal_ll2 = dValCl1 = dValCl2 = dValPPo1 = dValPPo2 = dValCp = dValCz1 = dValCz2 = dValF0 = 0.0;
    dValRn = dValde1 = dValde2 = dValM = 0.0;
    iValRemen1 = iValRemen2 = iValZp1 = iValZp2 = 0;
    iValZp = 1;
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
    ib1 = ib2 = iZsum = iZ1 = iZ2 = iNaznachenie = iZm = iZV1 = iZV2 = iDrped = iSrped = iSzag1 = iSzag2 = 0;
    dKbe = dKbeu = dddl = dmll = dml = dRl = db = ddm1 = ddm2 = dBeta1 = dBeta2 = dFt12_5 = dFr1_5 = dFa2_5 = dFa1_5 = dFr2_5 = 0.0;
    iPodshipnikTupe = idl1 = idl2 = 0;
    dZV1 = dZV2 = dSigmaFmax1 = dSigmaFmax2 = dSigmaFFmax1 = dSigmaFFmax2 = 0.0;
    //Tab6
    dT3 = dn3 = du3 = dSf1 = dSf2 = dSF = dSff1 = dSff2 = dPsibd3 = dYF61 = dYF62 = dYF1SF1 = dYF2SF2 = dmm3 = dm = dd61 = dd62 = 0.0;
    dda61 = dda62 = ddf61 = ddf62 = dV61 = dFt12 = dFa1 = dKFV61 = dSigmaF61 = dSigmaF62 = dSigmaFmax61 = dSigmaFmax62 = 0.0;
    dSigmaFFmax61 = dSigmaFFmax62 = dSigmaH = dKHV61 = dSigmaHmax61 = dSigmaHHmax61 = 0.0;
    iLitje = iHB1 = iHB2 = iSb2 = iSt2 = iN1FE = iN2FE = iz1 = iz2 = iu = izv1 = izv2 = ib61 = ib62 = iStepenTochnostiPeredachi = 0;

    //Tab 2
    connect(ui->doubleSpinBox_nu1,                      SIGNAL(valueChanged(double)),       this, SLOT(updateKPDText()));
    connect(ui->doubleSpinBox_nu2,                      SIGNAL(valueChanged(double)),       this, SLOT(updateKPDText()));
    connect(ui->doubleSpinBox_nu3,                      SIGNAL(valueChanged(double)),       this, SLOT(updateKPDText()));
    connect(ui->doubleSpinBox_i1,                       SIGNAL(valueChanged(double)),       this, SLOT(updateTablePeredatochnoeOtnoshenie()));
    connect(ui->comboBox_i2,                            SIGNAL(currentIndexChanged(int)),   this, SLOT(updateTablePeredatochnoeOtnoshenie()));

    //Tab 3
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
    connect(ui->spinBox_KolRemney,                      SIGNAL(valueChanged(int)),          this, SLOT(updateNatyajenieRemnya()));

    //Tab 4
    connect(ui->spinBox_HVsr1,                         SIGNAL(valueChanged(int)),          this, SLOT(updateChisloCiclov()));
    connect(ui->spinBox_HVsr2,                         SIGNAL(valueChanged(int)),          this, SLOT(updateChisloCiclov()));
    connect(ui->spinBox_C,                             SIGNAL(valueChanged(int)),          this, SLOT(updateFactChisloCiclov()));
    connect(ui->doubleSpinBox_SH,                      SIGNAL(valueChanged(double)),       this, SLOT(updateKontaktnieNapryajenia()));
    connect(ui->doubleSpinBox_SF,                      SIGNAL(valueChanged(double)),       this, SLOT(updateNapryajenieIzgiba()));
    connect(ui->comboBox_Sb,                           SIGNAL(currentIndexChanged(int)),   this, SLOT(updateNapryajenieIzgiba()));
    connect(ui->comboBox_St,                           SIGNAL(currentIndexChanged(int)),   this, SLOT(updateNapryajenieIzgiba()));
    connect(ui->comboBox_Venec,                        SIGNAL(currentIndexChanged(int)),   this, SLOT(updateNapryajenieIzgiba()));

    //Tab 5
    connect(ui->doubleSpinBox_T2,                      SIGNAL(valueChanged(double)),       this, SLOT(KoefficientShirini()));
    connect(ui->doubleSpinBox_n2,                      SIGNAL(valueChanged(double)),       this, SLOT(KoefficientShirini()));
    connect(ui->doubleSpinBox_u2,                      SIGNAL(valueChanged(double)),       this, SLOT(KoefficientShirini()));
    connect(ui->doubleSpinBox_TmaxTnom,                SIGNAL(valueChanged(double)),       this, SLOT(KoefficientShirini()));
    connect(ui->comboBox_Psiba,                        SIGNAL(currentIndexChanged(int)),   this, SLOT(KoefficientShirini()));
    connect(ui->comboBox_KHBeta,                       SIGNAL(currentIndexChanged(int)),   this, SLOT(updateMejOsevoeRastoyanie()));
    connect(ui->comboBox_aw,                           SIGNAL(currentIndexChanged(int)),   this, SLOT(updateMejOsevoeRastoyanie()));
    connect(ui->comboBox_m,                            SIGNAL(currentIndexChanged(int)),   this, SLOT(ModulZacepleniya()));
    connect(ui->spinBox_StepenPeredachi,               SIGNAL(valueChanged(int)),          this, SLOT(ProverkaNaKontaktnuyuVinoslivost()));
    connect(ui->comboBox_Zm,                           SIGNAL(currentIndexChanged(int)),   this, SLOT(ProverkaNaKontaktnuyuVinoslivost()));
    connect(ui->doubleSpinBox_Khv,                     SIGNAL(valueChanged(double)),       this, SLOT(ProverkaNaKontaktnuyuVinoslivost()));
    connect(ui->doubleSpinBox_Beta,                    SIGNAL(valueChanged(double)),       this, SLOT(UgolNaklonaZubjev()));
    connect(ui->comboBox_Kfbeta,                       SIGNAL(currentIndexChanged(int)),   this, SLOT(ProverkaNaVinoslivostPoNapryajeniyuIzgiba()));
    connect(ui->doubleSpinBox_Kfv,                     SIGNAL(valueChanged(double)),       this, SLOT(ProverkaNaVinoslivostPoNapryajeniyuIzgiba()));

    connect(ui->doubleSpinBox_T2_2,                    SIGNAL(valueChanged(double)),       this, SLOT(KoefficientShiriniZubchastihVencov()));
    connect(ui->doubleSpinBox_n2_2,                    SIGNAL(valueChanged(double)),       this, SLOT(KoefficientShiriniZubchastihVencov()));
    connect(ui->doubleSpinBox_u2_2,                    SIGNAL(valueChanged(double)),       this, SLOT(KoefficientShiriniZubchastihVencov()));
    connect(ui->doubleSpinBox_TmaxTnom_2,              SIGNAL(valueChanged(double)),       this, SLOT(KoefficientShiriniZubchastihVencov()));

    connect(ui->doubleSpinBox_Kbe,                     SIGNAL(valueChanged(double)),       this, SLOT(KoefficientShiriniZubchastihVencov()));
    connect(ui->comboBox_Podshipnik,                   SIGNAL(currentIndexChanged(int)),   this, SLOT(KoefficientNeravnomernosti()));
    connect(ui->comboBox_Khb,                          SIGNAL(currentIndexChanged(int)),   this, SLOT(KoefficientNeravnomernosti()));
    connect(ui->spinBox_z1,                            SIGNAL(valueChanged(int)),          this, SLOT(ChisloZubjevKolesa()));
    connect(ui->comboBox_ml,                           SIGNAL(currentIndexChanged(int)),   this, SLOT(VneshnijOkrujnojModul()));
    connect(ui->spinBox_StepenTochnostiPeredachi_2,    SIGNAL(valueChanged(int)),          this, SLOT(OkrujnayaSkorostStepenTochnostiPeredach()));
    connect(ui->comboBox_Zm_2,                         SIGNAL(currentIndexChanged(int)),   this, SLOT(ProverochnijRaschetNaKontaktnujuVinoslivost()));
    connect(ui->doubleSpinBox_KHV,                     SIGNAL(valueChanged(double)),       this, SLOT(ProverochnijRaschetNaKontaktnujuVinoslivost()));
    connect(ui->comboBox_KFBeta,                       SIGNAL(currentIndexChanged(int)),   this, SLOT(ProverkaNaVinoslivostPoNapryjeniyuIzgiba()));
    connect(ui->doubleSpinBox_KFv,                     SIGNAL(valueChanged(double)),       this, SLOT(ProverkaNaVinoslivostPoNapryjeniyuIzgiba()));

    //Tab 6
    connect(ui->doubleSpinBox_T3,                      SIGNAL(valueChanged(double)),       this, SLOT(viborMaterialaZubchatihKoles()));
    connect(ui->doubleSpinBox_n3,                      SIGNAL(valueChanged(double)),       this, SLOT(viborMaterialaZubchatihKoles()));
    connect(ui->doubleSpinBox_u3,                      SIGNAL(valueChanged(double)),       this, SLOT(viborMaterialaZubchatihKoles()));
    connect(ui->spinBox_Litje,                         SIGNAL(valueChanged(int)),          this, SLOT(viborMaterialaZubchatihKoles()));
    connect(ui->spinBox_HB1,                           SIGNAL(valueChanged(int)),          this, SLOT(viborMaterialaZubchatihKoles()));
    connect(ui->spinBox_HB2,                           SIGNAL(valueChanged(int)),          this, SLOT(viborMaterialaZubchatihKoles()));
    connect(ui->comboBox_Sb_2,                         SIGNAL(currentIndexChanged(int)),   this, SLOT(viborMaterialaZubchatihKoles()));
    connect(ui->comboBox_St_2,                         SIGNAL(currentIndexChanged(int)),   this, SLOT(viborMaterialaZubchatihKoles()));
    connect(ui->comboBox_SF_2,                         SIGNAL(currentIndexChanged(int)),   this, SLOT(viborMaterialaZubchatihKoles()));
    connect(ui->comboBox_z1,                           SIGNAL(currentIndexChanged(int)),   this, SLOT(viborMaterialaZubchatihKoles()));
    connect(ui->doubleSpinBox_psibd,                   SIGNAL(valueChanged(double)),       this, SLOT(KoefficientShiriniVenca()));
    connect(ui->comboBox_m_2,                          SIGNAL(currentIndexChanged(int)),   this, SLOT(RaschetnoeZnachenieModulya()));
    connect(ui->spinBox_StepenTochnostiPeredachi,      SIGNAL(valueChanged(int)),          this, SLOT(OkrujnayaSkorostIStepenTochnostiPeredachi()));
    connect(ui->doubleSpinBox_KPV,                     SIGNAL(valueChanged(double)),       this, SLOT(ProverkaaNaVinoslivostPoNapryjeniyamIzgiba()));

    connect(ui->doubleSpinBox_T3_2,                    SIGNAL(valueChanged(double)),       this, SLOT(ChisloZubjevZvezdochki()));
    connect(ui->doubleSpinBox_n3_2,                    SIGNAL(valueChanged(double)),       this, SLOT(ChisloZubjevZvezdochki()));
    connect(ui->doubleSpinBox_u3_2,                    SIGNAL(valueChanged(double)),       this, SLOT(ChisloZubjevZvezdochki()));
    connect(ui->comboBox_K1,                           SIGNAL(currentIndexChanged(int)),   this, SLOT(KoefficientEkspluatacii()));
    connect(ui->comboBox_K2,                           SIGNAL(currentIndexChanged(int)),   this, SLOT(KoefficientEkspluatacii()));
    connect(ui->comboBox_K3,                           SIGNAL(currentIndexChanged(int)),   this, SLOT(KoefficientEkspluatacii()));
    connect(ui->comboBox_K4,                           SIGNAL(currentIndexChanged(int)),   this, SLOT(KoefficientEkspluatacii()));
    connect(ui->comboBox_K5,                           SIGNAL(currentIndexChanged(int)),   this, SLOT(KoefficientEkspluatacii()));
    connect(ui->comboBox_K6,                           SIGNAL(currentIndexChanged(int)),   this, SLOT(KoefficientEkspluatacii()));







    on_spinBox_Variant_valueChanged(1);
    setPicture(ui->graphicsView_2 , ":/resources/shkiv.jpg");
    on_comboBoxPrivodType_currentIndexChanged(0);
    on_comboBoxPeredacha1Type1_currentIndexChanged(0);
    on_comboBoxPeredacha3Type1_currentIndexChanged(0);
#ifdef TAB_CONTROL
    for (uint i = 2 ; i < ui->tabWidget->count() ; i++)
    {
        ui->tabWidget->setTabEnabled(i, false);
    }
#endif
    ui->tabWidget->setCurrentIndex(Tabs::TAB_1);
    setTablesWidht();
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
        iValFt = ui->doubleSpinBox_Ft->value();
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
        if (CurrentReductor == Reductor::CILINDRICHESKAYA_PRYMOZUBAYA || CurrentReductor == Reductor::CILINDRICHESKAYA_KOSOZUBAYA) {
            dT2 = ui->doubleSpinBox_T2->value();
            dn2 = ui->doubleSpinBox_n2->value();
            du2 = ui->doubleSpinBox_u2->value();

            KoefficientShirini();

            ui->scrollArea_Conisheskiy->setVisible(false);
            ui->scrollArea_Cilindricheskiy->setVisible(true);
        }
        else if (CurrentReductor == Reductor::KONICHESKAYA) {
            ui->scrollArea_Conisheskiy->setVisible(true);
            ui->scrollArea_Cilindricheskiy->setVisible(false);

            KoefficientShiriniZubchastihVencov();
        }

    }
    else if (index == Tabs::TAB_6)
    {
        if (CurrentPeredacha == Peredacha::CILINDRICHESKAYA) {
            dT3 = ui->doubleSpinBox_T3->value();
            dn3 = ui->doubleSpinBox_n3->value();
            du3 = ui->doubleSpinBox_u3->value();

            viborMaterialaZubchatihKoles();

            ui->scrollArea_PeredachaCilindricheskaya->setVisible(true);
            ui->scrollArea_PeredachCepnaya->setVisible(false);
        }
        else if (CurrentPeredacha == Peredacha::CEPNAYA) {
            ui->scrollArea_PeredachaCilindricheskaya->setVisible(false);
            ui->scrollArea_PeredachCepnaya->setVisible(true);

            ChisloZubjevZvezdochki();
        }

    }

}

void DmWindow::on_spinBox_Variant_valueChanged(int index)
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
    ui->tableWidget_remark->resizeColumnsToContents();
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
    switch(index)
    {
        case 0:
            CurrentReductor = Reductor::CILINDRICHESKAYA_PRYMOZUBAYA;
            ui->label_typreductora->setText(tr("Расчет цилиндрического прямозубого редуктора:"));
        break;
        case 1:
            CurrentReductor = Reductor::CILINDRICHESKAYA_KOSOZUBAYA;
            ui->label_typreductora->setText(tr("Расчет цилиндрического косозубого редуктора:"));
        break;
        case 2:
            CurrentReductor = Reductor::KONICHESKAYA;
            ui->label_typreductora->setText(tr("Расчет конического редуктора:"));
        break;
        case 3:
            CurrentReductor = Reductor::CHERVYACHNAYA;
            ui->label_typreductora->setText(tr("Расчет червячного редуктора:"));
        break;
    }
}

void DmWindow::on_comboBoxPeredacha3Type1_currentIndexChanged(int index)
{
    switch(index)
    {
        case 0:
            CurrentPeredacha = Peredacha::CILINDRICHESKAYA;
            ui->label_typotkritoiperedachi->setText(tr("Расчет цилиндрической открытой передачи:"));
        break;
        case 1:
            CurrentPeredacha = Peredacha::KONICHESKAYA;
            ui->label_typotkritoiperedachi->setText(tr("Расчет конической открытой передачи:"));
        break;
        case 2:
            CurrentPeredacha = Peredacha::CEPNAYA;
            ui->label_typotkritoiperedachi->setText(tr("Расчет цепной открытой передачи:"));
        break;
    }
}

void DmWindow::on_comboBoxPrivodType_currentIndexChanged(int index)
{
    switch(index)
    {
        case 0:
            CurrentPrivod = Privod::PLOSKOREMENNAYA;
            ui->label_TypRemPeredachi->setText(tr("Расчет плоскоременной передачи:"));
        break;
        case 1:
            CurrentPrivod = Privod::KLINNOREMENNAYA;
            ui->label_TypRemPeredachi->setText(tr("Расчет клинноременной передачи:"));
        break;
    }
}

void DmWindow::setTablesWidht()
{
    int i;
    ui->tableWidget_var->setColumnWidth(0, 100);
    for (i = 1; i < ui->tableWidget_var->columnCount(); i++)
        ui->tableWidget_var->setColumnWidth(i, 50);

    ui->tableWidget_var->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
    ui->tableWidget_var->verticalHeader()->setResizeMode(QHeaderView::Fixed);

    ui->tableWidget_remark->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
    ui->tableWidget_remark->verticalHeader()->setResizeMode(QHeaderView::Fixed);

    ui->tableWidgetPnom->setColumnWidth(0, 113);
    ui->tableWidgetPnom->setColumnWidth(1, 113);
    ui->tableWidgetPnom->setColumnWidth(2, 180);
    ui->tableWidgetPnom->setColumnWidth(3, 240);
    ui->tableWidgetPnom->setColumnWidth(4, 114);
    ui->tableWidgetPnom->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
    ui->tableWidgetPnom->verticalHeader()->setResizeMode(QHeaderView::Fixed);

    ui->tableWidget_4Privoda->setColumnWidth(0, 205);
    for (i = 1; i < ui->tableWidget_4Privoda->columnCount(); i++)
        ui->tableWidget_4Privoda->setColumnWidth(i, 111);
    ui->tableWidget_4Privoda->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
    ui->tableWidget_4Privoda->verticalHeader()->setResizeMode(QHeaderView::Fixed);

    ui->tableWidget_Charact1->setColumnWidth(0, 205);
    for (i = 1; i < ui->tableWidget_Charact1->columnCount(); i++)
        ui->tableWidget_Charact1->setColumnWidth(i, 50);
    ui->tableWidget_Charact1->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
    ui->tableWidget_Charact1->verticalHeader()->setResizeMode(QHeaderView::Fixed);

    for (i = 0; i < ui->tableWidget_Charact2->columnCount(); i++)
        ui->tableWidget_Charact2->setColumnWidth(i, 68);
    ui->tableWidget_Charact2->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
    ui->tableWidget_Charact2->verticalHeader()->setResizeMode(QHeaderView::Fixed);

    ui->tableWidgetSechenie->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
    ui->tableWidgetSechenie->verticalHeader()->setResizeMode(QHeaderView::Fixed);

}
