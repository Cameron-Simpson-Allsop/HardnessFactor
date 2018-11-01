int GraphsScaling()

{
        TGraphErrors *gr1 = new TGraphErrors("IVDiode2EC25Scaled_2410.txt");
        TGraphErrors *gr2 = new TGraphErrors("IVDiode2EC30Scaled_2410.txt");
        TGraphErrors *gr3 = new TGraphErrors("IVDiode2EC35Scaled_2610.txt");
        TGraphErrors *gr4 = new TGraphErrors("IVDiode2EC40Scaled_2610.txt");

                gr1->GetXaxis()->SetTitle("Voltage(V)");
                gr1->GetYaxis()->SetTitle("Leakage Current (uA)");
                gr1->GetYaxis()->SetTitleOffset(1.4);
                gr1->SetTitle("Photodiode 2 Temperature Comparison");

                gr1->SetLineColor(kBlue);
                gr2->SetLineColor(kRed);
                gr3->SetLineColor(kGreen);
                gr4->SetLineColor(kOrange);

        TCanvas *c1 = new TCanvas("c1","c1",600,700);
                gr1->Draw("ALP");
                gr2->Draw("same");
                gr3->Draw("same");
                gr4->Draw("same");

        auto legend = new TLegend(0.5,0.5,0.7,0.7);
                legend->SetHeader("Legend");
                legend->AddEntry(gr1,"25C","l");
                legend->AddEntry(gr2,"30C","l");
                legend->AddEntry(gr3,"35C","l");
                legend->AddEntry(gr4,"40C","l");
                legend->Draw();

return 0;
}

