/*
 * Name: Cody Graves
 * Program: MaxOnes
 * Date: 4/24/18
 */

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

struct sample
{
    int bit[32]; 
    int fitness;
};


//prototype functions
bool rand_test(int);
void populate(sample*, int);
bool test_fitness(sample*, int);
int selection(sample*, int, int);
void crossover(sample*, sample*, int, int, int, int&); 
bool newPopFull(int, int);
void mutate(sample*, int, int);
void killOldPop(sample*, sample*, int, int&);
void printSample(sample);

//main
int main()
{
    srand(time(NULL));
    int newPopSize = 0;
    int oldPopSize = 25;
    int pc = 90; 
    int pm = 1;
    sample oldPop[oldPopSize];
    sample newPop[oldPopSize];

    populate(oldPop, oldPopSize);
   
    int it = 0;
    int selectIndex;
    //continue until finding the perfect sample
    while (!test_fitness(oldPop, oldPopSize))//&& it == 0)
    {
        for (int i = 0; i < oldPopSize; i++)
        {
            if (rand_test(pc))
            {
                selectIndex = i;
                while(selectIndex == i)
                    selectIndex = selection(oldPop,oldPopSize,3);
                crossover(oldPop, newPop, i, selectIndex, oldPopSize, newPopSize);
                if (rand_test(pm))
                    mutate(newPop, newPopSize - 2, newPopSize - 1);
                if(newPopFull(oldPopSize, newPopSize))
                    killOldPop(oldPop, newPop, oldPopSize, newPopSize);
            }
        }
        it++;
        cout << "================================================\n";
    }
    return 0;
}

void printSample(sample individual)
{
    for (int i = 0; i < 32; i++)
        cout << individual.bit[i];
    cout << endl;
}

//mutate 2 individuals
void mutate(sample* pop, int index1, int index2)
{
    int bit1 = rand() % 32;
    int bit2 = rand() % 32;
    
    pop[index1].bit[bit1] = !pop[index1].bit[bit1];
    pop[index2].bit[bit2] = !pop[index2].bit[bit2];
    
}

bool newPopFull(int oSize, int nSize)
{
    if (nSize >= oSize)
        return true;
    return false;
}

void killOldPop(sample* oPop, sample* nPop, int oPopSize, int& nPopSize)
{
    for (int i = 0; i < oPopSize; i++)
    {
        oPop[i] = nPop[i];
        for (int j = 0; j < 32; j++)
            nPop[i].bit[j] = 0;
    }
    nPopSize = 0; 
}

//single point crossover between two individuals. 
void crossover(sample* oPop, sample* nPop, int index1, int index2, int oPopSize, int& nPopSize)
{
    //create 2 children samples from two selected samples in the old population
    
    
    sample newSamples[2];
    for (int i = 0; i < 32 / 2; i++)
    {
        newSamples[0].bit[i] = oPop[index1].bit[i];
        newSamples[1].bit[i] = oPop[index2].bit[i];
    }
    for (int i = 32 / 2; i < 32; i++)
    {
        newSamples[0].bit[i] = oPop[index2].bit[i];
        newSamples[1].bit[i] = oPop[index1].bit[i];
    }
    //cout << "\nMating: \n";
    //cout << "P1: ";
    //for (int j = 0; j < 32; j++)
        //cout << oPop[index1].bit[j];
    //cout << "\nP2: ";
    //for (int j = 0; j < 32; j++)
        //cout << oPop[index2].bit[j];

    for (int i = 0; i < 2; i++)
    {
        nPopSize ++;
        nPop[nPopSize-1] = newSamples[i];
        
        //cout << "\nC" << i+1 << ": ";
        //for (int j = 0; j < 32; j++)
            //cout << nPop[nPopSize-1].bit[j];

    }
}

//selects the most fit individual from a subset of a population
int selection(sample* population, int size, int subset)
{
    int index;
    int mostFit;
    for (int i = 0; i < subset; i++)
    {
       index = rand() % size;
       if (i == 0)
           mostFit = index;
       else if (population[index].fitness > population[mostFit].fitness)
           mostFit = index;
    }
    return mostFit;
}

//test fitness of each individual in a population
//fitness = number of 1s in sample. returns true if all 1s
bool test_fitness(sample* population, int size)
{
    for (int i = 0; i < size; i++)
    {
        int numOnes = 0;
        for (int j = 0; j < 32; j++)
        {
            if (population[i].bit[j] == 1)
                numOnes++;
        }
        population[i].fitness = numOnes;
        cout << "Individual " << i << ": [";
        for (int j = 0; j < 32; j++)
            cout << population[i].bit[j];
        cout << "] and fitness is " << population[i].fitness << endl;
        if (population[i].fitness == 32)
        {
            cout << "Termination condition met by sample " << i << ": ";
            for (int j = 0; j < 32; j++)
                cout << population[i].bit[j];
            cout << endl;
            return true;
        }
    }
    return false;
}

//populate a population of individuals with a randomized bit string
void populate(sample* population, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < 32; j++)
            population[i].bit[j] = rand() % 2;
}

//takes in a percent chance something happens, returns true or false
bool rand_test(int pc)
{
    int randomNum = rand() % 100;
    if (randomNum < pc)
        return true;
    else
        return false;
}
