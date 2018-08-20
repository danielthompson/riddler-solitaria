#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <random>
#include <atomic>
#include <thread>
#include <future>

// minimum size of population
constexpr unsigned int minPopulation = 1000;
constexpr unsigned int maxPopulation = 100000;
constexpr unsigned int populationStepSize = 1000;
constexpr unsigned int iterationsPerStep = 1000;
constexpr float oneOverIterationsPerStep = 1.0f / iterationsPerStep;

std::random_device randomDevice;
std::mt19937 generator(randomDevice());

unsigned int runIteration(const unsigned int populationSize) {
   std::vector<bool> people(populationSize, true);

   unsigned int winners = 0;

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

      if (peopleRemaining == 1) {
         winners++;
      }
   }
   return winners;
}

int main() {

   std::string header = "Population\tWinners\tLosers\tPercentage";

   std::cout << header << std::endl;

   const unsigned threads = std::thread::hardware_concurrency();

   for (unsigned int populationSize = minPopulation; populationSize <= maxPopulation; populationSize += populationStepSize) {

      std::vector<unsigned int> winnersVector = std::vector<unsigned int>(threads);

      std::vector<std::future<unsigned int>> futures = std::vector<std::future<unsigned int>>(threads);

      for (int i = 0; i < threads; i++) {
         futures[i] = std::async(std::launch::async, runIteration, populationSize);
      }

      for (int i = 0; i < threads; i++) {
         winnersVector[i] = futures[i].get();
      }

      unsigned int winners = 0;

      for (auto& element : winnersVector) {
         winners += element;
      }

      const unsigned int losers = iterationsPerStep * threads - winners;

      float winningPercentage = winners / (float)(iterationsPerStep * threads);

      std::cout << std::fixed;

      std::cout << populationSize << "\t\t" << winners << "\t\t" << losers << "\t\t";

      std::cout << std::fixed << std::setprecision(4) << winningPercentage << std::endl;
   }
}