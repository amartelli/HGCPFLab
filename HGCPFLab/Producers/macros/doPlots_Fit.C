#include "TLegend.h"
#include "TLatex.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <iostream>
#include <TF1.h>
#include <TGraph.h>
#include "TTree.h"
#include "TChain.h"
#include <vector>
#include <fstream>
#include <string>




void doPlots_Fit(){
  gROOT->Reset();
  gROOT->Macro("~/public/setStyle.C");
  //  gROOT->LoadMacro("~/public/myStyle.C");
  //gROOT->LoadMacro("~/public/setStyle.C");
  //gROOT->LoadMacro("~/public/rootLogon.C");
  //gStyle->SetOptTitle(0);
  //  gStyle->SetOptStat(1111);
  //  gStyle->SetOptFit(1111);

  /*
   gStyle->SetTitleOffset(1.1,"x");//X-axis title offset from axis
   gStyle->SetTitleOffset(1.1,"y");//X-axis title offset from axis                                                               
   gStyle->SetTitleSize(0.5,"x");//X-axis title size                         
   gStyle->SetTitleSize(0.5,"y");
   gStyle->SetTitleSize(0.05,"z");
   gStyle->SetLabelOffset(0.025);
  */

  //  gStyle->SetOptStat(0);
  //gStyle->SetOptTitle(0);
  // gPad->SetGridx();
  // gPad->SetGridy();


  //  std::cout << " ene = " << ene << std::endl; 


  //  TFile *inF = TFile::Open("hydra_CalibOnly_Pho35.root");
  TFile* inF[3];
  inF[0] = TFile::Open("hydra_CalibOnly_PhoE60.root");
  inF[1] = TFile::Open("hydra_CalibOnly_PhoE100.root");
  inF[2] = TFile::Open("hydra_CalibOnly_PhoE250.root");

  //vs gen                                                                                                                                                                      

  TH1F* h_EoP_hitTrack_100[3];
  TH1F* h_EoP_hitTrack_200[3];
  TH1F* h_EoP_hitTrack_300[3];



  TF1* fitF_100[3];
  fitF_100[0] = new TF1("Si100_E60", "gaus", 0.8, 1. );
  fitF_100[1] = new TF1("Si100_E100", "gaus", 0.8, 1. );
  fitF_100[2] = new TF1("Si100_E250", "gaus", 0.8, 1. );
  //  fitF_60->SetParameters(600, 0.92, 1.5);
  TF1* fitF_200[3];
  fitF_200[0] = new TF1("Si200_E60", "gaus", 0.8, 1. );
  fitF_200[1] = new TF1("Si200_E100", "gaus", 0.8, 1. );
  fitF_200[2] = new TF1("Si200_E250", "gaus", 0.8, 1. );
  //
  TF1* fitF_300[3];
  fitF_300[0] = new TF1("Si300_E60", "gaus", 0.8, 1. );
  fitF_300[1] = new TF1("Si300_E100", "gaus", 0.8, 1. );
  fitF_300[2] = new TF1("Si300_E250", "gaus", 0.8, 1. );


  int colorsExt[6] = {kBlue, kRed+2, kGreen+2};
  //  std::vector<int> colors;

  for(int iC=0; iC<3; ++iC){
    h_EoP_hitTrack_100[iC] = (TH1F*)(inF[iC]->Get("HydraCaloCalibrator/h_EoP_hitTrack_100"));
    h_EoP_hitTrack_200[iC] = (TH1F*)(inF[iC]->Get("HydraCaloCalibrator/h_EoP_hitTrack_200"));
    h_EoP_hitTrack_300[iC] = (TH1F*)(inF[iC]->Get("HydraCaloCalibrator/h_EoP_hitTrack_300"));

    h_EoP_hitTrack_100[iC]->Rebin(4);
    h_EoP_hitTrack_200[iC]->Rebin(4);
    h_EoP_hitTrack_300[iC]->Rebin(4);

    //    colors.push_back(colorsExt[iC]);
    h_EoP_hitTrack_100[iC]->SetLineColor(colorsExt[iC]);
    h_EoP_hitTrack_200[iC]->SetLineColor(colorsExt[iC]);
    h_EoP_hitTrack_300[iC]->SetLineColor(colorsExt[iC]);

    h_EoP_hitTrack_100[iC]->SetLineWidth(2);
    h_EoP_hitTrack_200[iC]->SetLineWidth(2);
    h_EoP_hitTrack_300[iC]->SetLineWidth(2);


    fitF_100[iC]->SetParameters(600, 0.92, 1.5);
    fitF_200[iC]->SetParameters(600, 0.92, 1.5);
    fitF_300[iC]->SetParameters(600, 0.92, 1.5);
    fitF_100[iC]->SetLineColor(colorsExt[iC]);
    fitF_200[iC]->SetLineColor(colorsExt[iC]);
    fitF_300[iC]->SetLineColor(colorsExt[iC]);
  }




  std::cout << " ci sono " << std::endl;

  TLegend *leg = new TLegend(0.70,0.80,0.99,1.,NULL,"brNDC");
  leg->SetTextFont(42);
  leg->SetFillColor(kWhite);
  leg->SetLineColor(kWhite);
  leg->SetShadowColor(kWhite);
  leg->AddEntry(h_EoP_hitTrack_100[0], "#gamma E=60GeV", "l");
  leg->AddEntry(h_EoP_hitTrack_100[1], "#gamma E=100GeV", "l");
  leg->AddEntry(h_EoP_hitTrack_100[2], "#gamma E=250GeV", "l");



  TLatex t3a;
  t3a.SetNDC();
  t3a.SetTextSize(0.03);
  t3a.SetTextFont(132);
  t3a.SetTextColor(kBlue);

  h_EoP_hitTrack_100[0]->Fit("Si100_E60", "R");
  h_EoP_hitTrack_100[1]->Fit("Si100_E100", "R");
  h_EoP_hitTrack_100[2]->Fit("Si100_E250", "R");

  std::cout << " passa a 200 " << std::endl;
  TLatex t1a;
  t1a.SetNDC();
  t1a.SetTextSize(0.03);
  t1a.SetTextFont(132);
  t1a.SetTextColor(kRed+2);

  h_EoP_hitTrack_200[0]->Fit("Si200_E60", "R");
  h_EoP_hitTrack_200[1]->Fit("Si200_E100", "R");
  h_EoP_hitTrack_200[2]->Fit("Si200_E250", "R");

  std::cout << " passa a 300 " << std::endl;
  TLatex t1p;
  t1p.SetNDC();
  t1p.SetTextSize(0.03);
  t1p.SetTextFont(132);
  t1p.SetTextColor(kGreen+2);

  h_EoP_hitTrack_300[0]->Fit("Si300_E60", "R");
  h_EoP_hitTrack_300[1]->Fit("Si300_E100", "R");
  h_EoP_hitTrack_300[2]->Fit("Si300_E250", "R");


  //  std::string folder = "plots"+std::string(Form("_E%d",ene));
  std::string folder = "plots_Efit";
  //     std::string folder = "plots_E250";

   TCanvas* ch_100 = new TCanvas();
  ch_100->cd();
  h_EoP_hitTrack_100[0]->GetXaxis()->SetTitle("#Sigma E_{i} / E_{simTrack} in 100#mum");
  h_EoP_hitTrack_100[0]->GetXaxis()->SetRangeUser(0.6, 1.2);
  h_EoP_hitTrack_100[0]->GetYaxis()->SetRangeUser(0., 1400);
  h_EoP_hitTrack_100[0]->Draw();
  h_EoP_hitTrack_100[1]->Draw("same");
  h_EoP_hitTrack_100[2]->Draw("same");

  t3a.DrawLatex(0.15,0.9,Form("m = %.2e +/- %.2e   #sigma = %.2e +/- %.2e", fitF_100[0]->GetParameter(1), fitF_100[0]->GetParError(1), 
   			     fitF_100[0]->GetParameter(2), fitF_100[0]->GetParError(2)));
  t1a.DrawLatex(0.15,0.85,Form("m = %.2e +/- %.2e   #sigma = %.2e +/- %.2e", fitF_100[1]->GetParameter(1), fitF_100[1]->GetParError(1),
   			     fitF_100[1]->GetParameter(2), fitF_100[1]->GetParError(2)));
  t1p.DrawLatex(0.15,0.8,Form("m = %.2e +/- %.2e   #sigma = %.2e +/- %.2e", fitF_100[2]->GetParameter(1), fitF_100[2]->GetParError(1),
			     fitF_100[2]->GetParameter(2), fitF_100[2]->GetParError(2)) );
  //  t1p.DrawLatex(0.2, 0.85, "#sigma");

  ////////////
  // TLatex latexLabel;
  // latexLabel.SetNDC();
  // latexLabel.SetTextSize(0.04);
  // //  latexLabel.DrawLatex(0.18, 0.96, "#font[132]{CMS Preliminary 2010}");
  // // latexLabel.DrawLatex(0.77, 0.955, "#font[132]{#sqrt{s} = 7 TeV}");
  // //  latexLabel.DrawLatex(0.2, 0.85, "#font[132]{#sigma}");


  leg->Draw("same");
  ch_100->Print((folder+"/h_EoP_hitTrack_100.png").c_str(), "png");




  TCanvas* ch_200 = new TCanvas();
  ch_200->cd();
  h_EoP_hitTrack_200[0]->GetXaxis()->SetTitle("#Sigma E_{i} / E_{simTrack} in 200#mum");
  h_EoP_hitTrack_200[0]->GetXaxis()->SetRangeUser(0.6, 1.2);
  h_EoP_hitTrack_200[0]->GetYaxis()->SetRangeUser(0., 1400);
  h_EoP_hitTrack_200[0]->Draw();
  h_EoP_hitTrack_200[1]->Draw("same");
  h_EoP_hitTrack_200[2]->Draw("same");
  leg->Draw("same");

  t3a.DrawLatex(0.15,0.9,Form("m = %.2e +/- %.2e   #sigma = %.2e +/- %.2e", fitF_200[0]->GetParameter(1), fitF_200[0]->GetParError(1), 
			     fitF_200[0]->GetParameter(2), fitF_200[0]->GetParError(2)));
  t1a.DrawLatex(0.15,0.85,Form("m = %.2e +/- %.2e   #sigma = %.2e +/- %.2e", fitF_200[1]->GetParameter(1), fitF_200[1]->GetParError(1),
			     fitF_200[1]->GetParameter(2), fitF_200[1]->GetParError(2)));
  t1p.DrawLatex(0.15,0.8,Form("m = %.2e +/- %.2e   #sigma = %.2e +/- %.2e", fitF_200[2]->GetParameter(1), fitF_200[2]->GetParError(1),
			     fitF_200[2]->GetParameter(2), fitF_200[2]->GetParError(2)));

  ch_200->Print((folder+"/h_EoP_hitTrack_200.png").c_str(), "png");




  TCanvas* ch_300 = new TCanvas();
  ch_300->cd();
  h_EoP_hitTrack_300[0]->GetXaxis()->SetTitle("#Sigma E_{i} / E_{simTrack} in 300#mum");
  h_EoP_hitTrack_300[0]->GetXaxis()->SetRangeUser(0.6, 1.2);
  h_EoP_hitTrack_300[0]->GetYaxis()->SetRangeUser(0., 1000);
  h_EoP_hitTrack_300[0]->Draw();
  h_EoP_hitTrack_300[1]->Draw("same");
  h_EoP_hitTrack_300[2]->Draw("same");
  leg->Draw("same");

  t3a.DrawLatex(0.15,0.9,Form("m = %.2e +/- %.2e   #sigma = %.2e +/- %.2e", fitF_300[0]->GetParameter(1), fitF_300[0]->GetParError(1), 
			     fitF_300[0]->GetParameter(2), fitF_300[0]->GetParError(2)));
  t1a.DrawLatex(0.15,0.85,Form("m = %.2e +/- %.2e   #sigma = %.2e +/- %.2e", fitF_300[1]->GetParameter(1), fitF_300[1]->GetParError(1),
			     fitF_300[1]->GetParameter(2), fitF_300[1]->GetParError(2)));
  t1p.DrawLatex(0.15,0.8,Form("m = %.2e +/- %.2e   #sigma = %.2e +/- %.2e", fitF_300[2]->GetParameter(1), fitF_300[2]->GetParError(1),
			     fitF_300[2]->GetParameter(2), fitF_300[2]->GetParError(2)));

  ch_300->Print((folder+"/h_EoP_hitTrack_300.png").c_str(), "png");



}
