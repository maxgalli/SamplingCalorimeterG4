{
        TFile f("rootfiles/SCExam10GeVG4_Pb10cm20layers.root");
        TH1D* h = (TH1D*)f.Get("Egap_tot");

        // resolutions
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
        cout << "Energy resolution (with RMS) is: " << res2*100 << "%" << endl;
}
