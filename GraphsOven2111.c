void rootlogonATLAS(double ytoff = 1.0, bool atlasmarker =true, double left_margin=0.14) 
{

TStyle* atlasStyle= new TStyle("ATLAS","Atlas style");

// use plain black on white colors
Int_t icol=0;
atlasStyle->SetFrameBorderMode(icol);
atlasStyle->SetCanvasBorderMode(icol);
atlasStyle->SetPadBorderMode(icol);
atlasStyle->SetPadColor(icol);
atlasStyle->SetCanvasColor(icol);
atlasStyle->SetStatColor(icol);
//atlasStyle->SetFillColor(icol);

// set the paper & margin sizes
atlasStyle->SetPaperSize(20,26);
atlasStyle->SetPadTopMargin(0.05);
atlasStyle->SetPadRightMargin(0.05);
atlasStyle->SetPadBottomMargin(0.16);
atlasStyle->SetPadLeftMargin(0.12);

// use large fonts
//Int_t font=72;
Int_t font=42;
Double_t tsize=0.05;
atlasStyle->SetTextFont(font);


atlasStyle->SetTextSize(tsize);
atlasStyle->SetLabelFont(font,"x");
atlasStyle->SetTitleFont(font,"x");
atlasStyle->SetLabelFont(font,"y");
atlasStyle->SetTitleFont(font,"y");
atlasStyle->SetLabelFont(font,"z");
atlasStyle->SetTitleFont(font,"z");

atlasStyle->SetLabelSize(tsize,"x");
atlasStyle->SetTitleSize(tsize,"x");
atlasStyle->SetLabelSize(tsize,"y");
atlasStyle->SetTitleSize(tsize,"y");
atlasStyle->SetLabelSize(tsize,"z");
atlasStyle->SetTitleSize(tsize,"z");


//use bold lines and markers
if ( atlasmarker ) {
  atlasStyle->SetMarkerStyle(20);
  atlasStyle->SetMarkerSize(1.2);
}
atlasStyle->SetHistLineWidth(2.);
atlasStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

//get rid of X error bars and y error bar caps
//atlasStyle->SetErrorX(0.001);

//do not display any of the standard histogram decorations
atlasStyle->SetOptTitle(0);
//atlasStyle->SetOptStat(1111);
atlasStyle->SetOptStat(0);
//atlasStyle->SetOptFit(1111);
atlasStyle->SetOptFit(0);

// put tick marks on top and RHS of plots
atlasStyle->SetPadTickX(1);
atlasStyle->SetPadTickY(1);

//gStyle->SetPadTickX(1);
//gStyle->SetPadTickY(1);

// DLA overrides
atlasStyle->SetPadLeftMargin(left_margin);
atlasStyle->SetPadBottomMargin(0.13);
atlasStyle->SetTitleYOffset(ytoff);
atlasStyle->SetTitleXOffset(1.0);

 const Int_t NRGBs = 5;
 const Int_t NCont = 255;
 
 Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
 Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
 Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
 Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
 TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
 atlasStyle->SetNumberContours(NCont);

// Enforce the style.
gROOT->SetStyle("ATLAS");
gROOT->ForceStyle();
}

int GraphsOven2111()


{
	rootlogonATLAS();
	TGraphErrors *gr1 = new TGraphErrors("OvenDial_vs_OvenTemp_2111.txt");
	TGraphErrors *gr2 = new TGraphErrors("OvenDial_vs_TCTemp_2111.txt");
	TGraphErrors *gr3 = new TGraphErrors("OvenTemp_vs_TCTemp_2111.txt");
	
		gr1->GetXaxis()->SetTitle("Oven Dial Reading");
		gr1->GetYaxis()->SetTitle("Temperature (deg C)");
		gr1->SetTitle("Oven Dial vs Oven Temperature");
		gr1->SetLineColor(kBlue);		

		gr2->GetXaxis()->SetTitle("Oven Dial Reading");
		gr2->GetYaxis()->SetTitle("Average Thermocouple Reading (deg C)");
		gr2->SetTitle("Oven Dial vs Thermocouple");
		gr2->SetLineColor(kRed);

		gr3->GetXaxis()->SetTitle("Oven Temperature Reading (deg C)");
		gr3->GetYaxis()->SetTitle("Average Thermocouple Reading (deg C)");
		gr3->SetTitle("Oven Temperature vs Thermocouple");
		gr3->SetLineColor(kGreen);

	TF1 *fit1 = new TF1("fit1","pol1",1,4.5);
	TF1 *fit2 = new TF1("fit2","pol1",1,4.5);
	TF1 *fit3 = new TF1("fit3","pol1",22,120);		

	fit1->SetParameter(1,100);
	fit2->SetParameter(1,100);
	fit3->SetParameter(1,1);	

	TCanvas *c1 = new TCanvas("c1","c1",600,700);
		c1->Divide(1,2);
		c1->cd(1);
		gr1->Draw("AP");
		gr1->Fit(fit1,"RN");
		fit1->Draw("same");
	
		gr2->Draw("sames");
		gr2->Fit(fit2,"RN");
		fit2->Draw("same");
		
	auto legend = new TLegend(0.1,0.6,0.58,0.9);
		legend->SetHeader("Legend");
		legend->AddEntry(gr1,"Displayed Oven Temperature (deg C)","l");
		legend->AddEntry(gr2,"Average Thermocouple Reading (deg C)","l");
		legend->Draw();

		c1->cd(2);
		gr3->Draw("AP");
		gr3->Fit(fit3,"RN");
		fit3->Draw("same");
	
	TCanvas *c2 = new TCanvas("c2","c2",600,700);
		c2->SetRightMargin(1);
		gr1->SetMarkerStyle(20);
		gr2->SetMarkerStyle(24);
		gr1->SetLineColor(kBlack);
		gr2->SetLineColor(kBlack);
		gr1->SetTitle("");
		fit1->SetLineColor(kBlack);
		fit2->SetLineColor(kBlack);
		fit1->SetLineStyle(7);
		fit2->SetLineStyle(9);
		gr1->Draw("AP");
		gr2->Draw("psame");
		fit1->Draw("same");
		fit2->Draw("same");

		auto legend1 = new TLegend(0.15,0.7,0.4,0.9);
		legend1->AddEntry(gr1,"Displayed Oven Temperature (deg C)","p");
		legend1->AddEntry(gr2,"Average Thermocouple Reading (deg C)","p");
		legend1->AddEntry(fit1,"Fit to Oven Data","l");
		legend1->AddEntry(fit2,"Fit to Thermocouple Data","l");
		legend1->Draw();

	TCanvas *c3 = new TCanvas("c3","c3",600,700);
		gr3->SetMarkerStyle(20);
		gr3->SetLineColor(kBlack);
		gr3->SetTitle("");
		fit3->SetLineColor(kBlack);
		gr3->Draw("AP");
		fit3->Draw("same");
				
	
	/*double y=0;
	std::cout << "Give temperature (deg C) for eqivalent oven dial reading" << std::endl;
	std::cin >> y;
	double m = fit2->GetParameter(1);
	double c = fit2->GetParameter(0);
	double x = (y-c)/m;
	std::cout << "Equivalent oven dial reading = " << x << std::endl;
	std::cout << "Note: Dial readings of <1 are unreliable" << std::endl;*/
	

return 0;
}
