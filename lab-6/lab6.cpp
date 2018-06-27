#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
//main
int main(int argc, char *argv[])
{
    //predicted labels 5th col
    vector <double> labels;
       //featured vectors cols 1-4
    std::vector< std::vector <double> > data;
    std::ifstream infile(argv[1]);

    std::string line;
    //fill 2d array
    while(std::getline(infile,line))
    {
        std::vector<double> row;
        std::stringstream iss(line);
        std::string val;
        while(std::getline(iss,val,','))
        {
            try
            {
                double temp = std::stod(val);
                row.push_back(temp);
            }
            catch (...)
            {
                std::cout << "Bad input: " << val << std::endl;
            }
        }
        data.push_back(row);
    }
    //columns:
    //0.Sepal Length(cm)
    //1.Septal Width(cm)
    //2.Petal Length(cm)
    //3.Petal Width(cm)
    //labels vector Plant Species: -1 - Not Iris V. or 1 - Iris V.
  
    int numCorrect = 0;
    for (int row = 0; row < (signed)data.size(); row++)
    {
        double prediction;
        labels.push_back((data.at(row).at(4)));
        data.at(row).pop_back();
        //expert system
        if (data.at(row).at(2) > 0)
            prediction = 1;
        else
            prediction = -1;
        //if prediction is correct
        if (prediction == labels.at(row))
            numCorrect ++;
    }
    cout << "Percent correct: " << numCorrect << "%\n";
    
    //perceptron algorithm
    vector<double> weights;
    weights.push_back(0.25);
    weights.push_back(0.05);
    weights.push_back(-.15);
    weights.push_back(-.3);
    double lr = 0.05; //learning rate
    double error, y, weightedVal;
    double theta = 0.5;
    string outcome;
    //200 iterations
    for (int i = 0; i < 100; i++)
    {
        double totalCorrect = 0;
        //single iteration
        for (int row = 0; row < (signed)data.size(); row++)
        {
            double sum = 0;
            for (int col = 0; col < (signed)data.at(row).size(); col++)
            {
                weightedVal = data.at(row).at(col) * weights.at(col);
                sum += weightedVal;
            }
            y = sum - theta;
            
            //step function
            if (y > 0)
                y = 1;
            else
                y = 0;

            error = labels.at(row) - y; //desired - actual
            //cout << "Act: " << labels.at(row) << "\tDes: " << y << endl;
            if (error == 0)
            {
                outcome = "CORRECT!\n";
                totalCorrect++;
            }
            else
                outcome = "ERROR!\n";
            
        
            cout << "Iteration " << row + 1 << ": Weights are [" << 
                weights.at(0) << ", " << weights.at(1) << ", " << 
                weights.at(2) << ", " << weights.at(3) << 
                "], classification was " << outcome << error << endl; 
            
            //update weights
            weights.at(0) = weights.at(0) + lr * data.at(row).at(0) * error;
            weights.at(1) = weights.at(1) + lr * data.at(row).at(1) * error;
            weights.at(2) = weights.at(2) + lr * data.at(row).at(2) * error;
            weights.at(3) = weights.at(3) + lr * data.at(row).at(3) * error;
        }
        cout << "TOTAL CORRECT: " << totalCorrect << endl;
    }

    infile.close();
    return(0);
}
