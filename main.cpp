#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

int main() {

   const std::string filePath = "/Users/daniel/Documents/solitaria2.txt";
   std::ofstream logfile;
   logfile.open(filePath, std::ios::trunc);

   std::cout << "Population\tWinners\tPercentage" << std::endl;
   logfile << "Population\tWinners\tPercentage" << std::endl;

   // minimum size of population
   const int minpopulation = 1000;
   const int maxpopulation = 1000000;
   const int stepsize = 1000;
   const int iterationsperstep = 1000;

   // placeholders per iteration
   int winners = 0;
   int losers = 0;

   for (int k = minpopulation; k <= maxpopulation; k += stepsize) {

      for (int j = 0; j < iterationsperstep; j++) {
         std::vector<bool> people(k, 1);
         int max = k;

         do {
            for (int i = 0; i < max; i++) {
               people[rand() % max] = 0;
            }

            int newMax = 0;

            for (int i = 0; i < max; i++) {
               newMax = people[i] ? newMax + 1 : newMax;
            }

            for (int i = 0; i < newMax; i++) {
               people[i] = 1;
            }

            for (int i = newMax; i < max; i++) {
               people[i] = 0;
            }

            max = newMax;

         } while (max > 1);

         winners = (max == 1) ? winners + 1 : winners;
         losers = (max == 0) ? losers + 1 : losers;
      }
      float percentage = winners * stepsize / (float)(k * iterationsperstep);

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