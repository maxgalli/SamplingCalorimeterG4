{

        gROOT->Reset();
        gROOT->SetStyle("Plain");
        gStyle->SetOptTitle(kFALSE);
        gStyle->SetOptStat(0);
        gStyle->SetPalette();

        TFile f("rootfiles/SCExam3GeVG4_Pb5cm20layers.root");

        //c1 = new TCanvas("c1", "c1", 20, 20, 1000, 1000);


        /*
           h1 = (TH1D*)f.Get("Pgap2");
           nbins_h1 = h1->GetSize()-2;
           xmax_h1 = h1->GetBinCenter(nbins_h1)+(h1->GetBinWidth(nbins_h1-1)/2);
           h_new1 = new TH1D("h1", "Depth: 1.75 int. lenghts", nbins_h1, 0., (xmax_h1/1000));
           for (int i=0; i<nbins_h1; i++) {
           h_new1->SetBinContent(i, h1->GetBinContent(i));
        //cout << h_new1->GetBinContent(i) << endl;
        //cout << h_new1->GetBinCenter(i) << endl;
        }
        h_new1->GetXaxis()->SetRangeUser(0,2);
        h_new1->GetXaxis()->SetTitle("R [m]");
        h_new1->GetYaxis()->SetTitle("Events");
        h_new1->SetMarkerStyle(kFullCircle);
        h_new1->SetMarkerColor(kRed);

        h2 = (TH1D*)f.Get("Pgap12");
        nbins_h2 = h2->GetSize()-2;
        xmax_h2 = h2->GetBinCenter(nbins_h2)+(h2->GetBinWidth(nbins_h2-1)/2);
        h_new2 = new TH1D("h2", "Depth: 7.61 int.lenghts", nbins_h2, 0., (xmax_h2/1000));
        for (int i=0; i<nbins_h2; i++) {
        h_new2->SetBinContent(i, h2->GetBinContent(i));
        }
        h_new2->GetXaxis()->SetRangeUser(0,2);
        h_new2->GetXaxis()->SetTitle("R [m]");
        h_new2->GetYaxis()->SetTitle("Events");
        h_new2->SetMarkerStyle(kFullSquare);
        h_new2->SetMarkerColor(kBlue);

        h3 = (TH1D*)f.Get("Pgap16");
        nbins_h3 = h3->GetSize()-2;
        xmax_h3 = h3->GetBinCenter(nbins_h3)+(h3->GetBinWidth(nbins_h3-1)/2);
        h_new3 = new TH1D("h3", "Depth: 9.91 int.lenghts", nbins_h3, 0., (xmax_h3/1000));
        for (int i=0; i<nbins_h3; i++) {
        h_new3->SetBinContent(i, h3->GetBinContent(i));
        }
        h_new3->GetXaxis()->SetRangeUser(0,2);
        h_new3->GetXaxis()->SetTitle("R [m]");
        h_new3->GetYaxis()->SetTitle("Events");
        h_new3->SetMarkerStyle(kFullTriangleUp);
        h_new3->SetMarkerColor(kGreen);

        h_new1->Draw("P");
        h_new2->Draw("SAME P");
        h_new3->Draw("SAME P");

        gPad->BuildLegend();*/


        c1 = new TCanvas("c1", "c1", 20, 20, 1000, 1000);
        h1 = (TH2D*)f.Get("Pgap2D12");
        h1->SetTitle("XY plan, depth: 7.61 int. lenghts");
        h1->GetXaxis()->SetTitle("X [mm]");
        h1->GetYaxis()->SetTitle("Y [mm]");
        h1->SetMarkerColor(kRed);
        h1->SetLineColor(kRed);
        h1->Draw();
        gPad->BuildLegend();

        c2 = new TCanvas("c2", "c2", 20, 20, 1000, 1000);
        h2 = (TH2D*)f.Get("Pgap2D2");
        h2->SetTitle("XY plan, depth: 1.75 int.lenghts");
        h2->GetXaxis()->SetTitle("X [mm]");
        h2->GetYaxis()->SetTitle("Y [mm]");
        h2->SetMarkerColor(kBlue);
        h2->SetLineColor(kBlue);
        h2->Draw();
        gPad->BuildLegend();
}
