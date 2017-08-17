#include <string>
#include <iostream>

#include "TDirectory.h"
#include "TStyle.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TVirtualPad.h"
#include "TH1F.h"
#include "TProfile.h"
#include "TF1.h"
#include "TLegend.h"


struct Parameters
{
  int logX;
  int logY;
  int nbin;
  double range[2];
  double miny;
  double maxy;

  Parameters() : logX(0), logY(0), nbin(), range(), miny(), maxy() {}
};



void
plot_rates(TVirtualPad* pad,
           std::vector<int>& fills,
           std::vector<TChain*>& chains,
           std::vector<std::string>& seeds,
           const Parameters& par)
{
  const int random = rand();
  char buf[BUFSIZ];
  const int symbols[] = {24, 25, 26, 32, 30, 27, 28, 46};
  const int colors[] = {kBlue, kMagenta, kGreen+1, kRed, kGray+1, kOrange-1, kCyan+1, kViolet-1, kYellow+1, kBlack};

  const char pileUp[] = "pileup"; 
  const char format[] = "%s/23.31/nCollidingBunches:pileUp>>%s";

  std::vector<TH1F*> th1f;
  size_t nn = 0;
  for (size_t ii = 0; ii < chains.size(); ii++)
  {
    TChain* chain = chains.at(ii);
    for (size_t jj = 0; jj < seeds.size(); jj++)
    {
      th1f.push_back(0);
      std::stringstream ss;
      ss << "th1f_" << seeds[jj] << "_" << std::setw(2) << std::setfill('0') << nn << "_" << random;
      TProfile* tprof = new TProfile(ss.str().c_str(), "", par.nbin, par.range[0], par.range[1], "");
      snprintf(buf, sizeof(buf), format, seeds[jj].c_str(), ss.str().c_str());
      chain->Draw(buf, "", "prof");
      th1f[nn] = (TH1F*)gDirectory->Get(ss.str().c_str());
      th1f[nn]->SetXTitle(pileUp);
      th1f[nn]->SetYTitle("Single BX Rate [Hz]");
      th1f[nn]->SetTitle("");
      th1f[nn]->SetStats(0);
      th1f[nn]->SetMarkerStyle(symbols[jj%8]);
      th1f[nn]->SetMarkerSize(0.6);
      th1f[nn]->SetMarkerColor(colors[ii%(sizeof(colors)/sizeof(colors[0]))]);
      nn++;
    }
  }


  TLegend *legend = new TLegend(0.15, 0.70, 0.65, 0.90);
  for (size_t ii = 0; ii < seeds.size(); ii++)
  {
    legend->AddEntry(th1f[ii], seeds[ii].c_str(), "p");
  }


  nn = 0;
  pad->SetLogy(par.logY);
  pad->SetLogx(par.logX);
  for (int ii = 0; ii < chains.size(); ii++)
  {
    for (size_t jj = 0; jj < seeds.size(); jj++)
    {
      if ((ii == 0) and (jj == 0))
      {
        th1f[nn]->SetMaximum(par.maxy*1.1);
        th1f[nn]->SetMinimum(par.miny*0.9);
        th1f[nn]->Draw();
      }
      else
      {
        th1f[nn]->Draw("same");
      }
      nn++;
    }
  }


  legend->SetBorderSize(0);
  legend->SetFillColor(kWhite);
  legend->Draw();

  TLegend *fill = new TLegend(0.75, 0.20, 0.85, 0.40);
  for (size_t ii = 0; ii < fills.size(); ii++)
  {
    snprintf(buf, sizeof(buf), "fill %4d", fills.at(ii));
    fill->AddEntry(th1f[ii], buf, "p");
  }
  fill->SetBorderSize(0);
  fill->SetFillColor(kWhite);
  fill->Draw();
}



void l1_rate_study()
{
  gStyle->SetOptStat(0);
  gStyle->SetPaintTextFormat(".2f");
  gStyle->SetHistMinimumZero(kTRUE);

  std::vector<int> fills;

  /*=================================================================*
   * select list of fills
   *=================================================================*/
#if 0
  fills.push_back(5704);
  fills.push_back(5710);
  fills.push_back(5717);
  fills.push_back(5718);
  fills.push_back(5719);
  fills.push_back(5722);
  fills.push_back(5730);
  fills.push_back(5737);
  fills.push_back(5746);
  fills.push_back(5749);
#endif
#if 0
  fills.push_back(5750);
  fills.push_back(5822);
  fills.push_back(5824);
  fills.push_back(5825);
  fills.push_back(5830);
  fills.push_back(5833);
  fills.push_back(5834);
  fills.push_back(5837);
  fills.push_back(5838);
  fills.push_back(5839);
#endif
#if 0
  fills.push_back(5840);
  fills.push_back(5842);
  fills.push_back(5845);
  fills.push_back(5848);
  fills.push_back(5849);
  fills.push_back(5856);
  fills.push_back(5864);
  fills.push_back(5865);
  fills.push_back(5868);
  fills.push_back(5870);
#endif
#if 0
  fills.push_back(5872);
  fills.push_back(5873);
  fills.push_back(5876);
  fills.push_back(5878);
  fills.push_back(5880);
  fills.push_back(5882);
  fills.push_back(5883);
  fills.push_back(5885);
  fills.push_back(5887);
  fills.push_back(5919);
#endif
#if 0
  fills.push_back(5920);
  fills.push_back(5930);
  fills.push_back(5934);
  fills.push_back(5942);
  fills.push_back(5946);
  fills.push_back(5950);
  fills.push_back(5952);
  fills.push_back(5954);
  fills.push_back(5958);
  fills.push_back(5960);
#endif

  //
  // L1 menu v2
  //
#if 1
  fills.push_back(5962);
  fills.push_back(5963);
  fills.push_back(5965);
  fills.push_back(5966);
  fills.push_back(5971);
  fills.push_back(5974);
  fills.push_back(5976);
  fills.push_back(5979);
  fills.push_back(5984);
  fills.push_back(6020);
#endif
#if 1
  fills.push_back(6021);
  fills.push_back(6024);
  fills.push_back(6026);
  fills.push_back(6030);
  fills.push_back(6031);
  fills.push_back(6035);
  fills.push_back(6041);
  fills.push_back(6044);
  fills.push_back(6046);
  fills.push_back(6048);
#endif
#if 1
  fills.push_back(6050);
  fills.push_back(6052);
  fills.push_back(6053);
  fills.push_back(6054);
  fills.push_back(6055);
  fills.push_back(6057);
  fills.push_back(6060);
  fills.push_back(6061);
  fills.push_back(6072);
  fills.push_back(6079);
#endif
#if 1
  fills.push_back(6082);
  fills.push_back(6084);
  fills.push_back(6086);
  fills.push_back(6089);
  fills.push_back(6090);
  fills.push_back(6091);
  fills.push_back(6093);
  fills.push_back(6094);
#endif


  /*=================================================================*
   * prepare chains
   *=================================================================*/
  const std::string data_directory = "2017";
  const std::string year = "2017";
  std::vector<TChain*> chains;
  for (size_t ii = 0; ii < fills.size(); ii++)
  {
    TChain *chain = new TChain("rate");
    std::stringstream ss;
    ss << year << "/fill" << fills.at(ii) << ".txt";
    std::ifstream text(ss.str());
    std::vector<std::string> list;
    if (text.is_open())
    { 
      std::string line;
      while (getline(text, line))
      { 
        if (line.at(0) == '#') continue;
        list.push_back(line);
      }
      text.close();
    }
    else
    {
      std::cout << "err> could not open '" << ss.str() << "'\n";
    }

    for (size_t ii = 0; ii < list.size(); ii++)
    {
      std::cout << "inf> " << list[ii] << "\n";
      const std::string path = data_directory + "/" + list[ii];
      chain->AddFile(path.c_str());
    }
    chains.push_back(chain);
  }


  /*=================================================================*
   * set parameters
   *=================================================================*/
  Parameters par;
  par.nbin = 200;
  par.range[0] = 30.;
  par.range[1] = 50.;
  par.logX = 0;
  par.logY = 0;


  /*=================================================================*
   * make plots
   *=================================================================*/
  TVirtualPad* pad;
  char buf[BUFSIZ];
  std::vector<std::string> seeds;

  TCanvas canvas("canvas", "canvas", 800, 600);
  canvas.Divide(2,2);


  /*-----------------------------------------------------------------*/
  canvas.Clear();
  pad = canvas.cd(1);

  seeds.clear();
  seeds.push_back("L1_SingleEG38");
  par.miny = 2.5;
  par.maxy = 5.3;

  plot_rates(pad, fills, chains, seeds, par);
  canvas.Update();
  pad->Print("EG38.pdf");


  /*-----------------------------------------------------------------*/
  canvas.Clear();
  pad = canvas.cd(1);

  seeds.clear();
  seeds.push_back("L1_SingleEG38er2p1");
  par.miny = 1.8;
  par.maxy = 3.5;

  plot_rates(pad, fills, chains, seeds, par);
  canvas.Update();
  pad->Print("EG38er.pdf");

  /*-----------------------------------------------------------------*/
  canvas.Clear();
  pad = canvas.cd(1);

  seeds.clear();
  seeds.push_back("L1_SingleEG28");
  par.miny = 6.8;
  par.maxy = 15.;

  plot_rates(pad, fills, chains, seeds, par);
  canvas.Update();
  pad->Print("EG28.pdf");

  /*-----------------------------------------------------------------*/
  canvas.Clear();
  pad = canvas.cd(1);

  seeds.clear();
  seeds.push_back("L1_SingleEG18");
  par.miny = 34.;
  par.maxy = 75.;

  plot_rates(pad, fills, chains, seeds, par);
  canvas.Update();
  pad->Print("EG18.pdf");

  /*-----------------------------------------------------------------*/
  canvas.Clear();
  pad = canvas.cd(1);

  seeds.clear();
  seeds.push_back("L1_SingleIsoEG38");
  par.miny = 1.9;
  par.maxy = 4.0;

  plot_rates(pad, fills, chains, seeds, par);
  canvas.Update();
  pad->Print("IsoEG38.pdf");

  /*-----------------------------------------------------------------*/
  canvas.Clear();
  pad = canvas.cd(1);

  seeds.clear();
  seeds.push_back("L1_SingleIsoEG38er2p1");
  par.miny = 1.6;
  par.maxy = 3.0;

  plot_rates(pad, fills, chains, seeds, par);
  canvas.Update();
  pad->Print("IsoEG38er.pdf");

  /*-----------------------------------------------------------------*/
  canvas.Clear();
  pad = canvas.cd(1);

  seeds.clear();
  seeds.push_back("L1_SingleIsoEG28");
  par.miny = 3.0;
  par.maxy = 7.0;

  plot_rates(pad, fills, chains, seeds, par);
  canvas.Update();
  pad->Print("IsoEG28.pdf");

  /*-----------------------------------------------------------------*/
  canvas.Clear();
  pad = canvas.cd(1);

  seeds.clear();
  seeds.push_back("L1_SingleIsoEG18");
  par.miny = 8.0;
  par.maxy = 13.;

  plot_rates(pad, fills, chains, seeds, par);
  canvas.Update();
  pad->Print("IsoEG18.pdf");

  /*-----------------------------------------------------------------*/
  canvas.Clear();
  pad = canvas.cd(1);

  seeds.clear();
  seeds.push_back("L1_DoubleIsoTau32er2p1");
  par.miny = 2.3;
  par.maxy = 4.0;

  plot_rates(pad, fills, chains, seeds, par);
  canvas.Update();
  pad->Print("DIsoTau32er.pdf");

  /*-----------------------------------------------------------------*/
  canvas.Clear();
  pad = canvas.cd(1);

  seeds.clear();
  seeds.push_back("L1_SingleJet170");
  par.miny = 0.95;
  par.maxy = 1.8;

  plot_rates(pad, fills, chains, seeds, par);
  canvas.Update();
  pad->Print("JET170.pdf");

  /*-----------------------------------------------------------------*/
  canvas.Clear();
  pad = canvas.cd(1);

  seeds.clear();
  seeds.push_back("L1_ETM60");
  par.miny = 20.;
  par.maxy = 160.;

  plot_rates(pad, fills, chains, seeds, par);
  canvas.Update();
  pad->Print("ETM60.pdf");

  /*-----------------------------------------------------------------*/
  canvas.Clear();
  pad = canvas.cd(1);

  seeds.clear();
  seeds.push_back("L1_ETM120");
  par.miny = 0.25;
  par.maxy = 1.1;

  plot_rates(pad, fills, chains, seeds, par);
  canvas.Update();
  pad->Print("ETM120.pdf");

  /*-----------------------------------------------------------------*/
  canvas.Clear();
  pad = canvas.cd(1);

  seeds.clear();
  seeds.push_back("L1_ETMHF70");
  par.miny = 0.;
  par.maxy = 80.;

  plot_rates(pad, fills, chains, seeds, par);
  canvas.Update();
  pad->Print("ETMHF70.pdf");

  /*-----------------------------------------------------------------*/
  canvas.Clear();
  pad = canvas.cd(1);

  seeds.clear();
  seeds.push_back("L1_ETMHF120");
  par.miny = 0.32;
  par.maxy = 1.4;

  plot_rates(pad, fills, chains, seeds, par);
  canvas.Update();
  pad->Print("ETMHF120.pdf");

  /*-----------------------------------------------------------------*/
  canvas.Clear();
  pad = canvas.cd(1);

  seeds.clear();
  seeds.push_back("L1_HTT380er");
  par.miny = 0.6;
  par.maxy = 1.4;

  plot_rates(pad, fills, chains, seeds, par);
  canvas.Update();
  pad->Print("HTT380er.pdf");

  /*-----------------------------------------------------------------*/
  canvas.Clear();
  pad = canvas.cd(1);

  seeds.clear();
  seeds.push_back("L1_DoubleJet40er3p0");
  par.miny = 50.;
  par.maxy = 500.;

  plot_rates(pad, fills, chains, seeds, par);
  canvas.Update();
  pad->Print("DoubleJet40er3p0.pdf");

}

// eof
