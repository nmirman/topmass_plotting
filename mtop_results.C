#include "TH2.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TEllipse.h"
#include "TStyle.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
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
#include "TLatex.h"

#include "tdrStyle.C"
#include "CMS_lumi.C"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

void mtop_results(){

   setTDRStyle();

   double mt1D = 172.39;
   double mt1D_stat = 0.17;
   double mt1D_systUP = 0.91;
   double mt1D_systDN = 0.95;
   double mt1D_totUP = TMath::Sqrt(mt1D_stat*mt1D_stat+mt1D_systUP*mt1D_systUP);
   double mt1D_totDN = TMath::Sqrt(mt1D_stat*mt1D_stat+mt1D_systDN*mt1D_systDN);

   double mt2D = 171.56;
   double mt2D_stat = 0.46;
   double mt2D_systUP = 1.31;
   double mt2D_systDN = 1.25;
   double mt2D_totUP = TMath::Sqrt(mt2D_stat*mt2D_stat+mt2D_systUP*mt2D_systUP);
   double mt2D_totDN = TMath::Sqrt(mt2D_stat*mt2D_stat+mt2D_systDN*mt2D_systDN);

   double mthyb = 172.22;
   double mthyb_stat = 0.18;
   double mthyb_systUP = 0.89;
   double mthyb_systDN = 0.93;
   double mthyb_totUP = TMath::Sqrt(mthyb_stat*mthyb_stat+mthyb_systUP*mthyb_systUP);
   double mthyb_totDN = TMath::Sqrt(mthyb_stat*mthyb_stat+mthyb_systDN*mthyb_systDN);

   double mtMAOS = 171.54;
   double mtMAOS_stat = 0.19;
   double mtMAOS_systUP = 1.27;
   double mtMAOS_systDN = 1.02;
   double mtMAOS_totUP = TMath::Sqrt(mtMAOS_stat*mtMAOS_stat+mtMAOS_systUP*mtMAOS_systUP);
   double mtMAOS_totDN = TMath::Sqrt(mtMAOS_stat*mtMAOS_stat+mtMAOS_systDN*mtMAOS_systDN);

   double mtCMS = 172.44;
   double mtCMS_stat = 0.13;
   double mtCMS_systUP = 0.47;
   double mtCMS_systDN = 0.47;
   double mtCMS_totUP = TMath::Sqrt(mtCMS_stat*mtCMS_stat+mtCMS_systUP*mtCMS_systUP);
   double mtCMS_totDN = TMath::Sqrt(mtCMS_stat*mtCMS_stat+mtCMS_systDN*mtCMS_systDN);

   TCanvas *c = new TCanvas("c","c",800,800);
   c->SetRightMargin(0.1);
   c->SetLeftMargin(0.1);
   TGraphErrors *g = new TGraphErrors();
   TGraphAsymmErrors *g2 = new TGraphAsymmErrors();
   TGraphErrors *gCMS = new TGraphErrors();
   TGraphAsymmErrors *gCMS2 = new TGraphAsymmErrors();
   TGraphErrors *gLeg = new TGraphErrors();
   TGraphAsymmErrors *g2Leg = new TGraphAsymmErrors();

   // 1D fit
   g->SetPoint(0, mt1D, 10);
   g->SetPointError(0, mt1D_stat, 0);
   g2->SetPoint(0, mt1D, 10);
   g2->SetPointError(0, mt1D_totDN, mt1D_totUP, 0, 0);

   // 2D fit
   g->SetPoint(1, mt2D, 8);
   g->SetPointError(1, mt2D_stat, 0);
   g2->SetPoint(1, mt2D, 8);
   g2->SetPointError(1, mt2D_totDN, mt2D_totUP, 0, 0);

   // hyb fit
   g->SetPoint(2, mthyb, 6);
   g->SetPointError(2, mthyb_stat, 0);
   g2->SetPoint(2, mthyb, 6);
   g2->SetPointError(2, mthyb_totDN, mthyb_totUP, 0, 0);

   // MAOS fit
   g->SetPoint(3, mtMAOS, 4);
   g->SetPointError(3, mtMAOS_stat, 0);
   g2->SetPoint(3, mtMAOS, 4);
   g2->SetPointError(3, mtMAOS_totDN, mtMAOS_totUP, 0, 0);

   // CMS combination
   gCMS->SetPoint(0, mtCMS, 2);
   gCMS->SetPointError(0, mtCMS_stat, 0);
   gCMS2->SetPoint(0, mtCMS, 2);
   gCMS2->SetPointError(0, mtCMS_totDN, mtCMS_totUP, 0, 0);

   // legend
   gLeg->SetPoint(4, 166, 12);
   gLeg->SetPointError(4, 1.5, 0);
   g2Leg->SetPoint(4, 166, 12);
   g2Leg->SetPointError(4, 3, 3, 0, 0);


   // draw plot
   g->SetMarkerStyle(20);
   g->SetLineWidth(3);
   g->SetMarkerSize(1.3);
   g->SetMaximum(14);
   g->SetMinimum(0);
   g->GetXaxis()->SetTitle("M_{t} [GeV]");
   g->GetXaxis()->SetLimits(160, 185);
   g->GetYaxis()->SetLabelSize(0);
   g->GetYaxis()->SetTickSize(0);

   g->Draw("AEP");
   g2->Draw("E");

   gCMS->SetMarkerStyle(20);
   gCMS->SetMarkerColor(2);
   gCMS->SetLineColor(2);
   gCMS->SetLineWidth(3);
   gCMS->SetMarkerSize(1.3);
   gCMS2->SetLineColor(2);
   gCMS->Draw("EP");
   gCMS2->Draw("E");

   gLeg->SetMarkerStyle(20);
   gLeg->SetMarkerColor(12);
   gLeg->SetLineColor(12);
   gLeg->SetLineWidth(3);
   gLeg->SetMarkerSize(1.3);
   g2Leg->SetLineColor(12);
   //gLeg->Draw("EP");
   //g2Leg->Draw("E");

   TBox *band = new TBox(mtCMS-mtCMS_totDN, 0, mtCMS+mtCMS_totUP, 14);
   TBox *border = new TBox(mtCMS-mtCMS_totDN, 0, mtCMS+mtCMS_totUP, 14);
   band->SetFillColor(2);
   band->SetFillStyle(3004);
   band->SetLineColor(2);
   band->SetLineWidth(3);
   border->SetLineColor(2);
   border->SetLineColorAlpha(2, 0.5);
   border->SetLineWidth(1);
   border->SetFillStyle(0);
   band->Draw();
   border->Draw("same");

   // redraw tgraph
   g->Draw("EP");
   g2->Draw("E");


   // write labels
   TLatex latex;
   latex.SetTextSize(0.035);
   latex.SetTextFont(42);

   latex.DrawLatex(161, 10, "1D fit");
   latex.DrawLatex(161, 8, "2D fit");
   latex.DrawLatex(161, 6, "Hybrid fit");
   latex.DrawLatex(161, 4, "MAOS fit");
   latex.SetTextColor(2);
   latex.DrawLatex(161, 2, "CMS combination");

   latex.SetTextSize(0.025);
   latex.DrawLatex(161.25, 1.5, "PRD 93, 2016, 072004");


   latex.SetTextColor(1);
   latex.SetTextSize(0.03);

   ostringstream cmt1D, cmt2D, cmthyb, cmtMAOS, cmtCMS;
   cmt1D << mt1D << " #pm " << mt1D_stat << std::fixed << setprecision(2) << " ^{#plus " << mt1D_systUP << "}_{#minus " << mt1D_systDN << "}  GeV"; 
   cmt2D << mt2D << " #pm " << mt2D_stat << std::fixed << setprecision(2) << " ^{#plus " << mt2D_systUP << "}_{#minus " << mt2D_systDN << "}  GeV"; 
   cmthyb << mthyb << " #pm " << mthyb_stat << std::fixed << setprecision(2) << " ^{#plus " << mthyb_systUP << "}_{#minus " << mthyb_systDN << "}  GeV"; 
   cmtMAOS << mtMAOS << " #pm " << mtMAOS_stat << std::fixed << setprecision(2) << " ^{#plus " << mtMAOS_systUP << "}_{#minus " << mtMAOS_systDN << "}  GeV"; 
   cmtCMS << mtCMS << " #pm " << mtCMS_stat << std::fixed << setprecision(2) << " ^{#plus " << mtCMS_systUP << "}_{#minus " << mtCMS_systDN << "}  GeV"; 

   latex.DrawLatex(175, 10, cmt1D.str().c_str());
   latex.DrawLatex(175, 8, cmt2D.str().c_str());
   latex.DrawLatex(175, 6, cmthyb.str().c_str());
   latex.DrawLatex(175, 4, cmtMAOS.str().c_str());
   latex.SetTextColor(2);
   latex.DrawLatex(175, 2, cmtCMS.str().c_str());

   latex.SetTextColor(12);
   //latex.SetTextSize(0.025);
   latex.DrawLatex(176, 12, "(value #pm stat #pm syst)");

   latex.SetTextColor(12);
   //latex.DrawLatex(162.2, 11.5, "total");
   //latex.DrawLatex(164.2, 11.5, "stat");

   int iPeriod = 2;
   int iPos = 11;
   lumi_sqrtS = "8 TeV";
   writeExtraText = false;
   //extraText = "Preliminary";

   c->SetTopMargin(0.06);
   CMS_lumi( c, iPeriod, iPos );
   c->Update();
   c->RedrawAxis();
   c->GetFrame()->Draw();

   c->Print("pdfplots/mtop_results.pdf");

   //delete c;

   return;
}
