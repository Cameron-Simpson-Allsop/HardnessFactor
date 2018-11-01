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

void GraphsOven2311()

{
	rootlogonATLAS();
	TGraphErrors *gr1 = new TGraphErrors("Temp_vs_OvenRecoveryTime_2311.txt");
	TGraphErrors *gr2 = new TGraphErrors("Temp_vs_RecoveryRate_2311.txt");
	
		gr1->GetXaxis()->SetTitle("Temperature (deg C)");
		gr1->GetYaxis()->SetTitle("Recovery Time (s)");
		gr1->SetTitle("Temperature vs Oven Recovery Time");
		gr1->SetLineColor(kBlue);		

		gr2->GetXaxis()->SetTitle("Temperature (deg C)");
		gr2->GetYaxis()->SetTitle("Recovery Rate (deg C/s)");
		gr2->SetTitle("Temperature vs Oven Recovery Rate");
		gr2->SetLineColor(kRed);

	TF1 *fit1 = new TF1("fit1","pol1",50,100);
	TF1 *fit2 = new TF1("fit2","pol1",50,100);

	fit1->SetParameter(1,5);
	fit2->SetParameter(1,70);
		
	TCanvas *c1 = new TCanvas("c1","c1",600,700);
		c1->Divide(1,2);
		c1->cd(1);
		gr1->Draw("AP");
		gr1->Fit(fit1,"RN");
		fit1->Draw("same");
		
		c1->cd(2);
		gr2->Draw("AP");
		gr2->Fit(fit2,"RN");
		fit2->Draw("same");

	TCanvas *c2 = new TCanvas("c2","c2",600,700);
		c2->SetRightMargin(1);
		gr1->SetMarkerStyle(20);
		gr1->SetLineColor(kBlack);
		gr1->SetTitle("");
		fit1->SetLineColor(kBlack);
		gr1->Draw("AP");
		fit1->Draw("same");

	TCanvas *c3 = new TCanvas("c3","c3",600,700);
		gr2->SetMarkerStyle(20);
		gr2->SetLineColor(kBlack);
		gr2->SetTitle("");
		fit2->SetLineColor(kBlack);
		gr2->Draw("AP");
		fit2->Draw("same");

			

}
