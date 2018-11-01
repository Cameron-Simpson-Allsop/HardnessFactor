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


void CV0503_all()
{
	rootlogonATLAS();
    TGraphErrors *g1 = new TGraphErrors("Diode37_CV_10kHz_0503.txt");
    TGraphErrors *g2 = new TGraphErrors("Diode38_CV_10kHz_0503.txt");
    TGraphErrors *g3 = new TGraphErrors("Diode39_CV_10kHz_0503.txt");
    TGraphErrors *g4 = new TGraphErrors("Diode40_CV_10kHz_0503.txt");
    TGraphErrors *g5 = new TGraphErrors("Diode41_CV_10kHz_0503.txt");
    TGraphErrors *g6 = new TGraphErrors("Diode42_CV_10kHz_0503.txt");
    TGraphErrors *g7 = new TGraphErrors("Diode43_CV_10kHz_0503.txt");
    TGraphErrors *g8 = new TGraphErrors("Diode44_CV_10kHz_0503.txt");
    TGraphErrors *g9 = new TGraphErrors("Diode45_CV_10kHz_0503.txt");
    TGraphErrors *g10 = new TGraphErrors("Diode46_CV_10kHz_0503.txt");
    TGraphErrors *g11 = new TGraphErrors("Diode47_CV_10kHz_0503.txt");
    TGraphErrors *g12 = new TGraphErrors("Diode48_CV_10kHz_0503.txt");

        TF1* fit1a = new TF1("fit1","pol1",1.0,3.9);//37
	    TF1* fit1b = new TF1("fit2","pol1",4.1,5.0);	
	    fit1a->SetParameter(1,-0.1);
	    fit1b->SetParameter(1,-0.5);

        TF1* fit2a = new TF1("fit1","pol1",1.0,4.3);//38
	    TF1* fit2b = new TF1("fit2","pol1",4.4,5.0);	
	    fit2a->SetParameter(1,-1.5);
	    fit2b->SetParameter(1,-0.5);
        
        TF1* fit3a = new TF1("fit1","pol1",1.0,4.0);//39
	    TF1* fit3b = new TF1("fit2","pol1",4.4,5.0);	
	    fit3a->SetParameter(1,-1.0);
	    fit3b->SetParameter(1,-0.5);

        TF1* fit4a = new TF1("fit1","pol1",1.0,4.3);//40
	    TF1* fit4b = new TF1("fit2","pol1",4.4,5.1);	
	    fit4a->SetParameter(1,-1.5);
	    fit4b->SetParameter(1,-0.5);

        TF1* fit5a = new TF1("fit1","pol1",1.0,4.3);//41
	    TF1* fit5b = new TF1("fit2","pol1",4.4,5.1);	
	    fit5a->SetParameter(1,-1.5);
	    fit5b->SetParameter(1,-0.5);

        TF1* fit6a = new TF1("fit1","pol1",1.0,4.3);//42
	    TF1* fit6b = new TF1("fit2","pol1",4.4,5.0);	
	    fit6a->SetParameter(1,-1.0);
	    fit6b->SetParameter(1,-0.5);

        TF1* fit7a = new TF1("fit1","pol1",1.0,4.3);//43
	    TF1* fit7b = new TF1("fit2","pol1",4.4,5.2);	
	    fit7a->SetParameter(1,-1.5);
	    fit7b->SetParameter(1,-0.5);
        
        TF1* fit8a = new TF1("fit1","pol1",1.0,4.3);//44
	    TF1* fit8b = new TF1("fit2","pol1",4.4,5.05);	
	    fit8a->SetParameter(1,-1.5);
	    fit8b->SetParameter(1,-0.5);

        TF1* fit9a = new TF1("fit1","pol1",1.0,4.3);//45
	    TF1* fit9b = new TF1("fit2","pol1",4.5,5.2);	
	    fit9a->SetParameter(1,-0.1);
	    fit9b->SetParameter(1,-0.5);

        TF1* fit10a = new TF1("fit1","pol1",1.0,4.3);//46
	    TF1* fit10b = new TF1("fit2","pol1",4.5,5.2);	
	    fit10a->SetParameter(1,-1.5);
	    fit10b->SetParameter(1,-0.1);
         
        TF1* fit11a = new TF1("fit1","pol1",1.0,4.5);//47
	    TF1* fit11b = new TF1("fit2","pol1",4.6,5.2);	
	    fit11a->SetParameter(1,-0.5);
	    fit11b->SetParameter(1,-0.5);

        /*TF1* fit12a = new TF1("fit1","pol1",1.0,4.3);//48
	    TF1* fit12b = new TF1("fit2","pol1",4.6,5.2);	
	    fit12a->SetParameter(1,-1.5);
	    fit12b->SetParameter(1,-0.5);*/
        
            TCanvas *D37 = new TCanvas("D37","D37",600,700);
		        g1->Draw("ALP");
		        g1->Fit(fit1a,"RN");
		        g1->Fit(fit1b,"RN");
		        fit1a->Draw("same");
		        fit1b->Draw("same");
            
            TCanvas *D38 = new TCanvas("D38","D38",600,700);
		        g2->Draw("ALP");
		        g2->Fit(fit2a,"RN");
		        g2->Fit(fit2b,"RN");
		        fit2a->Draw("same");
		        fit2b->Draw("same");

            TCanvas *D39 = new TCanvas("D39","D39",600,700);
		        g3->Draw("ALP");
		        g3->Fit(fit3a,"RN");
		        g3->Fit(fit3b,"RN");
		        fit3a->Draw("same");
		        fit3b->Draw("same");

            TCanvas *D40 = new TCanvas("D40","D40",600,700);
		        g4->Draw("ALP");
		        g4->Fit(fit4a,"RN");
		        g4->Fit(fit4b,"RN");
		        fit4a->Draw("same");
		        fit4b->Draw("same");

            TCanvas *D41 = new TCanvas("D41","D41",600,700);
		        g5->Draw("ALP");
		        g5->Fit(fit5a,"RN");
		        g5->Fit(fit5b,"RN");
		        fit5a->Draw("same");
		        fit5b->Draw("same");

            TCanvas *D42 = new TCanvas("D42","D42",600,700);
		        g6->Draw("ALP");
		        g6->Fit(fit6a,"RN");
		        g6->Fit(fit6b,"RN");
		        fit6a->Draw("same");
		        fit6b->Draw("same");

            TCanvas *D43 = new TCanvas("D43","D43",600,700);
		        g7->Draw("ALP");
		        g7->Fit(fit7a,"RN");
		        g7->Fit(fit7b,"RN");
		        fit7a->Draw("same");
		        fit7b->Draw("same");

            TCanvas *D44 = new TCanvas("D44","D44",600,700);
		        g8->Draw("ALP");
		        g8->Fit(fit8a,"RN");
		        g8->Fit(fit8b,"RN");
		        fit8a->Draw("same");
		        fit8b->Draw("same");
            
            TCanvas *D45 = new TCanvas("D45","D45",600,700);
		        g9->Draw("ALP");
		        g9->Fit(fit9a,"RN");
		        g9->Fit(fit9b,"RN");
		        fit9a->Draw("same");
		        fit9b->Draw("same");
            
            TCanvas *D46 = new TCanvas("D46","D46",600,700);
		        g10->Draw("ALP");
		        g10->Fit(fit10a,"RN");
		        g10->Fit(fit10b,"RN");
		        fit10a->Draw("same");
		        fit10b->Draw("same");

            TCanvas *D47 = new TCanvas("D47","D47",600,700);
		        g11->Draw("ALP");
		        g11->Fit(fit11a,"RN");
		        g11->Fit(fit11b,"RN");
		        fit11a->Draw("same");
		        fit11b->Draw("same");

            /*TCanvas *D48 = new TCanvas("D48","D48",600,700);
		        g12->Draw("ALP");
		        g12->Fit(fit12a,"RN");
		        g12->Fit(fit12b,"RN");
		        fit12a->Draw("same");
		        fit12b->Draw("same");*/

double c1a = fit1a->GetParameter(0);
double m1a = fit1a->GetParameter(1);
double c1b = fit1b->GetParameter(0);
double m1b = fit1b->GetParameter(1);
double ec1a = fit1a->GetParError(0);
double em1a = fit1a->GetParError(1);
double ec1b = fit1b->GetParError(0);
double em1b = fit1b->GetParError(1);
double Intersect1 = (c1b-c1a)/(m1a-m1b); 
double e1a = ec1b/(m1a-m1b);
double e1b = ec1a/(m1a-m1b);
double e1c = em1a*(c1b-c1a)/(pow(m1a-m1b,2));
double e1d = em1b*(c1b-c1a)/(pow(m1a-m1b,2));
double eIntersect1 = pow(e1a*e1a+e1b*e1b+e1c*e1c+e1d*e1d,0.5);
double V1 = -exp(Intersect1);
double V1e = exp(Intersect1)*eIntersect1;

double c2a = fit2a->GetParameter(0);
double m2a = fit2a->GetParameter(1);
double c2b = fit2b->GetParameter(0);
double m2b = fit2b->GetParameter(1);
double ec2a = fit2a->GetParError(0);
double em2a = fit2a->GetParError(1);
double ec2b = fit2b->GetParError(0);
double em2b = fit2b->GetParError(1);
double Intersect2 = (c2b-c2a)/(m2a-m2b); 
double e2a = ec2b/(m2a-m2b);
double e2b = ec2a/(m2a-m2b);
double e2c = em2a*(c2b-c2a)/(pow(m2a-m2b,2));
double e2d = em2b*(c2b-c2a)/(pow(m2a-m2b,2));
double eIntersect2 = pow(e2a*e2a+e2b*e2b+e2c*e2c+e2d*e2d,0.5);
double V2 = -exp(Intersect2);
double V2e = exp(Intersect2)*eIntersect2;

double c3a = fit3a->GetParameter(0);
double m3a = fit3a->GetParameter(1);
double c3b = fit3b->GetParameter(0);
double m3b = fit3b->GetParameter(1);
double ec3a = fit3a->GetParError(0);
double em3a = fit3a->GetParError(1);
double ec3b = fit3b->GetParError(0);
double em3b = fit3b->GetParError(1);
double Intersect3 = (c3b-c3a)/(m3a-m3b); 
double e3a = ec3b/(m3a-m3b);
double e3b = ec3a/(m3a-m3b);
double e3c = em3a*(c3b-c3a)/(pow(m3a-m3b,2));
double e3d = em3b*(c3b-c3a)/(pow(m3a-m3b,2));
double eIntersect3 = pow(e3a*e3a+e3b*e3b+e3c*e3c+e3d*e3d,0.5);
double V3 = -exp(Intersect3);
double V3e = exp(Intersect3)*eIntersect3;

double c4a = fit4a->GetParameter(0);
double m4a = fit4a->GetParameter(1);
double c4b = fit4b->GetParameter(0);
double m4b = fit4b->GetParameter(1);
double ec4a = fit4a->GetParError(0);
double em4a = fit4a->GetParError(1);
double ec4b = fit4b->GetParError(0);
double em4b = fit4b->GetParError(1);
double Intersect4 = (c4b-c4a)/(m4a-m4b); 
double e4a = ec4b/(m4a-m4b);
double e4b = ec4a/(m4a-m4b);
double e4c = em4a*(c4b-c4a)/(pow(m4a-m4b,2));
double e4d = em4b*(c4b-c4a)/(pow(m4a-m4b,2));
double eIntersect4 = pow(e4a*e4a+e4b*e4b+e4c*e4c+e4d*e4d,0.5);
double V4 = -exp(Intersect4);
double V4e = exp(Intersect4)*eIntersect4;

double c5a = fit5a->GetParameter(0);
double m5a = fit5a->GetParameter(1);
double c5b = fit5b->GetParameter(0);
double m5b = fit5b->GetParameter(1);
double ec5a = fit5a->GetParError(0);
double em5a = fit5a->GetParError(1);
double ec5b = fit5b->GetParError(0);
double em5b = fit5b->GetParError(1);
double Intersect5 = (c5b-c5a)/(m5a-m5b); 
double e5a = ec5b/(m5a-m5b);
double e5b = ec5a/(m5a-m5b);
double e5c = em5a*(c5b-c5a)/(pow(m5a-m5b,2));
double e5d = em5b*(c5b-c5a)/(pow(m5a-m5b,2));
double eIntersect5 = pow(e5a*e5a+e5b*e5b+e5c*e5c+e5d*e5d,0.5);
double V5 = -exp(Intersect5);
double V5e = exp(Intersect5)*eIntersect5;

double c6a = fit6a->GetParameter(0);
double m6a = fit6a->GetParameter(1);
double c6b = fit6b->GetParameter(0);
double m6b = fit6b->GetParameter(1);
double ec6a = fit6a->GetParError(0);
double em6a = fit6a->GetParError(1);
double ec6b = fit6b->GetParError(0);
double em6b = fit6b->GetParError(1);
double Intersect6 = (c6b-c6a)/(m6a-m6b); 
double e6a = ec6b/(m6a-m6b);
double e6b = ec6a/(m6a-m6b);
double e6c = em6a*(c6b-c6a)/(pow(m6a-m6b,2));
double e6d = em6b*(c6b-c6a)/(pow(m6a-m6b,2));
double eIntersect6 = pow(e6a*e6a+e6b*e6b+e6c*e6c+e6d*e6d,0.5);
double V6 = -exp(Intersect6);
double V6e = exp(Intersect6)*eIntersect6;

double c7a = fit7a->GetParameter(0);
double m7a = fit7a->GetParameter(1);
double c7b = fit7b->GetParameter(0);
double m7b = fit7b->GetParameter(1);
double ec7a = fit7a->GetParError(0);
double em7a = fit7a->GetParError(1);
double ec7b = fit7b->GetParError(0);
double em7b = fit7b->GetParError(1);
double Intersect7 = (c7b-c7a)/(m7a-m7b); 
double e7a = ec7b/(m7a-m7b);
double e7b = ec7a/(m7a-m7b);
double e7c = em7a*(c7b-c7a)/(pow(m7a-m7b,2));
double e7d = em7b*(c7b-c7a)/(pow(m7a-m7b,2));
double eIntersect7 = pow(e7a*e7a+e7b*e7b+e7c*e7c+e7d*e7d,0.5);
double V7 = -exp(Intersect7);
double V7e = exp(Intersect7)*eIntersect7;

double c8a = fit8a->GetParameter(0);
double m8a = fit8a->GetParameter(1);
double c8b = fit8b->GetParameter(0);
double m8b = fit8b->GetParameter(1);
double ec8a = fit8a->GetParError(0);
double em8a = fit8a->GetParError(1);
double ec8b = fit8b->GetParError(0);
double em8b = fit8b->GetParError(1);
double Intersect8 = (c8b-c8a)/(m8a-m8b); 
double e8a = ec8b/(m8a-m8b);
double e8b = ec8a/(m8a-m8b);
double e8c = em8a*(c8b-c8a)/(pow(m8a-m8b,2));
double e8d = em8b*(c8b-c8a)/(pow(m8a-m8b,2));
double eIntersect8 = pow(e8a*e8a+e8b*e8b+e8c*e8c+e8d*e8d,0.5);
double V8 = -exp(Intersect8);
double V8e = exp(Intersect8)*eIntersect8;

double c9a = fit9a->GetParameter(0);
double m9a = fit9a->GetParameter(1);
double c9b = fit9b->GetParameter(0);
double m9b = fit9b->GetParameter(1);
double ec9a = fit9a->GetParError(0);
double em9a = fit9a->GetParError(1);
double ec9b = fit9b->GetParError(0);
double em9b = fit9b->GetParError(1);
double Intersect9 = (c9b-c9a)/(m9a-m9b); 
double e9a = ec9b/(m9a-m9b);
double e9b = ec9a/(m9a-m9b);
double e9c = em9a*(c9b-c9a)/(pow(m9a-m9b,2));
double e9d = em9b*(c9b-c9a)/(pow(m9a-m9b,2));
double eIntersect9 = pow(e9a*e9a+e9b*e9b+e9c*e9c+e9d*e9d,0.5);
double V9 = -exp(Intersect9);
double V9e = exp(Intersect9)*eIntersect9;

double c10a = fit10a->GetParameter(0);
double m10a = fit10a->GetParameter(1);
double c10b = fit10b->GetParameter(0);
double m10b = fit10b->GetParameter(1);
double ec10a = fit10a->GetParError(0);
double em10a = fit10a->GetParError(1);
double ec10b = fit10b->GetParError(0);
double em10b = fit10b->GetParError(1);
double Intersect10 = (c10b-c10a)/(m10a-m10b); 
double e10a = ec10b/(m10a-m10b);
double e10b = ec10a/(m10a-m10b);
double e10c = em10a*(c10b-c10a)/(pow(m10a-m10b,2));
double e10d = em10b*(c10b-c10a)/(pow(m10a-m10b,2));
double eIntersect10 = pow(e10a*e10a+e10b*e10b+e10c*e10c+e10d*e10d,0.5);
double V10 = -exp(Intersect10);
double V10e = exp(Intersect10)*eIntersect10;

double c11a = fit11a->GetParameter(0);
double m11a = fit11a->GetParameter(1);
double c11b = fit11b->GetParameter(0);
double m11b = fit11b->GetParameter(1);
double ec11a = fit11a->GetParError(0);
double em11a = fit11a->GetParError(1);
double ec11b = fit11b->GetParError(0);
double em11b = fit11b->GetParError(1);
double Intersect11 = (c11b-c11a)/(m11a-m11b); 
double e11a = ec11b/(m11a-m11b);
double e11b = ec11a/(m11a-m11b);
double e11c = em11a*(c11b-c11a)/(pow(m11a-m11b,2));
double e11d = em11b*(c11b-c11a)/(pow(m11a-m11b,2));
double eIntersect11 = pow(e11a*e11a+e11b*e11b+e11c*e11c+e11d*e11d,0.5);
double V11 = -exp(Intersect11);
double V11e = exp(Intersect11)*eIntersect11;

/*double c12a = fit12a->GetParameter(0);
double m12a = fit12a->GetParameter(1);
double c12b = fit12b->GetParameter(0);
double m12b = fit12b->GetParameter(1);
double ec12a = fit12a->GetParError(0);
double em12a = fit12a->GetParError(1);
double ec12b = fit12b->GetParError(0);
double em12b = fit12b->GetParError(1);
double Intersect12 = (c12b-c12a)/(m12a-m12b); 
double e12a = ec12b/(m12a-m12b);
double e12b = ec12a/(m12a-m12b);
double e12c = em12a*(c12b-c12a)/(pow(m12a-m12b,2));
double e12d = em12b*(c12b-c12a)/(pow(m12a-m12b,2));
double eIntersect12 = pow(e12a*e12a+e12b*e12b+e12c*e12c+e12d*e12d,0.5);
double V12 = -exp(Intersect12);
double V12e = exp(Intersect12)*eIntersect12;*/

double fluence1_2 = 14023253749889.1;
double fluence3_4 = 2494009052986.6;
double fluence5_6 = 666548326972.575;
double fluence7_8 = 1002928907428.77;
double fluence9_10 = 433123280376.32;
double fluence11_12 = 156208396201.296;

double efluence1_2 = 7.57E+11;
double efluence3_4 = 1.49E+11;
double efluence5_6 = 5.05E+10;
double efluence7_8 = 6.35E+10;
double efluence9_10 = 3.92E+10;
double efluence11_12 = 2.53E+10;
    
const Int_t n = 11;

Double_t x[n] = {fluence1_2, fluence1_2, fluence3_4, fluence3_4, fluence5_6, fluence5_6, fluence7_8, fluence7_8, fluence9_10, fluence9_10, fluence11_12};//, fluence11_12}; 
Double_t y[n] = {V1, V2, V3, V4, V5, V6, V7, V8, V9, V10, V11};//, V12};
Double_t ex[n] = {efluence1_2, efluence1_2, efluence3_4, efluence3_4, efluence5_6, efluence5_6, efluence7_8, efluence7_8, efluence9_10, efluence9_10, efluence11_12};//, efluence11_12}; 
Double_t ey[n] = {V1e, V2e, V3e, V4e, V5e, V6e, V7e, V8e, V9e, V10e, V11e};//, V12e};
    
    TCanvas *Results = new TCanvas("Results","Results",600,700);
    TGraphErrors *Result = new TGraphErrors(n,x,y,ex,ey);
        Result->SetTitle("");
		Result->GetXaxis()->SetTitle("Fluence #left(pcm^{-2}#right)");
		Result->GetYaxis()->SetTitle("Max. Depletion Voltage (V)");
        Result->SetMarkerStyle(20);
        Result->Draw("AP");

//2202 data

	TGraphErrors *gr1 = new TGraphErrors("Diode7_CV_2202_10kHz_irradiated.txt");
	TGraphErrors *gr2 = new TGraphErrors("Diode9_CV_2202_10kHz_irradiated.txt");
	TGraphErrors *gr3 = new TGraphErrors("Diode10_CV_2202_10kHz_irradiated.txt");
	TGraphErrors *gr4 = new TGraphErrors("Diode14_CV_2202_10kHz_irradiated.txt");
	TGraphErrors *gr5 = new TGraphErrors("DiodeKIT1s_CV_2202_10kHz_irradiated.txt");
	TGraphErrors *gr6 = new TGraphErrors("Diode24_CV_2301_10kHz.txt");
	
	TF1* fitD41 = new TF1("fit1","pol1",1.0,4.3);
	TF1* fitD42 = new TF1("fit2","pol1",4.4,5.0);	
	fitD41->SetParameter(1,-1.5);
	fitD42->SetParameter(1,-0.5);

	TF1* fitD61 = new TF1("fit1","pol1",1.0,4.5);
	TF1* fitD62 = new TF1("fit2","pol1",4.55,5.15);	
	fitD61->SetParameter(1,-1);
	fitD62->SetParameter(1,-1);

	TF1* fitD81 = new TF1("fit1","pol1",1.0,3.8);
	TF1* fitD82 = new TF1("fit2","pol1",4.1,5.0);	
	fitD81->SetParameter(1,-1.5);
	fitD82->SetParameter(1,-1);

	TF1* fitD151 = new TF1("fit1","pol1",1.0,4.1);
	TF1* fitD152 = new TF1("fit2","pol1",4.4,5.2);	
	fitD151->SetParameter(1,-1);
	fitD152->SetParameter(1,-1);

	TF1* fitDKIT1 = new TF1("fit1","pol1",1.0,3.9);
	TF1* fitDKIT2 = new TF1("fit2","pol1",4.0,4.5);	
	fitDKIT1->SetParameter(1,-0.5);
	fitDKIT2->SetParameter(1,-0.3);
	fitDKIT2->SetParameter(0,2.5);

	TF1* fitD241 = new TF1("fitD241","pol1",2.8,4.5);
	TF1* fitD242 = new TF1("fitD242","pol1",4.6,5.3);	
	fitD241->SetParameter(1,-1);
	fitD241->SetParameter(1,-1);

	//TCanvas *D4 = new TCanvas("D7","D7",600,700);//7
		//gr1->Draw("ALP");
		gr1->Fit(fitD41,"RN");
		gr1->Fit(fitD42,"RN");
		//fitD41->Draw("same");
		//fitD42->Draw("same");
	
	//TCanvas *D6 = new TCanvas("D9","D9",600,700);//9
		//gr2->Draw("ALP");
		gr2->Fit(fitD61,"RN");
		gr2->Fit(fitD62,"RN");
		//fitD61->Draw("same");
		//fitD62->Draw("same");

	//TCanvas *D8 = new TCanvas("D10","D10",600,700);//10
		//gr3->Draw("ALP");
		gr3->Fit(fitD81,"RN");
		gr3->Fit(fitD82,"RN");
		//fitD81->Draw("same");
		//fitD82->Draw("same");

	//TCanvas *D15 = new TCanvas("D14","D14",600,700);//14
		//gr4->Draw("ALP");
		gr4->Fit(fitD151,"RN");
		gr4->Fit(fitD152,"RN");
		//fitD151->Draw("same");
		//fitD152->Draw("same");
	
	//TCanvas *DKIT = new TCanvas("DKIT","DKIT",600,700);//KIT
		//gr5->Draw("ALP");
		gr5->Fit(fitDKIT1,"RN");
		gr5->Fit(fitDKIT2,"RN");
		//fitDKIT1->Draw("same");
		//fitDKIT2->Draw("same");

	/*TCanvas *D24 = new TCanvas("D24","D24",600,700);//24
		gr6->Draw("ALP");
		gr6->Fit(fitDKIT1,"RN");
		gr6->Fit(fitDKIT2,"RN");
		fitD241->Draw("same");
		fitD242->Draw("same");*/

	double cD41 = fitD41->GetParameter(0);
	double mD41 = fitD41->GetParameter(1);
	double cD42 = fitD42->GetParameter(0);
	double mD42 = fitD42->GetParameter(1);
	double ecD41 = fitD41->GetParError(0);
	double emD41 = fitD41->GetParError(1);
	double ecD42 = fitD42->GetParError(0);
	double emD42 = fitD42->GetParError(1);
    double IntersectD4 = (cD42-cD41)/(mD41-mD42); 
	double eD41 = ecD42/(mD41-mD42);
	double eD42 = ecD41/(mD41-mD42);
	double eD43 = emD41*(cD42-cD41)/(pow(mD41-mD42,2));
	double eD44 = emD42*(cD42-cD41)/(pow(mD41-mD42,2));
    double eIntersectD4 = pow(eD41*eD41+eD42*eD42+eD43*eD43+eD44*eD44,0.5);

	double cD61 = fitD61->GetParameter(0);
	double mD61 = fitD61->GetParameter(1);
	double cD62 = fitD62->GetParameter(0);
	double mD62 = fitD62->GetParameter(1);
	double ecD61 = fitD61->GetParError(0);
	double emD61 = fitD61->GetParError(1);
	double ecD62 = fitD62->GetParError(0);
	double emD62 = fitD62->GetParError(1);
    double IntersectD6 = (cD62-cD61)/(mD61-mD62); 
	double eD61 = ecD62/(mD61-mD62);
	double eD62 = ecD61/(mD61-mD62);
	double eD63 = emD61*(cD62-cD61)/(pow(mD61-mD62,2));
	double eD64 = emD62*(cD62-cD61)/(pow(mD61-mD62,2));
    double eIntersectD6 = pow(eD61*eD61+eD62*eD62+eD63*eD63+eD64*eD64,0.5);

	double cD81 = fitD81->GetParameter(0);
	double mD81 = fitD81->GetParameter(1);
	double cD82 = fitD82->GetParameter(0);
	double mD82 = fitD82->GetParameter(1);
	double ecD81 = fitD81->GetParError(0);
	double emD81 = fitD81->GetParError(1);
	double ecD82 = fitD82->GetParError(0);
	double emD82 = fitD82->GetParError(1);
    double IntersectD8 = (cD82-cD81)/(mD81-mD82); 
	double eD81 = ecD82/(mD81-mD82);
	double eD82 = ecD81/(mD81-mD82);
	double eD83 = emD81*(cD82-cD81)/(pow(mD81-mD82,2));
	double eD84 = emD82*(cD82-cD81)/(pow(mD81-mD82,2));
    double eIntersectD8 = pow(eD81*eD81+eD82*eD82+eD83*eD83+eD84*eD84,0.5);

	double cD151 = fitD151->GetParameter(0);
	double mD151 = fitD151->GetParameter(1);
	double cD152 = fitD152->GetParameter(0);
	double mD152 = fitD152->GetParameter(1);
	double ecD151 = fitD151->GetParError(0);
	double emD151 = fitD151->GetParError(1);
	double ecD152 = fitD152->GetParError(0);
	double emD152 = fitD152->GetParError(1);
    double IntersectD15 = (cD152-cD151)/(mD151-mD152); 
	double eD151 = ecD152/(mD151-mD152);
	double eD152 = ecD151/(mD151-mD152);
	double eD153 = emD151*(cD152-cD151)/(pow(mD151-mD152,2));
	double eD154 = emD152*(cD152-cD151)/(pow(mD151-mD152,2));
    double eIntersectD15 = pow(eD151*eD151+eD152*eD152+eD153*eD153+eD154*eD154,0.5);

	double cDKIT1 = fitDKIT1->GetParameter(0);
	double mDKIT1 = fitDKIT1->GetParameter(1);
	double cDKIT2 = fitDKIT2->GetParameter(0);
	double mDKIT2 = fitDKIT2->GetParameter(1);
	double ecDKIT1 = fitDKIT1->GetParError(0);
	double emDKIT1 = fitDKIT1->GetParError(1);
	double ecDKIT2 = fitDKIT2->GetParError(0);
	double emDKIT2 = fitDKIT2->GetParError(1);
    double IntersectDKIT = (cDKIT2-cDKIT1)/(mDKIT1-mDKIT2); 
	double eDKIT1 = ecDKIT2/(mDKIT1-mDKIT2);
	double eDKIT2 = ecDKIT1/(mDKIT1-mDKIT2);
	double eDKIT3 = emDKIT1*(cDKIT2-cDKIT1)/(pow(mDKIT1-mDKIT2,2));
	double eDKIT4 = emD152*(cDKIT2-cDKIT1)/(pow(mDKIT1-mDKIT2,2));
    double eIntersectDKIT = pow(eDKIT1*eDKIT1+eDKIT2*eDKIT2+eDKIT3*eDKIT3+eDKIT4*eDKIT4,0.5);

	/*double cD241 = fitD241->GetParameter(0);
	double mD241 = fitD241->GetParameter(1);
	double cD242 = fitD242->GetParameter(0);
	double mD242 = fitD242->GetParameter(1);
	double ecD241 = fitD241->GetParError(0);
	double emD241 = fitD241->GetParError(1);
	double ecD242 = fitD242->GetParError(0);
	double emD242 = fitD242->GetParError(1);
    double IntersectD24 = (cD242-cD241)/(mD241-mD242); 
	double eD241 = ecD242/(mD241-mD242);
	double eD242 = ecD241/(mD241-mD242);
	double eD243 = emD241*(cD242-cD241)/(pow(mD241-mD242,2));
	double eD244 = emD242*(cD242-cD241)/(pow(mD241-mD242,2));
    double eIntersectD24 = pow(eD241*eD241+eD242*eD242+eD243*eD243+eD244*eD244,0.5);*/

	double VD4 = -exp(IntersectD4);
	double VD4e = exp(IntersectD4)*eIntersectD4;

	double VD6 = -exp(IntersectD6);
	double VD6e = exp(IntersectD6)*eIntersectD6;

	double VD8 = -exp(IntersectD8);
	double VD8e = exp(IntersectD8)*eIntersectD8;

	double VD15 = -exp(IntersectD15);
	double VD15e = exp(IntersectD15)*eIntersectD15;
	
	double VDKIT = -exp(IntersectDKIT);
	double VDKITe = exp(IntersectDKIT)*eIntersectDKIT;
	
	/*double VD24 = -exp(IntersectD24);
	double VD24e = exp(IntersectD24)*eIntersectD24;*/

	double VD24 = -97.1892, VD24e = 3.95294;

	double calibration = 112.67;
	double calibration_error = 0.55238 + 5.358;

	double rawfluence1 = 1.30e14;
	double rawfluence2 = 5.27e13;
	double rawfluence3 = 5.90e14;
	double rawfluence4 = 2.28e13;
	double rawfluenceKIT = 5.0e12;
	
	double erawfluence1 = 84297588525.2318;
	double erawfluence2 = 74998109020.2371;
	double erawfluence3 = 90393110979.9842;
	double erawfluence4 = 81418286762.212;

	double sys_error = 0.134;

	double fluence1 = rawfluence1/calibration;
	double fluence2 = rawfluence2/calibration;
	double fluence3 = rawfluence3/calibration;
	double fluence4 = rawfluence4/calibration;
	
	double efluence1 = pow(pow(erawfluence1/calibration,2) + pow(rawfluence1*calibration_error/pow(calibration,2),2),0.5);
	double efluence2 = pow(pow(erawfluence2/calibration,2) + pow(rawfluence2*calibration_error/pow(calibration,2),2),0.5);
	double efluence3 = pow(pow(erawfluence3/calibration,2) + pow(rawfluence3*calibration_error/pow(calibration,2),2),0.5);
	double efluence4 = pow(pow(erawfluence4/calibration,2) + pow(rawfluence4*calibration_error/pow(calibration,2),2),0.5);
	double erawfluenceKIT = rawfluenceKIT*sys_error;

	double efluencesys1 = pow(pow(efluence1,2) + pow(fluence1*sys_error,2),0.5);
	double efluencesys2 = pow(pow(efluence2,2) + pow(fluence2*sys_error,2),0.5);
	double efluencesys3 = pow(pow(efluence3,2) + pow(fluence3*sys_error,2),0.5);
	double efluencesys4 = pow(pow(efluence4,2) + pow(fluence4*sys_error,2),0.5);	

	const Int_t n1 = 5;
	Double_t y1[n] = {VD4, VD6, VD8, VD15, VD24};
	Double_t x1[n] = {fluence1, fluence2, fluence3, fluence4, 0};//fluences
	Double_t ey1[n] = {VD4e, VD6e, VD8e, VD15e, VD24};
	Double_t ex1[n] = {efluencesys1, efluencesys2, efluencesys3, efluencesys4, 0};

	const Int_t i = 1;
	Double_t yKIT[i] = {VDKIT};
	Double_t xKIT[i] = {rawfluenceKIT};//fluences
	Double_t eKITy[i] = {VDKITe};
	Double_t eKITx[i] = {erawfluenceKIT};

	TCanvas *Results1 = new TCanvas("Results1","Results1",600,700);
	TGraphErrors *Result1 = new TGraphErrors(n1,x1,y1,ex1,ey1);
	TGraphErrors *Result2 = new TGraphErrors(i,xKIT,yKIT,eKITx,eKITy);
		TGaxis::SetMaxDigits(3);
		Result1->SetTitle("");
		Result1->GetXaxis()->SetTitle("Fluence #left(pcm^{-2}#right)");
		Result1->GetYaxis()->SetTitle("Max. Depletion Voltage (V)");
		Result1->SetMarkerStyle(20);
		Result2->SetMarkerStyle(24);
				
		/*TLatex *latex1 = new TLatex(Result->GetX()[0], Result->GetY()[0],"Diode 7");
		TLatex *latex2 = new TLatex(Result->GetX()[1], Result->GetY()[1],"Diode 9");
		TLatex *latex3 = new TLatex(Result->GetX()[2], Result->GetY()[2],"Diode 10");
		TLatex *latex4 = new TLatex(Result->GetX()[3], Result->GetY()[3],"Diode 14");
		TLatex *latex5 = new TLatex(Result->GetX()[4], Result->GetY()[4],"Diode KIT 1s");
		TLatex *latex6 = new TLatex(Result->GetX()[5], Result->GetY()[5],"Diode 24");
		Result->GetListOfFunctions()->Add(latex1);
		Result->GetListOfFunctions()->Add(latex2);
		Result->GetListOfFunctions()->Add(latex3);
		Result->GetListOfFunctions()->Add(latex4);
		Result->GetListOfFunctions()->Add(latex5);
		Result->GetListOfFunctions()->Add(latex6);
		latex1->SetTextSize(0.02); 
		latex2->SetTextSize(0.02); 
		latex3->SetTextSize(0.02); 
		latex4->SetTextSize(0.02);
		latex5->SetTextSize(0.02);
		latex6->SetTextSize(0.02);*/  

		Result1->Draw("AP");
		Result2->Draw("psame");

	 TLegend *legend = new TLegend(0.15,0.75,0.35,0.85);
   		legend->AddEntry(Result1,"MC40 Diodes","p");
   		legend->AddEntry(Result2,"KIT Diode","p");
   		legend->Draw();

	

	std::cout << "Diode 7 Max Depletion Voltage = " << VD4 << " +/- " << VD4e << " V" << std::endl;
	std::cout << "Diode 9 Max Depletion Voltage = " << VD6 << " +/- " << VD6e << " V" << std::endl;
	std::cout << "Diode 10 Max Depletion Voltage = " << VD8 << " +/- " << VD8e << " V" << std::endl;
	std::cout << "Diode 14 Max Depletion Voltage = " << VD15 << " +/- " << VD15e << " V" << std::endl;
	std::cout << "Diode KIT_1_s Max Depletion Voltage = " << VDKIT << " +/- " << VDKITe << " V" << std::endl;
	std::cout << "Diode 24 Max Depletion Voltage = " << VD24 << " +/- " << VD24e << " V" << std::endl;
	//std::cout << "Gradient = " << fit->GetParameter(1) << " +/- " << fit->GetParError(1) << std::endl;
	

    std::cout << V1 << " +/- " << V1e << "  " << fluence1_2 << efluence1_2 << std::endl;
    std::cout << V2 << " +/- " << V2e << "  " << fluence1_2 << efluence1_2 <<  std::endl;
    std::cout << V3 << " +/- " << V3e << "  " << fluence3_4 << efluence3_4 <<  std::endl;
    std::cout << V4 << " +/- " << V4e << "  " << fluence3_4 << efluence3_4 <<  std::endl;
    std::cout << V5 << " +/- " << V5e << "  " << fluence5_6 << efluence5_6 <<  std::endl;
    std::cout << V6 << " +/- " << V6e << "  " << fluence5_6 << efluence5_6 <<  std::endl;
    std::cout << V7 << " +/- " << V7e << "  " << fluence7_8 << efluence7_8 <<  std::endl;
    std::cout << V8 << " +/- " << V8e << "  " << fluence7_8 << efluence7_8 <<  std::endl;
    std::cout << V9 << " +/- " << V9e << "  " << fluence9_10 << efluence9_10 <<  std::endl;
    std::cout << V10 << " +/- " << V10e << "  " << fluence9_10 << efluence9_10 <<  std::endl;
    std::cout << V11 << " +/- " << V11e << "  " << fluence11_12 << efluence11_12 <<  std::endl;
    //std::cout << V12 << " +/- " << V12e << "  " << fluence11_12 << efluence11_12 <<  std::endl;
 
	Result1->SetMarkerSize(1.5);
	Result2->SetMarkerSize(1.5);
	Result->SetMarkerSize(1.5);
	

    TCanvas *Combined = new TCanvas("Combined","Combined",600,700);
	Combined->SetRightMargin(1);
    TMultiGraph *mg = new TMultiGraph();
        mg->Add(Result,"p");
        mg->Add(Result1,"p");
        mg->Add(Result2,"p");
        mg->Draw("AP");        
        TGaxis::SetMaxDigits(3);
		mg->SetTitle("");
		mg->GetXaxis()->SetTitle("Fluence #left(pcm^{-2}#right)");
		mg->GetYaxis()->SetTitle("Max. Depletion Voltage (V)");

        TLegend *legend1 = new TLegend(0.15,0.75,0.35,0.85);
   		legend1->AddEntry(Result1,"MC40 Diodes","p");
   		legend1->AddEntry(Result2,"KIT Diode","p");
   		legend1->Draw();
       
       
}
