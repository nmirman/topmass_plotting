#include "TFile.h"
#include "TCanvas.h"
#include "TFrame.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TList.h"
#include "TObject.h"
#include "TH1.h"
#include "THStack.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TGAxis.h"
#include <map>

#include "tdrStyle.C"
#include "CMS_lumi.C"

void plotmod(){

   setTDRStyle();
   int iPeriod = 2;
   int iPos = 11;
   lumi_sqrtS = "8 TeV";
   writeExtraText = 1;
   //extraText = "Preliminary";
   extraText = "";

   TGaxis::SetMaxDigits(3);

   // ***************
   // * stack plots *
   // ***************

   TFile *f = new TFile("rootfiles/plotsDataMC.root");
   TFile *fsyst = new TFile("rootfiles/plotsysts.root");

   // mbl
   TCanvas *c = (TCanvas*)f->Get("cmbl_gpttbar172");
   TPad *p = (TPad*)c->FindObject("pad1");
   p->cd();

   TGraphAsymmErrors* g = (TGraphAsymmErrors*)fsyst->Get("mbl_gpttbar172");

   TLegend *l = (TLegend*)c->FindObject("TPave");
   p->GetListOfPrimitives()->Remove(l);
   //TLegend *ln = new TLegend(0.634, 0.481, 0.873, 0.871);
   TLegend *ln = new TLegend(0.605,0.474,0.931,0.881);
   TIter next(l->GetListOfPrimitives());
   TObject *obj = 0;
   while ((obj = next())){
      TLegendEntry *ent = (TLegendEntry*)obj;
      string label = ent->GetLabel();
      if( label == "hadronic decays" ) label = "had. decays";
      ln->AddEntry( ent->GetObject(), label.c_str(), ent->GetOption() );
   }
   ln->SetFillStyle(0);
   ln->SetBorderSize(0);
   ln->Draw();

   THStack* h = (THStack*)c->FindObject("hsmbl_gpttbar172");
   h->SetMaximum(1.2*h->GetMaximum());
   h->GetXaxis()->SetLabelSize(0);

   p->SetBottomMargin(0.03);

   g->SetFillStyle(3001);
   g->SetFillColor(15);
   g->Draw("2");

   TH1D* hdata = (TH1D*)c->FindObject("data_cl");
   hdata->Draw("same");

   CMS_lumi( p, iPeriod, iPos );
   p->Update();
   p->RedrawAxis();
   p->GetFrame()->Draw();

   p = (TPad*)c->FindObject("pad2");
   p->cd();
   p->SetBottomMargin(0.36);

   TH1* hratio = (TH1*)c->FindObject("hratio");
   hratio->GetXaxis()->SetTitle("M_{bl} [GeV]");
   //hratio->GetXaxis()->SetLabelSize(0.12);
   hratio->GetXaxis()->SetLabelOffset(0.06);
   hratio->GetXaxis()->SetTitleOffset(1.18);

   TGraphAsymmErrors* gratio = new TGraphAsymmErrors();
   for(int i=0; i < g->GetN(); i++){
      double x=0, y=0;
      g->GetPoint(i,x,y);
      gratio->SetPoint(i, x, 1);
      gratio->SetPointError(i, g->GetErrorXlow(i), g->GetErrorXhigh(i), g->GetErrorYlow(i)/y, g->GetErrorYhigh(i)/y);
   }

   gratio->SetFillStyle(3001);
   gratio->SetFillColor(15);
   gratio->Draw("2");

   hratio->Draw("same");

   TLegend *lr = new TLegend(0.198, 0.774, 0.724, 0.935);
   lr->SetFillStyle(0);
   lr->SetBorderSize(0);
   lr->SetLineStyle(0);
   lr->AddEntry( gratio, "uncertainties (stat.+syst.)", "f" );
   lr->Draw();

   c->Draw();
   c->Print("pdfplots/mbl_stack.pdf");

   // mt2 221
   c = (TCanvas*)f->Get("cmt2_221_gpttbar172");
   p = (TPad*)c->FindObject("pad1");
   p->cd();

   g = (TGraphAsymmErrors*)fsyst->Get("mt2_221_gpttbar172");

   l = (TLegend*)c->FindObject("TPave");
   p->GetListOfPrimitives()->Remove(l);
   //ln = new TLegend(0.634, 0.481, 0.873, 0.871);
   ln = new TLegend(0.576,0.474,0.902,0.881);
   next = (TIter)l->GetListOfPrimitives();
   while ((obj = next())){
      TLegendEntry *ent = (TLegendEntry*)obj;
      string label = ent->GetLabel();
      if( label == "hadronic decays" ) label = "had. decays";
      ln->AddEntry( ent->GetObject(), label.c_str(), ent->GetOption() );
   }
   ln->SetFillStyle(0);
   ln->SetBorderSize(0);
   ln->Draw();

   h = (THStack*)c->FindObject("hsmt2_221_gpttbar172");
   h->SetMaximum(1.2*h->GetMaximum());
   h->GetXaxis()->SetLabelSize(0);

   p->SetBottomMargin(0.03);

   g->SetFillStyle(3001);
   g->SetFillColor(15);
   g->Draw("2");

   hdata = (TH1D*)c->FindObject("data_cl");
   hdata->Draw("same");

   CMS_lumi( p, iPeriod, iPos );
   p->Update();
   p->RedrawAxis();
   p->GetFrame()->Draw();

   p = (TPad*)c->FindObject("pad2");
   p->cd();
   p->SetBottomMargin(0.36);

   hratio = (TH1*)c->FindObject("hratio");
   hratio->GetXaxis()->SetTitle("M_{T2}^{bb} [GeV]");
   //hratio->GetXaxis()->SetLabelSize(0.12);
   hratio->GetXaxis()->SetLabelOffset(0.06);
   hratio->GetXaxis()->SetTitleOffset(1.18);
   hratio->GetXaxis()->SetNdivisions(505);

   gratio = new TGraphAsymmErrors();
   for(int i=0; i < g->GetN(); i++){
      double x=0, y=0;
      g->GetPoint(i,x,y);
      gratio->SetPoint(i, x, 1);
      gratio->SetPointError(i, g->GetErrorXlow(i), g->GetErrorXhigh(i), g->GetErrorYlow(i)/y, g->GetErrorYhigh(i)/y);
   }

   gratio->SetFillStyle(3001);
   gratio->SetFillColor(15);
   gratio->Draw("2");

   hratio->Draw("same");

   lr = new TLegend(0.198, 0.774, 0.724, 0.935);
   lr->SetFillStyle(0);
   lr->SetBorderSize(0);
   lr->SetLineStyle(0);
   lr->AddEntry( gratio, "uncertainties (stat.+syst.)", "f" );
   lr->Draw();

   c->Draw();
   c->Print("pdfplots/mt2_stack.pdf");

   // maos 210
   c = (TCanvas*)f->Get("cmaos210_gpttbar172");
   p = (TPad*)c->FindObject("pad1");
   p->cd();

   g = (TGraphAsymmErrors*)fsyst->Get("maos210_gpttbar172");

   l = (TLegend*)c->FindObject("TPave");
   p->GetListOfPrimitives()->Remove(l);
   //ln = new TLegend(0.634, 0.481, 0.873, 0.871);
   ln = new TLegend(0.591,0.474,0.917,0.881);
   next = (TIter)l->GetListOfPrimitives();
   while ((obj = next())){
      TLegendEntry *ent = (TLegendEntry*)obj;
      string label = ent->GetLabel();
      if( label == "hadronic decays" ) label = "had. decays";
      ln->AddEntry( ent->GetObject(), label.c_str(), ent->GetOption() );
   }
   ln->SetFillStyle(0);
   ln->SetBorderSize(0);
   ln->Draw();

   h = (THStack*)c->FindObject("hsmaos210_gpttbar172");
   h->SetMaximum(1.2*h->GetMaximum());
   h->GetXaxis()->SetLabelSize(0);

   p->SetBottomMargin(0.03);

   g->SetFillStyle(3001);
   g->SetFillColor(15);
   g->Draw("2");

   hdata = (TH1D*)c->FindObject("data_cl");
   hdata->Draw("same");

   CMS_lumi( p, iPeriod, iPos );
   p->Update();
   p->RedrawAxis();
   p->GetFrame()->Draw();

   p = (TPad*)c->FindObject("pad2");
   p->cd();
   p->SetBottomMargin(0.36);

   hratio = (TH1*)c->FindObject("hratio");
   hratio->GetXaxis()->SetTitle("M_{bl#nu} [GeV]");
   //hratio->GetXaxis()->SetLabelSize(0.12);
   hratio->GetXaxis()->SetLabelOffset(0.06);
   hratio->GetXaxis()->SetTitleOffset(1.18);
   hratio->GetXaxis()->SetNdivisions(505);

   gratio = new TGraphAsymmErrors();
   for(int i=0; i < g->GetN(); i++){
      double x=0, y=0;
      g->GetPoint(i,x,y);
      gratio->SetPoint(i, x, 1);
      gratio->SetPointError(i, g->GetErrorXlow(i), g->GetErrorXhigh(i), g->GetErrorYlow(i)/y, g->GetErrorYhigh(i)/y);
   }

   gratio->SetFillStyle(3001);
   gratio->SetFillColor(15);
   gratio->Draw("2");

   hratio->Draw("same");

   lr = new TLegend(0.198, 0.774, 0.724, 0.935);
   lr->SetFillStyle(0);
   lr->SetBorderSize(0);
   lr->SetLineStyle(0);
   lr->AddEntry( gratio, "uncertainties (stat.+syst.)", "f" );
   lr->Draw();

   c->Draw();
   c->Print("pdfplots/maos_stack.pdf");

   f->Close();

   // **************************
   // * best fit distributions *
   // **************************
   iPos = 33;
   TLatex latex;
   latex.SetNDC();
   latex.SetTextFont(42);
   latex.SetTextSize(0.08);

   // 2D fit: mbl
   f = new TFile("rootfiles/plotsFitResults_0_2d.root");
   c = (TCanvas*)f->Get("c_mbl_gp");
   p = (TPad*)c->FindObject("pad1");
   p->cd();

   TH1D* he = (TH1D*)c->FindObject("fitevts");
   he->SetMaximum( 1.2*he->GetMaximum() );
   he->GetYaxis()->SetTitle("events per 1.9 GeV");
   he->GetXaxis()->SetLabelSize(0);

   p->SetBottomMargin(0.03);

   CMS_lumi( p, iPeriod, iPos );
   p->Update();
   p->RedrawAxis();
   p->GetFrame()->Draw();

   latex.DrawLatex(0.2, 0.8, "M_{bl}");

   p = (TPad*)c->FindObject("pad2");
   p->cd();
   p->SetBottomMargin(0.36);

   hratio = (TH1*)c->FindObject("hratio");
   hratio->GetXaxis()->SetTitle("M_{bl} [GeV]");
   hratio->GetXaxis()->SetLabelSize(0.12);
   hratio->GetXaxis()->SetLabelOffset(0.06);
   hratio->GetXaxis()->SetTitleOffset(1.18);

   c->Draw();
   c->Print("pdfplots/plotresults_2dfit_mbl.pdf");

   // 2D fit: mt2
   c = (TCanvas*)f->Get("c_mt2_221_gp");
   p = (TPad*)c->FindObject("pad1");
   p->cd();

   he = (TH1D*)c->FindObject("fitevts");
   he->GetYaxis()->SetTitle("events per 1.3 GeV");
   he->GetXaxis()->SetLabelSize(0);

   p->SetBottomMargin(0.03);

   CMS_lumi( p, iPeriod, iPos );
   p->Update();
   p->RedrawAxis();
   p->GetFrame()->Draw();

   latex.DrawLatex(0.2, 0.8, "M_{T2}^{bb}");

   p = (TPad*)c->FindObject("pad2");
   p->cd();
   p->SetBottomMargin(0.36);

   hratio = (TH1*)c->FindObject("hratio");
   hratio->GetXaxis()->SetTitle("M_{T2}^{bb} [GeV]");
   hratio->GetXaxis()->SetLabelSize(0.12);
   hratio->GetXaxis()->SetLabelOffset(0.06);
   hratio->GetXaxis()->SetTitleOffset(1.18);

   c->Draw();
   c->Print("pdfplots/plotresults_2dfit_mt2.pdf");


   // 1D fit: mbl
   f = new TFile("rootfiles/plotsFitResults_0_1d.root");
   c = (TCanvas*)f->Get("c_mbl_gp");
   p = (TPad*)c->FindObject("pad1");
   p->cd();

   he = (TH1D*)c->FindObject("fitevts");
   he->SetMaximum( 1.2*he->GetMaximum() );
   he->GetYaxis()->SetTitle("events per 1.9 GeV");
   he->GetXaxis()->SetLabelSize(0);

   p->SetBottomMargin(0.03);

   CMS_lumi( p, iPeriod, iPos );
   p->Update();
   p->RedrawAxis();
   p->GetFrame()->Draw();

   latex.DrawLatex(0.2, 0.8, "M_{bl}");

   p = (TPad*)c->FindObject("pad2");
   p->cd();
   p->SetBottomMargin(0.36);

   hratio = (TH1*)c->FindObject("hratio");
   hratio->GetXaxis()->SetTitle("M_{bl} [GeV]");
   hratio->GetXaxis()->SetLabelSize(0.12);
   hratio->GetXaxis()->SetLabelOffset(0.06);
   hratio->GetXaxis()->SetTitleOffset(1.18);

   c->Draw();
   c->Print("pdfplots/plotresults_1dfit_mbl.pdf");

   // 1D fit: mt2
   c = (TCanvas*)f->Get("c_mt2_221_gp");
   p = (TPad*)c->FindObject("pad1");
   p->cd();

   he = (TH1D*)c->FindObject("fitevts");
   he->GetYaxis()->SetTitle("events per 1.3 GeV");
   he->GetXaxis()->SetLabelSize(0);

   p->SetBottomMargin(0.03);

   CMS_lumi( p, iPeriod, iPos );
   p->Update();
   p->RedrawAxis();
   p->GetFrame()->Draw();

   latex.DrawLatex(0.2, 0.8, "M_{T2}^{bb}");

   p = (TPad*)c->FindObject("pad2");
   p->cd();
   p->SetBottomMargin(0.36);

   hratio = (TH1*)c->FindObject("hratio");
   hratio->GetXaxis()->SetTitle("M_{T2}^{bb} [GeV]");
   hratio->GetXaxis()->SetLabelSize(0.12);
   hratio->GetXaxis()->SetLabelOffset(0.06);
   hratio->GetXaxis()->SetTitleOffset(1.18);

   c->Draw();
   c->Print("pdfplots/plotresults_1dfit_mt2.pdf");

   // MAOS fit: maos
   f = new TFile("rootfiles/plotsFitResults_0_maos.root");
   c = (TCanvas*)f->Get("c_maos210_gp");
   p = (TPad*)c->FindObject("pad1");
   p->cd();

   he = (TH1D*)c->FindObject("fitevts");
   he->GetYaxis()->SetTitle("events per 2.7 GeV");
   he->GetXaxis()->SetLabelSize(0);

   p->SetBottomMargin(0.03);

   CMS_lumi( p, iPeriod, iPos );
   p->Update();
   p->RedrawAxis();
   p->GetFrame()->Draw();

   latex.DrawLatex(0.2, 0.8, "M_{bl#nu}");

   p = (TPad*)c->FindObject("pad2");
   p->cd();
   p->SetBottomMargin(0.36);

   hratio = (TH1*)c->FindObject("hratio");
   hratio->GetXaxis()->SetTitle("M_{bl#nu} [GeV]");
   hratio->GetXaxis()->SetLabelSize(0.12);
   hratio->GetXaxis()->SetLabelOffset(0.06);
   hratio->GetXaxis()->SetTitleOffset(1.18);

   c->Draw();
   c->Print("pdfplots/plotresults_maosfit_maos.pdf");

   // MAOS fit: mt2
   c = (TCanvas*)f->Get("c_mt2_221_gp");
   p = (TPad*)c->FindObject("pad1");
   p->cd();

   he = (TH1D*)c->FindObject("fitevts");
   he->GetYaxis()->SetTitle("events per 1.3 GeV");
   he->GetXaxis()->SetLabelSize(0);

   p->SetBottomMargin(0.03);

   CMS_lumi( p, iPeriod, iPos );
   p->Update();
   p->RedrawAxis();
   p->GetFrame()->Draw();

   latex.DrawLatex(0.2, 0.8, "M_{T2}^{bb}");

   p = (TPad*)c->FindObject("pad2");
   p->cd();
   p->SetBottomMargin(0.36);

   hratio = (TH1*)c->FindObject("hratio");
   hratio->GetXaxis()->SetTitle("M_{T2}^{bb} [GeV]");
   hratio->GetXaxis()->SetLabelSize(0.12);
   hratio->GetXaxis()->SetLabelOffset(0.06);
   hratio->GetXaxis()->SetTitleOffset(1.18);

   c->Draw();
   c->Print("pdfplots/plotresults_maosfit_mt2.pdf");

   return;
}
