#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

int main() {

   const std::string filePath = "/Users/daniel/Documents/solitaria2.txt";
   std::ofstream logfile;
   logfile.open(filePath, std::ios::trunc);

   int winners = 0;
   int losers = 0;

   const int min = 0;
   const int maxpopulation = 1000000;
   const int step = 1000;

   const int overallIterations = 1000;

   std::cout << "Population\tWinners\tPercentage" << std::endl;
   logfile << "Population\tWinners\tPercentage" << std::endl;

   for (int k = step; k <= maxpopulation; k += step) {

      for (int j = 0; j < overallIterations; j++) {
         std::vector<bool> myset(k, 1);
         int max = k;

         do {
            for (int i = min; i < max; i++) {
               myset[rand() % max] = 0;
            }

            int newMax = 0;

            for (int i = min; i < max; i++) {
               newMax = myset[i] ? newMax + 1 : newMax;
            }
            for (int i = min; i < newMax; i++) {
               myset[i] = 1;
            }
            for (int i = newMax; i < max; i++) {
               myset[i] = 0;
            }

            max = newMax;

         } while (max > 1);

         winners = (max == 1) ? winners + 1 : winners;
         losers = (max == 0) ? losers + 1 : losers;
      }
      float percentage = winners * step / (float)(k * overallIterations);

      std::cout << std::fixed;
      logfile << std::fixed;

      std::cout << k << "\t" << winners << "\t";
      logfile << k << "\t" << winners << "\t";

      std::cout << std::fixed;
      logfile << std::fixed;

      std::cout << std::setprecision(4);
      logfile << std::setprecision(4);

      std::cout << percentage ;
      logfile << percentage ;

      std::cout << std::endl;
      logfile << std::endl;

      logfile << std::flush;
   }
   logfile.close();
}