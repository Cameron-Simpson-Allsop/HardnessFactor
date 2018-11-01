
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

void BandGap0503()
{
	rootlogonATLAS();
	TGraphErrors *g1u = new TGraphErrors("Diode24_unscaled_15_5C_0503.txt");
	TGraphErrors *g2u = new TGraphErrors("Diode24_unscaled_18_2C_0503.txt");
	TGraphErrors *g3u = new TGraphErrors("Diode24_unscaled_21C_0503.txt");
	TGraphErrors *g4u = new TGraphErrors("Diode24_unscaled_24C_0503.txt");
	TGraphErrors *g5u = new TGraphErrors("Diode24_unscaled_27C_0503.txt");
	TGraphErrors *g6u = new TGraphErrors("Diode24_unscaled_30C_0503.txt");

	TGraphErrors *g1s = new TGraphErrors("Diode24_scaled_15_5C_0503.txt");
	TGraphErrors *g2s = new TGraphErrors("Diode24_scaled_18_2C_0503.txt");
	TGraphErrors *g3s = new TGraphErrors("Diode24_scaled_21C_0503.txt");
	TGraphErrors *g4s = new TGraphErrors("Diode24_scaled_24C_0503.txt");
	TGraphErrors *g5s = new TGraphErrors("Diode24_scaled_27C_0503.txt");
	TGraphErrors *g6s = new TGraphErrors("Diode24_scaled_30C_0503.txt");

	g1u->SetMarkerStyle(20);
	g2u->SetMarkerStyle(21);
	g3u->SetMarkerStyle(22);
	g4u->SetMarkerStyle(23);
	g5u->SetMarkerStyle(33);
	g6u->SetMarkerStyle(34);

	g1u->SetMarkerSize(1.5);
	g2u->SetMarkerSize(1.5);
	g3u->SetMarkerSize(1.5);
	g4u->SetMarkerSize(1.5);
	g5u->SetMarkerSize(1.5);
	g6u->SetMarkerSize(1.5);

	g1s->SetMarkerStyle(20);
	g2s->SetMarkerStyle(21);
	g3s->SetMarkerStyle(22);
	g4s->SetMarkerStyle(23);
	g5s->SetMarkerStyle(33);
	g6s->SetMarkerStyle(34);

	g1s->SetMarkerSize(1.5);
	g2s->SetMarkerSize(1.5);
	g3s->SetMarkerSize(1.5);
	g4s->SetMarkerSize(1.5);
	g5s->SetMarkerSize(1.5);
	g6s->SetMarkerSize(1.5);

	TMultiGraph *mgu = new TMultiGraph();
		//mgu->Add(g1u,"cp");
		mgu->Add(g2u,"cp");
		mgu->Add(g3u,"cp");
		mgu->Add(g4u,"cp");
		mgu->Add(g5u,"cp");
		mgu->Add(g6u,"cp");
	
	TMultiGraph *mgs = new TMultiGraph();
		//mgs->Add(g1s,"cp");
		mgs->Add(g2s,"cp");
		mgs->Add(g3s,"cp");
		mgs->Add(g4s,"cp");
		mgs->Add(g5s,"cp");
		mgs->Add(g6s,"cp");

	TCanvas *unscaled = new TCanvas("unscaled","unscaled",600,700);
		mgu->Draw("ACP");
		mgu->GetYaxis()->SetRangeUser(-4,2);
		mgu->GetXaxis()->SetRangeUser(-180,0);
		mgu->GetXaxis()->SetTitle("Voltage (V)");
		mgu->GetYaxis()->SetTitle("Leakage Current (nA)");
		unscaled->SetRightMargin(1);

	TLegend *legendu = new TLegend(0.65,0.15,0.85,0.35);
   		//legendu->AddEntry(g1u,"15.5#circC","p");
   		legendu->AddEntry(g2u,"18.2#circC","p");
		legendu->AddEntry(g3u,"21#circC","p");
		legendu->AddEntry(g4u,"24#circC","p");
		legendu->AddEntry(g5u,"27#circC","p");
		legendu->AddEntry(g6u,"30#circC","p");
   		legendu->Draw();

	TCanvas *scaled = new TCanvas("scaled","scaled",600,700);
		mgs->Draw("ACP");
		mgs->GetYaxis()->SetRangeUser(-4,2);
		mgs->GetXaxis()->SetRangeUser(-180,0);
		mgs->GetXaxis()->SetTitle("Voltage (V)");
		mgs->GetYaxis()->SetTitle("Leakage Current (nA)");
		scaled->SetRightMargin(1);

	TLegend *legends = new TLegend(0.65,0.15,0.85,0.35);
   		//legends->AddEntry(g1s,"15.5#circC","p");
   		legends->AddEntry(g2s,"18.2#circC","p");
		legends->AddEntry(g3s,"21#circC","p");
		legends->AddEntry(g4s,"24#circC","p");
		legends->AddEntry(g5s,"27#circC","p");
		legends->AddEntry(g6s,"30#circC","p");
   		legends->Draw();

	
}
