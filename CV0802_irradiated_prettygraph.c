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


void CV0802_irradiated_prettygraph()
{
	rootlogonATLAS();
	TGraphErrors *gr1 = new TGraphErrors("Diode3_CV_0802_5kHz.txt");
	TGraphErrors *gr2 = new TGraphErrors("Diode3_CV_0802_10kHz.txt");
	TGraphErrors *gr3 = new TGraphErrors("Diode3_CV_0802_30kHz.txt");
	TGraphErrors *gr4 = new TGraphErrors("Diode3_CV_0802_60kHz.txt");
	TGraphErrors *gr5 = new TGraphErrors("Diode3_CV_0802_100kHz.txt");
		
	gr1->SetMarkerStyle(34);
        gr2->SetMarkerStyle(20);
        gr3->SetMarkerStyle(21);
        gr4->SetMarkerStyle(22);
        gr5->SetMarkerStyle(23);
        
        gr1->SetMarkerSize(1.5);
        gr2->SetMarkerSize(1.5);
        gr3->SetMarkerSize(1.5);
        gr4->SetMarkerSize(1.5);
        gr5->SetMarkerSize(1.5);

    TMultiGraph *mg = new TMultiGraph();
        mg->Add(gr1);
        mg->Add(gr2);
        mg->Add(gr3);
        mg->Add(gr4);
        mg->Add(gr5); 

	TCanvas *cv = new TCanvas("cv","cv",600,700);
	cv->SetRightMargin(1);
		mg->Draw("ACP");
		mg->SetTitle("");
        	mg->GetXaxis()->SetTitle("Ln(-V) (Ln(V))");
        	mg->GetYaxis()->SetTitle("Ln(C) (Ln(pF))");

	TLegend *legend = new TLegend(0.6,0.5,0.88,0.7);
		legend->AddEntry(gr1,"5kHz Irradiated","lp");
		legend->AddEntry(gr2,"10kHz Irradiated","lp");
		legend->AddEntry(gr3,"30kHz Irradiated","lp");
		legend->AddEntry(gr4,"60kHz Irradiated","lp");
		legend->AddEntry(gr5,"100kHz Irradiated","lp");
      	legend->Draw();


}
