#include "TFile.h"
#include "TCanvas.h"
#include "TFrame.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TList.h"
#include "TObject.h"
#include "TH1.h"
#include "TGraphErrors.h"
#include <map>

#include "tdrStyle.C"
#include "CMS_lumi.C"

void plotmod(){

   setTDRStyle();
   int iPeriod = 0;
   int iPos = 11;
   lumi_sqrtS = "8 TeV";


   // ***************
   // * stack plots *
   // ***************

   TFile *f = new TFile("rootfiles/plotsDataMC.root");

   // mbl
   TCanvas *c = (TCanvas*)f->Get("cmbl_gpttbar172");
   TPad *p = (TPad*)c->FindObject("pad1");
   p->cd();

   TLegend *l = (TLegend*)c->FindObject("TPave");
   p->GetListOfPrimitives()->Remove(l);
   TLegend *ln = new TLegend(0.634, 0.481, 0.873, 0.871);
   TIter next(l->GetListOfPrimitives());
   TObject *obj = 0;
   while ((obj = next())){
      TLegendEntry *ent = (TLegendEntry*)obj;
      ln->AddEntry( ent->GetObject(), ent->GetLabel(), ent->GetOption() );
   }
   ln->SetFillStyle(0);
   ln->SetBorderSize(0);
   ln->Draw();

   CMS_lumi( p, iPeriod, iPos );
   p->Update();
   p->RedrawAxis();
   p->GetFrame()->Draw();

   TH1* hratio = (TH1*)c->FindObject("hratio");
   hratio->GetXaxis()->SetTitle("M_{bl} [GeV]");

   c->Draw();
   c->Print("pdfplots/mbl_stack.pdf");

   delete ln;

   // mt2 221
   c = (TCanvas*)f->Get("cmt2_221_gpttbar172");
   p = (TPad*)c->FindObject("pad1");
   p->cd();

   l = (TLegend*)c->FindObject("TPave");
   p->GetListOfPrimitives()->Remove(l);
   ln = new TLegend(0.634, 0.481, 0.873, 0.871);
   next = (TIter)l->GetListOfPrimitives();
   while ((obj = next())){
      TLegendEntry *ent = (TLegendEntry*)obj;
      ln->AddEntry( ent->GetObject(), ent->GetLabel(), ent->GetOption() );
   }
   ln->SetFillStyle(0);
   ln->SetBorderSize(0);
   ln->Draw();

   CMS_lumi( p, iPeriod, iPos );
   p->Update();
   p->RedrawAxis();
   p->GetFrame()->Draw();

   hratio = (TH1*)c->FindObject("hratio");
   hratio->GetXaxis()->SetTitle("M_{T2}^{bb} [GeV]");

   c->Draw();
   c->Print("pdfplots/mt2_stack.pdf");

   // maos 210
   c = (TCanvas*)f->Get("cmaos210_gpttbar172");
   p = (TPad*)c->FindObject("pad1");
   p->cd();

   l = (TLegend*)c->FindObject("TPave");
   p->GetListOfPrimitives()->Remove(l);
   ln = new TLegend(0.634, 0.481, 0.873, 0.871);
   next = (TIter)l->GetListOfPrimitives();
   while ((obj = next())){
      TLegendEntry *ent = (TLegendEntry*)obj;
      ln->AddEntry( ent->GetObject(), ent->GetLabel(), ent->GetOption() );
   }
   ln->SetFillStyle(0);
   ln->SetBorderSize(0);
   ln->Draw();

   CMS_lumi( p, iPeriod, iPos );
   p->Update();
   p->RedrawAxis();
   p->GetFrame()->Draw();

   hratio = (TH1*)c->FindObject("hratio");
   hratio->GetXaxis()->SetTitle("M_{bl#nu} [GeV]");

   c->Draw();
   c->Print("pdfplots/maos_stack.pdf");

   f->Close();

   // **************************
   // * best fit distributions *
   // **************************

   // 2D fit: mbl
   f = new TFile("rootfiles/plotsFitResults_300_2d.root");
   c = (TCanvas*)f->Get("c_mbl_gp");
   p = (TPad*)c->FindObject("pad1");
   p->cd();

   CMS_lumi( p, iPeriod, iPos );
   p->Update();
   p->RedrawAxis();
   p->GetFrame()->Draw();

   hratio = (TH1*)c->FindObject("hratio");
   hratio->GetXaxis()->SetTitle("M_{bl} [GeV]");

   c->Draw();
   c->Print("pdfplots/plotresults_2dfit_mbl.pdf");

   // 2D fit: mt2
   c = (TCanvas*)f->Get("c_mt2_221_gp");
   p = (TPad*)c->FindObject("pad1");
   p->cd();

   CMS_lumi( p, iPeriod, iPos );
   p->Update();
   p->RedrawAxis();
   p->GetFrame()->Draw();

   hratio = (TH1*)c->FindObject("hratio");
   hratio->GetXaxis()->SetTitle("M_{T2}^{bb} [GeV]");

   c->Draw();
   c->Print("pdfplots/plotresults_2dfit_mt2.pdf");


   // 1D fit: mbl
   f = new TFile("rootfiles/plotsFitResults_300_1d.root");
   c = (TCanvas*)f->Get("c_mbl_gp");
   p = (TPad*)c->FindObject("pad1");
   p->cd();

   CMS_lumi( p, iPeriod, iPos );
   p->Update();
   p->RedrawAxis();
   p->GetFrame()->Draw();

   hratio = (TH1*)c->FindObject("hratio");
   hratio->GetXaxis()->SetTitle("M_{bl} [GeV]");

   c->Draw();
   c->Print("pdfplots/plotresults_1dfit_mbl.pdf");

   // 1D fit: mt2
   c = (TCanvas*)f->Get("c_mt2_221_gp");
   p = (TPad*)c->FindObject("pad1");
   p->cd();

   CMS_lumi( p, iPeriod, iPos );
   p->Update();
   p->RedrawAxis();
   p->GetFrame()->Draw();

   hratio = (TH1*)c->FindObject("hratio");
   hratio->GetXaxis()->SetTitle("M_{T2}^{bb} [GeV]");

   c->Draw();
   c->Print("pdfplots/plotresults_1dfit_mt2.pdf");

   // MAOS fit: maos
   f = new TFile("rootfiles/plotsFitResults_300_maos.root");
   c = (TCanvas*)f->Get("c_maos210_gp");
   p = (TPad*)c->FindObject("pad1");
   p->cd();

   CMS_lumi( p, iPeriod, iPos );
   p->Update();
   p->RedrawAxis();
   p->GetFrame()->Draw();

   hratio = (TH1*)c->FindObject("hratio");
   hratio->GetXaxis()->SetTitle("M_{bl#nu} [GeV]");

   c->Draw();
   c->Print("pdfplots/plotresults_maosfit_maos.pdf");

   // MAOS fit: mt2
   c = (TCanvas*)f->Get("c_mt2_221_gp");
   p = (TPad*)c->FindObject("pad1");
   p->cd();

   CMS_lumi( p, iPeriod, iPos );
   p->Update();
   p->RedrawAxis();
   p->GetFrame()->Draw();

   hratio = (TH1*)c->FindObject("hratio");
   hratio->GetXaxis()->SetTitle("M_{T2}^{bb} [GeV]");

   c->Draw();
   c->Print("pdfplots/plotresults_maosfit_mt2.pdf");

   return;
}
