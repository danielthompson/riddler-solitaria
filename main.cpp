#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <random>

int main() {

   const std::string filePath = "/Users/daniel/Documents/solitaria2.txt";
   std::ofstream logfile;
   logfile.open(filePath, std::ios::trunc);

   std::cout << "Population\tWinners\tPercentage" << std::endl;
   logfile << "Population\tWinners\tPercentage" << std::endl;

   // minimum size of population
   constexpr unsigned int minPopulation = 1000;
   constexpr unsigned int maxPopulation = 100000;
   constexpr unsigned int populationStepSize = 1000;
   constexpr unsigned int iterationsPerStep = 100;

   std::random_device randomDevice;
   std::mt19937 generator(randomDevice());
   std::uniform_int_distribution<> distribution(0);

   // placeholders per iteration
   int winners = 0;
   int losers = 0;

   for (int populationSize = minPopulation; populationSize <= maxPopulation; populationSize += populationStepSize) {

      std::vector<bool> people(populationSize, true);
      for (int j = 0; j < iterationsPerStep; j++) {

         int peopleRemaining = populationSize;

         do {
            for (int i = 0; i < peopleRemaining; i++) {
               people[distribution(generator) % peopleRemaining] = false;
            }

            int newPeopleRemaining = 0;

            for (int i = 0; i < peopleRemaining; i++) {
               newPeopleRemaining = people[i] ? newPeopleRemaining + 1 : newPeopleRemaining;
               people[i] = true;
            }

            peopleRemaining = newPeopleRemaining;

         } while (peopleRemaining > 1);

         winners = (peopleRemaining == 1) ? winners + 1 : winners;
         losers = (peopleRemaining == 0) ? losers + 1 : losers;
      }
      float percentage = winners * populationStepSize / (float)(populationSize * iterationsPerStep);

      std::cout << std::fixed;
      logfile << std::fixed;

      std::cout << populationSize << "\t" << winners << "\t";
      logfile << populationSize << "\t" << winners << "\t";

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