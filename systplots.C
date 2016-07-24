#include "TFile.h"
#include "TCanvas.h"
#include "TFrame.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TList.h"
#include "TObject.h"
#include "TH1.h"
#include "THStack.h"
#include "TGraphErrors.h"
#include "TGAxis.h"
#include <map>

#include "tdrStyle.C"
#include <iostream>

struct Systematic {

   string fCentral;
   string fUP;
   string fDN;

   string lCentral;
   string lUP;
   string lDN;

   Systematic( string fC="", string fU="", string fD="", string lC="", string lU="", string lD="" )
      : fCentral(fC), fUP(fU), fDN(fD), lCentral(lC), lUP(lU), lDN(lD) {
      }

};

void systplots(){

   setTDRStyle(); 

   vector<string> dists;
   dists.push_back("mbl");
   dists.push_back("mt2_221");
   dists.push_back("maos210");

   map<string, Systematic> systs;
   systs[ "JESTotal" ] = Systematic( "Central", "JESTotalUP", "JESTotalDN", "Central", "UP", "DN" );
   systs[ "BFRAGnu" ] = Systematic( "Central", "BFRAGnuUP", "BFRAGnuDN", "Central", "UP", "DN" );
   systs[ "BFRAGrbLEP" ] = Systematic( "Central", "BFRAGrbLEPUP", "Central", "Central", "UP", "" );
   systs[ "ElectronEnergyScale" ] = Systematic( "Central", "ElectronEnergyScaleUP", "ElectronEnergyScaleDN", "Central", "UP", "DN" );
   systs[ "ElectronId" ] = Systematic( "Central", "ElectronIdUP", "ElectronIdDN", "Central", "UP", "DN" );
   systs[ "JetEnergyResolution" ] = Systematic( "Central", "JetEnergyResolutionUP", "JetEnergyResolutionDN", "Central", "UP", "DN" );
   systs[ "METUnclustered" ] = Systematic( "Central", "METUnclusteredUP", "METUnclusteredDN", "Central", "UP", "DN" );
   systs[ "MuonId" ] = Systematic( "Central", "MuonIdUP", "MuonIdDN", "Central", "UP", "DN" );
   systs[ "MuonMomentumScale" ] = Systematic( "Central", "MuonMomentumScaleUP", "MuonMomentumScaleDN", "Central", "UP", "DN" );
   systs[ "PileUp" ] = Systematic( "Central", "PileUpUP", "PileUpDN", "Central", "UP", "DN" );
   systs[ "PtTopReweighting" ] = Systematic( "Central", "PtTopReweightingUP", "Central", "Central", "UP", "" );
   systs[ "UETunes" ] = Systematic( "MCTuneP11", "MCTuneP11TeV", "MCTuneP11mpiHi", "TuneP11", "TuneP11TeV", "TuneP11mpiHi" );
   systs[ "CR" ] = Systematic( "MCTuneP11", "MCTuneP11noCR", "MCTuneP11", "TuneP11", "TuneP11noCR", "" );
   systs[ "Matching" ] = Systematic( "Central", "MCmatchingup", "MCmatchingdown", "Central", "UP", "DN" );
   systs[ "Scale" ] = Systematic( "Central", "MCscaleup", "MCscaledown", "Central", "UP", "DN" );

   for( map<string, Systematic>::iterator s = systs.begin(); s != systs.end(); s++ ){

      string title = s->first;
      Systematic syst = s->second;

      std::cout << "Analyzing " << title << std::endl;

      TFile *f = new TFile( ("rootfiles/syst/plotsDataMC_"+syst.fCentral+".root").c_str() );
      TFile *fUP = new TFile( ("rootfiles/syst/plotsDataMC_"+syst.fUP+".root").c_str() );
      TFile *fDN = new TFile( ("rootfiles/syst/plotsDataMC_"+syst.fDN+".root").c_str() );

      for( vector<string>::iterator d = dists.begin(); d < dists.end(); d++ ){

         TCanvas *c = (TCanvas*)f->Get( ("c"+*d+"_gpttbar172").c_str() );
         TCanvas *cUP = (TCanvas*)fUP->Get( ("c"+*d+"_gpttbar172").c_str() );
         TCanvas *cDN = (TCanvas*)fDN->Get( ("c"+*d+"_gpttbar172").c_str() );

         // mbl
         TPad *p = (TPad*)c->FindObject("pad1");
         p->cd();

         THStack* h = (THStack*)c->FindObject( ("hs"+*d+"_gpttbar172").c_str() );
         THStack* hUP = (THStack*)cUP->FindObject( ("hs"+*d+"_gpttbar172").c_str() );
         THStack* hDN = (THStack*)cDN->FindObject( ("hs"+*d+"_gpttbar172").c_str() );

         TH1D* h1 = (TH1D*)h->GetStack()->Last();
         TH1D* h1UP = (TH1D*)hUP->GetStack()->Last();
         TH1D* h1DN = (TH1D*)hDN->GetStack()->Last();

         TCanvas *cnew = new TCanvas("cnew","cnew",800,800);
         TPad *pad1 = new TPad("pad1","pad1",0,0.33,1,1);
         TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.33);
         pad1->SetTopMargin(0.1);
         pad1->SetBottomMargin(0.01);
         pad1->SetRightMargin(0.1);
         pad1->SetFillColor(0);
         pad2->SetTopMargin(0.01);
         pad2->SetBottomMargin(0.3);
         pad2->SetRightMargin(0.1);
         pad2->SetFillColor(0);
         pad1->Draw();
         pad2->Draw();

         pad1->cd();

         h1->GetXaxis()->SetTitleSize(0.00);
         h1->GetYaxis()->SetLabelSize(0.07);
         h1->GetYaxis()->SetTitleSize(0.08);
         h1->GetYaxis()->SetTitleOffset(1.0);
         h1->GetXaxis()->SetLabelFont(42);
         h1->GetYaxis()->SetLabelFont(42);
         h1->GetXaxis()->SetTitleFont(42);
         h1->GetYaxis()->SetTitleFont(42);


         h1->SetFillStyle(0);
         h1->SetLineColor(1);
         h1->Draw("HIST");
         h1UP->SetFillStyle(0);
         h1UP->SetLineColor(2);
         h1UP->Draw("same HIST");
         h1DN->SetFillStyle(0);
         h1DN->SetLineColor(4);
         h1DN->Draw("same HIST");

         TLegend * legend = new TLegend(0.58,0.550,0.93,0.870);
         legend->SetHeader(title.c_str());
         legend->AddEntry( h1, (syst.lCentral).c_str(), "l" );
         legend->AddEntry( h1UP, (syst.lUP).c_str(), "l" );
         legend->AddEntry( h1DN, (syst.lDN).c_str(), "l" );
         legend->SetFillStyle(0);
         legend->SetBorderSize(0);
         legend->Draw();

         pad2->cd();

         TH1D* hr = (TH1D*)h1->Clone( ("hr"+*d+"_"+title).c_str() );
         TH1D* hrUP = (TH1D*)h1UP->Clone( ("hrUP"+*d+"_"+title).c_str());
         TH1D* hrDN = (TH1D*)h1DN->Clone( ("hrDN"+*d+"_"+title).c_str());

         hr->Divide(h1);
         hrUP->Divide(h1);
         hrDN->Divide(h1);

         hr->SetStats(0);
         hr->GetXaxis()->SetTitleSize(0.14);
         hr->GetXaxis()->SetLabelSize(0.14);
         hr->GetYaxis()->SetLabelSize(0.11);
         hr->GetYaxis()->SetTitleSize(0.14);
         hr->GetYaxis()->SetTitleOffset(0.28);
         hr->GetXaxis()->SetLabelFont(42);
         hr->GetYaxis()->SetLabelFont(42);
         hr->GetXaxis()->SetTitleFont(42);
         hr->GetYaxis()->SetTitleFont(42);
         hr->SetMaximum( 1.6 );
         hr->SetMinimum( 0.4 );
         hr->GetYaxis()->SetNdivisions(505);
         hr->GetYaxis()->SetTitle("ratio");
         hr->GetYaxis()->CenterTitle();

         hr->Draw("HIST");
         hrUP->SetLineColor(2);
         hrUP->Draw("HIST same");
         hrDN->SetLineColor(4);
         hrDN->Draw("HIST same");

         cnew->Draw();
         cnew->Print( ("pdfplots/syst/"+*d+"_"+title+".pdf").c_str() );


      }

   }

   return;
}
