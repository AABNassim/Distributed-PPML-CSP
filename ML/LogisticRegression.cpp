//
// Created by root on 28/05/19.
//

#include "LogisticRegression.h"
#include "DatasetReader.h"
#include <iomanip>
#include <ctime>
#include <sstream>

using namespace std;

LogisticRegression::LogisticRegression(void) {
    alpha = 0.1;
    th = 0.5;
    dataset_name = "Edin";
    epochs = 200;
    dt = new DatasetReader(datasets_path + dataset_name + "/", 2, 9);
    for (int j = 0; j < 9; j++) {
        w.push_back(0);
    }
}

double LogisticRegression::sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

double LogisticRegression::approx_sigmoid(double x) {
    return sigmoid_coeffs[0] + sigmoid_coeffs[1] * x + sigmoid_coeffs[2] * x * x * x;
}

double LogisticRegression::dot_product(vector<double> a, vector<double> b) {
    double sum = 0.0;
    for (int i = 0; i < a.size(); i++) {
        sum += a[i] * b[i];
    }
    return sum;
}

int LogisticRegression::predict(Record* r) {
    double wx = 0.0, prob = 0.0;
    int label = 0;
    int d = r->dim();
    //cout << "WTH " << d << endl;

    //cout << "W = ";
    //for (int j = 0; j < d; j++) {
    //    cout << w[j] << "  ";
    //}
    //cout << " " << endl;
    for (int i = 0; i < d; i++) {
        wx += w[i] * r->values[i];
    }
    prob = sigmoid(wx);
    //cout << "PROB : " << prob << endl;
    if (prob >= th) {
        label = 1;
    } else {
        label = 0;
    }
    return label;
}

void LogisticRegression::fit() {
    // Read the hole data set
    train_records = dt->read_all_train_records();
    //int m = train_records.size();
    int m = 64;
    int d = train_records[0]->dim();


    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;

    oss << std::put_time(&tm, "%Y-%m-%d %H-%M");
    auto file_name = "PLAIN_APPROX_GRADS_" + oss.str();

    ofstream log_file;

    log_file.open(file_name);


    //cout << file_name << endl;
    //cout << "GOD d = " << d << endl;



    for (int i = 0; i < m; i++) {
        Record* rcd = train_records[i];
        //cout << "Record num " << rcd->id << ". Values: ";
        //for (int j = 0; j < d; j++) {
        //    cout << rcd->values[j] << " ";
        //}
        //cout << " Label: " << rcd->label << endl;
    }

    for (int e = 0; e < epochs; e++) {
        double grad[d];
        for (int j = 0; j < d; j++) {
            grad[j] = 0.0;
        }
        for (int i = 0; i < m; i++) {
            Record* rcd = train_records[i];
            /*for (int k = 0; k < d; k++) {
                cout << rcd->values[k] << " ";
            }*/
            //cout << " " << endl;
            //cout << "Label: " << rcd->label << endl;
            double wx = 0.0;
            for (int j = 0; j < d; j++) {
                wx += w[j] * rcd->values[j];
            }
            double sig = approx_sigmoid(wx);
            //cout << "Sig value:" << sig << ", " << endl;

            for (int j = 0; j < d; j++) {
                grad[j] += (sig - rcd->label) * rcd->values[j];
            }
        }
        //ut << "Weights : ";
        cout << "Gradient : " << e << endl;
        for (int j = 0; j < d; j++) {
            grad[j] = grad[j] * alpha;
            w[j] -= grad[j];
            log_file << grad[j] << ", ";
        }
        log_file << " " << endl;
        cout << "Loss : " << loss() << endl;
        ///cout << "" << endl;
    }
    log_file.close();
    /*cout << "Weight vector" << endl;
    for (int j = 0; j < d; j++) {
        cout << w[j] << " ";
    }
    cout << " " << endl;*/
}



double LogisticRegression::loss() {
    double loss = 0.0;
    int m = train_records.size();
    int d = train_records[0]->dim();
    for (int i = 0; i < m; i++) {
        Record* rcd = train_records[i];
        double wx = 0.0;
        for (int j = 0; j < d; j++) {
            wx += w[j] * rcd->values[j];
        }
        double h = sigmoid(wx);
        int y = rcd->label;
        loss += -y * log(h) - (1 - y) * (1 - h);
    }
    return loss;
}

vector<int> LogisticRegression::test() {
    test_records = dt->read_all_test_records();
    int m = test_records.size();
    vector <int> labels(m);
    cout << "khra " << m << endl;
    // Read the hole data set
    for (int i = 0; i < m; i++) {
        cout << test_records[i]->label;
        labels[i] = predict(test_records[i]);
    }
    cout << "" << endl;
    return labels;
}