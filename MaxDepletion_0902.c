#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TAxis.h"
#include "TString.h"
#include "iostream"

struct Irradiated_Voltage
{ 
	float irr_voltage = 0;
    float irr_voltage_error = 0;
};

struct Voltage
{ 
	float voltage = 0;
    float voltage_error = 0;
};

Irradiated_Voltage ExtractIrradiatedVoltage(TString txtName="", TString graphTitle="")
{
	TGraphErrors *g = new TGraphErrors(txtName); 		
	g->GetXaxis()->SetTitle("Ln(-V) (Ln(v))");
	g->GetYaxis()->SetTitle("Ln(C) (Ln(pF))");
	g->GetYaxis()->SetTitleOffset(1.45);
	g->SetTitle("");
	
	g->SetMarkerStyle(20);
	g->SetMarkerSize(0.5);		

	TF1* fit1 = new TF1("fit1","pol1",1.0,3.8);
	TF1* fit2 = new TF1("fit2","pol1",3.9,5.2);	
	fit1->SetParameter(1,-2);
	fit1->SetLineColor(kBlack);
	fit2->SetLineColor(kBlack);
	fit1->SetLineWidth(1);
	fit2->SetLineWidth(1);

	TCanvas *canvas = new TCanvas(txtName,txtName);
		g->Draw("AP");
		g->Fit(fit1,"RN");
		g->Fit(fit2,"RN");
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
    double Intersect = (c2-c1)/(m1-m2); 
	double e1 = ec2/(m1-m2);
	double e2 = ec1/(m1-m2);
	double e3 = em1*(c2-c1)/(pow(m1-m2,2));
	double e4 = em2*(c2-c1)/(pow(m1-m2,2));
    double eIntersect = pow(e1*e1+e2*e2+e3*e3+e4*e4,0.5);

    Irradiated_Voltage iV;
    iV.irr_voltage = -exp(Intersect);
    iV.irr_voltage_error = exp(Intersect)*eIntersect;
    
    //std::cout << txtName << " Max Depletion Voltage = " << iV.irr_voltage << " +/- " << iV.irr_voltage_error << std::endl;

    return iV;

}

Voltage ExtractVoltage(TString txtName="", TString graphTitle="")
{
	TGraphErrors *g = new TGraphErrors(txtName); 		
	g->GetXaxis()->SetTitle("Ln(-V) (Ln(v))");
	g->GetYaxis()->SetTitle("Ln(C) (Ln(pF))");
	g->GetYaxis()->SetTitleOffset(1.45);
	g->SetTitle(graphTitle);
		

	TF1* fit1 = new TF1("fit1","pol1",2.8,4.55);
	TF1* fit2 = new TF1("fit2","pol1",4.6,5.3);	
	fit1->SetParameter(1,-1);

	TCanvas *canvas = new TCanvas(txtName,txtName);
		g->Draw("ALP");
		g->Fit(fit1,"RN");
		g->Fit(fit2,"RN");
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
    double Intersect = (c2-c1)/(m1-m2); 
	double e1 = ec2/(m1-m2);
	double e2 = ec1/(m1-m2);
	double e3 = em1*(c2-c1)/(pow(m1-m2,2));
	double e4 = em2*(c2-c1)/(pow(m1-m2,2));
    double eIntersect = pow(e1*e1+e2*e2+e3*e3+e4*e4,0.5);

    Voltage V;
    V.voltage = -exp(Intersect);
    V.voltage_error = exp(Intersect)*eIntersect;
    
    //std::cout << txtName << " Max Depletion Voltage = " << V.voltage << " +/- " << V.voltage_error << std::endl;

    return V;

}

void Evaluate_Irradiated_Voltage(std::vector<Irradiated_Voltage> ivoltages)
{

    double x = 0;
    double ex = 0;
    double ex_squared = 0;
    double j = 0;
    
    std::cout << "=======================================================================" << std::endl;
    std::cout << "Max depletion voltage in order of increasing frequency (irradiated)..." << std::endl;
    std::cout << " " << std::endl;

    for(unsigned int i(0); i<ivoltages.size(); i++)  
	{ 
        x = x + ivoltages[i].irr_voltage;
        ex_squared = ex_squared + pow(ivoltages[i].irr_voltage_error,2);
        ex = pow(ex_squared,0.5);
        j = j + 1.0;   

        std::cout << "Max Depletion Voltage " << j << " = " << ivoltages[i].irr_voltage << " +/- " << ivoltages[i].irr_voltage_error << " V" << std::endl;
        //std::cout << x << " " << ex << std::endl;         
	}

    std::cout << " " << std::endl;
    std::cout << "=======================================================================" << std::endl;

    for(unsigned int n(0); n<ivoltages.size(); n++)
    {
        if(n==1)
        {
        std::cout << "Max Depletion Voltage (Irradiated, 10kHz) = " << ivoltages[n].irr_voltage << " +/- " << ivoltages[n].irr_voltage_error << " V" << std::endl;  
        }
    }

    double average = x/j;
    double average_error = ex/j;
    
    std::cout << "Average Max Depletion Voltage (Irradiated) = " << average << " +/- " << average_error << " V" << std::endl;
    std::cout << "=======================================================================" << std::endl;
    
}

void Evaluate_Voltage(std::vector<Voltage> voltages)
{

    double x = 0;
    double ex = 0;
    double ex_squared = 0;
    double j = 0;
    
    std::cout << "=======================================================================" << std::endl;
    std::cout << "Max depletion voltage in order of increasing frequency (non-irradiated)..." << std::endl;
    std::cout << " " << std::endl;

    for(unsigned int i(0); i<voltages.size(); i++)  
	{ 
        x = x + voltages[i].voltage;
        ex_squared = ex_squared + pow(voltages[i].voltage_error,2);
        ex = pow(ex_squared,0.5);
        j = j + 1.0;

        std::cout << "Max Depletion Voltage " << j << " = " << voltages[i].voltage << " +/- " << voltages[i].voltage_error << " V" << std::endl;
        //std::cout << x << " " << ex << std::endl; 
	}
    std::cout << " " << std::endl;
    std::cout << "=======================================================================" << std::endl;

    for(unsigned int n(0); n<voltages.size(); n++)
    {
        if(n==1)
        {
        std::cout << "Max Depletion Voltage (Non-Irradiated, 10kHz) = " << voltages[n].voltage << " +/- " << voltages[n].voltage_error << " V" << std::endl;  
        }
    }

    double average = x/j;
    double average_error = ex/j;
    
    std::cout << "Average Max Depletion Voltage (Non-Irradiated) = " << average << " +/- " << average_error << " V" << std::endl;
    std::cout << "=======================================================================" << std::endl;
    
}

void MaxDepletion_0902()
{

    std::vector<Irradiated_Voltage> V_irr;

    Irradiated_Voltage iV1 = ExtractIrradiatedVoltage("Diode3_CV_0802_5kHz.txt","Diode 3 Irradiated C-V 08/02 5kHz");
    Irradiated_Voltage iV2 = ExtractIrradiatedVoltage("Diode3_CV_0802_10kHz.txt","Diode 3 Irradiated C-V 08/02 10kHz");
    Irradiated_Voltage iV3 = ExtractIrradiatedVoltage("Diode3_CV_0802_30kHz.txt","Diode 3 Irradiated C-V 08/02 30kHz");
    Irradiated_Voltage iV4 = ExtractIrradiatedVoltage("Diode3_CV_0802_60kHz.txt","Diode 3 Irradiated C-V 08/02 60kHz");
    Irradiated_Voltage iV5 = ExtractIrradiatedVoltage("Diode3_CV_0802_100kHz.txt","Diode 3 Irradiated C-V 08/02 100kHz");
    
    std::vector<Voltage> V;

    Voltage V1 = ExtractVoltage("Diode24_CV_2301_5kHz.txt","Diode 24 Non-Irradiated C-V 23/01 5kHz");
    Voltage V2 = ExtractVoltage("Diode24_CV_2301_10kHz.txt","Diode 24 Non-Irradiated C-V 23/01 10kHz");
    Voltage V3 = ExtractVoltage("Diode24_CV_2301_30kHz.txt","Diode 24 Non-Irradiated C-V 23/01 30kHz");
    Voltage V4 = ExtractVoltage("Diode24_CV_2301_60kHz.txt","Diode 24 Non-Irradiated C-V 23/01 60kHz");
    Voltage V5 = ExtractVoltage("Diode24_CV_2301_100kHz.txt","Diode 24 Non-Irradiated C-V 23/01 100kHz");

    V_irr.push_back(iV1);
    V_irr.push_back(iV2);
    V_irr.push_back(iV3);
    V_irr.push_back(iV4);
    V_irr.push_back(iV5);

    V.push_back(V1);
    V.push_back(V2);
    V.push_back(V3);
    V.push_back(V4);
    V.push_back(V5);
    
    Evaluate_Irradiated_Voltage(V_irr);
    Evaluate_Voltage(V);    
    
}






