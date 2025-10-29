// Moin!

#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

double mean_calculation(ifstream& file);
double variance_calculation(ifstream& file, double mean);
double std_calculation(double variance);
void split_into_bunches(ifstream&, int);


int main() {
  double initial_mean, mean_means = 0;
  double initial_vars, mean_vars = 0;
  double bessel_correction;
  ifstream input_file;
  input_file.open("datensumme.txt");

  initial_mean = mean_calculation(input_file);
  input_file.clear();
  input_file.seekg(0, ios::beg);

  initial_vars = variance_calculation(input_file, initial_mean);
  input_file.clear();
  input_file.seekg(0, ios::beg);

  
  split_into_bunches(input_file, 9);
  input_file.close();
  
  
  ofstream means_file("mittelwerte.txt");
  ofstream vars_file("varianzen.txt");
  
  int num_bunches = 26;
  for (int i = 1; i <= num_bunches; ++i) {
    string bunch_filename = "bunch" + to_string(i) + ".txt";
    ifstream bunch_file(bunch_filename);
    double mean = mean_calculation(bunch_file);
    
    bunch_file.clear();
    bunch_file.seekg(0, ios::beg);
    
    double variance = variance_calculation(bunch_file, mean);
    
    
    means_file << mean << endl;
    vars_file << variance << endl;
    mean_means += mean;
    mean_vars += variance;
    
    bunch_file.close();
    remove(bunch_filename.c_str());
  }
  
  means_file.close();
  vars_file.close();



  mean_means /= num_bunches;
  mean_vars /= (num_bunches - 1);

  bessel_correction = mean_vars * (double(num_bunches) / (num_bunches -1));
  
  cout << "done! \nThe mean of means is : " << mean_means<<endl;
  cout << "And the mean of variances si : "<< mean_vars<<endl;
  cout << "While the mean of total data is : " << initial_mean<<endl;
  cout << "And the variance of total data is: "<< initial_vars<<endl;
  cout << "as it seen the bessel corrected of variance is : "<< bessel_correction <<endl;
  
  return 0;
}


double mean_calculation(ifstream& file) {
  double sum = 0.0;
  int count = 0;
  int col1;
  while (file >> col1) {
    sum += col1;
    count++;
    }
  return sum / count;
}

double variance_calculation(ifstream& file, double mean){
  double variance = 0;
  double count = 0;
  int col1;

  while(file >> col1){
    variance += pow((col1 - mean), 2);
    count++;
  }
  variance /= count;
  return variance;
}

double std_calculation(double variance) {
    return sqrt(variance);
}


void split_into_bunches(ifstream& input, int bunch_size) {
  ofstream bunch_file;
  string line;
  int bunch_num = 1;
  int line_count = 0;
  
    while (getline(input, line)) {  
      if (line_count % bunch_size == 0) {
	if (bunch_file.is_open()) {
	  bunch_file.close();
	}
	string filename = "bunch" + to_string(bunch_num) + ".txt";
	bunch_file.open(filename);
	++bunch_num;
      }
      bunch_file << line << endl;
      ++line_count;
    }
    if (bunch_file.is_open()) {
      bunch_file.close();
    }
}
