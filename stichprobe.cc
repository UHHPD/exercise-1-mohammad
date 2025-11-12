// Moin!

#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

double mean_calculation(ifstream&);
double variance_calculation(ifstream&, double);
double std_calculation(double);

int main (){
  double mean, variance, standard_deviation;
  ifstream input_file;
  input_file.open("datensumme.txt");


  mean = mean_calculation(input_file);
  cout<< "mean value of summs is :\t"<<mean<<endl;

  input_file.clear();
  input_file.seekg(0, ios::beg);

  
  variance = variance_calculation(input_file, mean);
  cout<< "variance value of summs is :\t"<<variance<<endl;


  standard_deviation = std_calculation(variance);
  cout<< "Standard Deviation is :\t"<<standard_deviation<<endl;
  
  input_file.close();

  return 0;
}



double mean_calculation(ifstream& file){
  double sum = 0;
  int count = 0;
  int col1;
  while(file >> col1){
    sum += col1;
    count ++;
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

double std_calculation(double variance){
  double standard_deviation;
  standard_deviation = sqrt(variance);
  return standard_deviation;
}
