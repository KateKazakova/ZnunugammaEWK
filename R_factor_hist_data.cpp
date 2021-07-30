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

  TH1F *DrawRatioPlot(TString TitleY, TH1F* hist1, TH1F* hist2, TH1F* hist3, float setRangeA_Y = 0.81,
                         float setRangeB_Y = 1.21, float setRangeA_X = 0., float setRangeB_X = 0.){
                              /// setRangeA_X and setRangeB_X it is a boundaries of ratio plot
                              /// it may not equal to boundaries of main hist, it is reason
                              ///why we use if(setRangeA_X!=setRangeB_X) and if(setRangeA_X==setRangeB_X)

    if(!hist1) {
      cout<<"Something wrong with your histogram!"<<endl;
      exit(1);
    }
    if(!hist2) {
      cout<<"Something wrong with your histogram!"<<endl;
      exit(1);
    }
    if(!hist3) {
      cout<<"Something wrong with your histogram!"<<endl;
      exit(1);
    }

    TH1F* h_ratio = (TH1F*)hist1->Clone("Clone1");
    TH1F* h_ratio2 = (TH1F*)hist3->Clone("Clone2");
    h_ratio->Divide(hist1, hist2);
    h_ratio2->Divide(hist3, hist2);


    float rel_uncert_from_1histo, rel_uncert_from_2histo, rel_uncert_from_3histo, rel_uncert_overall;
    float rel_uncert_from_2histo2, rel_uncert_from_3histo2, rel_uncert_overall2;

    int nBins = 0;
    int nBins2 = 0;
    nBins = h_ratio->GetNbinsX();  /// method GetNBinsX() provides get  number of bins in histogram
    nBins2 = h_ratio2->GetNbinsX();

    for(int i = 1; i<=nBins; i++){

      rel_uncert_from_2histo = (hist2->GetBinContent(i) == 0) ? 0.: hist2->GetBinError(i)/hist2->GetBinContent(i);
      rel_uncert_from_1histo = (hist1->GetBinContent(i) == 0) ? 0.: hist1->GetBinError(i)/hist1->GetBinContent(i);
      rel_uncert_overall = sqrt(pow(rel_uncert_from_2histo,2) + pow(rel_uncert_from_1histo,2));
      h_ratio->SetBinError(i,rel_uncert_overall*h_ratio->GetBinContent(i));
    }
    for(int i = 1; i<=nBins2; i++){

      rel_uncert_from_2histo2 = (hist2->GetBinContent(i) == 0) ? 0.: hist2->GetBinError(i)/hist2->GetBinContent(i);
      rel_uncert_from_3histo2 = (hist3->GetBinContent(i) == 0) ? 0.: hist3->GetBinError(i)/hist3->GetBinContent(i);
      rel_uncert_overall2 = sqrt(pow(rel_uncert_from_2histo2,2) + pow(rel_uncert_from_3histo2,2));
      h_ratio2->SetBinError(i,rel_uncert_overall2*h_ratio2->GetBinContent(i));
    }

    h_ratio->GetXaxis()->SetTitle(hist1->GetXaxis()->GetTitle());  /// put Xtitle of hist1 to the XTitle h_ratio
    h_ratio->GetYaxis()->SetTitle(TitleY.Data());
    h_ratio2->GetXaxis()->SetTitle(hist1->GetXaxis()->GetTitle());  /// put Xtitle of hist1 to the XTitle h_ratio
    h_ratio2->GetYaxis()->SetTitle(TitleY.Data());

    h_ratio->GetXaxis()->SetLabelSize(0.13);
    h_ratio->GetYaxis()->SetLabelSize(0.13);  /// set the size of the font ( <0.15 smaller, >0.15 bigger)

    h_ratio->GetYaxis()->SetTitleOffset(0.4);
    h_ratio->GetXaxis()->SetTitleOffset(1.0);    /// distinction between text (new/old bla bla) and axis
                                               /// more - bigger distin-on, less - smaller dis-on

    h_ratio->GetXaxis()->SetTitleSize(0.15);
    h_ratio->GetYaxis()->SetTitleSize(0.15);    /// the size of the text around the ration plot
                                                /// more - bigger, less

    h_ratio->GetXaxis()->SetTickLength(0.15);   /// the length of the hatches, that have perpendicular position in ratio plot
    h_ratio->GetYaxis()->SetTickLength(0.03);


    h_ratio->SetMarkerSize(1.3);
    h_ratio->SetMarkerColor(kRed);
  //  h_ratio->SetMarkerStyle(43);
    h_ratio->SetLineColor(kRed);
    h_ratio->SetLineWidth(3);

    h_ratio2->SetMarkerSize(1.3);
    h_ratio2->SetMarkerColor(kBlack);
  //  h_ratio->SetMarkerStyle(43);
    h_ratio2->SetLineColor(kBlack);
    h_ratio2->SetLineWidth(3);



    h_ratio->GetYaxis()->SetRangeUser(setRangeA_Y,setRangeB_Y); /// setting the range of Y axis in ration plot
    h_ratio2->GetYaxis()->SetRangeUser(setRangeA_Y,setRangeB_Y);

    if(setRangeA_X!=setRangeB_X) {

        h_ratio->GetXaxis()->SetRangeUser(setRangeA_X,setRangeB_X);
        h_ratio2->GetXaxis()->SetRangeUser(setRangeA_X,setRangeB_X);
         /// setting boundaries of ration plot
        h_ratio->Draw("E");
        h_ratio2->Draw("eSame");

    }


    if (setRangeA_X==setRangeB_X){
          float minX, maxX;
          minX = h_ratio->GetXaxis()->GetXmin();
          maxX = h_ratio->GetXaxis()->GetXmax();
          TLine *l = new TLine(minX, 1., maxX, 1.); /// setting the main line on ratio plot from minX from maxX, min and max range, 1.0 in is angle of line (horizontal)

          l->SetLineColor(kBlack);
          l->SetLineStyle(9);    /// breaking line
          l->SetLineWidth(2);

          h_ratio->Draw("E");
          h_ratio2->Draw("eSame");
          l->Draw();

    } else{
          float minX, maxX;
          minX = h_ratio->GetXaxis()->GetXmin();
          maxX = h_ratio->GetXaxis()->GetXmax();
          TLine *l = new TLine(minX, 1., maxX, 1.);

          l->SetLineColor(kBlack);
          l->SetLineStyle(9);
          l->SetLineWidth(2);
          h_ratio->Draw("E");
          h_ratio2->Draw("eSame");
          l->Draw();

    }

    return h_ratio;

 }


  TH1F *DrawThreeHist(TString name, TString band1, TString band2, TString band3, TH1F *hist1, TH1F *hist2, TH1F *hist3,
                        TString TitleX, TString TitleY,
                      bool SetNormalization = false, bool DrawPlot = false, TString TitleY_sub = "ratio"){

      if(!hist1) {
        cout<<"Something wrong with you histogram!"<<endl;
        exit(1);
      }
      if(!hist2) {
        cout<<"Something wrong with you histogram!"<<endl;
        exit(1);
      }
      if(!hist3) {
        cout<<"Something wrong with you histogram!"<<endl;
        exit(1);
      }

      /// the size of the main canvas (ration + hist)
      TCanvas *c01 = new TCanvas(name.Data(), name.Data(), 147, 100, 780, 665);
      /// the size of the hist plot
      TPad *c1 = new TPad("c1", "c1",0.007905138,0.2347107,0.9891304,0.9950413);
      /// the size of the ratio plot
      TPad *c2 = new TPad("c2", "c2",0.008814887,0.006589786,0.9892262,0.2652389);

      float minx = hist1->GetXaxis()->GetXmin();
      float maxX = hist1->GetXaxis()->GetXmax();
      float minY = hist1->GetYaxis()->GetXmin();
      float maxY = hist1->GetYaxis()->GetXmax();


      if (DrawPlot){
        c1->Draw();
        c1->cd();
        ///set the size of the hist plot
        c1->SetLeftMargin(0.1596366);
        c1->SetRightMargin(0.05080911);
        c1->SetTopMargin(0.04981374);
        c1->SetBottomMargin(0.0448469);
      }

       /// set parameters of the histograms (color, width ...)
      hist1->SetLineWidth(3);
      hist1->SetLineColor(kRed);
      hist1->SetMarkerSize(1.4);
      hist1->SetMarkerColor(kRed);
      hist1->SetMarkerStyle(20);

      hist2->SetLineWidth(3);
      hist2->SetLineColor(kBlue+2);
      hist2->SetMarkerSize(1.4);
      hist2->SetMarkerColor(kBlue+2);
      hist2->SetMarkerStyle(20);

      hist3->SetLineWidth(3);
      hist3->SetLineColor(kBlack);
      hist3->SetMarkerSize(1.4);
      hist3->SetMarkerColor(kBlack);
      hist3->SetMarkerStyle(20);


      if(SetNormalization){
      float integral1 = hist1->Integral();
      float integral2 = hist2->Integral();
      float integral3 = hist3->Integral();
      hist1->Scale(1./integral1);
      hist2->Scale(1./integral2);
      hist3->Scale(1./integral3);
      }

      hist2->GetXaxis()->SetLabelSize(0.045);
      hist2->GetYaxis()->SetLabelSize(0.045);
      hist2->GetYaxis()->SetTitleOffset(1.4);
      hist2->GetXaxis()->SetTitleOffset(1.3);
      hist2->GetXaxis()->SetTitleSize(0.04);
      hist2->GetYaxis()->SetTitleSize(0.05);

      hist1->GetXaxis()->SetTitle(TitleX.Data());
      hist1->GetYaxis()->SetTitle(TitleY.Data());
      hist2->GetXaxis()->SetTitle(TitleX.Data());
      hist2->GetYaxis()->SetTitle(TitleY.Data());
      hist3->GetXaxis()->SetTitle(TitleX.Data());
      hist3->GetYaxis()->SetTitle(TitleY.Data());
      //hist1->GetYaxis()->SetRangeUser(0.0, 250.0);


      hist2->Draw("");
      hist1->Draw("Same");
      hist3->Draw("eSame");

      Double_t y_axis = 0.3, x_axis = -0.01;

      hist1->GetYaxis()->SetRangeUser(x_axis, y_axis);
      hist2->GetYaxis()->SetRangeUser(x_axis, y_axis);
      hist3->GetYaxis()->SetRangeUser(x_axis, y_axis);
      //hist2->GetYaxis()->SetRangeUser(0.0, 250.0);

       /// setting the legend
      TLegend *leg = new TLegend(0.1729323,0.8330435,0.2230576,0.8678261);
      leg->SetShadowColor(10);
      leg->SetBorderSize(0);    /// without borders
      leg->SetTextSize(0.052);
      leg->SetTextFont(42);
      leg->SetFillColor(10);   /// white color
      leg->AddEntry(hist1,"#sqrt{s}=13 TeV","");
      leg->Draw();

      TLegend *leg1 = new TLegend(0.7042607,0.6578261,0.839599,0.8330435);
      leg1->SetShadowColor(10);
      leg1->SetBorderSize(0);
      leg1->SetTextSize(0.05217391);
      leg1->SetFillStyle(1002);
      leg1->SetFillColor(10);
      ATLASLabel(0.19,0.90,"Internal");
     // leg1->AddEntry(hist2, Form("%s", band1.Data()),"f");
     // leg1->AddEntry(hist3, Form("%s", band2.Data()),"f");
     //  leg1->AddEntry(hist1, Form("%s", band3.Data()),"lp");
      leg1->Draw();


      TLegend *leg4 = new TLegend(0.6626333,0.6955674,0.8512648,0.8679203);
      leg4->SetShadowColor(10);
      leg4->SetBorderSize(0);
      leg4->SetTextSize(0.04817391);
      leg4->SetFillStyle(1002);
      leg4->SetFillColor(10);
      leg4->SetTextFont(42);
      leg4->AddEntry(hist1, Form("%s", band1.Data()),"lp");
      leg4->AddEntry(hist2, Form("%s", band2.Data()),"lp");
      leg4->AddEntry(hist3, Form("%s", band3.Data()),"lp");

      leg4->Draw();

      TLegend *leg5 = new TLegend(0.1801169,0.7315777,0.2390642,0.8300651);
      leg5->SetShadowColor(10);
      leg5->SetBorderSize(0);
      leg5->SetTextSize(0.04404537);
      leg5->SetFillStyle(1001);
      leg5->SetFillColor(10);
      leg5->SetTextFont(42);
      if (name.Contains("Tight")) leg5->AddEntry(hist1,"FixedCutTight","");
      if (name.Contains("CaloOnly")) leg5->AddEntry(hist1,"FixedCutTightCaloOnly","");
      if (name.Contains("Loose")) leg5->AddEntry(hist1,"FixedCutLoose","");
      leg5->Draw();




      if (DrawPlot){
        c1->Modified();
        c01->cd();
        c2->Draw();
        c2->cd();
        c2->Range(-18.10151,-1.965632,32.61929,2.637034);
        c2->SetLeftMargin(0.1597275);
        c2->SetRightMargin(0.05164129);
        c2->SetTopMargin(0.0437885);
        c2->SetBottomMargin(0.3381574);

        DrawRatioPlot(TitleY_sub.Data(), hist1, hist2, hist3, -1.0, 6.0);
      }

      c01->SaveAs(Form("%s.pdf", name.Data()));
      return hist1;


 }


  const char *fname[] = {
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Zj364222.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Zj364223.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Zj366011.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Zj366012.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Zj366013.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Zj366014.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Zj366015.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Zj366016.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Zj366017.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Zj366020.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Zj366021.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Zj366022.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Zj366023.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Zj366024.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Zj366025.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Zj366026.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Zj366029.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Zj366030.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Zj366031.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Zj366032.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Zj366033.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Zj366034.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Zj366035.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Zj364222.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Zj364223.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Zj366011.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Zj366012.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Zj366013.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Zj366014.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Zj366015.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Zj366016.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Zj366017.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Zj366020.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Zj366021.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Zj366022.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Zj366023.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Zj366024.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Zj366025.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Zj366026.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Zj366029.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Zj366030.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Zj366031.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Zj366032.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Zj366033.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Zj366034.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Zj366035.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Zj364222.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Zj364223.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Zj366011.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Zj366012.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Zj366013.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Zj366014.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Zj366015.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Zj366016.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Zj366017.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Zj366020.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Zj366021.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Zj366022.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Zj366023.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Zj366024.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Zj366025.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Zj366026.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Zj366029.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Zj366030.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Zj366031.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Zj366032.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Zj366033.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Zj366034.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Zj366035.root"};

    const char *fname_mk_data[111] = {
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


    TH1F *hist_iso_tight_mk = new TH1F("hist_iso_tight_mk", "hist_iso_tight_mk", 29, -12, 46);  // Zj
    TH1F *hist_iso_loose_mk = new TH1F("hist_iso_loose_mk", "hist_iso_loose_mk", 29, -12, 46);  //Zj
    TH1F *hist_iso_loose_temp_mk = new TH1F("hist_iso_loose_temp_mk", "hist_iso_loose_temp_mk", 29, -12, 46);
    TH1F *hist_iso_loose_temp_data = new TH1F("hist_iso_loose_temp_data", "hist_iso_loose_temp_data", 29, -12, 46);


 void R_factor_hist_data(){
   SetAtlasStyle();

   double sum_A = 0, sum_B = 0, sum_C = 0, sum_D = 0, R_sum = 0, del_R_sum = 0;
   double sum_err_A = 0, sum_err_B = 0, sum_err_C = 0, sum_err_D = 0;
   //TString PhotonIsolationName = "FixedCutTight_Tight";
   //TString PhotonIsolationName = "FixedCutTightCaloOnly";
   //TString  PhotonIsolationName = "FixedCutLoose";

   for(int j = 0; j<69; j++){

     char ftempname[105]{};
     sprintf( ftempname, "%s", fname[j] );
     TFile *file = new TFile(ftempname, "READ");
     cout<<ftempname<<endl;

   double sum_of_weights_bk_xAOD, sumw_MC16a = 0, weight, sum = 0, ph_pt, sum_koef = 0, koef;
   double ph_iso_pt, ph_iso_et40, ph_z_point, metTST_pt, ph_iso_et20, E_miss;
   UInt_t ph_isem, n_ph, n_mu, n_e_medium;
   Int_t mc_ph_type;
   TTree *tree_MC_sw = (TTree*)file->Get("output_tree_sw");
   TTree *tree = (TTree*)file->Get("output_tree");
   TTree *tree_norm = (TTree*)file->Get("norm_tree");
   tree_MC_sw->SetBranchAddress("sum_of_weights_bk_xAOD",&sum_of_weights_bk_xAOD);
   tree->SetBranchAddress("weight",&weight);
   tree->SetBranchAddress("ph_pt",&ph_pt);
   tree->SetBranchAddress("ph_iso_et40", &ph_iso_et40);
   tree->SetBranchAddress("ph_iso_et20", &ph_iso_et20);
   tree->SetBranchAddress("ph_iso_pt", &ph_iso_pt);
   tree->SetBranchAddress("weight", &weight);
   tree->SetBranchAddress("n_ph", &n_ph);
   tree->SetBranchAddress("n_mu", &n_mu);
   tree->SetBranchAddress("metTST_pt", &metTST_pt);
   tree->SetBranchAddress("n_e_looseBL", &n_e_medium);
   tree->SetBranchAddress("ph_isem", &ph_isem);
   tree->SetBranchAddress("ph_z_point", &ph_z_point);
   tree->SetBranchAddress("mc_ph_type", &mc_ph_type);
   tree->SetBranchAddress("metTSTsignif", &E_miss);
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

   //LoosePrime2 = ph_isem & 0x27fc01;
   //LoosePrime3 = ph_isem & 0x25fc01;
   //LoosePrime4 = ph_isem & 0x5fc01;
   //LoosePrime5 = ph_isem & 0x1fc01;

   Double_t lumi_mc16a = 36214.96;
   Double_t lumi_mc16d = 44307.4;
   Double_t lumi_mc16e = 58450.1;



   for(int i = 0; i < N; i++){
     tree->GetEntry(i);
       if(ph_iso_pt/ph_pt >= 0.05 || fabs(ph_z_point)>=250 || fabs(weight)>=100) continue;
       if(ph_pt <= 150) continue;
       if(metTST_pt <= 120) continue;
       if(n_ph !=1 || n_mu !=0 || n_e_medium != 0) continue;
       TString new_ftempname = TString(ftempname);
       if(new_ftempname.Contains("MC16a")){
         if(ph_isem == 0) hist_iso_tight_mk->Fill(ph_iso_et40 - 0.022*ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
         //else if(ph_isem == 0) hist_iso_tight_mk->Fill(ph_iso_et40 - 0.022*ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
         else if(ph_isem != 0 && (ph_isem & 0x1fc01) == 0 ) hist_iso_loose_mk->Fill(ph_iso_et40 - 0.022*ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
         //else if(ph_isem != 0 && (ph_isem & 0x27fc01) == 0 )) hist_iso_loose_mk->Fill(ph_iso_et40 - 0.022*ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
       }
      else if(new_ftempname.Contains("MC16d")){
         if(ph_isem == 0 ) hist_iso_tight_mk->Fill(ph_iso_et40 - 0.022*ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
         //else if( (ph_isem == 0) hist_iso_tight_mk->Fill(ph_iso_et40 - 0.022*ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
         else if(((ph_isem & 0x1fc01) == 0 )) hist_iso_loose_mk->Fill(ph_iso_et40 - 0.022*ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
         //else if((ph_isem != 0 && (ph_isem & 0x27fc01) == 0 )) hist_iso_loose_mk->Fill(ph_iso_et40 - 0.022*ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
      }
      else if(new_ftempname.Contains("MC16e")){
         if(ph_isem == 0) hist_iso_tight_mk->Fill(ph_iso_et40 - 0.022*ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
         //else if( ph_isem == 0) hist_iso_tight_mk->Fill(ph_iso_et40 - 0.022*ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
         else if(ph_isem != 0 && (ph_isem & 0x1fc01) == 0 ) hist_iso_loose_mk->Fill(ph_iso_et40 - 0.022*ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
         //else if(ph_isem != 0 && (ph_isem & 0x27fc01) == 0 ) hist_iso_loose_mk->Fill(ph_iso_et40 - 0.022*ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
  }
}

  cout<<hist_iso_tight_mk->GetEntries()<<endl;

                  //  if(i == 0) break;

  file->Close();
  cout<<"j = "<<j<<endl;
 }


   for(int i = 0; i<111; i++){

     char ftempname[111]{};
     sprintf( ftempname, "%s", fname_mk_data[i] );
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

    for(int i = 0; i < 1; i++){
      tree_norm->GetEntry(i);
      sum_koef = koef;
    }


   TH1F *hist_BE = new TH1F ("hist_BE", "hist_BE", 100, -100, 10000);
   TH1F *hist_DF = new TH1F ("hist_DF", "hist_DF", 100, -100, 10000);
   TH1F *hist_E = new TH1F ("hist_E", "hist_E", 100, -100, 10000);
   TH1F *hist_F = new TH1F ("hist_F", "hist_F", 100, -100, 10000);

   TH1F *hist_B = new TH1F ("hist_B", "hist_B", 100, -100, 10000);
   TH1F *hist_D = new TH1F ("hist_D", "hist_D", 100, -100, 10000);


   //LoosePrime2 = ph_isem & 0x27fc01;
   //LoosePrime3 = ph_isem & 0x25fc01;
   //LoosePrime4 = ph_isem & 0x5fc01;
   //LoosePrime5 = ph_isem & 0x1fc01;

   Double_t lumi_mc16a = 36214.96;
   Double_t lumi_mc16d = 44307.4;
   Double_t lumi_mc16e = 58450.1;

    //topoetcone40 < 0.022 pT + 2.45
    //Track isolation - ptcone20/pT < 0.05

  for(int i = 0; i < N; i++){

     tree->GetEntry(i);
     if(ph_iso_pt/ph_pt >= 0.05 || fabs(ph_z_point)>=250 || fabs(weight)>=100) continue;
     if(ph_pt <= 150) continue;
     if(metTST_pt <= 120) continue;
     if(n_ph !=1 || n_mu !=0 || n_e_medium != 0 ) continue;
     TString new_ftempname = TString(ftempname);
     if(new_ftempname.Contains("MC16a")){
       if(ph_isem == 0  ) hist_BE->Fill(ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
       else if((ph_isem != 0 && (ph_isem & 0x1fc01) == 0 ) ) hist_iso_loose_temp_mk->Fill((ph_iso_et40 - 0.022*ph_pt), lumi_mc16a*sum_koef*weight/(sumw_MC16a));
       //else if((ph_isem == 0) ) hist_E->Fill(ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
       //else if((ph_isem != 0 && (ph_isem & 0x27fc01) == 0 ) ) hist_iso_loose_temp_mk->Fill((ph_iso_et40 - 0.022*ph_pt), lumi_mc16a*sum_koef*weight/(sumw_MC16a));

     }
    else if(new_ftempname.Contains("MC16d")){
      if(ph_isem == 0  ) hist_BE->Fill(ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
      else if((ph_isem != 0 && (ph_isem & 0x1fc01) == 0 ) ) hist_iso_loose_temp_mk->Fill((ph_iso_et40 - 0.022*ph_pt), lumi_mc16d*sum_koef*weight/(sumw_MC16a));
      //else if((ph_isem == 0) ) hist_E->Fill(ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
      //else if((ph_isem != 0 && (ph_isem & 0x27fc01) == 0 ) ) hist_iso_loose_temp_mk->Fill((ph_iso_et40 - 0.022*ph_pt), lumi_mc16a*sum_koef*weight/(sumw_MC16a));
    }
    else if(new_ftempname.Contains("MC16e")){
      if(ph_isem == 0  ) hist_BE->Fill(ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
      else if((ph_isem != 0 && (ph_isem & 0x1fc01) == 0 ) ) hist_iso_loose_temp_mk->Fill((ph_iso_et40 - 0.022*ph_pt), lumi_mc16e*sum_koef*weight/(sumw_MC16a));
      //else if((ph_isem == 0) ) hist_E->Fill(ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
      //else if((ph_isem != 0 && (ph_isem & 0x27fc01) == 0 ) ) hist_iso_loose_temp_mk->Fill((ph_iso_et40 - 0.022*ph_pt), lumi_mc16a*sum_koef*weight/(sumw_MC16a));
    }

    }



  file->Close();
  cout<<"i = "<<i<<endl;
  } //конец цикла по файлам

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

/// начало цикла по дереву данных

    for(int i = 0; i < N_data; i++){

      tree->GetEntry(i);
      if(ph_iso_pt/ph_pt >= 0.05 || fabs(ph_z_point)>=250) continue;
      if(ph_pt <= 150) continue;
      if(metTST_pt <= 120) continue;
      if(n_ph !=1 || n_mu !=0 || n_e_medium != 0) continue;
      //if((ph_iso_et40 - 0.022*ph_pt) < 11.45 && (ph_iso_et40 - 0.022*ph_pt) > 4.45 && ph_isem == 0  ) hist_BE->Fill(ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
      if((ph_isem != 0 && (ph_isem & 0x1fc01) == 0 ) ) hist_iso_loose_temp_mk->Fill((ph_iso_et40 - 0.022*ph_pt), 1.0);
      //else if((ph_iso_et40 - 0.022*ph_pt) > 11.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem == 0) ) hist_E->Fill(ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
      //else if((ph_iso_et40 - 0.022*ph_pt) > 2.45  && (ph_isem != 0 && (ph_isem & 0x27fc01) == 0 ) ) hist_iso_loose_temp_mk->Fill((ph_iso_et40 - 0.022*ph_pt), 1.0);

  }
  TH1F *hist_iso_loose_data = new TH1F(*hist_iso_loose_temp_data);
  hist_iso_loose_data->Add(hist_iso_loose_temp_mk, -1.0);
  hist_iso_loose_data = new TH1F(*hist_iso_loose_data);

  //fname_data->Close();

 DrawThreeHist("Tight", "Tight(MC)", "Loose'5(MC)" , "Loose'5(Data)", hist_iso_tight_mk,
                   hist_iso_loose_mk , hist_iso_loose_data, "E_{T}^{cone40} - 0.022 p_{T}^{#gamma}, [GeV]", "Events", true,
                  true, "Ratio");

}
