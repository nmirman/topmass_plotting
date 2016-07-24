#include "TH2.h"
#include "TFile.h"
#include "TTree.h"
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
#include "TLine.h"
#include "TMarker.h"

#include "tdrStyle.C"
#include "CMS_lumi.C"

#include <iostream>

void gp_schematic(){

   setTDRStyle();

   double phi = -45;
   double sigma_1 = 0.2;
   double sigma_2 = 0.4;
   double rho = 0.6;

   double gmean = 0.32;


   TF1 *fg = new TF1("fg", "gaus(0)", -1, 1);
   fg->SetParameter(0, 0.2);
   fg->SetParameter(1, rho*gmean);
   //fg->SetParameter(2, 4*(1-rho*rho)*sigma_1);
   fg->SetParameter(2, sqrt((1-rho*rho)*0.5*(sigma_1*sigma_1+sigma_2*sigma_2)));
   fg->GetXaxis()->SetTitle("f(#bf{u}_{test})");
   fg->GetYaxis()->SetTitle("f(#bf{u}_{train})");
   fg->GetXaxis()->CenterTitle();
   fg->GetYaxis()->CenterTitle();

   TEllipse *el = new TEllipse(0, 0, sigma_1, sigma_2, 0, 360, phi);
   TEllipse *el2 = new TEllipse(0, 0, 2*sigma_1, 2*sigma_2, 0, 360, phi);
   
   //gStyle->SetPadRightMargin(0.16);
   //gStyle->SetPadTopMargin(0.08);

   TCanvas *c = new TCanvas("c","c",800,800);

   fg->GetXaxis()->SetNdivisions(2);
   fg->GetYaxis()->SetNdivisions(2);
   fg->SetMinimum(-1);
   fg->SetMaximum(1);
   fg->SetLineColor(4);
   fg->SetLineStyle(7);
   fg->SetLineWidth(5);
   fg->Draw();

   el->SetFillStyle(0);
   el->SetLineColor(2);
   el->SetLineWidth(2);
   el->Draw();
   el2->SetFillStyle(0);
   el2->SetLineColor(2);
   el2->SetLineWidth(2);
   el2->Draw();

   c->Update();
   c->RedrawAxis();
   c->GetFrame()->Draw();

   TLine *a1 = new TLine(0, 1, 0, -1);
   TLine *a2 = new TLine(1, 0, -1, 0);

   a1->SetLineWidth(0.5);
   a2->SetLineWidth(0.5);
   a1->Draw();
   a2->Draw();

   TLine *l1 = new TLine(rho*gmean, 0, rho*gmean, 1);
   l1->SetLineColor(3);
   l1->SetLineWidth(2);
   l1->Draw();

   TLine *l2 = new TLine(-1, gmean, 1, gmean);
   l2->SetLineColor(4);
   l2->SetLineWidth(2);
   l2->Draw();

   TMarker *mx = new TMarker(rho*gmean, 0, 20);
   mx->SetMarkerColor(3);
   mx->SetMarkerStyle(20);
   mx->SetMarkerSize(2);
   TMarker *my = new TMarker(0, gmean, 20);
   my->SetMarkerColor(4);
   my->SetMarkerStyle(21);
   my->SetMarkerSize(2);


   mx->Draw();
   my->Draw();

   c->Print("pdfplots/gp_schematic.pdf");

   delete c;


   return;
}
