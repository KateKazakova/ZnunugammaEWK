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

    TH1F* h_ratio = (TH1F*)hist1->Clone("Clone1");
    h_ratio->Divide(hist2, hist1);


    float rel_uncert_from_2histo, rel_uncert_from_3histo, rel_uncert_from_4histo, rel_uncert_overall;

    int nBins = 0;
    nBins = h_ratio->GetNbinsX();  /// method GetNBinsX() provides get  number of bins in histogram

    for(int i = 1; i<=nBins; i++){

      rel_uncert_from_2histo = (hist2->GetBinContent(i) == 0) ? 0.: hist2->GetBinError(i)/hist2->GetBinContent(i);
      rel_uncert_from_3histo = (hist3->GetBinContent(i) == 0) ? 0.: hist3->GetBinError(i)/hist3->GetBinContent(i);
      rel_uncert_overall = sqrt(pow(rel_uncert_from_2histo,2)+pow(rel_uncert_from_3histo,2));
      h_ratio->SetBinError(i,rel_uncert_overall*h_ratio->GetBinContent(i));

    }

    h_ratio->GetXaxis()->SetTitle(hist1->GetXaxis()->GetTitle());  /// put Xtitle of hist1 to the XTitle h_ratio
    h_ratio->GetYaxis()->SetTitle(TitleY.Data());

    h_ratio->GetXaxis()->SetLabelSize(0.25);
    h_ratio->GetYaxis()->SetLabelSize(0.25);  /// set the size of the font ( <0.15 smaller, >0.15 bigger)

    h_ratio->GetYaxis()->SetTitleOffset(0.46);
    h_ratio->GetXaxis()->SetTitleOffset(1.3);    /// distinction between text (new/old bla bla) and axis
                                               /// more - bigger distin-on, less - smaller dis-on

    h_ratio->GetXaxis()->SetTitleSize(0.15);
    h_ratio->GetYaxis()->SetTitleSize(0.15);    /// the size of the text around the ration plot
                                                /// more - bigger, less

    h_ratio->GetXaxis()->SetTickLength(0.15);   /// the length of the hatches, that have perpendicular position in ratio plot
    h_ratio->GetYaxis()->SetTickLength(0.03);

    h_ratio->SetMarkerSize(1.1);
    h_ratio->SetMarkerColor(kBlack);
  //  h_ratio->SetMarkerStyle(43);
    h_ratio->SetLineColor(kBlack);
    h_ratio->SetLineWidth(3);



    h_ratio->GetYaxis()->SetRangeUser(setRangeA_Y,setRangeB_Y); /// setting the range of Y axis in ration plot

    if(setRangeA_X!=setRangeB_X) {

        h_ratio->GetXaxis()->SetRangeUser(setRangeA_X,setRangeB_X);
         /// setting boundaries of ration plot
        h_ratio->Draw("E");
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
          l->Draw();

    }

    return h_ratio;

 }


  TH1F *DrawThreeHist(TString name, TString band1, TString band2,TString band3, TH1F *hist1, TH1F *hist2,
                      TH1F *hist3, TString TitleX, TString TitleY, bool DrawPlot = false,
                      bool SetNormalization = false, TString TitleY_sub = "ratio"){

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
      hist1->SetLineColor(kBlue+2);
      hist1->SetMarkerSize(1);
      hist1->SetMarkerColor(kBlue+2);
      hist1->SetMarkerStyle(20);
      hist2->SetMarkerSize(1.5);
      hist2->SetMarkerColor(1);
      hist2->SetFillColor(kGreen-7);
      hist3->SetLineWidth(0.);
      hist2->SetLineColor(kGreen-7);
      hist3->SetMarkerColor(kRed);
      hist3->SetFillColor(kAzure);
      hist3->SetMarkerSize(5);
     // hist1->GetXaxis()->SetTitleOffset(1);
      //hist1->GetYaxis()->SetTitleOffset(0.4);

    //  hist1->SetMarkerStyle(43);

      if(SetNormalization){
      float integral1 = hist1->Integral();
      float integral2 = hist2->Integral();
      float integral3 = hist3->Integral();
      hist1->Scale(1./integral1);
      hist2->Scale(1./integral2);
      hist3->Scale(1./integral3);
      }

      hist1->Sumw2();
      hist2->Sumw2();
      hist3->Sumw2();

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


      hist2->Draw("HIST");
      hist3->Draw("HISTsame");
      hist1->Draw("eSame");

      hist1->GetYaxis()->SetRangeUser(0.01, 190);
      hist2->GetYaxis()->SetRangeUser(0.01, 190);
      hist3->GetYaxis()->SetRangeUser(0.01, 190);
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


      TLegend *leg4 = new TLegend(0.7042607,0.6578261,0.839599,0.8330435);
      leg4->SetShadowColor(10);
      leg4->SetBorderSize(0);
      leg4->SetTextSize(0.04517391);
      leg4->SetFillStyle(1002);
      leg4->SetFillColor(10);
      leg4->SetTextFont(42);
      leg4->AddEntry(hist1, Form("%s", band1.Data()),"lp");
      leg4->AddEntry(hist2, Form("%s", band2.Data()),"f");
      leg4->AddEntry(hist3, Form("%s", band3.Data()),"f");

      leg4->Draw();

      TLegend *leg5 = new TLegend(0.41339,0.2334027,0.4721371,0.3752174);
      leg5->SetShadowColor(10);
      leg5->SetBorderSize(0);
      leg5->SetTextSize(0.04404537);
      leg5->SetFillStyle(1001);
      leg5->SetFillColor(10);
      leg5->SetTextFont(42);
      if (name.Contains("loose2")) leg5->AddEntry(hist1,"LoosePrime2","");
      if (name.Contains("loose3")) leg5->AddEntry(hist1,"LoosePrime3","");
      if (name.Contains("loose4")) leg5->AddEntry(hist1,"LoosePrime4","");
      if (name.Contains("loose5")) leg5->AddEntry(hist1,"LoosePrime5","");
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

        DrawRatioPlot(TitleY_sub.Data(), hist1, hist2, hist3, -0.5, 2.0);
      }

      c01->SaveAs(Form("%s.pdf", name.Data()));
      return hist1;


 }


  const char *fname[104] = {
    /*"/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Multijet32.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Multijet33.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Multijet34.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Multijet35.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Multijet36.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Multijet37.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Multijet38.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Multijet39.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Multijet40.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Multijet41.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16a_Multijet42.root",*/
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
    /*"/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Multijet31.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Multijet32.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Multijet33.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Multijet34.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Multijet35.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Multijet36.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Multijet37.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Multijet38.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Multijet39.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Multijet40.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Multijet41.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16d_Multijet42.root",*/
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
    /*"/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Multijet31.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Multijet32.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Multijet33.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Multijet34.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Multijet35.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Multijet36.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Multijet37.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Multijet38.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Multijet39.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Multijet40.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Multijet41.root",
    "/home/katet/Programs/Znunugamma/Samples/user.akurova.MxAOD_MC16e_Multijet42.root",*/
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

    TH1F *hist_iso_calo = new TH1F("hist_iso_calo", "hist_iso_calo", 100, -10, 100);
    TH1F *hist_iso_loose = new TH1F("hist_iso_loose", "hist_iso_loose", 100, -10, 100);
    TH1F *hist_iso_tight = new TH1F("hist_iso_tight", "hist_iso_tight", 100, -10, 100);


 void R_factor_hist(){
   SetAtlasStyle();

   double sum_A = 0, sum_B = 0, sum_C = 0, sum_D = 0, R_sum = 0, del_R_sum = 0;
   double sum_err_A = 0, sum_err_B = 0, sum_err_C = 0, sum_err_D = 0;
   //TString PhotonIsolationName = "FixedCutTight_Tight";
   //TString PhotonIsolationName = "FixedCutTightCaloOnly";
   TString  PhotonIsolationName = "FixedCutLoose";

   for(int i = 0; i<104; i++){

     char ftempname[104]{};
     sprintf( ftempname, "%s", fname[i] );
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

   TH1F *hist_A = new TH1F ("hist_A", "hist_A", 100, -100, 200);
   TH1F *hist_B = new TH1F ("hist_B", "hist_B", 100, -100, 200);
   TH1F *hist_C = new TH1F ("hist_C", "hist_C", 100, -100, 200);
   TH1F *hist_D = new TH1F ("hist_D", "hist_D", 100, -100, 200);


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
       if(mc_ph_type >= 13 && mc_ph_type <= 15) continue;
       if(ph_pt <= 150) continue;
       if(metTST_pt <= 120) continue;
       if(n_ph !=1 || n_mu !=0 || n_e_medium != 0) continue;
       TString new_ftempname = TString(ftempname);
       if(new_ftempname.Contains("MC16a")){
         if((ph_iso_et40 - 0.022*ph_pt) < 2.45 && ph_isem != 0 && (ph_isem & 0x1fc01) == 0 ) hist_iso_tight->Fill(ph_iso_et40 - 0.022*ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
         //else if((ph_iso_et40 - 0.022*ph_pt) > 4.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && ph_isem == 0) hist_B->Fill(ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
         //else if((ph_iso_et40 - 0.022*ph_pt) < 2.45 && (ph_isem != 0 && (ph_isem & 0x27fc01) == 0 )) hist_C->Fill(ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
         //else if((ph_iso_et40 - 0.022*ph_pt) > 4.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem != 0 && (ph_isem & 0x27fc01) == 0 )) hist_D->Fill(ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
       }
      else if(new_ftempname.Contains("MC16d")){
         if((ph_iso_et40 - 0.022*ph_pt) < 2.45 && ph_isem != 0 && (ph_isem & 0x1fc01) == 0 ) hist_iso_tight->Fill(ph_iso_et40 - 0.022*ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
         //else if((ph_iso_et40 - 0.022*ph_pt) > 4.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && ph_isem == 0) hist_B->Fill(ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
         //else if((ph_iso_et40 - 0.022*ph_pt) < 2.45 && (ph_isem != 0 && (ph_isem & 0x27fc01) == 0 )) hist_C->Fill(ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
         //else if((ph_iso_et40 - 0.022*ph_pt) > 4.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem != 0 && (ph_isem & 0x27fc01) == 0 )) hist_D->Fill(ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
      }
      else if(new_ftempname.Contains("MC16e")){
         if((ph_iso_et40 - 0.022*ph_pt) < 2.45 && ph_isem != 0 && (ph_isem & 0x1fc01) == 0 ) hist_iso_tight->Fill(ph_iso_et40 - 0.022*ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
         //else if((ph_iso_et40 - 0.022*ph_pt) > 4.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && ph_isem == 0) hist_B->Fill(ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
         //else if((ph_iso_et40 - 0.022*ph_pt) < 2.45 && (ph_isem != 0 && (ph_isem & 0x27fc01) == 0 )) hist_C->Fill(ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
         //else if((ph_iso_et40 - 0.022*ph_pt) > 4.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem != 0 && (ph_isem & 0x27fc01) == 0 )) hist_D->Fill(ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
  }
}

       for(int i = 0; i < N; i++){

          tree->GetEntry(i);
          if(fabs(ph_z_point)>=250 || fabs(weight)>=100) continue;
          if(mc_ph_type >= 13 && mc_ph_type <= 15) continue;
          if(ph_pt <= 150) continue;
          if(metTST_pt <= 120) continue;
          if(n_ph !=1 || n_mu !=0 || n_e_medium != 0) continue;
          TString new_ftempname = TString(ftempname);
          if(new_ftempname.Contains("MC16a")){
            if((ph_iso_et40 - 0.022*ph_pt) < 2.45 && ph_isem != 0  && (ph_isem & 0x1fc01) == 0 ) hist_iso_calo->Fill(ph_iso_et40 - 0.022*ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
            //else if((ph_iso_et40 - 0.022*ph_pt) > 4.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && ph_isem == 0) hist_B->Fill(ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
            //else if((ph_iso_et40 - 0.022*ph_pt) < 2.45 && (ph_isem != 0 && (ph_isem & 0x1fc01) == 0 )) hist_C->Fill(ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
            //else if((ph_iso_et40 - 0.022*ph_pt) > 4.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem != 0 && (ph_isem & 0x1fc01) == 0 )) hist_D->Fill(ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
          }
         else if(new_ftempname.Contains("MC16d")){
            if((ph_iso_et40 - 0.022*ph_pt) < 2.45 && ph_isem != 0  && (ph_isem & 0x1fc01) == 0 ) hist_iso_calo->Fill(ph_iso_et40 - 0.022*ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
            //else if((ph_iso_et40 - 0.022*ph_pt) > 4.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && ph_isem == 0) hist_B->Fill(ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
            //else if((ph_iso_et40 - 0.022*ph_pt) < 2.45 && (ph_isem != 0 && (ph_isem & 0x1fc01) == 0 )) hist_C->Fill(ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
            //else if((ph_iso_et40 - 0.022*ph_pt) > 4.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem != 0 && (ph_isem & 0x1fc01) == 0 )) hist_D->Fill(ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
         }
         else if(new_ftempname.Contains("MC16e")){
            if((ph_iso_et40 - 0.022*ph_pt) < 2.45 && ph_isem != 0 && (ph_isem & 0x1fc01) == 0 ) hist_iso_calo->Fill(ph_iso_et40 - 0.022*ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
            //else if((ph_iso_et40 - 0.022*ph_pt) > 4.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && ph_isem == 0) hist_B->Fill(ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
            //else if((ph_iso_et40 - 0.022*ph_pt) < 2.45 && (ph_isem != 0 && (ph_isem & 0x1fc01) == 0 )) hist_C->Fill(ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
            //else if((ph_iso_et40 - 0.022*ph_pt) > 4.45 && (ph_iso_et40 - 0.022*ph_pt) < 29.45 && (ph_isem != 0 && (ph_isem & 0x1fc01) == 0 )) hist_D->Fill(ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
         }

         }



       for(int i = 0; i < N; i++){

          tree->GetEntry(i);
          if(ph_iso_pt/ph_pt >= 0.05 || fabs(ph_z_point)>=250 || fabs(weight)>=100) continue;
          if(mc_ph_type >= 13 && mc_ph_type <= 15) continue;
          if(ph_pt <= 150) continue;
          if(metTST_pt <= 120) continue;
          if(n_ph !=1 || n_mu !=0 || n_e_medium != 0) continue;
          TString new_ftempname = TString(ftempname);
          if(new_ftempname.Contains("MC16a")){
            if((ph_iso_et20 - 0.065*ph_pt) < 0.0 && ph_isem != 0 && (ph_isem & 0x1fc01) == 0 ) hist_iso_loose->Fill(ph_iso_et40 - 0.022*ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
            //else if((ph_iso_et20 - 0.065*ph_pt) > 2.0 /*&& (ph_iso_et20 - 0.065*ph_pt) < 27.0 */&& ph_isem == 0 && n_jet >= 0 ) hist_B->Fill(ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
            //else if((ph_iso_et20 - 0.065*ph_pt) < 0.0 && (ph_isem != 0 && (ph_isem & 0x27fc01) == 0 ) && n_jet >= 0 ) hist_C->Fill(ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
            //else if((ph_iso_et20 - 0.065*ph_pt) > 2.0  && n_jet >= 0 /*&& (ph_iso_et20 - 0.065*ph_pt) < 27.0 */&& (ph_isem != 0 && (ph_isem & 0x27fc01) == 0 )) hist_D->Fill(ph_pt, lumi_mc16a*sum_koef*weight/(sumw_MC16a));
          }
         else if(new_ftempname.Contains("MC16d")){
           if((ph_iso_et20 - 0.065*ph_pt) < 0.0 && ph_isem != 0 && (ph_isem & 0x1fc01) == 0 ) hist_iso_loose->Fill(ph_iso_et40 - 0.022*ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
           //else if((ph_iso_et20 - 0.065*ph_pt) > 2.0  && n_jet >= 0 /*&& (ph_iso_et20 - 0.065*ph_pt) < 27.0 */&& ph_isem == 0) hist_B->Fill(ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
           //else if((ph_iso_et20 - 0.065*ph_pt) < 0.0 && (ph_isem != 0 && (ph_isem & 0x27fc01) == 0 ) && n_jet >= 0 ) hist_C->Fill(ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
           //else if((ph_iso_et20 - 0.065*ph_pt) > 2.0  && n_jet >= 0 /*&& (ph_iso_et20 - 0.065*ph_pt) < 27.0 */&& (ph_isem != 0 && (ph_isem & 0x27fc01) == 0 )) hist_D->Fill(ph_pt, lumi_mc16d*sum_koef*weight/(sumw_MC16a));
         }
         else if(new_ftempname.Contains("MC16e")){
           if((ph_iso_et20 - 0.065*ph_pt) < 0.0 && ph_isem != 0 && (ph_isem & 0x1fc01) == 0 ) hist_iso_loose->Fill(ph_iso_et40 - 0.022*ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
           //else if((ph_iso_et20 - 0.065*ph_pt) > 2.0 && n_jet >= 0 /* && (ph_iso_et20 - 0.065*ph_pt) < 27.0*/ && ph_isem == 0) hist_B->Fill(ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
           //else if((ph_iso_et20 - 0.065*ph_pt) < 0.0 && (ph_isem != 0 && (ph_isem & 0x27fc01) == 0 ) && n_jet >= 0 ) hist_C->Fill(ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
           //else if((ph_iso_et20 - 0.065*ph_pt) > 2.0  && n_jet >= 0 /*&& (ph_iso_et20 - 0.065*ph_pt) < 27.0 */&& (ph_isem != 0 && (ph_isem & 0x27fc01) == 0 )) hist_D->Fill(ph_pt, lumi_mc16e*sum_koef*weight/(sumw_MC16a));
         }

         }



/*

   Double_t errA, errB, errC, errD;

   double N_A = hist_A->IntegralAndError(-100, 10000, errA, "");
   double N_B = hist_B->IntegralAndError(-100, 10000, errB, "");
   double N_C = hist_C->IntegralAndError(-100, 10000, errC, "");
   double N_D = hist_D->IntegralAndError(-100, 10000, errD, "");



   double R;
   R = N_A*N_D/(N_C*N_B);

   cout<<"N_A = "<<N_A<<" +- "<<errA<<endl;
   cout<<"N_B = "<<N_B<<" +- "<<errB<<endl;
   cout<<"N_C = "<<N_C<<" +- "<<errC<<endl;
   cout<<"N_D = "<<N_D<<" +- "<<errD<<endl;
   double deltaR;
   deltaR = sqrt(pow(errA*N_D/(N_B*N_C) , 2) + pow(errD*N_A/(N_B*N_C), 2) + pow(errB*N_D*N_A/(N_B*N_C*N_B), 2) + pow(errC*N_D*N_A/(N_B*N_C*N_C) , 2));
   cout<<"R factor = "<<R<<" +- "<<deltaR<<endl;


   /// couting sum of events with weights
   sum_A += N_A;
   sum_B += N_B;
   sum_C += N_C;
   sum_D += N_D;

   sum_err_A += errA*errA;
   sum_err_B += errB*errB;
   sum_err_C += errC*errC;
   sum_err_D += errD*errD;

   cout<<"Photons isolation: "<<PhotonIsolationName<<endl;
   cout<<"loose'3:"<<endl;
   cout<<"Sum in region A = "<<sum_A<<" +- "<<sqrt(sum_err_A)<<endl;
   cout<<"Sum in region B = "<<sum_B<<" +- "<<sqrt(sum_err_B)<<endl;
   cout<<"Sum in region C = "<<sum_C<<" +- "<<sqrt(sum_err_C)<<endl;
   cout<<"Sum in region D = "<<sum_D<<" +- "<<sqrt(sum_err_D)<<endl;
   R_sum = sum_A*sum_D/(sum_C*sum_B);
   del_R_sum = sqrt(pow(sqrt(sum_err_A)*sum_D/(sum_B*sum_C) , 2) + pow(sqrt(sum_err_D)*sum_A/(sum_B*sum_C), 2) + pow(sqrt(sum_err_B)*sum_D*sum_A/(sum_B*sum_C*sum_B), 2) + pow(sqrt(sum_err_C)*sum_D*sum_A/(sum_B*sum_C*sum_C) , 2));

   cout<<"Summing for R factor = "<<R_sum<<" +- "<<del_R_sum<<endl;

*/
  cout<<hist_iso_calo->GetEntries()<<endl;


  DrawThreeHist("loose5", "Loose","CaloOnly", "Tight" ,hist_iso_loose, hist_iso_calo,
                     hist_iso_tight ,"p_{T}, [GeV]", "Events", false,
                    true, "Data/MC");

 }
}
