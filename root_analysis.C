//void root_analysis(char* filename)
{
        gROOT->Reset();
        gROOT->SetStyle("Plain");
        gStyle->SetOptTitle(0);
        gStyle->SetOptStat(1101);

        //TFile f(filename);
        TFile f("rootfiles/SCExam10GeVG4_Pb10cm20layers.root");

        TCanvas* c1 = new TCanvas("c1", "c1", 20, 20, 1000, 1000);
        TH1D* h = (TH1D*)f.Get("Eabs_tot");
        int nbins_h = h->GetSize()-2;
        double xmax_h = h->GetBinCenter(nbins_h)+(h->GetBinWidth(nbins_h-1)/2);
        TH1D* h_new = new TH1D("Eabs_deposited", "Eabs deposited", nbins_h, 0., (xmax_h/1000));
        for (int i=0; i<nbins_h; i++) {
                h_new->SetBinContent(i, h->GetBinContent(i));
        }
        h_new->GetXaxis()->SetTitle("E [GeV]");
        h_new->GetYaxis()->SetTitle("Events");
        h_new->SetFillColor(kBlue);
        h_new->Draw("HIST");

        c2 = new TCanvas("c2", "c2", 20, 20, 1000, 1000);
        h = (TH1D*)f.Get("Egap_tot");
        nbins_h = h->GetSize()-2;
        xmax_h = h->GetBinCenter(nbins_h)+(h->GetBinWidth(nbins_h-1)/2);
        h_new = new TH1D("Egap_deposited", "Egap deposited", nbins_h, 0., (xmax_h/1000));
        for (int i=0; i<nbins_h; i++) {
                h_new->SetBinContent(i, h->GetBinContent(i));
        }
        h_new->GetXaxis()->SetTitle("E [GeV]");
        h_new->GetYaxis()->SetTitle("Events");
        h_new->SetFillColor(kBlue);
        h_new->Draw("HIST");

        c3 = new TCanvas("c3", "c3", 20, 20, 1000, 1000);
        h = (TH1D*)f.Get("Labs_tot");
        nbins_h = h->GetSize()-2;
        xmax_h = h->GetBinCenter(nbins_h)+(h->GetBinWidth(nbins_h-1)/2);
        h_new = new TH1D("Labs_deposited", "Labs deposited", nbins_h, 0., (xmax_h/1000));
        for (int i=0; i<nbins_h; i++) {
                h_new->SetBinContent(i, h->GetBinContent(i));
        }
        h_new->GetXaxis()->SetTitle("Depth [m]");
        h_new->GetYaxis()->SetTitle("Events");
        h_new->SetFillColor(kBlue);
        h_new->Draw("HIST");

        c4 = new TCanvas("c4", "c4", 20, 20, 1000, 1000);
        h = (TH1D*)f.Get("Lgap_tot");
        nbins_h = h->GetSize()-2;
        xmax_h = h->GetBinCenter(nbins_h)+(h->GetBinWidth(nbins_h-1)/2);
        h_new = new TH1D("Lgap_deposited", "Lgap deposited", nbins_h, 0., (xmax_h/1000));
        for (int i=0; i<nbins_h; i++) {
                h_new->SetBinContent(i, h->GetBinContent(i));
        }
        h_new->GetXaxis()->SetTitle("Depth [m]");
        h_new->GetYaxis()->SetTitle("Events");
        h_new->SetFillColor(kBlue);
        h_new->Draw("HIST");

}


