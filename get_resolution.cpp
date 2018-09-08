#include <iostream>
#include <TFile.h>
#include <TH1.h>

using namespace std;

int main (int argc, char** argv ){

        char* filename = argv[1];

        TFile f(filename);

        // with logaritmic scale for y
        TH1D* h = (TH1D*)f.Get("histograms/Egap");
        int bin1 = h->FindFirstBinAbove(h->GetMaximum()/2);
        int bin2 = h->FindLastBinAbove(h->GetMaximum()/2);
        double fwhm = h->GetBinCenter(bin2) - h->GetBinCenter(bin1);
        double mean = h->GetMean();
        double res = fwhm/mean;

        cout << "FWHM for Egap is: " << fwhm << endl;
        cout << "Mean for Egap is: " << mean << endl;
        cout << "Energy resolution is: " << res*100 << "%" << endl;

}
