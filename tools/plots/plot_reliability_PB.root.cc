{
	gROOT -> Reset();
	
	ifstream input;
	input.open("../../reliability_PowerBoard.txt");
	
	vector<float> FITpoe, POEvoltage, temperature, FITtemp;
	float rFIT, rPOEvoltage, rtemperature, help;

	// 1486633848	40	24	48	40.8425
	while(true){
		input >> help >> rtemperature >> help >> rPOEvoltage >> rFIT;
		if(!input.good()) break;
	
		if( fabs(rtemperature - 40.) < 0.1) {	
			FITpoe.push_back(rFIT);
			POEvoltage.push_back(rPOEvoltage);
		}
		if( fabs(rPOEvoltage - 48.) < 0.2){
			FITtemp.push_back(rFIT);
			temperature.push_back(rtemperature);
		}
	}

	TCanvas* c1 = new TCanvas("c1", "Reliability PowerBoard", 800,600);

	TGraph* gPOEfit = new TGraph(FITpoe.size(), &POEvoltage[0], &FITpoe[0]);
	gPOEfit -> Sort();

	gPOEfit -> SetTitle("Reliability PowerBoard @ 40 #circ C"); 
	gPOEfit -> GetXaxis() -> SetTitle("POE input voltage [V]");
	gPOEfit -> GetYaxis() -> SetTitle("FIT value [/1e9h]");

	gPOEfit -> SetMarkerStyle(7);

	gPOEfit -> Draw("ALP");

	c1 -> SaveAs("reliability_vs_POEinput.png");

	TGraph* gTempfit = new TGraph(FITtemp.size(), &temperature[0], &FITtemp[0]);
	gTempfit -> Sort();

	gTempfit -> SetTitle("Reliability PowerBoard @ POE = 48V");
	gTempfit -> GetXaxis() -> SetTitle("ambient temperature [#circ C]");
	gTempfit -> GetYaxis() -> SetTitle("FIT value [/1e9h]");

	gTempfit -> SetMarkerStyle(7);

	gTempfit -> Draw("ALP");

	c1 -> SaveAs("reliability_vs_temperature.png");
}
