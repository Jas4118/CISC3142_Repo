// This file shows basic functions of reading in a CSV file using C++98
// Please add your name to your code! 

/* Homework Objective: fix this program to match the requirements listed: 
  1. successfully reads all lines of the input file
  2. calculate the average price per brand, average price per category 
  3. writes to an output file
  4. for each unique year, list the count of skus and also print out the skus as a list i.e. 2000 (3): 111, 211, 311 and make a new line per year.

All programs must be able to compile in C++98 standard (the default version on Linux Machine). That means you cannot use the new features of C++11! :(

*/
#include <iterator>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <map>
using namespace std; 
int findAvgBrand(vector<string> vBrand,vector<string> vPrice, ofstream &out_stream){
  float temp=0.0;
  float totalSum=0.0;
  float totalNum=0.0;
  string pl,m="";
  map<string,string>brandMap; 
  for (int i=0;i<vBrand.size();i++){
   if(brandMap.count(vBrand[i])==0){
      brandMap.insert(make_pair(vBrand[i],vPrice[i]));
   } else {
      pl=brandMap.at(vBrand[i]);
      pl.append(", ");
      pl.append(vPrice[i]);
      brandMap.erase(vBrand[i]);
      brandMap.insert(make_pair(vBrand[i],pl));
          
   }

  }


  map<string,string >::iterator itr;

  for(itr = brandMap.begin(); itr != brandMap.end(); itr++){
    string iBrand = itr->first;
    string iPrice = itr->second;
    stringstream ps(iPrice);
    while(getline(ps,m,',')){
      stringstream w(m);
      w>>temp;
      totalSum=totalSum+temp;
      totalNum=totalNum+1.0;
    }
    out_stream<<iBrand<<" Average: "<< totalSum/totalNum<< endl;
    totalSum=0.0;
    totalNum=0.0;
  }
}
int findAvgCategory(vector<string> vCategory,vector<string> vPrice,ofstream &out_stream){
  float temp=0.0;
  float totalSum=0.0;
  float totalNum=0.0;
  string pl,m="";
  map<string,string> categoryMap;

  for (int i=0;i<vCategory.size();i++){
   if(categoryMap.count(vCategory[i])==0){
      categoryMap.insert(make_pair(vCategory[i],vPrice[i]));

   } else {
      pl=categoryMap.at(vCategory[i]);
      pl.append(", ");
      pl.append(vPrice[i]);
      categoryMap.erase(vCategory[i]);
      categoryMap.insert(make_pair(vCategory[i],pl));

   }

  }

  map<string,string >::iterator itr;

  for(itr = categoryMap.begin(); itr != categoryMap.end(); itr++){
    string iCategory = itr->first;
    string iPrice = itr->second;
    stringstream ps(iPrice);
    while(getline(ps,m,',')){
      stringstream w(m);
      w>>temp;
      totalSum=totalSum+temp;
      totalNum=totalNum+1.0;
    }
    out_stream<<iCategory<<" Average: "<< totalSum/totalNum<< endl;
    totalSum=0.0;
    totalNum=0.0;
  }
}
void findSKU(vector<string> vYear,vector<string> vSKU,ofstream &out_stream){
  int totalNum=0;
  string pl,m="";
  map<string,string> yearMap;

  for (int i=0;i<vYear.size();i++){
   if(yearMap.count(vYear[i])==0){
      yearMap.insert(make_pair(vYear[i],vSKU[i]));

   } else {
      pl=yearMap.at(vYear[i]);
      pl.append(", ");
      pl.append(vSKU[i]);
      yearMap.erase(vYear[i]);
      yearMap.insert(make_pair(vYear[i],pl));

   }

  }

  map<string,string >::iterator itr;

  for(itr = yearMap.begin(); itr != yearMap.end(); itr++){
    string iYear = itr->first;
    string iSKU = itr->second;
    stringstream ps(iSKU);
    while(getline(ps,m,',')){
      totalNum=totalNum+1;
      
    }
    out_stream<<iYear<<" Count: "<< totalNum<<" "<< iSKU << endl;
    totalNum=0;
  }
}

int main() {

     // define variables
     string sku, brand, category, year, price; 
     vector<string> vSKU;
     vector<string> vBrand;
     vector<string> vCategory;
     vector<string> vYear;
     vector<string> vPrice;

     ifstream in_stream;
     ofstream out_stream;

     in_stream.open("data.csv"); //opening the file.
     ofstream myfile("output.txt");
     out_stream.open("output.txt");//putting info into output file
     

     if (!in_stream.fail()) { //if the file is open

     string line;
     getline(in_stream,line); //Skips column title line
     while (getline(in_stream, line)) { //while the end of file is NOT reached
     stringstream ss(line);  
     // Fields: sku,brand,category,year,price

     getline(ss, sku, ',');
     stringstream ssku(sku); 
     string iSKU;
     ssku >> iSKU;
     vSKU.push_back(iSKU);

     getline(ss, brand, ',');
     vBrand.push_back(brand);

     getline(ss, category, ',');
     vCategory.push_back(category);

     getline(ss, year, ','); 
     stringstream syear(year);
     string iYear;
     syear >> iYear;
     vYear.push_back(iYear);

     getline(ss, price, '\n'); 
     stringstream sprice(price);
     string fPrice;
     sprice >> fPrice;
     vPrice.push_back(fPrice);
     
    }

    in_stream.close(); //closing the file cout << "Number of entries: " << i-1 << endl;

   } else {
    out_stream << "Unable to open file"; 
   }
 
  //output values 
  out_stream << "SKU" << "\t" << "Brand" << "\t" << "Category Year" << "\t" << "Price" << endl; 

  for (int j = 0; j < vSKU.size(); j++) {
    out_stream << vSKU[j] << "\t" << vBrand[j] << "\t" << vCategory[j] << "\t" << vYear[j] << "\t" << vPrice[j] << endl;
  }
  
  findAvgBrand(vBrand, vPrice, out_stream);
  findAvgCategory(vCategory, vPrice, out_stream);
  findSKU(vYear, vSKU, out_stream);
  out_stream << endl;
}
