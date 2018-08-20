#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <random>

int main() {

   std::string header = "Population\tWinners\tLosers\tPercentage";

   std::cout << header << std::endl;

   // minimum size of population
   constexpr unsigned int minPopulation = 1000;
   constexpr unsigned int maxPopulation = 100000;
   constexpr unsigned int populationStepSize = 1000;
   constexpr unsigned int iterationsPerStep = 1000;

   std::random_device randomDevice;
   std::mt19937 generator(randomDevice());

   for (unsigned int populationSize = minPopulation; populationSize <= maxPopulation; populationSize += populationStepSize) {

      unsigned long winners = 0;
      unsigned long losers = 0;

      std::vector<bool> people(populationSize, true);
      for (unsigned int j = 0; j < iterationsPerStep; j++) {

         unsigned int peopleRemaining = populationSize;

         do {
            std::uniform_int_distribution<unsigned int> distribution(0, peopleRemaining - 1);

            for (unsigned int i = 0; i < peopleRemaining; i++) {
               unsigned int choice;
               // subjects do not choose themselves, presumably
               do {
                  choice = distribution(generator);
               }
               while (choice == i);
               people[choice] = false;
            }

            unsigned int newPeopleRemaining = 0;

            for (unsigned int i = 0; i < peopleRemaining; i++) {
               newPeopleRemaining = people[i] ? newPeopleRemaining + 1 : newPeopleRemaining;
               people[i] = true;
            }

            peopleRemaining = newPeopleRemaining;

         } while (peopleRemaining > 1);

         winners = (peopleRemaining == 1) ? winners + 1 : winners;
         losers = (peopleRemaining == 0) ? losers + 1 : losers;
      }
      float winningPercentage = winners / (float)(winners + losers);
      float losingPercentage = losers / (float)(winners + losers);

      std::cout << std::fixed;

      std::cout << populationSize << "\t\t" << winners << "\t\t" << losers << "\t\t";

      std::cout << std::fixed << std::setprecision(4) << winningPercentage << std::endl;
   }
}