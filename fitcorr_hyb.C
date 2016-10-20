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
#include "TLatex.h"

#include "tdrStyle.C"
#include "CMS_lumi.C"

#include <iostream>

void fitcorr_hyb(){

   setTDRStyle();

   TFile *f = new TFile("rootfiles/fitresults_2D_data.root");
   TTree *t = (TTree*)f->Get("FitResults");

   double mt_temp=0, jsf_temp=0, mcmass=0, mtfix_temp=0;
   t->SetBranchAddress("mt", &mt_temp);
   t->SetBranchAddress("mt_fix", &mtfix_temp);
   t->SetBranchAddress("jesfactor", &jsf_temp);
   t->SetBranchAddress("mcmass", &mcmass);

   //TH2D *h2D = new TH2D("h2D",";M_{t} [GeV];JSF", 10, 171.9, 172.9, 10, 0.9992, 1.001 );
   TH2D *h2D = new TH2D("h2D",";M_{t} [GeV];JSF", 20, 170, 173, 20, 0.99, 1.04 );
   TGraph *g = new TGraph();
   for( int i=0; i < t->GetEntries(); i++ ){
      t->GetEntry(i);
      //if( mcmass != 172.5 ) continue;

      double mt = 0.2*mt_temp+0.8*mtfix_temp;
      double jsf = 0.2*jsf_temp + 0.8*1.0;

      h2D->Fill(mt, jsf);
      g->SetPoint(g->GetN(), mt, jsf);

   }

   // uncertainty contour
   double mean_mt = g->GetMean(1);
   double mean_jsf = g->GetMean(2);
   double sigma_mt = g->GetRMS(1);
   double sigma_jsf = g->GetRMS(2);
   double rho = g->GetCorrelationFactor();
   std::cout << "Mean Mt = " << mean_mt << " +- " << sigma_mt << std::endl;
   std::cout << "Mean JSF = " << mean_jsf << " +- " << sigma_jsf << std::endl;
   std::cout << "Correlation = " << rho << std::endl;

   TMatrixDSym m(2);
   m(0,0) = sigma_mt*sigma_mt;
   m(1,1) = sigma_jsf*sigma_jsf;
   m(0,1) = rho*sigma_mt*sigma_jsf;
   m(1,0) = rho*sigma_mt*sigma_jsf;
   TMatrixDSymEigen eigen(m);
   TVectorD eigenval = eigen.GetEigenValues();
   std::cout << eigenval[0] << " " << eigenval[1] << endl;

   // convert to ellipse tilt and radius
   double phi = (180.0/TMath::Pi())*0.5*TMath::ATan( (2*rho*sigma_mt*sigma_jsf)/(sigma_mt*sigma_mt-sigma_jsf*sigma_jsf) );
   std::cout << "phi = " << phi << std::endl;

   TEllipse *el = new TEllipse(mean_mt, mean_jsf, sqrt(eigenval[0]), sqrt(eigenval[1]), 0, 360, phi);
   TEllipse *el2 = new TEllipse(mean_mt, mean_jsf, 2*sqrt(eigenval[0]), 2*sqrt(eigenval[1]), 0, 360, phi);
   
   /*
   TF2* fell = new TF2("fell","pow((x-[1])*cos([0])+(y-[2])*sin([0]),2)/[3] + pow((x-[1])*sin([0])-(y-[2])*cos([0]),2)/[4]",171,174,0.985,1.015);
   fell->SetParameter(0,phi);
   fell->SetParameter(1,mean_mt);
   fell->SetParameter(2,mean_jsf);
   fell->SetParameter(3,eigenval[0]);
   fell->SetParameter(4,eigenval[1]);

   double cont[1] = {1};
   fell->SetContour(1, cont);
   */
   
   const Int_t Number = 2;
   Double_t Red[Number]    = { 0.90, 0.10};
   Double_t Green[Number]  = { 0.90, 0.10};
   Double_t Blue[Number]   = { 0.90, 0.10};
   Double_t Stops [Number] = {0, 1};
   Double_t Length [Number] = {0, 1};
   Int_t nb=50;
   TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nb);

   gStyle->SetPadRightMargin(0.16);
   gStyle->SetPadTopMargin(0.08);

   TCanvas *c = new TCanvas("c","c",800,600);
   //h2D->GetXaxis()->SetNdivisions(1005);
   h2D->Draw("colzC");
   el->SetFillStyle(0);
   el->SetLineColor(2);
   el->SetLineWidth(3);
   el->Draw();
   el2->SetFillStyle(0);
   el2->SetLineColor(2);
   el2->SetLineWidth(3);
   el2->Draw();

   int iPeriod = 2;
   int iPos = 33;
   lumi_sqrtS = "8 TeV";
   writeExtraText = false;
   CMS_lumi( c, iPeriod, iPos );

   c->Update();
   c->RedrawAxis();
   c->GetFrame()->Draw();

   TLatex latex;
   latex.SetNDC();
   latex.SetTextSize(0.06);
   latex.SetTextFont(42);
   latex.DrawLatex(0.2, 0.84, "Hybrid fit");

   c->Print("pdfplots/fitcorr_hyb.pdf");

   //delete c;


   return;
}
