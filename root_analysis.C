
{
        gROOT->Reset();
        gROOT->SetStyle("Plain");

        //TFile f(filename);
        TFile f("rootfiles/SCExam1GeVG4_Pb5cm.root");

        TCanvas* c1 = new TCanvas("c1", "c1", 20, 20, 1000, 1000);
        TH1D* h = (TH1D*)f.Get("Eabs_tot");
        h->GetXaxis()->SetTitle("E [GeV]");
        h->Draw("HIST");

        TCanvas* c2 = new TCanvas("c2", "c2", 20, 20, 1000, 1000);
        h = (TH1D*)f.Get("Egap_tot");
        h->GetXaxis()->SetTitle("E [GeV]");
        h->Draw("HIST");

        TCanvas* c3 = new TCanvas("c3", "c3", 20, 20, 1000, 1000);
        h = (TH1D*)f.Get("Labs_tot");
        h->GetXaxis()->SetTitle("depth [cm]");
        h->Draw("HIST");

        TCanvas* c4 = new TCanvas("c4", "c4", 20, 20, 1000, 1000);
        h = (TH1D*)f.Get("Lgap_tot");
        h->GetXaxis()->SetTitle("depth [cm]");
        h->Draw("HIST");

        /*TH1D* h = (TH1D*)f.Get("histograms/Egap");
          int bin1 = h->FindFirstBinAbove(h->GetMaximum()/2);
          int bin2 = h->FindLastBinAbove(h->GetMaximum()/2);
          double fwhm = h->GetBinCenter(bin2) - h->GetBinCenter(bin1);
          double mean = h->GetMean();
          double rms = h->GetRMS();
          double res = fwhm/mean;
          double res2 = rms/mean;

          cout << "FWHM for Egap is: " << fwhm << endl;
          cout << "RMS for Egap is: " << rms << endl;
          cout << "Mean for Egap is: " << mean << endl;
          cout << "Energy resolution (with FWHM) is: " << res*100 << "%" << endl;
          cout << "Energy resolution (with RMS) is: " << res2*100 << "%" << endl;*/
}


