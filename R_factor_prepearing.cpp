#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "AtlasUtils.C"
#include "AtlasLabels.C"
#include "AtlasStyle.C"

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"


 void R_factor_prepearing(const char *fname = "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Zj366020.root"){
   SetAtlasStyle();

   TFile *file = new TFile(fname, "READ");

   double sum_of_weights_bk_xAOD, sumw_MC16a = 0, weight, sum = 0, ph_pt, sum_koef = 0, koef;
   double ph_iso_pt, ph_iso_et40, ph_z_point;
   UInt_t ph_isem, n_ph, n_mu, n_e_medium;
   Int_t mc_ph_type;
   double sum_A = 0, sum_B = 0, sum_C = 0, sum_D = 0;
   TTree *tree_MC_sw = (TTree*)file->Get("output_tree_sw");
   TTree *tree = (TTree*)file->Get("output_tree");
   TTree *tree_norm = (TTree*)file->Get("norm_tree");
   tree_MC_sw->SetBranchAddress("sum_of_weights_bk_xAOD",&sum_of_weights_bk_xAOD);
   tree->SetBranchAddress("weight",&weight);
   tree->SetBranchAddress("ph_pt",&ph_pt);
   tree->SetBranchAddress("ph_iso_et40", &ph_iso_et40);
   tree->SetBranchAddress("ph_iso_pt", &ph_iso_pt);
   tree->SetBranchAddress("weight", &weight);
   tree->SetBranchAddress("n_ph", &n_ph);
   tree->SetBranchAddress("n_mu", &n_mu);
   tree->SetBranchAddress("n_e_medium", &n_e_medium);
   tree->SetBranchAddress("ph_isem", &ph_isem);
   tree->SetBranchAddress("ph_z_point", &ph_z_point);
   tree->SetBranchAddress("mc_ph_type", &mc_ph_type);
   tree_norm->SetBranchAddress("koef",&koef);

   int entry = (int)tree_MC_sw->GetEntries();
   int N = (int)tree->GetEntries();
   int N_koef = (int)tree_norm->GetEntries();
   for (int i=0; i<entry; i++) {
    tree_MC_sw->GetEntry(i);
    sumw_MC16a += sum_of_weights_bk_xAOD;
   }
   for(int i = 0; i < N; i++){
     tree->GetEntry(i);
     sum += weight;
   }
   for (int i=0; i<N_koef; i++) {
    tree_norm->GetEntry(i);
    sum_koef += koef;
   }


   //cout<<"sumw_MC16a = "<<sumw_MC16a<<endl;
   //cout<<"weight = "<<sum_koef<<endl;

   TH1F *hist_A = new TH1F ("hist_A", "hist_A", 100, -100, 10000);
   TH1F *hist_B = new TH1F ("hist_B", "hist_B", 100, -100, 10000);
   TH1F *hist_C = new TH1F ("hist_C", "hist_C", 100, -100, 10000);
   TH1F *hist_D = new TH1F ("hist_D", "hist_D", 100, -100, 10000);
   sumw_MC16a = sumw_MC16a;
   //sum = sum/1000;


  for(int i = 0; i<N; i++){

     tree->GetEntry(i);
     if(ph_iso_pt/ph_pt >= 0.05 || fabs(ph_z_point)>=250 || fabs(weight)>=100) continue;
     if(mc_ph_type >= 13 && mc_ph_type <= 15) continue;
     if(n_ph !=1 || n_mu !=0 || n_e_medium != 0) continue;
     if((ph_iso_et40 - 0.022*ph_pt) < 2.45 && ph_isem == 0 ) hist_A->Fill(ph_pt, 58450.1*sum_koef*weight/(sumw_MC16a));
     else if((ph_iso_et40 - 0.022*ph_pt) > 4.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && ph_isem == 0) hist_B->Fill(ph_pt, 58450.1*sum_koef*weight/(sumw_MC16a));
     else if((ph_iso_et40 - 0.022*ph_pt) < 2.45 && (ph_isem != 0 && (ph_isem & 0x27fc01) == 0 )) hist_C->Fill(ph_pt, 58450.1*sum_koef*weight/(sumw_MC16a));
     else if((ph_iso_et40 - 0.022*ph_pt) > 4.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem != 0 && (ph_isem & 0x27fc01) == 0 )) hist_D->Fill(ph_pt, 58450.1*sum_koef*weight/(sumw_MC16a));

  }
   double N_A = hist_A->Integral();
   double N_B = hist_B->Integral();
   double N_C = hist_C->Integral();
   double N_D = hist_D->Integral();

   double R;
   R = N_A*N_D/(N_C*N_B);
   cout<<"N_A = "<<N_A<<endl;
   cout<<"N_B = "<<N_B<<endl;
   cout<<"N_C = "<<N_C<<endl;
   cout<<"N_D = "<<N_D<<endl;
   cout<<"R factor = "<<R<<endl;


/*
   Double_t LoosePrime2 = ph_isem & 0x27fc01;
   Double_t LoosePrime3 = ph_isem & 0x25fc01;
   Double_t LoosePrime4 = ph_isem & 0x5fc01;
   Double_t LoosePrime5 = ph_isem & 0x1fc01;

   Double_t lumi_mc16a = 36214.96;
   Double_t lumi_mc16d = 44307.4;
   Double_t lumi_mc16e = 58450.1;
*/


 }
