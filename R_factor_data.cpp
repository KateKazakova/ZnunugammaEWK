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


  const char *fname[111] = {
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16a_361045.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16a_361046.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16a_361047.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16a_361048.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16a_361049.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16a_361050.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16a_361051.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16a_361052.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16a_361053.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16a_361054.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16a_361055.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16a_361056.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16d_361045.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16d_361046.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16d_361047.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16d_361048.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16d_361049.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16d_361050.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16d_361051.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16d_361052.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16d_361053.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16d_361054.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16d_361055.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16d_361056.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16e_361045.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16e_361046.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16e_361047.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16e_361048.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16e_361049.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16e_361050.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16e_361051.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16e_361052.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16e_361053.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16e_361054.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16e_361055.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Gammajet_MC16e_361056.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_ttgamma_MC16a.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_ttgamma_MC16d.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_ttgamma_MC16e.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_WgammaEWK_MC16a_361273.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_WgammaEWK_MC16a_361274.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_WgammaEWK_MC16a_361275.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_WgammaEWK_MC16d_361273.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_WgammaEWK_MC16d_361274.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_WgammaEWK_MC16d_361275.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_WgammaEWK_MC16e_361273.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_WgammaEWK_MC16e_361274.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_WgammaEWK_MC16e_361275.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_WgammaQCD_MC16a_364525.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_WgammaQCD_MC16a_364530.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_WgammaQCD_MC16a_364535.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_WgammaQCD_MC16d_364525.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_WgammaQCD_MC16d_364530.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_WgammaQCD_MC16d_364535.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_WgammaQCD_MC16e_364525.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_WgammaQCD_MC16e_364530.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_WgammaQCD_MC16e_364535.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16a_364184.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16a_364185.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16a_364186.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16a_364187.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16a_364188.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16a_364189.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16a_364190.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16a_364191.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16a_364192.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16a_364193.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16a_364194.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16a_364195.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16a_364196.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16d_364184.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16d_364185.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16d_364186.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16d_364187.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16d_364188.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16d_364189.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16d_364190.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16d_364191.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16d_364192.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16d_364193.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16d_364194.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16d_364195.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16d_364196.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16e_364184.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16e_364185.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16e_364186.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16e_364187.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16e_364188.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16e_364189.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16e_364190.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16e_364191.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16e_364192.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16e_364193.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16e_364194.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16e_364195.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Wtaunu_MC16e_364196.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Zllgamma_MC16a_364504.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Zllgamma_MC16a_364509.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Zllgamma_MC16a_364514.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Zllgamma_MC16d_364504.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Zllgamma_MC16d_364509.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Zllgamma_MC16d_364514.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Zllgamma_MC16e_364504.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Zllgamma_MC16e_364509.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Zllgamma_MC16e_364514.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Znunugamma2jEWK_MC16a.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Znunugamma2jEWK_MC16d.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Znunugamma2jEWK_MC16e.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Znunugamma2jQCD_MC16a.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Znunugamma2jQCD_MC16d.root",
      "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Znunugamma2jQCD_MC16e.root" };


 void R_factor_data(){
   SetAtlasStyle();

   double sum_BE = 0, sum_DF = 0, sum_E = 0, sum_F = 0, R_sum = 0, del_R_sum = 0;
   double sum_err_BE = 0, sum_err_DF = 0, sum_err_E = 0, sum_err_F = 0;
   TString PhotonIsolationName = "FixedCutTight_Tight";
   bool LoosePrime2 = true;
   bool LoosePrime3 = false;
   bool LoosePrime4 = false;
   bool LoosePrime5 = false;
   //TString PhotonIsolationName = "FixedCutTightCaloOnly";
   //TString  PhotonIsolationName = "FixedCutLoose";



   for(int i = 0; i<111; i++){

     char ftempname[111]{};
     sprintf( ftempname, "%s", fname[i] );
     TFile *file = new TFile(ftempname, "READ");
     cout<<ftempname<<endl;

   double sum_of_weights_bk_xAOD, sumw_MC16a = 0, weight, sum = 0, ph_pt, sum_koef = 0, koef;
   double ph_iso_pt, ph_iso_et40, ph_z_point, metTST_pt, ph_iso_et20;
   UInt_t ph_isem, n_ph, n_mu, n_e_medium, n_jets;
   Int_t mc_ph_type;
   TTree *tree_MC_sw = (TTree*)file->Get("output_tree_sw");
   TTree *tree = (TTree*)file->Get("output_tree");
   TTree *tree_norm = (TTree*)file->Get("norm_tree");
   tree_MC_sw->SetBranchAddress("sum_of_weights_bk_xAOD", &sum_of_weights_bk_xAOD);
   tree->SetBranchAddress("weight",&weight);
   tree->SetBranchAddress("ph_pt",&ph_pt);
   tree->SetBranchAddress("ph_iso_et40", &ph_iso_et40);
   tree->SetBranchAddress("ph_iso_et20", &ph_iso_et20);
   tree->SetBranchAddress("ph_iso_pt", &ph_iso_pt);
   tree->SetBranchAddress("weight", &weight);
   tree->SetBranchAddress("n_ph", &n_ph);
   tree->SetBranchAddress("n_mu", &n_mu);
   tree->SetBranchAddress("n_jet", &n_jets);
   tree->SetBranchAddress("metTST_pt", &metTST_pt);
   tree->SetBranchAddress("n_e_looseBL", &n_e_medium);
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

    sum_koef = tree_norm->GetEntry();
    cout<<"SUM_KOEF = "<<sum_koef<<endl;
    //sum_koef = 0.007754;

    double test_koef;
    for(int i = 0; i < 1; i++){
      tree_norm->GetEntry(i);
      cout<<"koef from tree = "<<koef<<endl;
      sum_koef = koef;
    }
    cout<<"TEST KOEF = "<<test_koef<<endl;



   //cout<<"sumw_MC16a = "<<sumw_MC16a<<endl;
   //cout<<"weight = "<<sum_koef<<endl;

   TH1F *hist_BE = new TH1F ("hist_BE", "hist_BE", 100, -100, 10000);
   TH1F *hist_DF = new TH1F ("hist_DF", "hist_DF", 100, -100, 10000);
   TH1F *hist_E = new TH1F ("hist_E", "hist_E", 100, -100, 10000);
   TH1F *hist_F = new TH1F ("hist_F", "hist_F", 100, -100, 10000);


   //LoosePrime2 = ph_isem & 0x27fc01;
   //LoosePrime3 = ph_isem & 0x25fc01;
   //LoosePrime4 = ph_isem & 0x5fc01;
   //LoosePrime5 = ph_isem & 0x1fc01;

   Double_t lumi_mc16a = 36214.96;
   Double_t lumi_mc16d = 44307.4;
   Double_t lumi_mc16e = 58450.1;

    //topoetcone40 < 0.022 pT + 2.45
    //Track isolation - ptcone20/pT < 0.05

  if(LoosePrime2){
  for(int i = 0; i < N; i++){

     tree->GetEntry(i);
     if(ph_iso_pt/ph_pt >= 0.05 || fabs(ph_z_point)>=250 || fabs(weight)>=100) continue;
     if(ph_pt <= 150) continue;
     if(metTST_pt <= 120) continue;
     if(n_ph !=1 || n_mu !=0 || n_e_medium != 0 ) continue;
     TString new_ftempname = TString(ftempname);
     if(new_ftempname.Contains("MC16a")){
       if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && ph_isem == 0  ) hist_BE->Fill(ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
       else if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && (ph_isem != 0 && (ph_isem & 0x27fc01) == 0 ) ) hist_DF->Fill(ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
       else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem == 0) ) hist_E->Fill(ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
       else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem != 0 && (ph_isem & 0x27fc01) == 0 ) ) hist_F->Fill(ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
     }
    else if(new_ftempname.Contains("MC16d")){
       if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && ph_isem == 0  ) hist_BE->Fill(ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
       else if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && (ph_isem != 0 && (ph_isem & 0x27fc01) == 0 ) ) hist_DF->Fill(ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
       else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem == 0) ) hist_E->Fill(ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
       else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem != 0 && (ph_isem & 0x27fc01) == 0 ) ) hist_F->Fill(ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
    }
    else if(new_ftempname.Contains("MC16e")){
       if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && ph_isem == 0 ) hist_BE->Fill(ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
       else if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && (ph_isem != 0 && (ph_isem & 0x27fc01) == 0 )) hist_DF->Fill(ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
       else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem == 0)) hist_E->Fill(ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
       else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem != 0 && (ph_isem & 0x27fc01) == 0 )) hist_F->Fill(ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
    }

    }
  }
  else if(LoosePrime3){
    for(int i = 0; i < N; i++){

       tree->GetEntry(i);
       if(ph_iso_pt/ph_pt >= 0.05 || fabs(ph_z_point)>=250 || fabs(weight)>=100) continue;
       if(ph_pt <= 150) continue;
       if(metTST_pt <= 120) continue;
       if(n_ph !=1 || n_mu !=0 || n_e_medium != 0 ) continue;
       TString new_ftempname = TString(ftempname);
       if(new_ftempname.Contains("MC16a")){
         if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && ph_isem == 0  ) hist_BE->Fill(ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
         else if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && (ph_isem != 0 && (ph_isem & 0x25fc01) == 0 ) ) hist_DF->Fill(ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
         else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem == 0) ) hist_E->Fill(ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
         else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem != 0 && (ph_isem & 0x25fc01) == 0 ) ) hist_F->Fill(ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
       }
      else if(new_ftempname.Contains("MC16d")){
         if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && ph_isem == 0  ) hist_BE->Fill(ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
         else if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && (ph_isem != 0 && (ph_isem & 0x25fc01) == 0 ) ) hist_DF->Fill(ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
         else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem == 0) ) hist_E->Fill(ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
         else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem != 0 && (ph_isem & 0x25fc01) == 0 ) ) hist_F->Fill(ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
      }
      else if(new_ftempname.Contains("MC16e")){
         if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && ph_isem == 0 ) hist_BE->Fill(ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
         else if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && (ph_isem != 0 && (ph_isem & 0x25fc01) == 0 )) hist_DF->Fill(ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
         else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem == 0)) hist_E->Fill(ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
         else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem != 0 && (ph_isem & 0x25fc01) == 0 )) hist_F->Fill(ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
      }

      }
    }

    else if(LoosePrime4){
      for(int i = 0; i < N; i++){

         tree->GetEntry(i);
         if(ph_iso_pt/ph_pt >= 0.05 || fabs(ph_z_point)>=250 || fabs(weight)>=100) continue;
         if(ph_pt <= 150) continue;
         if(metTST_pt <= 120) continue;
         if(n_ph !=1 || n_mu !=0 || n_e_medium != 0 ) continue;
         TString new_ftempname = TString(ftempname);
         if(new_ftempname.Contains("MC16a")){
           if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && ph_isem == 0  ) hist_BE->Fill(ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
           else if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && (ph_isem != 0 && (ph_isem & 0x5fc01) == 0 ) ) hist_DF->Fill(ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
           else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem == 0) ) hist_E->Fill(ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
           else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem != 0 && (ph_isem & 0x5fc01) == 0 ) ) hist_F->Fill(ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
         }
        else if(new_ftempname.Contains("MC16d")){
           if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && ph_isem == 0  ) hist_BE->Fill(ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
           else if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && (ph_isem != 0 && (ph_isem & 0x5fc01) == 0 ) ) hist_DF->Fill(ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
           else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem == 0) ) hist_E->Fill(ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
           else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem != 0 && (ph_isem & 0x5fc01) == 0 ) ) hist_F->Fill(ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
        }
        else if(new_ftempname.Contains("MC16e")){
           if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && ph_isem == 0 ) hist_BE->Fill(ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
           else if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && (ph_isem != 0 && (ph_isem & 0x5fc01) == 0 )) hist_DF->Fill(ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
           else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem == 0)) hist_E->Fill(ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
           else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem != 0 && (ph_isem & 0x5fc01) == 0 )) hist_F->Fill(ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
        }

        }
      }

      else if(LoosePrime5){
        for(int i = 0; i < N; i++){

           tree->GetEntry(i);
           if(ph_iso_pt/ph_pt >= 0.05 || fabs(ph_z_point)>=250 || fabs(weight)>=100) continue;
           if(ph_pt <= 150) continue;
           if(metTST_pt <= 120) continue;
           if(n_ph !=1 || n_mu !=0 || n_e_medium != 0 ) continue;
           TString new_ftempname = TString(ftempname);
           if(new_ftempname.Contains("MC16a")){
             if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && ph_isem == 0  ) hist_BE->Fill(ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
             else if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && (ph_isem != 0 && (ph_isem & 0x1fc01) == 0 ) ) hist_DF->Fill(ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
             else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem == 0) ) hist_E->Fill(ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
             else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem != 0 && (ph_isem & 0x1fc01) == 0 ) ) hist_F->Fill(ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
           }
          else if(new_ftempname.Contains("MC16d")){
             if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && ph_isem == 0  ) hist_BE->Fill(ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
             else if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && (ph_isem != 0 && (ph_isem & 0x1fc01) == 0 ) ) hist_DF->Fill(ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
             else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem == 0) ) hist_E->Fill(ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
             else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem != 0 && (ph_isem & 0x1fc01) == 0 ) ) hist_F->Fill(ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
          }
          else if(new_ftempname.Contains("MC16e")){
             if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && ph_isem == 0 ) hist_BE->Fill(ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
             else if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && (ph_isem != 0 && (ph_isem & 0x1fc01) == 0 )) hist_DF->Fill(ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
             else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem == 0)) hist_E->Fill(ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
             else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem != 0 && (ph_isem & 0x1fc01) == 0 )) hist_F->Fill(ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
          }

          }
        }



   Double_t errBE, errDF, errE, errF;

   double N_BE = hist_BE->IntegralAndError(-100, 10000, errBE, "");
   double N_DF = hist_DF->IntegralAndError(-100, 10000, errDF, "");
   double N_E = hist_E->IntegralAndError(-100, 10000, errE, "");
   double N_F = hist_F->IntegralAndError(-100, 10000, errF, "");



   double R;
   R = N_BE*N_F/(N_E*N_DF);

   cout<<"N_BE = "<<N_BE<<" +- "<<errBE<<endl;
   cout<<"N_DF = "<<N_DF<<" +- "<<errDF<<endl;
   cout<<"N_E = "<<N_E<<" +- "<<errE<<endl;
   cout<<"N_F = "<<N_F<<" +- "<<errF<<endl;
   double deltaR;
   deltaR = sqrt(pow(errBE*N_F/(N_DF*N_E) , 2) + pow(errF*N_BE/(N_DF*N_E), 2) + pow(errDF*N_F*N_BE/(N_DF*N_E*N_DF), 2) + pow(errE*N_F*N_BE/(N_DF*N_E*N_E) , 2));
   cout<<"R factor = "<<R<<" +- "<<deltaR<<endl;


   /// couting sum of events with weights
   sum_BE += N_BE;
   sum_DF += N_DF;
   sum_E += N_E;
   sum_F += N_F;

   sum_err_BE += errBE*errBE;
   sum_err_DF += errDF*errDF;
   sum_err_E += errE*errE;
   sum_err_F += errF*errF;


   if(i == 0){

   if(LoosePrime2) {
     cout<<"Plus W(enu): "<<endl;
     sum_BE = sum_BE + 312.0 - 6162;
     sum_err_BE = sum_err_BE + 0.25 + (78.4984*78.4984);
     sum_DF = sum_DF + 8.85 - 2189;
     sum_err_DF = sum_err_DF + 0.0004 + (46.7868*46.7868);
     sum_E = sum_E + 91.2 - 5225;
     sum_err_E = sum_err_E + 0.04 + (72.2842*72.2842);
     sum_F = sum_F + 0.02748 - 2437;
     sum_err_F = sum_err_F + 0.0000000025 + (49.366*49.366);

     /*
      loose2
      B-E: 312.0 ± 0.5
      E: 91.2 ± 0.2
      D-F: 8.85 ± 0.02
      F: 0.02748 ± 0.00005
     */
   }

   else if(LoosePrime3) {
     cout<<"Plus W(enu): "<<endl;
     sum_BE = sum_BE + 312.0 - 6162;
     sum_err_BE = sum_err_BE + 0.25 + (78.4984*78.4984);
     sum_DF = sum_DF + 8.85 - 3103;
     sum_err_DF = sum_err_DF + 0.0004 +(55.7046*55.7046);
     sum_E = sum_E + 91.2 - 5225;
     sum_err_E = sum_err_E + 0.04 + (72.2842*72.2842);
     sum_F = sum_F + 3.089 - 3495;
     sum_err_F = sum_err_F + 0.000025 + (59.1185*59.1185);
     /*
     loose'3 :
      B-E: 312.0 ± 0.5
      E: 91.2 ± 0.2
      D-F: 8.85 ± 0.02
      F: 3.089 ± 0.005
     */
   }

   else if(LoosePrime4) {
     cout<<"Plus W(enu): "<<endl;
     sum_BE = sum_BE + 312.0 -6162;
     sum_err_BE = sum_err_BE + 0.25 + (78.4984*78.4984);
     sum_DF = sum_DF + 4.092 - 6333;
     sum_err_DF = sum_err_DF + 0.000049 + (79.5801*79.5801);
     sum_E = sum_E + 91.2 - 5225;
     sum_err_E = sum_err_E + 0.04 + (72.2842*72.2842);
     sum_F = sum_F + 5.860 - 6687;
     sum_err_F = sum_err_F + 0.00010 + (81.7741*81.7741);
     /*
     loose'4 :
      B-E: 312.0 ± 0.5
      E: 91.2 ± 0.2
      D-F: 4.092 ± 0.007
      F: 5.860 ± 0.010
     */
   }
   else if(LoosePrime5) {
        cout<<"Plus W(enu): "<<endl;
        sum_BE = sum_BE + 312.0 - 6162;
        sum_err_BE = sum_err_BE + 0.25 + (78.4984*78.4984);
        sum_DF = sum_DF + 0.949 - 8467;
        sum_err_DF = sum_err_DF + 0.000004 + (92.0163*92.0163);
        sum_E = sum_E + 91.2 - 5225;
        sum_err_E = sum_err_E + 0.04 + (72.2842*72.2842);
        sum_F = sum_F + 15.61 - 9103;
        sum_err_F = sum_err_F + 0.0009 + (95.4096*95.4096);
        /*
        loose'5 :
        B-E: 312.0 ± 0.5
        E: 91.2 ± 0.2
        D-F: 0.949 ± 0.002
        F: 15.61 ± 0.03
        */
      }
    }

    R_sum = sum_BE*sum_F/(sum_E*sum_DF);
    del_R_sum = sqrt(pow(sqrt(sum_err_BE)*sum_F/(sum_DF*sum_E) , 2) + pow(sqrt(sum_err_F)*sum_BE/(sum_DF*sum_E), 2)
      + pow(sqrt(sum_err_DF)*sum_F*sum_BE/(sum_DF*sum_E*sum_DF), 2) + pow(sqrt(sum_err_E)*sum_F*sum_BE/(sum_DF*sum_E*sum_E) , 2));

    cout<<"Photons isolation: "<<PhotonIsolationName<<endl;
    if(LoosePrime2) cout<<"loose'2: "<<endl;
    else if(LoosePrime3) cout<<"loose'3: "<<endl;
    else if(LoosePrime4) cout<<"loose'4: "<<endl;
    else if(LoosePrime5) cout<<"loose'5: "<<endl;
    cout<<"Sum in region B-E = "<<sum_BE<<" +- "<<sqrt(sum_err_BE)<<endl;
    cout<<"Sum in region E = "<<sum_E<<" +- "<<sqrt(sum_err_E)<<endl;
    cout<<"Sum in region D-F = "<<sum_DF<<" +- "<<sqrt(sum_err_DF)<<endl;
    cout<<"Sum in region F = "<<sum_F<<" +- "<<sqrt(sum_err_F)<<endl;


    cout<<"Summing for R factor = "<<R_sum<<" +- "<<del_R_sum<<endl;

  } //конец цикла по файлам

 }
