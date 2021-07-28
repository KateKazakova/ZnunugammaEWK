
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

 void R_factor_data_file(){
  // SetAtlasStyle();

  const char *fname_data = "/home/katet/Programs/Znunugamma/ForDataSamples/user.akurova.MxAOD_Data.root";

    double N_B_data, N_D_data, N_E_data, N_F_data;


    TFile *file_data = new TFile(fname_data, "READ");
    cout<<fname_data<<endl;
    TTree *tree = (TTree*)file_data->Get("output_tree");

    TH1F *hist_B_data = new TH1F ("hist_B_data", "hist_B_data", 100, -100, 10000);
    TH1F *hist_D_data = new TH1F ("hist_D_data", "hist_D_data", 100, -100, 10000);
    TH1F *hist_E_data = new TH1F ("hist_E_data", "hist_E_data", 100, -100, 10000);
    TH1F *hist_F_data = new TH1F ("hist_F_data", "hist_F_data", 100, -100, 10000);


    double sum = 0, ph_pt, errB_data, errD_data, errE_data, errF_data;
    double ph_iso_pt, ph_iso_et40, ph_z_point, metTST_pt, ph_iso_et20;
    UInt_t ph_isem, n_ph, n_mu, n_e_medium;

    tree->SetBranchAddress("ph_pt",&ph_pt);
    tree->SetBranchAddress("ph_iso_et40", &ph_iso_et40);
    tree->SetBranchAddress("ph_iso_et20", &ph_iso_et20);
    tree->SetBranchAddress("ph_iso_pt", &ph_iso_pt);
    tree->SetBranchAddress("n_ph", &n_ph);
    tree->SetBranchAddress("n_mu", &n_mu);
    tree->SetBranchAddress("metTST_pt", &metTST_pt);
    tree->SetBranchAddress("n_e_looseBL", &n_e_medium);
    tree->SetBranchAddress("ph_isem", &ph_isem);
    tree->SetBranchAddress("ph_z_point", &ph_z_point);

    int N_data = (int)tree->GetEntries();

    bool LoosePrime2 = true;
    bool LoosePrime3 = false;
    bool LoosePrime4 = false;
    bool LoosePrime5 = false;

/// начало цикла по дереву данных

    if(LoosePrime2){
    for(int i = 0; i < N_data; i++){

      tree->GetEntry(i);
      if(ph_iso_pt/ph_pt >= 0.05 || fabs(ph_z_point)>=250) continue;
      if(ph_pt <= 150) continue;
      if(metTST_pt <= 120) continue;
      if(n_ph !=1 || n_mu !=0 || n_e_medium != 0) continue;
        if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && ph_isem == 0 ) hist_B_data->Fill(ph_pt, 1.0);
        else if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && (ph_isem != 0 && (ph_isem & 0x27fc01) == 0 ) ) hist_D_data->Fill(ph_pt, 1.0);
        else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem == 0)) hist_E_data->Fill(ph_pt, 1.0);
        else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem != 0 && (ph_isem & 0x27fc01) == 0 )) hist_F_data->Fill(ph_pt, 1.0);
    }



    N_B_data =  hist_B_data->IntegralAndError(-100, 10000, errB_data, "");
    N_D_data =  hist_D_data->IntegralAndError(-100, 10000, errD_data, "");
    N_E_data =  hist_E_data->IntegralAndError(-100, 10000, errE_data, "");
    N_F_data =  hist_F_data->IntegralAndError(-100, 10000, errF_data, "");

    cout<<"Loose'2: "<<endl;
    cout<<"N_B-E_data: "<<N_B_data<<" +- "<<errB_data<<endl;
    cout<<"N_D-F_data: "<<N_D_data<<" +- "<<errD_data<<endl;
    cout<<"N_E_data: "<<N_E_data<<" +- "<<errE_data<<endl;
    cout<<"N_F_data: "<<N_F_data<<" +- "<<errF_data<<endl;
    cout<<"N_data = "<<N_data<<endl;

  } else if(LoosePrime3){
      for(int i = 0; i < N_data; i++){

        tree->GetEntry(i);
        if(ph_iso_pt/ph_pt >= 0.05 || fabs(ph_z_point)>=250) continue;
        if(ph_pt <= 150) continue;
        if(metTST_pt <= 120) continue;
        if(n_ph !=1 || n_mu !=0 || n_e_medium != 0) continue;
          if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && ph_isem == 0 ) hist_B_data->Fill(ph_pt, 1.0);
          else if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && (ph_isem != 0 && (ph_isem & 0x25fc01) == 0 ) ) hist_D_data->Fill(ph_pt, 1.0);
          else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem == 0)) hist_E_data->Fill(ph_pt, 1.0);
          else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem != 0 && (ph_isem & 0x25fc01) == 0 )) hist_F_data->Fill(ph_pt, 1.0);
      }



      N_B_data =  hist_B_data->IntegralAndError(-100, 10000, errB_data, "");
      N_D_data =  hist_D_data->IntegralAndError(-100, 10000, errD_data, "");
      N_E_data =  hist_E_data->IntegralAndError(-100, 10000, errE_data, "");
      N_F_data =  hist_F_data->IntegralAndError(-100, 10000, errF_data, "");

      cout<<"Loose'3: "<<endl;
      cout<<"N_B-E_data: "<<N_B_data<<" +- "<<errB_data<<endl;
      cout<<"N_D-F_data: "<<N_D_data<<" +- "<<errD_data<<endl;
      cout<<"N_E_data: "<<N_E_data<<" +- "<<errE_data<<endl;
      cout<<"N_F_data: "<<N_F_data<<" +- "<<errF_data<<endl;
      cout<<"N_data = "<<N_data<<endl;

    } else if(LoosePrime4){
        for(int i = 0; i < N_data; i++){

          tree->GetEntry(i);
          if(ph_iso_pt/ph_pt >= 0.05 || fabs(ph_z_point)>=250) continue;
          if(ph_pt <= 150) continue;
          if(metTST_pt <= 120) continue;
          if(n_ph !=1 || n_mu !=0 || n_e_medium != 0) continue;
            if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && ph_isem == 0 ) hist_B_data->Fill(ph_pt, 1.0);
            else if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && (ph_isem != 0 && (ph_isem & 0x5fc01) == 0 ) ) hist_D_data->Fill(ph_pt, 1.0);
            else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem == 0)) hist_E_data->Fill(ph_pt, 1.0);
            else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem != 0 && (ph_isem & 0x5fc01) == 0 )) hist_F_data->Fill(ph_pt, 1.0);
        }



        N_B_data =  hist_B_data->IntegralAndError(-100, 10000, errB_data, "");
        N_D_data =  hist_D_data->IntegralAndError(-100, 10000, errD_data, "");
        N_E_data =  hist_E_data->IntegralAndError(-100, 10000, errE_data, "");
        N_F_data =  hist_F_data->IntegralAndError(-100, 10000, errF_data, "");

        cout<<"Loose'4: "<<endl;
        cout<<"N_B-E_data: "<<N_B_data<<" +- "<<errB_data<<endl;
        cout<<"N_D-F_data: "<<N_D_data<<" +- "<<errD_data<<endl;
        cout<<"N_E_data: "<<N_E_data<<" +- "<<errE_data<<endl;
        cout<<"N_F_data: "<<N_F_data<<" +- "<<errF_data<<endl;
        cout<<"N_data = "<<N_data<<endl;
     } else if(LoosePrime5){
         for(int i = 0; i < N_data; i++){

           tree->GetEntry(i);
           if(ph_iso_pt/ph_pt >= 0.05 || fabs(ph_z_point)>=250) continue;
           if(ph_pt <= 150) continue;
           if(metTST_pt <= 120) continue;
           if(n_ph !=1 || n_mu !=0 || n_e_medium != 0) continue;
             if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && ph_isem == 0 ) hist_B_data->Fill(ph_pt, 1.0);
             else if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && (ph_isem != 0 && (ph_isem & 0x1fc01) == 0 ) ) hist_D_data->Fill(ph_pt, 1.0);
             else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem == 0)) hist_E_data->Fill(ph_pt, 1.0);
             else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem != 0 && (ph_isem & 0x1fc01) == 0 )) hist_F_data->Fill(ph_pt, 1.0);
         }



         N_B_data =  hist_B_data->IntegralAndError(-100, 10000, errB_data, "");
         N_D_data =  hist_D_data->IntegralAndError(-100, 10000, errD_data, "");
         N_E_data =  hist_E_data->IntegralAndError(-100, 10000, errE_data, "");
         N_F_data =  hist_F_data->IntegralAndError(-100, 10000, errF_data, "");

         cout<<"Loose'5: "<<endl;
         cout<<"N_B-E_data: "<<N_B_data<<" +- "<<errB_data<<endl;
         cout<<"N_D-F_data: "<<N_D_data<<" +- "<<errD_data<<endl;
         cout<<"N_E_data: "<<N_E_data<<" +- "<<errE_data<<endl;
         cout<<"N_F_data: "<<N_F_data<<" +- "<<errF_data<<endl;
         cout<<"N_data = "<<N_data<<endl;
  }


  }
