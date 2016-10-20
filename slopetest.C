
/*
 * Usage instructions:
 *
 * .x slopetest.C++("VAR",MODE),
 * where VAR=mbl,mt2_221,maos210 and MODE=0,1
 *
 */


#include "TFile.h"
#include "TGraph.h"
#include "TH1.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TDirectory.h"
#include "TKey.h"
#include "TAxis.h"
#include "TGAxis.h"
#include "TMath.h"
#include "TLegend.h"
#include "TROOT.h"
#include "TLatex.h"
#include "TFrame.h"
#include "TAxis.h"

#include "tdrStyle.C"
#include "CMS_lumi.C"

#include <stdlib.h>
#include <iostream>

using namespace std;

void slopetest(string distarg="", int mode=0){
   
   //gROOT->LoadMacro("tdrstyle.C");
   setTDRStyle();
   gStyle->SetPadRightMargin(0.16);
   gStyle->SetPadTopMargin(0.07);
   if( mode == 0 ) gStyle->SetPadTickY(0);

   string dist = distarg;
   if( distarg.empty() ) dist = "mbl";
   string dim = "mt";
   if( mode==1 ) dim = "jes";

   double p1=0, p2=0, p3=0;
   double dx = 0;
   double eps = 0.2;
   int nument = 1;
   if( dim == "mt" ){
      p1 = 172.0; p2 = 172.5, p3 = 173.0;
   }
   if( dim == "jes" ){
      p1 = 0.999; p2 = 1.000, p3 = 1.001;
   }
   if( dist == "mbl" ){
      //dx = 2.8;
      //nument = 109745;
      cout << "Number of entries = " << nument << endl;
   }
   if( dist == "mt2_221" ){
      //dx = 1.9;
      //nument = 15714;
      cout << "Number of entries = " << nument << endl;
   }
   if( dist == "maos210" ){
      //nument = 333120;
      cout << "Number of entries = " << nument << endl;
   }

   string file = "rootfiles/plotsTemplates.root";
   //if( dist == "maos210" ) file = "rootfiles/plotsTemplatesMAOS.root";
   TFile *f = new TFile(file.c_str());
   TDirectory *d = (TDirectory*)f->Get((dim+"shape_"+dist+"_gp").c_str());

   TCanvas *c = (TCanvas*)f->Get(("c_"+dist+"_gp_signal_JSF1000").c_str());
   TH1 *h = (TH1*)(c->GetListOfPrimitives()->At(1));
   dx = h->GetBinWidth(1);

   delete c;

   TGraph *gslope = new TGraph();
   TGraph *gint = new TGraph();

   double sig = 0;
   double d2sig = 0;

   TIter nextkey(d->GetListOfKeys());
   TKey *key;
   while( (key = (TKey*)nextkey()) ){

      string name = key->GetName();
      string classname = key->GetClassName();

      TCanvas *c = (TCanvas*)d->Get(name.c_str());
      TGraph *g = (TGraph*)(c->GetListOfPrimitives()->At(1));

      double y1=0, y2=0;
      double ycent = 0;
      for(int i=0; i < g->GetN(); i++){
         double x=0, y=0;
         g->GetPoint(i, x, y);
         if( x == p1 ) y1 = y;
         if( x == p2 ) ycent = y;
         if( x == p3 ) y2 = y;
      }
      double slope = y2-y1;

      string sbin = name;
      string ntemp = "c"+dist+"_gp";
      sbin.erase(sbin.begin(), sbin.begin()+ntemp.length());
      if( dist == "mt2_221" ) sbin.erase(sbin.end(), sbin.end()+1);
      double dbin = atof(sbin.c_str());

      double integrand = slope*slope/ycent;

      gint->SetPoint(gint->GetN(), dbin, integrand);
      gslope->SetPoint(gslope->GetN(), dbin, slope);

      sig += slope*slope*eps*eps*-0.5*dx/ycent;
      d2sig += integrand*dx;

   }

   cout << "stat error = " << sqrt(1.0/(nument*d2sig)) << endl;

   // get mt dependence plot
   string canvas = "c_"+dist+"_gp_signal_JSF1000";
   if( mode == 1 ) canvas = "c_"+dist+"_gp_signal_jfact";
   TCanvas *c2 = (TCanvas*)f->Get(canvas.c_str());
   TH1D *h166 = (TH1D*)(c2->GetListOfPrimitives()->At(0));
   TH1D *h172 = (TH1D*)(c2->GetListOfPrimitives()->At(1));
   TH1D *h178 = (TH1D*)(c2->GetListOfPrimitives()->At(2));
   TF1 *f166 = (TF1*)(c2->GetListOfPrimitives()->At(3));
   TF1 *f172 = (TF1*)(c2->GetListOfPrimitives()->At(4));
   TF1 *f178 = (TF1*)(c2->GetListOfPrimitives()->At(5));
   
   int ydim = 800;
   if( mode == 1 ) ydim = 600;
   TCanvas *cf = new TCanvas("cf","cf",800,ydim);

   if( mode == 0 ){
      cf->SetTopMargin(0.1*(2.0/3));
      cf->SetBottomMargin(0.12);
      //cf->SetRightMargin(0.1);


      //f166->GetXaxis()->SetTitleSize(0.047);
      //f166->GetYaxis()->SetLabelSize(0.07);
      //f166->GetYaxis()->SetTitleSize(0.08);
      //f166->GetYaxis()->SetTitleOffset(0.95);
      f166->GetXaxis()->SetLabelFont(42);
      f166->GetYaxis()->SetLabelFont(42);
      f166->GetXaxis()->SetTitleFont(42);
      f166->GetYaxis()->SetTitleFont(42);

      f166->GetXaxis()->SetTitleSize(0.14/3);
      f166->GetXaxis()->SetLabelSize(0.14/3);
      //f166->GetXaxis()->SetLabelSize(0.04);
      f166->GetXaxis()->SetLabelFont(42);
      if( dist == "mt2_221" or dist == "maos210" ){
         f166->GetXaxis()->SetNdivisions(505);
      }
   }
   if( mode == 1 ){
      f166->GetXaxis()->SetTitleOffset(0.95);
      f166->GetXaxis()->SetLabelOffset(0.015);
      f166->GetYaxis()->SetLabelOffset(0.01);
   }

   f166->SetLineWidth(2);
   f172->SetLineWidth(2);
   f178->SetLineWidth(2);
   f166->SetLineColor(kBlack);
   f172->SetLineColor(kGray+2);
   f178->SetLineColor(kGray);

   // normalize sensitivity by number of entries
   for( int i=0; i < gint->GetN(); i++ ) gint->GetY()[i] *= nument;

   TGaxis::SetMaxDigits(3);
   string xtitle = "M_{bl} [GeV]";
   if( dist == "mt2_221" ) xtitle = "M_{T2}^{bb} [GeV]";
   if( dist == "maos210" ) xtitle = "M_{bl#nu} [GeV]";
   f166->GetXaxis()->SetTitle(xtitle.c_str());
   f166->GetYaxis()->SetTitle("arb. units");

   if( mode == 0 ){
      f166->GetXaxis()->SetLabelOffset(0.02);
      f166->GetYaxis()->SetLabelOffset(0.01);
      f166->GetXaxis()->SetTitleOffset(1.18);
      //f166->GetXaxis()->SetLabelOffset(0.01);
      //f166->GetYaxis()->SetLabelOffset(0.01);
   }

   double maxscale = 1.0;
   if( dist != "maos210" ) maxscale = 1.2;
   f166->SetMinimum(0);
   if( mode == 0 ){
      f166->SetMaximum(1.75*f166->GetMaximum());
   }
   if( mode == 1 ){
      f166->SetMaximum(1.25*f166->GetMaximum());
   }
   f166->Draw();
   f172->Draw("same");
   f178->Draw("same");

   h166->SetMarkerColor(kBlack);
   h166->SetLineColor(kBlack);
   h172->SetMarkerColor(kGray+2);
   h172->SetLineColor(kGray+2);
   h178->SetMarkerColor(kGray);
   h178->SetLineColor(kGray);

   h166->Draw("same"); 
   h172->Draw("same");
   h178->Draw("same");

   //pad->cd();
   cf->Update();

   double scalemod = 1.3;
   if( dist == "maos210" ) scalemod = 1.3;

   double rightmax = scalemod*1.1*TMath::MaxElement(gint->GetN(), gint->GetY());
   double scale = gPad->GetUymax()/rightmax;
   for(int i=0; i < gint->GetN(); i++) gint->GetY()[i] *= scale;
   gint->SetLineColor(2);
   gint->SetLineWidth(2);
   if( mode == 0 ) gint->Draw("C");

   // draw axis on the right side
   TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
         gPad->GetUxmax(), gPad->GetUymax(),0,rightmax,510,"+L");

   // formatting
   axis->SetLineColor(2);
   axis->SetLineWidth(2);
   axis->SetLabelColor(2);
   axis->SetTitleColor(2);
   axis->SetTitleFont(42);
   axis->SetTitleSize(0.06);
   axis->SetTitleOffset(1);
   axis->SetLabelFont(42);
   //axis->SetLabelOffset(0.007);
   //axis->SetLabelOffset(0.01);
   axis->SetLabelSize(0.05);

   axis->SetTitle("[GeV^{-3}]");
   if( mode == 0 ) axis->Draw();

   double ldim [] = {0.237,0.333,0.567,0.510};
   if( dist == "maos210" ){
      ldim[0] = 0.380;
      ldim[1] = 0.600;
      ldim[2] = 0.799;
      ldim[3] = 0.768;

   } else if( dist == "mt2_221" ){
      ldim[0] = 0.174;
      ldim[1] = 0.617;
      ldim[2] = 0.594;
      ldim[3] = 0.785;
   } else {
      ldim[0] = 0.204;
      ldim[1] = 0.612;
      ldim[2] = 0.623;
      ldim[3] = 0.779;
   }
   if( mode == 1 ){
      ldim[0] = 0.556;
      ldim[1] = 0.706;
      ldim[2] = 0.936;
      ldim[3] = 0.906;
   }

   TLegend* leg = new TLegend(ldim[0],ldim[1],ldim[2],ldim[3]);
   if( mode == 0 ){
      leg->AddEntry( h166, "M_{t}^{MC} = 166.5 GeV" );
      leg->AddEntry( h172, "M_{t}^{MC} = 172.5 GeV" );
      leg->AddEntry( h178, "M_{t}^{MC} = 178.5 GeV" );
      leg->AddEntry( gint, "local shape sensitivity", "l" );
   }
   if( mode == 1 ){
      leg->AddEntry( h166, "JSF = 0.97" );
      leg->AddEntry( h172, "JSF = 1.00" );
      leg->AddEntry( h178, "JSF = 1.03" );
   }

   leg->SetBorderSize(0);
   leg->SetFillStyle(0);
   leg->Draw("same");

   // CMS and lumi
   int iPeriod = 0;
   int iPos = 11;
   writeExtraText = true;
   //extraText = "Simulation Preliminary";
   extraText = "Simulation";
   lumi_sqrtS = "8 TeV";
   CMS_lumi( cf, iPeriod, iPos );   


   /*
   float l = gPad->GetLeftMargin();
   float t = gPad->GetTopMargin();
   float r = gPad->GetRightMargin();
   float r2 = gPad->GetRightMargin()+0.02;
   float b = gPad->GetBottomMargin();

   TLatex latex;
   latex.SetNDC();
   latex.SetTextAngle(0);
   latex.SetTextColor(kBlack);   
   latex.SetTextFont(42);
   latex.SetTextAlign(31); 
   latex.SetTextSize(lumiTextSize*t);    
   latex.DrawLatex(1-r2,1-t+lumiTextOffset*t,"8 TeV");
   */


   cf->Update();
   //TGaxis* axis2 = (TGaxis*)cf->FindObject("xaxis");
   //axis2->SetNdivisions(505);
   //cf->RedrawAxis();
   if( mode == 0 and (dist == "mt2_221" or dist == "maos210") )
      h178->GetXaxis()->SetNdivisions(505);
   h178->Draw("sameaxis");
   //cf->GetFrame()->Draw();

   string out = "pdfplots/sensitivity_mt_"+dist+".pdf";
   if( mode == 1 ) out = "pdfplots/sensitivity_jsf_"+dist+".pdf";
   cf->Print(out.c_str());


   return;
}
