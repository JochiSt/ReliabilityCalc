{
    gROOT -> Reset();

    gStyle -> SetOptStat(0);

    ifstream input;
    input.open("reliability_PowerBoard_FMD.txt");

    TH2F* histoFMD = new TH2F("histoFMD", "FMD FIT", 14, .5, 14.5, 100, 0, 15);
    TH2F* histoALL = new TH2F("histoALL", "ALL FIT", 14, .5, 14.5, 100, 0, 15);

    TH1F* histoTotFMD = new TH1F("histoTotFMD", "Total FIT FMD", 240, 0, 60);
    TH1F* histoTotALL = new TH1F("histoTotALL", "Total FIT ALL", 240, 0, 60);

    double FITset, FITfmd, FITall;
    while(true){
	input >> FITset >> FITall >> FITfmd;
	if(!input.good()) break;

	if(FITset < 0){
	    histoTotFMD -> Fill(FITfmd);
	    histoTotALL -> Fill(FITall);
	}
	
	histoFMD -> Fill(FITset, FITfmd);
	histoALL -> Fill(FITset, FITall);
    }

    TCanvas* c1 = new TCanvas("c1", "MC FIT", 800, 600);
    c1 -> Divide(2,1);
    c1 -> cd(1);
    c1 -> cd(1) -> SetLogz(1);
    histoFMD -> GetYaxis() -> SetTitle("FIT [Failures / 10^{9} h]");
    histoFMD -> GetYaxis() -> SetTitleOffset(1.2);
    histoFMD -> Draw("COLZ");
    histoFMD -> Draw("candlesame");

    c1 -> cd(2);
    c1 -> cd(2) -> SetLogz(1);
    histoALL -> GetYaxis() -> SetTitle("FIT [Failures / 10^{9} h]");
    histoALL -> GetYaxis() -> SetTitleOffset(1.2);
    histoALL -> Draw("COLZ");
    histoALL -> Draw("candlesame");

    c1 -> SaveAs("PowerBoard_schematic.png");

    TCanvas* c2 = new TCanvas("c2", "MC Total FIT", 800,600);
    histoTotFMD -> Draw();
    histoTotFMD -> SetLineColor(kRed);

    histoTotFMD -> GetYaxis() -> SetRangeUser(0, 250);

    histoTotFMD -> SetTitle("MC Fit with and without FMD");
    histoTotFMD -> GetXaxis() -> SetTitle("Total FIT [Failures / 10^{9} h]");
    histoTotFMD -> GetYaxis() -> SetTitle("MC results");
    histoTotFMD -> GetYaxis() -> SetTitleOffset(1.2);
    histoTotFMD -> SetLineWidth(2);

    histoTotALL -> Draw("same");
    histoTotALL -> SetLineWidth(2);

    TLine* myline1 = new TLine(40.8425, 0, 40.8425, 250);
    myline1 -> SetLineColor(6);
    myline1 -> SetLineStyle(2);
    myline1 -> SetLineWidth(2);
    myline1 -> Draw();
    TLine* myline2 = new TLine(histoTotALL->GetMean(), 0, histoTotALL->GetMean(), 250);
    myline2 -> SetLineColor( histoTotALL -> GetLineColor());
    myline2 -> Draw();
    TLine* myline3 = new TLine(histoTotFMD->GetMean(), 0, histoTotFMD->GetMean(), 250);
    myline3 -> SetLineColor( histoTotFMD -> GetLineColor());
    myline3 -> Draw();

    TLegend* myleg = new TLegend(0.7, 0.8, 0.9, 0.9);
    char buffer[64];
    sprintf(buffer, "FMD  %3.2lf FIT", histoTotFMD->GetMean());
    myleg -> AddEntry(histoTotFMD, buffer, "l");

    sprintf(buffer, "ALL  %3.2lf FIT", histoTotALL->GetMean());
    myleg -> AddEntry(histoTotALL, buffer, "l");

    sprintf(buffer, "CALC %3.2lf FIT", 40.8425);
//    myleg -> AddEntry((TObject*)0, buffer, " ");
    myleg -> AddEntry(myline1, buffer, "l");
    myleg -> Draw();
    c2 -> Update();
    c2 -> SaveAs("PowerBoard_total.png");
}
