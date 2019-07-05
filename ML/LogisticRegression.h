//
// Created by root on 28/05/19.
//

#ifndef DPPML_LOGISTICREGRESSION_H
#define DPPML_LOGISTICREGRESSION_H

#include <vector>
#include "DatasetReader.h"
#include <math.h>

using namespace std;

class LogisticRegression {
public:
    double alpha;
    vector<double> w;
    double th;
    DatasetReader *dt;
    int epochs;
    double static sigmoid(double x);
    vector<double> sigmoid_coeffs = {0.5, 0.15012, -0.0015930078125};
    vector<Record*> train_records;
    vector<Record*> test_records;
    string dataset_name;
    string datasets_path = "/home/st/Bureau/DPPML/DATA/Datasets/";
    int predict(Record* r);
    void fit();
    vector<int> test();
    double dot_product(vector<double> a, vector<double> b);
    double loss();
    double approx_sigmoid(double x);
    LogisticRegression();
};


#endif //DPPML_LOGISTICREGRESSION_H
