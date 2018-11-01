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


int GraphCV1011()


{
	rootlogonATLAS();
	TGraphErrors *gr1 = new TGraphErrors("CV_Diode_16_1011.txt");
		gr1->GetXaxis()->SetTitle("Ln(-V) (Ln(v))");
		gr1->GetYaxis()->SetTitle("Ln(C) (Ln(pF))");
		gr1->GetYaxis()->SetTitleOffset(1.45);
		gr1->SetTitle("Diode 16 C-V 10/11");
		gr1->SetLineColor(kBlack);
		

	TF1* fit1 = new TF1("fit1","pol1",1.9,4.43);
	TF1* fit2 = new TF1("fit2","pol1",4.6,5.25);
		fit1->SetLineWidth(1);
		fit2->SetLineWidth(1);	

	TCanvas *c1a = new TCanvas("c1","c1",600,700);
	c1a->SetRightMargin(1);
		gr1->Draw("AP");
		gr1->Fit(fit1,"RN");
		gr1->Fit(fit2,"RN");
		fit1->Draw("same");
		fit2->Draw("same");		

	double c1 = fit1->GetParameter(0);
	double m1 = fit1->GetParameter(1);
	double c2 = fit2->GetParameter(0);
	double m2 = fit2->GetParameter(1);
	
	double ec1 = fit1->GetParError(0);
	double em1 = fit1->GetParError(1);
	double ec2 = fit2->GetParError(0);
	double em2 = fit2->GetParError(1);

	TF1* fit3 = new TF1("fit3","[1]*x+[0]",4.4,4.7); //Extrapolates fit lines (Cosmetic).
	TF1* fit4 = new TF1("fit4","[1]*x+[0]",4.3,4.65);
	fit3->SetLineWidth(1);
	fit4->SetLineWidth(1);
	fit3->SetParameter(0,c1);
	fit3->SetParameter(1,m1);
	fit4->SetParameter(0,c2);
	fit4->SetParameter(1,m2);
	
		fit3->Draw("same");
		fit4->Draw("same");		
	
	double Intersect = (c2-c1)/(m1-m2); //Intersect of fit lines on x axis.
	double e1 = ec2/(m1-m2);
	double e2 = ec1/(m1-m2);
	double e3 = em1*(c2-c1)/(pow(m1-m2,2));
	double e4 = em2*(c2-c1)/(pow(m1-m2,2));
	double eIntersect = pow(e1*e1+e2*e2+e3*e3+e4*e4,0.5);

	std::cout << "x Intersect = " << Intersect << " +/- " << eIntersect << std::endl;
	std::cout << "Max Depletion Voltage = " << exp(Intersect) << " +/- " << exp(Intersect)*eIntersect <<std::endl; //Log scale so take exponents.
	std::cout << "Percentage Error = " << 100*exp(Intersect)*eIntersect/exp(Intersect) << "%" << std::endl;	
	
return 0;
}
