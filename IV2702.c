#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TAxis.h"
#include "TString.h"
#include "iostream"

void PlotDiodes(TString txtName="", TString graphTitle ="")
{
    TGraphErrors *graph = new TGraphErrors(txtName);
        graph->GetXaxis()->SetTitle("Voltage (V)");
        graph->GetYaxis()->SetTitle("Leakage Current (nA)");
        graph->SetTitle(graphTitle);

    TCanvas *canvas = new TCanvas(txtName,txtName);
        graph->Draw("ALP");

}

void IV2702()
{
    PlotDiodes("Diode25_IV_2602.txt","Diode 25 Non-Irradiated I-V Curve 26/02");
    PlotDiodes("Diode26_IV_2602.txt","Diode 26 Non-Irradiated I-V Curve 26/02");
    PlotDiodes("Diode27_IV_2602.txt","Diode 27 Non-Irradiated I-V Curve 26/02");
    PlotDiodes("Diode28_IV_2602.txt","Diode 28 Non-Irradiated I-V Curve 26/02");
    PlotDiodes("Diode29_IV_2602.txt","Diode 29 Non-Irradiated I-V Curve 26/02");
    PlotDiodes("Diode30_IV_2602.txt","Diode 30 Non-Irradiated I-V Curve 26/02");
    PlotDiodes("Diode31_IV_2602.txt","Diode 31 Non-Irradiated I-V Curve 26/02");
    PlotDiodes("Diode32_IV_2602.txt","Diode 32 Non-Irradiated I-V Curve 26/02");
    PlotDiodes("Diode33_IV_2602.txt","Diode 33 Non-Irradiated I-V Curve 26/02");
    PlotDiodes("Diode34_IV_2602.txt","Diode 34 Non-Irradiated I-V Curve 26/02");
    PlotDiodes("Diode35_IV_2602.txt","Diode 35 Non-Irradiated I-V Curve 26/02");
    PlotDiodes("Diode36_IV_2602.txt","Diode 36 Non-Irradiated I-V Curve 26/02");
    PlotDiodes("Diode37_IV_2602.txt","Diode 37 Non-Irradiated I-V Curve 26/02");
    PlotDiodes("Diode38_IV_2602.txt","Diode 38 Non-Irradiated I-V Curve 26/02");
    PlotDiodes("Diode39_IV_2602.txt","Diode 39 Non-Irradiated I-V Curve 26/02");
}
