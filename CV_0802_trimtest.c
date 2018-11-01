void CV_0802_trimtest()
{
    TGraph *g1 = new TGraph("CV_trimtest_5kHz_0802.txt");
    TGraph *g2 = new TGraph("CV_trimtest_10kHz_0802.txt");
    TGraph *g3 = new TGraph("CV_trimtest_30kHz_0802.txt");
    TGraph *g4 = new TGraph("CV_trimtest_60kHz_0802.txt");
    TGraph *g5 = new TGraph("CV_trimtest_100kHz_0802.txt");
    
    g1->SetMarkerStyle(20);
    g2->SetMarkerStyle(21);
    g3->SetMarkerStyle(22);
    g4->SetMarkerStyle(23);
    g5->SetMarkerStyle(33);

    g1->SetMarkerSize(1);
    g2->SetMarkerSize(1);
    g3->SetMarkerSize(1);
    g4->SetMarkerSize(1);
    g5->SetMarkerSize(1);

    g1->SetMarkerColor(1);
    g2->SetMarkerColor(2);
    g3->SetMarkerColor(8);
    g4->SetMarkerColor(4);
    g5->SetMarkerColor(6);
    
    TMultiGraph *mg = new TMultiGraph();
        mg->Add(g1);
        mg->Add(g2);
        mg->Add(g3);
        mg->Add(g4);
        mg->Add(g5);
        
        mg->SetTitle("C-V Background (No Diode)");
        mg->GetXaxis()->SetTitle("Voltage (-V)");
        mg->GetYaxis()->SetTitle("Capacitance (fF)");         

    TCanvas *errors = new TCanvas("errors","errors",600,700);

    mg->Draw("AP");

    TLegend *legend = new TLegend(0.13,0.63,0.25,0.88);
                legend->AddEntry(g1,"5kHz","p");
                legend->AddEntry(g2,"10kHz","p");
                legend->AddEntry(g3,"30kHz","p");
		        legend->AddEntry(g4,"60kHz","p");
		        legend->AddEntry(g5,"100kHz","p");
		        legend->Draw();
    
}
