#include <TFile.h>
#include <TH1F.h>
#include <TH1S.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <iostream>
#include <TF1.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TMath.h>
#include "langausfit.h"

using namespace std;






void FitLanGaus() {

  gROOT->Reset();
  //  gROOT->LoadMacro("/home/tdoan/CMSstyle.C");
  //  CMSstyle();
  gROOT->LoadMacro("~/public/style.C");
  //  tdrStyle();
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(1111);
  gStyle->SetOptFit(1111);


  //  TFile* inF = TFile::Open("histoMuon10GeV_calib.root");
  TFile* inF = TFile::Open("../test/histoMuon10GeV_calib.root");
  //  sprintf(fname, "rechit_trackIsolated.root");
  TH1F* hrec[3];
  hrec[0] = (TH1F*)inF->Get("HydraCaloCalibrator/h_recHitE_100");
  hrec[1] = (TH1F*)inF->Get("HydraCaloCalibrator/h_recHitE_200");
  hrec[2] = (TH1F*)inF->Get("HydraCaloCalibrator/h_recHitE_300");
  //

  for(int i=0; i<3; ++i){
    std::cout << " >>> nreC = " << hrec[i]->GetEntries() << std::endl;
    }



  TCanvas *c[3];

  TF1* f1 = new TF1("f1", langaufun, 0, 20., 4);
  f1->SetParNames("Width", "MPV", "Area", "GSigma");
  f1->SetNpx(10000); 

  float p1[4];
  p1[0] = 0.18; 
  p1[1] = 1.;
  p1[2] = 1.;
  p1[3] = 0.16;

  TF1* f2 = new TF1("f2", "landau", 0, 20.);
  f2->SetParNames("Constant", "MPV", "Sigma");
  f2->SetParameters(1., 1., 0.02);
  f2->SetNpx(10000);


  //write to file the fitted parameters
  ofstream myfile;
  myfile.open("MIPValues.txt");

  Int_t count = 0;
  for(int i = 0; i< 3; i++){
    if (hrec[i]->GetEntries() < 10) continue;
    std::cout << " histo name = " << hrec[i]->GetName() << std::endl;
    hrec[i]->Scale(1./hrec[i]->Integral());

    c[i] = new TCanvas(Form("Mip2fC_%d00", i),"", 700, 600);
    c[i]->SetLeftMargin(0.2);
    c[i]->SetRightMargin(0.12);
    //    hrec[i]->Sumw2();
    
    //	  hrec[i][j][k][l]->GetXaxis()->SetRangeUser(-0.0002, 0.1e-2);
    hrec[i]->GetXaxis()->SetNoExponent(kFALSE);
    hrec[i]->GetXaxis()->SetNoExponent(kFALSE);
    
    
    //	  hrec[i][j][k][l]->GetYaxis()->SetRangeUser(0., hrec[i][j][k][l]->GetMaximum());
    hrec[i]->GetYaxis()->SetTitle("Events");
    hrec[i]->GetXaxis()->SetTitle("amplitude (fC)");
    hrec[i]->GetYaxis()->SetTitleOffset(1.2);
    hrec[i]->Draw("e");
    
    p1[1] = i;
    //    p2[1] = i;
    f1->SetParameters(p1[0], p1[1], p1[2], p1[3]);
    f1->SetLineColor(kGreen+2);
    hrec[i]->Fit(f1, "+", "");

    f2->SetParameters(1., i, 0.02);
    f2->SetLineColor(kBlue);
    //hrec[i]->Fit(f2, "+", "");

    
    TLatex t3a;
    t3a.SetNDC();
    t3a.SetTextSize(0.04);
    t3a.SetTextFont(40);
    t3a.SetTextColor(kGreen+2);
    t3a.DrawLatex(0.4,0.4,Form("MP = %.2e +/- %.2e", f1->GetParameter(1), f1->GetParError(1)) );
    //t3a.DrawLatex(0.4,0.4,Form("MP = %.2e +/- %.2e", f2->GetParameter(1), f2->GetParError(1)) );
    
    /*
      f2->SetLineColor(kRed);
      hrec[i][j][k][l]->Fit(f2, "+", "", fr[0], fr[1]);
      
      TLatex t1a;
      t1a.SetNDC();
      t1a.SetTextSize(0.04);
      t1a.SetTextFont(40);
      t1a.SetTextColor(kRed);
      t1a.DrawLatex(0.4,0.6,Form("MP = %.2e +/- %.2e", f2->GetParameter(1), f2->GetParError(1)) );
      
      f1->SetParameter(0, f2->GetParameter(0));
      f1->SetParameter(1, f2->GetParameter(1));
      f1->SetParameter(2, f2->GetParameter(2));
      f1->SetParameter(3, f2->GetParameter(3));
    */
    
    /*
      f1->SetLineColor(kBlue);
      hrec[i][j][k][l]->Fit(f1, "+", "", fr[0], fr[1]);
      
      TLatex t2a;
      t2a.SetNDC();
      t2a.SetTextSize(0.04);
      t2a.SetTextFont(40);
      t2a.SetTextColor(kBlue);
      t2a.DrawLatex(0.4,0.5,Form("MP = %.2e +/- %.2e", f1->GetParameter(1), f1->GetParError(1)) );
    */
    
    
    double mpv = f1->GetParameter(1);
    double mpvE = f1->GetParError(1);
    double chi2 = f1->GetChisquare()/f1->GetNDF();
    /*
    double mpv = f2->GetParameter(1);              
    double mpvE = f2->GetParError(1);              
    double chi2 = f2->GetChisquare()/f1->GetNDF(); 
    */
    c[i]->SaveAs(Form("plots_MIP/Energy_%d_FitLanGau.png", i), ".png");
    if(chi2 < 100.){
      myfile << i << " " << mpv << " " << mpvE << " " << std::endl;
      //	      c[i][j][k][l]->SaveAs(Form("plots_AllRk/Energy_Z%d_P%d_X%d_Y%d_FitLanGau.png", i, j, k, l), ".png");
    }
    
    
  }

  TCanvas* c2 = new TCanvas();
  c2->cd();
  hrec[0]->SetMarkerColor(kRed);
  hrec[1]->SetMarkerColor(kBlue);
  hrec[2]->SetMarkerColor(kGreen+2);
  hrec[0]->Draw();
  hrec[1]->Draw("same");  
  hrec[2]->Draw("same");

  //cout << "number of rechit < 500 events: " << count << endl;

  myfile.close();
  
  TFile out("outReso.root", "recreate");
  out.cd();
  for (int i = 0; i< 3; i++)
    if(hrec[i]->GetEntries() > 0.) hrec[i]->Write();
	

  out.Close();


}
