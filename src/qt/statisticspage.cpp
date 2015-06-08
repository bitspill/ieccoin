#include "statisticspage.h"
#include "ui_statisticspage.h"
#include "main.h"
#include "wallet.h"
#include "init.h"
#include "base58.h"
#include "clientmodel.h"
#include "bitcoinrpc.h"
#include <sstream>
#include <string>

using namespace json_spirit;

StatisticsPage::StatisticsPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticsPage)
{
    ui->setupUi(this);
    
    setFixedSize(400, 420);
    
    connect(ui->startButton, SIGNAL(pressed()), this, SLOT(updateStatistics()));
}

int heightPrevious = -1;
int connectionPrevious = -1;
int volumePrevious = -1;
double netPawratePrevious = -1;
double pawratePrevious = -1;
double hardnessPrevious = -1;
double hardnessPrevious2 = -1;
QString stakecPrevious = "";
QString rewardPrevious = "";

void StatisticsPage::updateStatistics()
{
		
    double pHardness = GetDifficulty();
	// double pHardness2 = GetDifficulty(GetLastBlockIndex(pindexBest, true));
    double pHardness2 = 0;
 //   int pPawrate = GetPoWMHashPS();
	 int pPawrate = 0;
    double pPawrate2 = 0.000;
    int nHeight = pindexBest->nHeight;
 //    int volume = ((pindexBest->nMoneySupply)/100000000);
	 int volume = 0;
    int peers = this->model->getNumConnections();
    pPawrate2 = (double)pPawrate;
    QString height = QString::number(nHeight);
    QString phase = "";
    if (pindexBest->nHeight+1 > 0)
    {
        phase = "POW";
    }
    QString subsidy = "";
    if (pindexBest->nHeight+1 >= 0 && pindexBest->nHeight+1 < 2)
    {
        subsidy = "7.6 IEC per block";
    }
    else if(pindexBest->nHeight+1 == 2)
    {
        subsidy = "60000000 IEC  block";
    }
    else if (pindexBest->nHeight+1 > 2 && pindexBest->nHeight+1 < 5256000)
    {
        subsidy = "7.6 IEC per block";
    }
	else if (pindexBest->nHeight+1 >= 5256000 && pindexBest->nHeight+1 < 10512000)
    {
        subsidy = "3.8 IEC per block";
    }
	else if (pindexBest->nHeight+1 >= 10512000 && pindexBest->nHeight+1 < 15768000)
    {
        subsidy = "1.9 IEC per block";
    }
	else if (pindexBest->nHeight+1 >= 15768000)
    {
        subsidy = "0.95 IEC per block";
    }
    QString hardness = QString::number(pHardness, 'f', 6);
    QString hardness2 = QString::number(pHardness2, 'f', 6);
    QString pawrate = QString::number(pPawrate2, 'f', 3);
    QString Qlpawrate = model->getLastBlockDate().toString();

    QString QPeers = QString::number(peers);
    QString qVolume = QLocale(QLocale::English).toString(volume);

    if(nHeight > heightPrevious)
    {
        ui->heightBox->setText("<b><font color=\"#ebbcff\">" + height + "</font></b>");
    } else {
    ui->heightBox->setText(height);
    }

   
  
    ui->cBox->setText(phase);
    
    
    if(subsidy != rewardPrevious)
    {
        ui->rewardBox->setText("<b><font color=\"#ebbcff\">" + subsidy + "</font></b>");
    } else {
    ui->rewardBox->setText(subsidy);
    }
    
    if(pHardness > hardnessPrevious)
    {
        ui->diffBox->setText("<b><font color=\"#ebbcff\">" + hardness + "</font></b>");        
    } else if(pHardness < hardnessPrevious) {
        ui->diffBox->setText("<b><font color=\"red\">" + hardness + "</font></b>");
    } else {
        ui->diffBox->setText(hardness);        
    }
/*
    if(pHardness2 > hardnessPrevious2)
    {
        ui->diffBox2->setText("<b><font color=\"#ebbcff\">" + hardness2 + "</font></b>" + " DISABLED");
    } else if(pHardness2 < hardnessPrevious2) {
        ui->diffBox2->setText("<b><font color=\"red\">" + hardness2 + "</font></b>" + " DISABLED");
    } else {
        ui->diffBox2->setText(hardness2 + " DISABLED");
    }
*/
 /*   
    if(pPawrate2 > netPawratePrevious)
    {
        ui->pawrateBox->setText("<b><font color=\"#ebbcff\">" + pawrate + " MH/s</font></b>");
    } else if(pPawrate2 < netPawratePrevious) {
        ui->pawrateBox->setText("<b><font color=\"red\">" + pawrate + " MH/s</font></b>");
    } else {
        ui->pawrateBox->setText(pawrate + " MH/s");
    }
*/
    if(Qlpawrate != pawratePrevious)
    {
        ui->localBox->setText("<b><font color=\"#ebbcff\">" + Qlpawrate + "</font></b>");
    } else {
    ui->localBox->setText(Qlpawrate);
    }
    
    if(peers > connectionPrevious)
    {
        ui->connectionBox->setText("<b><font color=\"#ebbcff\">" + QPeers + "</font></b>");             
    } else if(peers < connectionPrevious) {
        ui->connectionBox->setText("<b><font color=\"red\">" + QPeers + "</font></b>");        
    } else {
        ui->connectionBox->setText(QPeers);  
    }
/*
    if(volume > volumePrevious)
    {
        ui->volumeBox->setText("<b><font color=\"#ebbcff\">" + qVolume + " IEC" + "</font></b>");
    } else if(volume < volumePrevious) {
        ui->volumeBox->setText("<b><font color=\"red\">" + qVolume + " IEC" + "</font></b>");
    } else {
        ui->volumeBox->setText(qVolume + " IEC");
    }
	*/
    updatePrevious(nHeight, phase, subsidy, pHardness, pHardness2, pPawrate2, Qlpawrate, peers, volume);
}

void StatisticsPage::updatePrevious(int nHeight, QString phase, QString subsidy, double pHardness, double pHardness2, double pPawrate2, QString Qlpawrate, int peers, int volume)
{
    heightPrevious = nHeight;
	stakecPrevious = phase;
    rewardPrevious = subsidy;
    hardnessPrevious = pHardness;
    hardnessPrevious2 = pHardness2;
    netPawratePrevious = pPawrate2;
    pawratePrevious = Qlpawrate;
    connectionPrevious = peers;
    volumePrevious = volume;
}

void StatisticsPage::setModel(ClientModel *model)
{
    updateStatistics();
    this->model = model;
}


StatisticsPage::~StatisticsPage()
{
    delete ui;
}
