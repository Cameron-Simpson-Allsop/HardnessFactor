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


void GraphAnnealingCurves0512(){
	rootlogonATLAS();
	TCanvas *canvas = new TCanvas("canvas","canvas",600,700);
	TGraphErrors *g1 = new TGraphErrors("Diode_3_Anneal_80mins_3011.txt");
	TGraphErrors *g2 = new TGraphErrors("Diode_4_Anneal_80mins_3011.txt");
	TGraphErrors *g3 = new TGraphErrors("Diode_5_Anneal_80mins_2411.txt");
	TGraphErrors *g4 = new TGraphErrors("Diode_15_Anneal_80mins_3011.txt");
	TGraphErrors *g5 = new TGraphErrors("Diode_8_Anneal_80mins_3011.txt");
canvas->SetRightMargin(1);
		g1->GetXaxis()->SetTitle("Voltage (V)");
		g1->GetYaxis()->SetTitle("Leakage Current (nA)");
		g1->SetTitle("");

		g1->SetMarkerStyle(33);
		g2->SetMarkerStyle(21);
		g3->SetMarkerStyle(22);
		g4->SetMarkerStyle(23);
		g5->SetMarkerStyle(34);

		g1->SetMarkerSize(1.5);
		g2->SetMarkerSize(1.5);
		g3->SetMarkerSize(1.5);
		g4->SetMarkerSize(1.5);
		g5->SetMarkerSize(1.5);

		TGaxis::SetMaxDigits(3);
		
		g1->Draw("ACP");
		g2->Draw("pcsame");
		g3->Draw("pcsame");
		g4->Draw("pcsame");
		g5->Draw("pcsame");

	
	TLegend *legend = new TLegend(0.6,0.2,0.85,0.4);
		legend->AddEntry(g4,"Diode 15 - 2.0x10^{11} (p/cm^{2}) ","lp");
		legend->AddEntry(g2,"Diode 4 - 4.7x10^{11} (p/cm^{2}) ","lp");
		legend->AddEntry(g3,"Diode 5 - 1.2x10^{12} (p/cm^{2}) ","lp");
		legend->AddEntry(g5,"Diode 8 - 1.2x10^{12} (p/cm^{2}) ","lp");	
		legend->AddEntry(g1,"Diode 3 - 5.2x10^{12} (p/cm^{2}) ","lp");
		legend->Draw();
	

}
