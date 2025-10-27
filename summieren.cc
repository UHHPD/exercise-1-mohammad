//moin!


#include<iostream>
#include<fstream>


using namespace std;



int main(){


  int a, b;
  int sum;
  ifstream file_reader;
  ofstream result_writer;
  file_reader.open("daten.txt");
  result_writer.open("datensumme.txt");
  while(file_reader>> a >> b){
    sum = a + b;
    result_writer << a << '\t' << b << '\t' << sum <<endl;
  }
  file_reader.close();
  result_writer.close();
  cout<<"done!"<<endl;
  return 0;
}
