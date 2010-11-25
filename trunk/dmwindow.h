#ifndef DMWINDOW_H
#define DMWINDOW_H

#include <QMainWindow>
#include <qgraphicsview.h>
#include "math.h"

#define ROUND3(x) ((double)((int)((x + 0.0005)*1000)))/1000.0;
#define ROUND2(x) ((double)((int)((x + 0.005)*100)))/100.0;
#define ROUND1(x) ((double)((int)((x + 0.05)*10)))/10.0;
#define ROUND(x) (static_cast<int>(x + 0.5));
#define LENGTH(x) sizeof(x)/sizeof(x[0])
#define PI 3.1415926

//#define TAB_CONTROL

namespace Ui {
    class DmWindow;
}

struct Tabs
{
    enum Enum
    {
        TAB_1 = 0,
        TAB_2,
        TAB_3,
        TAB_4,
        TAB_5,
        TAB_6,

        TAB_MAX
    };
};

struct Reductor
{
    enum Enum
    {
        CILINDRICHESKAYA_PRYMOZUBAYA = 0,
        CILINDRICHESKAYA_KOSOZUBAYA,
        KONICHESKAYA,
        CHERVYACHNAYA
    };
};

struct Peredacha
{
    enum Enum
    {
        CILINDRICHESKAYA = 0,
        KONICHESKAYA,
        CEPNAYA
    };
};

typedef unsigned int uint;

class DmWindow : public QMainWindow {
    Q_OBJECT

public:
    DmWindow(QWidget *parent = 0);
    ~DmWindow();

protected:
    void changeEvent(QEvent *e);
    

private:
    Ui::DmWindow *ui;

private slots:
    //Tab 6
    void chisloZubjev2(void);
    void on_spinBox_C_valueChanged(int );
    void on_doubleSpinBox_SF_2_valueChanged(double value);
    void DopustimieNapryajeniyaIzgiba(void);
    void on_comboBox_St_2_currentIndexChanged(QString value);
    void on_comboBox_Sb_2_currentIndexChanged(QString value);
    void on_spinBox_HB2_valueChanged(int value);
    void on_spinBox_HB1_valueChanged(int value);
    void on_spinBox_Litje_valueChanged(int value);
    void viborMaterialaZubchatihKoles(void);
    void on_doubleSpinBox_u3_valueChanged(double value);
    void on_doubleSpinBox_n3_valueChanged(double value);
    void on_doubleSpinBox_T3_valueChanged(double value);
    bool checkTab6(void);

    //Tab 2
    void on_spinBox_2_valueChanged(int index);
    void on_spinBox_Variant2_valueChanged(int );
    void on_comboBox_Pnom_currentIndexChanged(void);
    void on_tabWidget_currentChanged(int index);
    void updateKPDText(void);
    void updatePValues(void);
    void updateNValues(void);
    void updateIValues(void);
    void updatePnomTable(void);
    void updateTablePeredatochnoeOtnoshenie(void);
    void updateHarakteristiki(void);
    bool checkTab2(void);

    //Tab 3
    bool checkTab3(void);
    void updateLabelTextTab3(void);
    void updateDiametrVedushegoShkiva(void);
    void updateDiametrVedomogoShkiva(void);
    void updatePeredatochnoeChislo(void);
    void updatePredMejosevoeRastoyanie(void);
    void updateDlinaRemnya(void);
    void updateStandartDlinaRemnya(void);
    void updateMejosevoeRastoyanie(void);
    void updateSkorostRemney(void);
    void updateDolgovechnostiRemney(void);
    void updateUgolObhvataMinShkiva(void);
    void updateMoshnostNaOdnomRemne(void);
    void updateKolichestvoRemney(void);
    void updateNatyajenieRemnya(void);
    void updateNagruzkaVala(void);
    void updateOsnovnieRazmeriShkivov(void);
    double getValPo(uint start, uint end, double d1, double v);

    //Tab 4
    void on_spinBox_HVsr2_valueChanged(int value);
    void on_spinBox_HVsr1_valueChanged(int value);
    void on_comboBox_Koleso_currentIndexChanged(int index);
    void on_comboBox_Shesternya_currentIndexChanged(int index);
    void updateChisloCiclov(void);
    void updateFactChisloCiclov(void);
    void updateKontaktnieNapryajenia(void);
    bool checkTab4(void);
    void updateNapryajenieIzgiba(void);
    void updateMejOsevoeRastoyanie(void);
    void updateViborMateriala(void);
    void on_comboBox_Sb_currentIndexChanged(QString value);

    //Tab 5
    void ProverkaPrigodnostiZagotovki(void);
    void on_doubleSpinBox_Kfv_valueChanged(double value);
    void on_comboBox_Kfbeta_currentIndexChanged(QString value);
    void ProverkaNaVinoslivostPoNapryajeniyuIzgiba(void);
    void SilaDejstviyaVZaceplenii(void);
    void on_doubleSpinBox_Khv_valueChanged(double value);
    void on_comboBox_Zm_currentIndexChanged(QString value);
    void on_spinBox_StepenPeredachi_valueChanged(int value);
    void ProverkaNaKontaktnuyuVinoslivost(void);
    void OsnovnojGeometricheskijObjom(void);
    void FacticheskoePeredatochnoeOtnoshenie(void);
    void FacticheskijUgolNaklona(void);
    void ChisloZubjev(void);
    void UgolNaklonaZubjev(void);
    void on_comboBox_m_currentIndexChanged(QString value);
    void ModulZacepleniya(void);
    void ShirinaZubchatogoVenca(void);
    void on_comboBox_aw_currentIndexChanged(QString value);
    void on_comboBox_St_currentIndexChanged(QString value );
    void on_comboBox_KHBeta_currentIndexChanged(QString value);
    void on_comboBox_Psiba_currentIndexChanged(QString value);
    void on_doubleSpinBox_u2_valueChanged(double value);
    void on_doubleSpinBox_n2_valueChanged(double value);
    void on_doubleSpinBox_T2_valueChanged(double value);
    bool checkTab5(void);
    void KoefficientShirini(void);
    double GetVspomogatelniyKoeficient(void);

    //Global
    void on_comboBoxPeredacha1Type1_currentIndexChanged(int index);
    void on_comboBoxPeredacha3Type1_currentIndexChanged(int index);
    void setPicture(QGraphicsView *graphics, const char* buffer );

private:
    int CurrentReductor;
    int CurrentPeredacha;

    //Tab 1
    double  dValPiv;
    int     iValN;
    int     iValLh;
    double  iValFt;
    double  dValV;
    double  dValOmega;
    double  dValD;
    double  dValP;
    double  dValZ;

    //Tab 2
    double  dValOmega1, dValOmega2, dValOmega3, dValOmega4;
    double  dValEta, dValEta1, dValEta2, dValEta3;
    double  dValNiv;
    double  dValI, dValI1, dValI2, dValI3;
    double  dValN1, dValN2, dValN3, dValN4;
    double  dValP1, dValP2, dValP3, dValP4;
    double  dValT1, dValT2, dValT3, dValT4;

    //Tab 3
    double dValXi;
    double dVald11, dVald12;
    double dVald21, dVald22;
    double dValU, dValU1, dValU2;
    double dValaa1, dValaa2;
    double dVala1, dVala2, dVala12, dVala22;
    double dValll1, dValll2;
    double dVall1, dVall2;
    double dValV1, dValV2;
    double dValNpr1, dValNpr2;
    double dValAlpha1, dValAlpha2;
    double dValKp;
    double dValCa1, dValCa2;
    double dValPo1, dValPo2;
    double dVal_ll1, dVal_ll2;
    double dValCl1, dValCl2;
    double dValPPo1, dValPPo2;
    double dValCp;
    int    iValRemen1, iValRemen2;
    int    iValZp1, iValZp2;
    double dValCz1, dValCz2;
    double dValF0;
    double dValRn;
    double dValde1, dValde2;
    double dValM;

    //Tab 4
    int    iHBcp1, iHBcp2;
    double dNH01, dNH02;
    int    iShesternya4Index;
    int    iKoleso4Index;
    int    iN1, iN2;
    double dKHL1, dKHL2;
    double dSigmaH1, dSigmaH2, dSigmaH3;
    double dSigmaF1, dSigmaF2;
    double dKFL1, dKFL2;
    double dVs;
    int    iSb, iSt;
    int    iN2fe;
    int    iSigmaT;
    int    iC;

    //Tab 5
    double dT2;
    double dn2;
    double du2;
    double dPsiba;
    double dPsibd;
    double dKHBeta;
    double daw, daw2;
    double dKa;
    int    ib1, ib2;
    double dmm, dmm1, dmm2;
    double dbb;
    double dZsum;
    int    iZsum;
    double dZ1;
    int    iZ1 , iZ2;
    double dBeta;
    double dUf, dUf2;
    double dd1, dd2;
    double dda1, dda2;
    double ddf1, ddf2;
    double dPsibd2;
    double dV;
    int    iNaznachenie;
    double dEtaAlpha;
    int    iZm;
    double dZh;
    double dZe;
    double dKHa;
    double dKHV;
    double dSigmaH51;
    double dSigmaHmax, dSigmaHHmax;
    double dFt, dFr, dFa;
    double dKFBeta;
    double dKFV;
    double dKFa;
    int    iZV1, iZV2;
    double dYF1, dYF2;
    double dYb;
    double dSigmaF51, dSigmaF52;
    int    iSigmaFmax1, iSigmaFmax2;
    int    iSigmaFFmax1, iSigmaFFmax2;
    int    iDrped;
    double dDzag;
    int    iSrped;
    double dCzag;
    int    iSzag1, iSzag2;

    //Tab 6
    double dT3;
    double dn3;
    double du3;
    int    iLitje;
    int    iHB1, iHB2;
    int    iSb2, iSt2;
    double dSf1, dSf2;
    double dSF;
    int    iN1FE, iN2FE;
    double dSff1, dSff2;

};

#endif // DMWINDOW_H
