#include "TH2.h"
#include "TFile.h"
#include "TTree.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TEllipse.h"
#include "TStyle.h"
#include "TGraph.h"
#include "TMath.h"
#include "TMatrixD.h"
#include "TMatrixDBase.h"
#include "TMatrixDSym.h"
#include "TMatrixDSymEigen.h"
#include "TVectorD.h"
#include "TF2.h"
#include "TColor.h"
#include "TROOT.h"
#include "TFrame.h"

#include "tdrStyle.C"
#include "CMS_lumi.C"

#include <iostream>

void hybscan(){

   setTDRStyle();

   TGraph *gstat = new TGraph();
   TGraph *gsyst_tot = new TGraph();
   TGraph *gsyst_jes = new TGraph();

   int ip = 0;
   double whyb = 0;
   double whybcorr = 0;
   double sjsf = 0;

   double statsq = 0.0047*0.0047/13;

   // whyb = 0
   whyb = 0;
   sjsf = 0.0047*0.0047*(1-whyb)/whyb;
   whybcorr = statsq/(statsq+sjsf);
   ip = gstat->GetN();
   gstat->SetPoint(ip, whybcorr, 0.383);
   gsyst_tot->SetPoint(ip, whybcorr, 1.245);
   gsyst_jes->SetPoint(ip, whybcorr, 0.08);

   // whyb = 0.8
   whyb = 0.8;
   sjsf = 0.0047*0.0047*(1-whyb)/whyb;
   whybcorr = statsq/(statsq+sjsf);
   ip = gstat->GetN();
   gstat->SetPoint(ip, whybcorr, 0.162);
   gsyst_tot->SetPoint(ip, whybcorr, 1.026);
   gsyst_jes->SetPoint(ip, whybcorr, 0.22);

   // whyb = 0.9
   whyb = 0.9;
   sjsf = 0.0047*0.0047*(1-whyb)/whyb;
   whybcorr = statsq/(statsq+sjsf);
   ip = gstat->GetN();
   gstat->SetPoint(ip, whybcorr, 0.159);
   gsyst_tot->SetPoint(ip, whybcorr, 0.9235);
   gsyst_jes->SetPoint(ip, whybcorr, 0.321);

   // whyb = 0.95
   whyb = 0.95;
   sjsf = 0.0047*0.0047*(1-whyb)/whyb;
   whybcorr = statsq/(statsq+sjsf);
   ip = gstat->GetN();
   gstat->SetPoint(ip, whybcorr, 0.159);
   gsyst_tot->SetPoint(ip, whybcorr, 0.9125);
   gsyst_jes->SetPoint(ip, whybcorr, 0.41);

   // whyb = 0.98
   whyb = 0.98;
   sjsf = 0.0047*0.0047*(1-whyb)/whyb;
   whybcorr = statsq/(statsq+sjsf);
   ip = gstat->GetN();
   gstat->SetPoint(ip, whybcorr, 0.159);
   gsyst_tot->SetPoint(ip, whybcorr, 0.9285);
   gsyst_jes->SetPoint(ip, whybcorr, 0.4915);

   // whyb = 1.0
   whyb = 1.0;
   sjsf = 0.0047*0.0047*(1-whyb)/whyb;
   whybcorr = statsq/(statsq+sjsf);
   ip = gstat->GetN();
   gstat->SetPoint(ip, whybcorr, 0.147);
   gsyst_tot->SetPoint(ip, whybcorr, TMath::Sqrt(0.99*0.99-0.17*0.17)); // subtract out PDF systs
   gsyst_jes->SetPoint(ip, whybcorr, 0.58);

   // additional graphs
   TGraph *gtot = new TGraph();
   TGraph *gsyst_other = new TGraph();
   for(int i=0; i < gstat->GetN(); i++){
      double xtot, ytot;
      double xjes, yjes;
      double xstat, ystat;
      gsyst_tot->GetPoint(i, xtot, ytot);
      gsyst_jes->GetPoint(i, xjes, yjes);
      gstat->GetPoint(i, xstat, ystat);
      gsyst_other->SetPoint(i, xtot, TMath::Sqrt(ytot*ytot-yjes*yjes));
      gtot->SetPoint(i, xtot, TMath::Sqrt(ytot*ytot+ystat*ystat));
   }

   // formatting
   gtot->SetMarkerStyle(20);
   gtot->SetMarkerColor(2);
   gstat->SetMarkerStyle(21);
   gsyst_tot->SetMarkerStyle(22);
   gsyst_jes->SetMarkerStyle(24);
   gsyst_other->SetMarkerStyle(25);

   TCanvas *c = new TCanvas("c","c",800,800);
   gtot->SetMinimum(0);
   gtot->SetMaximum(1.4);
   gtot->Draw("AP");
   gstat->Draw("P");
   gsyst_tot->Draw("P");
   gsyst_jes->Draw("P");
   gsyst_other->Draw("P");

   TLegend *l = new TLegend(0.1,0.7,0.48,0.9);
   l->AddEntry(gtot, "Total Uncertainty","p");
   l->AddEntry(gstat, "Statistical","p");
   l->AddEntry(gsyst_tot, "Systematic","p");
   l->AddEntry(gsyst_jes, "JES systematics","p");
   l->AddEntry(gsyst_other, "Other systematics","p");
   l->Draw("same");

   return;
}

