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




void doPlots(int ene){
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


  std::cout << " ene = " << ene << std::endl; 


  //  TFile *inF = TFile::Open("hydra_CalibOnly_Pho35.root");
  TFile *inF = TFile::Open(Form("hydra_CalibOnly_PhoE%d.root", ene));
  //   TFile *inF = TFile::Open("hydra_CalibOnly_PhoE100.root");
  //   TFile *inF = TFile::Open("hydra_CalibOnly_PhoE250.root");

  //vs gen                                                                                                                                                                      
  TH1F* h_EoP_hitTrack = (TH1F*)inF->Get("HydraCaloCalibrator/h_EoP_hitTrack");
  TProfile* tp_EoP_hitTrack_vsP = (TProfile*)inF->Get("HydraCaloCalibrator/tp_EoP_hitTrack_vsP");
  TProfile* tp_EoP_hitTrack_vsPt = (TProfile*)inF->Get("HydraCaloCalibrator/tp_EoP_hitTrack_vsPt");
  TProfile* tp_EoP_hitTrack_vsEta = (TProfile*)inF->Get("HydraCaloCalibrator/tp_EoP_hitTrack_vsEta");
  TProfile* tp_EoP_hitTrack_vsAbsEta = (TProfile*)inF->Get("HydraCaloCalibrator/tp_EoP_hitTrack_vsAbsEta");
  TProfile* tp_EoP_hitTrack_vsPhi = (TProfile*)inF->Get("HydraCaloCalibrator/tp_EoP_hitTrack_vsPhi");
  TProfile* tp_EoP_hitTrack_vsR = (TProfile*)inF->Get("HydraCaloCalibrator/tp_EoP_hitTrack_vsR");
  TProfile* tp_EoP_hitTrack_vsType = (TProfile*)inF->Get("HydraCaloCalibrator/tp_EoP_hitTrack_vsType");
  TH1F* h_frac_recHitWithTime = (TH1F*)inF->Get("HydraCaloCalibrator/h_frac_recHitWithTime");
  TProfile* tp_frac_recHitWithTime_vsType = (TProfile*)inF->Get("HydraCaloCalibrator/tp_frac_recHitWithTime_vsType");
  //TProfile* tp_EoP_hitTrack_vsType = (TProfile*)inF->Get("HydraCaloCalibrator/tp_EoP_hitTrack_vsR");
  //TH2F                                                                                                                                                                        
  TH2F* h2_EoP_hitTrack_vsP = (TH2F*)inF->Get("HydraCaloCalibrator/h2_EoP_hitTrack_vsP");
  TH2F* h2_EoP_hitTrack_vsPt = (TH2F*)inF->Get("HydraCaloCalibrator/h2_EoP_hitTrack_vsPt");
  TH2F* h2_EoP_hitTrack_vsEta = (TH2F*)inF->Get("HydraCaloCalibrator/h2_EoP_hitTrack_vsEta");
  TH2F* h2_EoP_hitTrack_vsAbsEta = (TH2F*)inF->Get("HydraCaloCalibrator/h2_EoP_hitTrack_vsAbsEta");
  TH2F* h2_EoP_hitTrack_vsPhi = (TH2F*)inF->Get("HydraCaloCalibrator/h2_EoP_hitTrack_vsPhi");
  TH2F* h2_EoP_hitTrack_vsR = (TH2F*)inF->Get("HydraCaloCalibrator/h2_EoP_hitTrack_vsR");
  TH2F* h2_EoP_hitTrack_vsType = (TH2F*)inF->Get("HydraCaloCalibrator/h2_EoP_hitTrack_vsType");
  TH2F* h2_frac_recHitWithTime_vsType = (TH2F*)inF->Get("HydraCaloCalibrator/h2_frac_recHitWithTime_vsType");
  //TH2F* h2_EoP_hitTrack_vsType = (TH2F*)inF->Get("HydraCaloCalibrator/h2_EoP_hitTrack_vsR");


  std::cout << " ci sono " << std::endl;

  TLegend *leg = new TLegend(0.70,0.80,0.99,1.,NULL,"brNDC");
  leg->SetTextFont(42);
  leg->SetFillColor(kWhite);
  leg->SetLineColor(kWhite);
  leg->SetShadowColor(kWhite);
  //  leg->AddEntry(ee_vs_es[0], type1.c_str(), "l");


  h_frac_recHitWithTime->SetLineWidth(2);
  h_frac_recHitWithTime->SetLineColor(kBlue);

  tp_frac_recHitWithTime_vsType->SetMarkerStyle(7);
  tp_frac_recHitWithTime_vsType->SetMarkerColor(kBlue);
  tp_frac_recHitWithTime_vsType->SetLineWidth(2);
  tp_frac_recHitWithTime_vsType->SetLineColor(kBlue);

  h_EoP_hitTrack->SetLineWidth(2);
  h_EoP_hitTrack->SetLineColor(kBlue);

  tp_EoP_hitTrack_vsP->SetMarkerStyle(7); 
  tp_EoP_hitTrack_vsP->SetMarkerColor(kBlue);
  tp_EoP_hitTrack_vsP->SetLineWidth(2);
  tp_EoP_hitTrack_vsP->SetLineColor(kBlue);

  tp_EoP_hitTrack_vsPt->SetMarkerStyle(7); 
  tp_EoP_hitTrack_vsPt->SetMarkerColor(kBlue);
  tp_EoP_hitTrack_vsPt->SetLineWidth(2);
  tp_EoP_hitTrack_vsPt->SetLineColor(kBlue);

  tp_EoP_hitTrack_vsEta->SetMarkerStyle(7); 
  tp_EoP_hitTrack_vsEta->SetMarkerColor(kBlue);
  tp_EoP_hitTrack_vsEta->SetLineWidth(2);
  tp_EoP_hitTrack_vsEta->SetLineColor(kBlue);

  tp_EoP_hitTrack_vsAbsEta->SetMarkerStyle(7); 
  tp_EoP_hitTrack_vsAbsEta->SetMarkerColor(kBlue);
  tp_EoP_hitTrack_vsAbsEta->SetLineWidth(2);
  tp_EoP_hitTrack_vsAbsEta->SetLineColor(kBlue);

  tp_EoP_hitTrack_vsPhi->SetMarkerStyle(7); 
  tp_EoP_hitTrack_vsPhi->SetMarkerColor(kBlue);
  tp_EoP_hitTrack_vsPhi->SetLineWidth(2);
  tp_EoP_hitTrack_vsPhi->SetLineColor(kBlue);

  tp_EoP_hitTrack_vsR->SetMarkerStyle(7); 
  tp_EoP_hitTrack_vsR->SetMarkerColor(kBlue);
  tp_EoP_hitTrack_vsR->SetLineWidth(2);
  tp_EoP_hitTrack_vsR->SetLineColor(kBlue);


  tp_EoP_hitTrack_vsType->SetMarkerStyle(7); 
  tp_EoP_hitTrack_vsType->SetMarkerColor(kBlue);
  tp_EoP_hitTrack_vsType->SetLineWidth(2);
  tp_EoP_hitTrack_vsType->SetLineColor(kBlue);


  std::string folder = "plots"+std::string(Form("_E%d",ene));
  //  std::string folder = "plots_E100";
  //     std::string folder = "plots_E250";

  //time first
  TCanvas* chT = new TCanvas();
  chT->cd();
  h_frac_recHitWithTime->GetXaxis()->SetTitle("fraction of recHits with time");
  h_frac_recHitWithTime->Draw();
  chT->Print((folder+"/h_frac_recHitWithTime.png").c_str(), "png");

  TCanvas* chT_vsType = new TCanvas();
  gPad->SetGrid();
  chT_vsType->cd();
  tp_frac_recHitWithTime_vsType->GetXaxis()->SetTitle("Si thickness (#mum)");
  tp_frac_recHitWithTime_vsType->GetYaxis()->SetTitle("fraction of recHits with time");
  tp_frac_recHitWithTime_vsType->Draw();
  chT_vsType->Print((folder+"/tp_frac_recHitWithTime_vsType.png").c_str(), "png");

  TCanvas* ch2T_vsType = new TCanvas();
  gPad->SetGrid();
  ch2T_vsType->cd();
  h2_frac_recHitWithTime_vsType->GetXaxis()->SetTitle("Si thickness (#mum)");
  h2_frac_recHitWithTime_vsType->GetYaxis()->SetTitle("fraction of recHits with time");
  h2_frac_recHitWithTime_vsType->Draw("colz");
  ch2T_vsType->Print((folder+"/h2_frac_recHitWithTime_vsType.png").c_str(), "png");
  
  //
  TCanvas* ch = new TCanvas();
  ch->cd();
  h_EoP_hitTrack->GetXaxis()->SetTitle("#Sigma E_{i} / E_{simTrack}");
  h_EoP_hitTrack->Draw();
  ch->Print((folder+"/h_EoPsimTrack.png").c_str(), "png");


  TCanvas* ch_vsP = new TCanvas();
  gPad->SetGrid();
  ch_vsP->cd();
  tp_EoP_hitTrack_vsP->GetXaxis()->SetTitle("E_{simTrack}");
  tp_EoP_hitTrack_vsP->GetYaxis()->SetTitle("#Sigma E_{i} / E_{simTrack}");
  tp_EoP_hitTrack_vsP->Draw();
  ch_vsP->Print((folder+"/tp_EoPsimTrack_vsP.png").c_str(), "png");


  TCanvas* ch_vsPt = new TCanvas();
  ch_vsPt->cd();
  tp_EoP_hitTrack_vsPt->GetXaxis()->SetTitle("Pt_{simTrack}");
  tp_EoP_hitTrack_vsPt->GetYaxis()->SetTitle("#Sigma E_{i} / E_{simTrack}");
  tp_EoP_hitTrack_vsPt->Draw();
  ch_vsPt->Print((folder+"/tp_EoPsimTrack_vsPt.png").c_str(), "png");


  TCanvas* ch_vsEta = new TCanvas();
  ch_vsEta->cd();
  tp_EoP_hitTrack_vsEta->GetXaxis()->SetTitle("Eta_{simTrack}");
  tp_EoP_hitTrack_vsEta->GetYaxis()->SetTitle("#Sigma E_{i} / E_{simTrack}");
  tp_EoP_hitTrack_vsEta->Draw();
  ch_vsEta->Print((folder+"/tp_EoPsimTrack_vsEta.png").c_str(), "png");


  TCanvas* ch_vsAbsEta = new TCanvas();
  ch_vsAbsEta->cd();
  tp_EoP_hitTrack_vsAbsEta->GetXaxis()->SetTitle("|Eta_{simTrack}|");
  tp_EoP_hitTrack_vsAbsEta->GetYaxis()->SetTitle("#Sigma E_{i} / E_{simTrack}");
  tp_EoP_hitTrack_vsAbsEta->Draw();
  ch_vsAbsEta->Print((folder+"/tp_EoPsimTrack_vsAbsEta.png").c_str(), "png");


  TCanvas* ch_vsPhi = new TCanvas();
  ch_vsPhi->cd();
  tp_EoP_hitTrack_vsPhi->GetXaxis()->SetTitle("Phi_{simTrack}");
  tp_EoP_hitTrack_vsPhi->GetYaxis()->SetTitle("#Sigma E_{i} / E_{simTrack}");
  tp_EoP_hitTrack_vsPhi->Draw();
  ch_vsPhi->Print((folder+"/tp_EoPsimTrack_vsPhi.png").c_str(), "png");

  TCanvas* ch_vsR = new TCanvas();
  ch_vsR->cd();
  tp_EoP_hitTrack_vsR->GetXaxis()->SetTitle("R_{simTrack}");
  tp_EoP_hitTrack_vsR->GetYaxis()->SetTitle("#Sigma E_{i} / E_{simTrack}");
  tp_EoP_hitTrack_vsR->Draw();
  ch_vsR->Print((folder+"/tp_EoPsimTrack_vsR.png").c_str(), "png");

  TCanvas* ch_vsT = new TCanvas();
  ch_vsT->cd();
  tp_EoP_hitTrack_vsType->GetXaxis()->SetTitle("Si thickness (#mum)");
  tp_EoP_hitTrack_vsType->GetYaxis()->SetTitle("#Sigma E_{i} / E_{simTrack}");
  tp_EoP_hitTrack_vsType->Draw();
  ch_vsT->Print((folder+"/tp_EoPsimTrack_vsType.png").c_str(), "png");


  ////
  TCanvas* ch2_vsP = new TCanvas();
  ch2_vsP->cd();
  h2_EoP_hitTrack_vsP->GetXaxis()->SetTitle("E_{simTrack}");
  h2_EoP_hitTrack_vsP->GetYaxis()->SetTitle("#Sigma E_{i} / E_{simTrack}");
  h2_EoP_hitTrack_vsP->Draw("colz");
  ch2_vsP->Print((folder+"/h2_EoPsimTrack_vsP.png").c_str(), "png");


  TCanvas* ch2_vsPt = new TCanvas();
  ch2_vsPt->cd();
  h2_EoP_hitTrack_vsPt->GetXaxis()->SetTitle("Pt_{simTrack}");
  h2_EoP_hitTrack_vsPt->GetYaxis()->SetTitle("#Sigma E_{i} / E_{simTrack}");
  h2_EoP_hitTrack_vsPt->Draw("colz");
  ch2_vsPt->Print((folder+"/h2_EoPsimTrack_vsPt.png").c_str(), "png");


  TCanvas* ch2_vsEta = new TCanvas();
  ch2_vsEta->cd();
  h2_EoP_hitTrack_vsEta->GetXaxis()->SetTitle("Eta_{simTrack}");
  h2_EoP_hitTrack_vsEta->GetYaxis()->SetTitle("#Sigma E_{i} / E_{simTrack}");
  h2_EoP_hitTrack_vsEta->Draw("colz");
  ch2_vsEta->Print((folder+"/h2_EoPsimTrack_vsEta.png").c_str(), "png");


  TCanvas* ch2_vsAbsEta = new TCanvas();
  ch2_vsAbsEta->cd();
  h2_EoP_hitTrack_vsAbsEta->GetXaxis()->SetTitle("|Eta_{simTrack}|");
  h2_EoP_hitTrack_vsAbsEta->GetYaxis()->SetTitle("#Sigma E_{i} / E_{simTrack}");
  h2_EoP_hitTrack_vsAbsEta->Draw("colz");
  ch2_vsAbsEta->Print((folder+"/h2_EoPsimTrack_vsAbsEta.png").c_str(), "png");


  TCanvas* ch2_vsPhi = new TCanvas();
  ch2_vsPhi->cd();
  h2_EoP_hitTrack_vsPhi->GetXaxis()->SetTitle("Phi_{simTrack}");
  h2_EoP_hitTrack_vsPhi->GetYaxis()->SetTitle("#Sigma E_{i} / E_{simTrack}");
  h2_EoP_hitTrack_vsPhi->Draw("colz");
  ch2_vsPhi->Print((folder+"/h2_EoPsimTrack_vsPhi.png").c_str(), "png");


  TCanvas* ch2_vsT = new TCanvas();
  ch2_vsT->cd();
  h2_EoP_hitTrack_vsType->GetXaxis()->SetTitle("Si thickness (#mum)");
  h2_EoP_hitTrack_vsType->GetYaxis()->SetTitle("#Sigma E_{i} / E_{simTrack}");
  h2_EoP_hitTrack_vsType->Draw("colz");
  ch2_vsT->Print((folder+"/h2_EoPsimTrack_vsType.png").c_str(), "png");


  TCanvas* ch2_vsT_zoom = new TCanvas();
  ch2_vsT_zoom->cd();
  h2_EoP_hitTrack_vsType->GetZaxis()->SetRangeUser(100, 7000);
  h2_EoP_hitTrack_vsType->GetXaxis()->SetTitle("Si thickness (#mum)");
  h2_EoP_hitTrack_vsType->GetYaxis()->SetTitle("#Sigma E_{i} / E_{simTrack}");
  h2_EoP_hitTrack_vsType->Draw("colz");
  ch2_vsT_zoom->Print((folder+"/h2_EoPsimTrack_vsType_above10.png").c_str(), "png");

}
