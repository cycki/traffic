package pakietowiec.AdmissionControl;

import pakietowiec.Generator.AbstractGenerator;

simple ExponentialGenerator3 extends AbstractGenerator
{
    parameters:
        double mean @unit("s") = default(1s);
        @class(ExponentialGenerator);
}

simple PoissonGenerator3 extends AbstractGenerator
{
    parameters:
        double lambda = default(10);
        @class(PoissonGenerator);
}
simple OnOffGenerator3 extends AbstractGenerator
{
    parameters:
        double shape = default(2.0);
        double scale = default(2.0);
        double shift = default(2.0);

        @class(OnOffGenerator);
}
simple MMPPGenerator3 extends AbstractGenerator
{
    parameters:
        int quantState = default(3);
        int maxPack = default(10);
        string transP = default("");
        string poissonLambdaP = default("");
        @class(MMPPGenerator);
}

simple MAvgAdmissionControl3 extends AdmissionControl
{
    parameters:
        double timeWindow @unit("s") = default(5.0s);
        double samplingPeriod @unit("s") = default(0.5s);
        double targetAvg @unit("b") = default(200b);
        @class(MAvgAdmissionControl);
}
simple Receiver3
{
    parameters:
        @display("i=block/process");
         @class(Receiver);
    gates:
        input in;
}

network AVG
{
    @display("bgb=733,431");
    submodules:
        gen: PoissonGenerator3 {
            parameters:
                @display("i=block/routing,cyan;p=488,240;is=vl");
        }
        gen2: ExponentialGenerator3 {
            parameters:
                @display("i=block/routing,red;p=191,240;is=vl");
        }
        gen3: OnOffGenerator3 {
            parameters:
                @display("i=block/routing,green;p=290,240;is=vl");
        }
        gen4: MMPPGenerator3 {
            parameters:
                @display("i=block/routing,magenta;p=389,240;is=vl");
        }
        rec: Receiver3 {
            parameters:
                @display("i=,gold;p=42,86");
        }


     admission: MAvgAdmissionControl3 {
            @display("p=166,391");
        }

    connections:
        gen.out --> admission.in++;
        gen2.out --> admission.in++;
        gen3.out --> admission.in++;
        gen4.out --> admission.in++;
        admission.out --> rec.in;


}
