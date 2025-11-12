//moin!


#include<iostream>
#include<cmath>
#include<fstream>
#include<vector>
#include<numeric>


using namespace std;

vector<int> abundance_calculator(ifstream&);
vector<double> poisson_collector(vector<int>);
double poisson(double, int);

int main(){

  vector<int> zaehler(11);
  vector<double> poisson_estimations(11);
  ifstream summs_file;
  ofstream output_file1;
  ofstream output_file2;
  
  summs_file.open("datensumme.txt");
  output_file1.open("hist.txt");
  output_file2.open("histpoi.txt");

  zaehler = abundance_calculator(summs_file);
  poisson_estimations = poisson_collector(zaehler);
  
  for(int i=0; i< zaehler.size(); i++){
    //cout<< i << " : " << zaehler[i]<<endl;
    output_file1 << i << '\t' << zaehler[i] << endl;
    output_file2 << i << '\t' << zaehler[i] << '\t' << poisson_estimations[i] << endl;
    cout << i << '\t' << zaehler[i] << '\t' << poisson_estimations[i] << endl;
  }

  summs_file.close();
  output_file1.close();
  output_file2.close();
  return 0;
}


vector<int> abundance_calculator(ifstream& file){
  vector<int> abund_vect(11);
  int col1;

  while(file >> col1)
    abund_vect[col1] += 1;
  return abund_vect;
}



double poisson(double mean, int observation){
  int gamma;
  double mu_ka, exp_mu, pois;
  gamma = tgamma(double(observation + 1));
  mu_ka = pow(mean, observation);
  exp_mu = exp(-1 * mean);
  pois = (mu_ka * exp_mu) / (gamma);
  pois;
  return pois;
}

vector<double> poisson_collector(vector<int> hists){
  vector<double> poisson_values(hists.size());
  double mean, sum_games, sum_goals;

  sum_goals = 0.;
  sum_games = accumulate(hists.begin(), hists.end(), 0.0);
  for(int i=0; i < hists.size(); i++)
    sum_goals += (hists[i] * i);
  
  mean = sum_goals / sum_games;  
  
  for(int i=0; i < hists.size(); i++)
    poisson_values[i] = poisson(mean, i) * sum_games;

  return poisson_values;
}

    
  
  
  
