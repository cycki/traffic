#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include <Message_m.h>
#include <Generator.h>

class MMPPGenerator: public Generator {
private:
    int current_state;
    int states;
    float* upProbability;
    float* downProbability;
    float* lambdas;

protected:
    virtual void handleMessage(cMessage *msg);
    virtual void initialize();
    float getCurrentStateLambda();
};
Define_Module(MMPPGenerator);

void stofa(const char* string, int array_size, float* float_array,
        int max_floats) {
    int begin = 0;
    int end = 0;
    int j = 0;
    for (int i = 0; i < array_size && j < max_floats; ++i, ++j) {
        begin = i;
        end = begin;
        while (i < array_size && string[i] != ' ') {
            end++;
            i++;
        }
        char a[end - begin];
        for (int k = 0; k < end - begin; k++) {
            a[k] = string[begin + k];
        }
        float_array[j] = atof(a);
    }
}

void MMPPGenerator::initialize() {
    states = par("states");
    upProbability = new float[states];
    downProbability = new float[states];
    lambdas = new float[states];
    const char* up = par("upProbability").stringValue();
    const char* dp = par("downProbability").stringValue();
    const char* ps = par("lambdas").stringValue();
    stofa(up, opp_strlen(up), upProbability, states);
    stofa(dp, opp_strlen(dp), downProbability, states);
    stofa(ps, opp_strlen(ps), lambdas, states);
    current_state = 0;

    Generator::initialize();
}

void MMPPGenerator::handleMessage(cMessage *msg) {
    simtime_t time = poisson(getCurrentStateLambda(), 0);
    send(Generator::generateMessage(), "out");
    scheduleAt(simTime() + time + timeBetweenPackets, timeoutEvent);
}

float MMPPGenerator::getCurrentStateLambda() {
    double p = uniform(0.0, 1.0);

    EV << "state: " << current_state <<endl;
    EV << "p = " << p << endl;
    EV << "up Probability" << upProbability[current_state] << endl;

    if (p < upProbability[current_state]) {
        current_state++;
        current_state %= states;
    } else if (p
            < (downProbability[current_state] + upProbability[current_state])) {
        current_state--;
        if (current_state < 0){
            current_state = states - 1;
        }
    }
    return lambdas[current_state];
}
