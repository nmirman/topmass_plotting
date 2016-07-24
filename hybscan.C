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

   double statsq = 0.0047*0.0047;

   // whyb = 0
   whyb = 0;
   ip = gstat->GetN();
   gstat->SetPoint(ip, whyb, 0.383);
   gsyst_tot->SetPoint(ip, whyb, 1.245);
   gsyst_jes->SetPoint(ip, whyb, 0.08);

   // whyb = 0.25
   whyb = 0.25;
   ip = gstat->GetN();
   gstat->SetPoint(ip, whyb, 0.32);
   gsyst_tot->SetPoint(ip, whyb, 0.5*(1.08+1.35));
   gsyst_jes->SetPoint(ip, whyb, 0.5*(0.16+0.17));

   // whyb = 0.50
   whyb = 0.50;
   ip = gstat->GetN();
   gstat->SetPoint(ip, whyb, 0.21);
   gsyst_tot->SetPoint(ip, whyb, 0.5*(0.97+1.11));
   gsyst_jes->SetPoint(ip, whyb, 0.5*(0.285+0.295));

   // whyb = 0.60
   whyb = 0.60;
   ip = gstat->GetN();
   gstat->SetPoint(ip, whyb, 0.17);
   gsyst_tot->SetPoint(ip, whyb, 0.5*(0.945+1.047));
   gsyst_jes->SetPoint(ip, whyb, 0.5*(0.34+0.35));

   // whyb = 0.75
   whyb = 0.75;
   ip = gstat->GetN();
   gstat->SetPoint(ip, whyb, 0.19);
   gsyst_tot->SetPoint(ip, whyb, 0.5*(0.93+0.98));
   gsyst_jes->SetPoint(ip, whyb, 0.5*(0.41+0.42));

   // whyb = 0.80
   whyb = 0.80;
   ip = gstat->GetN();
   gstat->SetPoint(ip, whyb, 0.18);
   gsyst_tot->SetPoint(ip, whyb, 0.5*(0.92+0.96));
   gsyst_jes->SetPoint(ip, whyb, 0.5*(0.44+0.45));

   // whyb = 0.85
   whyb = 0.85;
   ip = gstat->GetN();
   gstat->SetPoint(ip, whyb, 0.16);
   gsyst_tot->SetPoint(ip, whyb, 0.5*(0.93+0.96));
   gsyst_jes->SetPoint(ip, whyb, 0.5*(0.47+0.48));

   // whyb = 0.90
   whyb = 0.90;
   ip = gstat->GetN();
   gstat->SetPoint(ip, whyb, 0.13);
   gsyst_tot->SetPoint(ip, whyb, 0.5*(0.94+0.95));
   gsyst_jes->SetPoint(ip, whyb, 0.5*(0.505+0.509));

   // whyb = 0.95
   whyb = 0.95;
   ip = gstat->GetN();
   gstat->SetPoint(ip, whyb, 0.13);
   gsyst_tot->SetPoint(ip, whyb, 0.5*(0.946+0.950));
   gsyst_jes->SetPoint(ip, whyb, 0.5*(0.535+0.539));

   // whyb = 1.0
   whyb = 1.0;
   ip = gstat->GetN();
   gstat->SetPoint(ip, whyb, 0.147);
   gsyst_tot->SetPoint(ip, whyb, TMath::Sqrt(0.99*0.99-0.17*0.17)); // subtract out PDF systs
   gsyst_jes->SetPoint(ip, whyb, 0.58);

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

