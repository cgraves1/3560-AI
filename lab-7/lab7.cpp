#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <ctime>
using namespace std;
//main

struct neuron
{
    double desired, charge, output, delta;
    //double weight = (rand() % 200 - 100) * .01;
    vector <double> weights;
    double theta = (rand() % 200 - 100) * .01;
};


//calculates the charge of neuron n from values of neurons in another layer l
void calcCharge(vector <neuron> l, neuron &n)
{
    double sum = 0;
    for (int i = 0; i < (signed)l.size(); i++)
        sum += l.at(i).output * n.weights.at(i);
    n.charge = sum - n.theta;
}

void activation(neuron &n)
{
    n.output = 1.0 / (1.0 + exp(-n.charge));
}

//calculates delta of a neuron using values from neurons of another layer l
void calcDelta(vector <neuron> l, neuron &n, int neuronNum, bool out)
{
    if (out) //output layer neuron
    {
        n.delta = n.output * (1 - n.output) * (n.desired - n.output);
        //cout << "Desired: " << n.desired << "\nOutput: " << n.output << "\nDelta: " << n.delta << endl << endl;
    }
    else //hidden layer neuron
    {
        double sum = 0;
        for (int i = 0; i < (signed)l.size(); i++)
            sum += l.at(i).delta * l.at(i).weights.at(neuronNum);
        n.delta = n.output * (1 - n.output) * sum;
        //cout << "Output: " << n.output << "\nDelta: " << n.delta << endl << endl;
    }
}

//calculate neuron weight
void calcWeight(vector<neuron> l, neuron &n, double a)
{
    for (int i = 0; i < (signed)n.weights.size(); i++)
    {
        //cout << "OldWeight " << i << ": " << n.weights.at(i) << endl;
        //output layer
        n.weights.at(i) = n.weights.at(i) + a * l.at(i).output * n.delta;
        //cout << "NewWeight " << i << ": " << n.weights.at(i) << endl;
    }
    n.theta = n.theta + a * (-1) * n.delta;
}


void feedForward(vector< vector <neuron> > &l)
{
    //cout << "Feed Forward\n";
    for (int i = 1; i < (signed)l.size(); i++) //each layer, skip input layer
    {
        for (int j = 0; j < (signed)l.at(i).size(); j++) //each neuron
        {
            calcCharge(l.at(i-1), l.at(i).at(j)); //calc charge of neuron using prev. layer
            activation(l.at(i).at(j)); //calc output
            //cout << "Layer: " << i << ", Neuron: " << j << "\nCharge: " << l.at(i).at(j).charge 
                 //<< "\nOutput: " << l.at(i).at(j).output << endl << endl;
        }
    }
}

void backProp(vector< vector <neuron> > &l, double a)
{
    //cout << "\nBack Propagation\n";
    for (int i = l.size() - 1; i > 0;  i--) //each layer, starting at output layer until first hidden layer
    {
        bool isOutputNeuron = false;
        if (i == (signed)l.size() - 1)
            isOutputNeuron = true;

        for (int j = 0; j < (signed)l.at(i).size(); j ++) //each neuron
        {
            //cout << "Layer: " << i << ", Neuron: " << j << "\n";
            if (isOutputNeuron)
                calcDelta(l.at(i), l.at(i).at(j), j, isOutputNeuron);
            else
                calcDelta(l.at(i+1), l.at(i).at(j), j, isOutputNeuron);

            calcWeight(l.at(i-1), l.at(i).at(j), a);
            //cout << endl;
        }
    }
}

void initWeights(vector< vector <neuron> > &l)
{
    for (int i = 1; i < (signed)l.size(); i++) //# layers
        for (int j = 0; j < (signed)l.at(i).size(); j++) //# neurons
            for (int k = 0; k < (signed)l.at(i-1).size(); k++) //# weights = # neurons in prev layer
            {
                l.at(i).at(j).weights.push_back((rand() % 200 - 100) * .01);
                //cout << "Layer " << i << ", Neuron " << j << ", Weight " << 
                     //k << ": " << l.at(i).at(j).weights.at(k) << ", Theta "
                       //<< ": " << l.at(i).at(j).theta << endl;
            }
            cout << endl;
}

int main(int argc, char *argv[])
{
    srand(time(0));
    vector <vector <neuron> > layers;
    //data values cols 1-4
    vector <vector <neuron> > data;
    //predicted labels cols 5-7. 1-Setosa, 2-Versicolor, 3-Virginica
    vector<double> label1;
    vector<double> label2;
    vector<double> label3; 

    //featured vectors cols 1-4
    std::ifstream infile(argv[1]);

    std::string line;
    //fill 2d array
    while(std::getline(infile,line))
    {
        //std::vector<double> row;
        std::vector<neuron> row;
        neuron tmp;
        std::stringstream iss(line);
        std::string val;
        while(std::getline(iss,val,','))
        {
            try
            {
                //double temp = std::stod(val);
                tmp.output = std::stod(val);
                row.push_back(tmp);
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
    //labels vector Plant Species: 
    //4.Iris Setosa (0-1)
    //5.Iris Versicolor (0-1)
    //6.Iris Virginica (0-1)
  
    for (int row = 0; row < (signed)data.size(); row++)
    {
        //save last three columns/labels
        label1.push_back((data.at(row).at(4).output));
        label2.push_back((data.at(row).at(5).output));
        label3.push_back((data.at(row).at(6).output));
        data.at(row).pop_back();
        data.at(row).pop_back();
        data.at(row).pop_back();
    }
    
    //create layers
    vector <neuron> tmpHiddenLayer;
    vector <neuron> tmpOutputLayer;

    //create first layer with data input
    layers.push_back(data.at(0));     
    //create 3 neurons for hidden and output layers
    for (int i = 0; i < 3; i++)
    {
        neuron tmp;
        tmpHiddenLayer.push_back(tmp);
        tmpOutputLayer.push_back(tmp);
    }
    layers.push_back(tmpHiddenLayer);
    layers.push_back(tmpOutputLayer);

    //initialize weights for hidden and output layers
    initWeights(layers);

    double mad = 0.0;
    for (int epoch = 0; epoch < 200; epoch++)
    {
        for (int i = 0; i < 150; i++)//(signed)data.size(); i++) 
        {
            layers.at(0) = data.at(i); //replace input layer data
            //assigned desired 
            layers.at(2).at(0).desired = label1.at(i);
            layers.at(2).at(1).desired = label2.at(i);
            layers.at(2).at(2).desired = label3.at(i);
            
            feedForward(layers);
            backProp(layers,.05);

            cout << "Epoch " << epoch << ", Iteration " << i << ": Prediction is [";
            double performance = 0.0;
            for (int j = 0; j < (signed)layers.at(2).size(); j++)
            {
                performance += abs(layers.at(2).at(j).desired - layers.at(2).at(j).output);
                cout << layers.at(2).at(j).output;
                if (j != (signed)layers.at(2).size() - 1)
                    cout << ", ";
            }
            cout << "].\n";
            mad+= performance / data.size();
            cout << "MAD: " << mad << endl;
            cout << "-----------------------------------------------------\n";
        }
        mad = 0.0;
    }

    infile.close();
    return(0);
}
