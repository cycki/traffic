package pakietowiec.AdmissionControl;

import pakietowiec.Generator.AbstractGenerator;

simple ExponentialGeneratorA extends AbstractGenerator
{
    parameters:
        double mean @unit("s") = default(1s);
        @class(ExponentialGenerator);
}

simple PoissonGeneratorA extends AbstractGenerator
{
    parameters:
        double lambda = default(10);
        @class(PoissonGenerator);
}
simple OnOffGeneratorA extends AbstractGenerator
{
    parameters:
        double shape = default(2.0);
        double scale = default(2.0);
        double shift = default(2.0);

        @class(OnOffGenerator);
}
simple MMPPGeneratorA extends AbstractGenerator
{
    parameters:
        int quantState = default(3);
        int maxPack = default(10);
        string transP = default("");
        string poissonLambdaP = default("");
        @class(MMPPGenerator);
}
simple SourceAdmissionControlA extends AdmissionControl
{
    parameters:

        int deny = default(2);

        @class(SourceAdmissionControl);
}
simple SessionAdmissionControlA extends AdmissionControl
{
    parameters:
        double timeWindow @unit("s") = default(5.0s);
        double samplingPeriod @unit("s") = default(0.5s);
        double terminationTimeout @unit("s") = default(5.0s);
        int targetBandwidth @unit("b") = default(500b);
        int maxBandwith @unit("b") = default(1024b);
        @class(SessionAdmissionControl);
}
simple PriorityAdmissionControlA extends AdmissionControl
{
    parameters:
        int Maximal_priority = default(3);
        int Minimal_priority = default(0);
        @class(PriorityAdmissionControl);
}
simple MAvgAdmissionControlA extends AdmissionControl
{
    parameters:
        double timeWindow @unit("s") = default(5.0s);
        double samplingPeriod @unit("s") = default(0.5s);
        double targetAvg @unit("b") = default(200b);
        @class(MAvgAdmissionControl);
}
simple ReceiverA
{
    parameters:
        @display("i=block/process");
        @class(Receiver);
    gates:
        input in;
}

network AdmissionControlNetwork
{
    @display("bgb=733,431");
    submodules:
        pss: PoissonGeneratorA {
            parameters:
                @display("i=block/routing,cyan;p=508,231;is=l");
        }
        expo: ExponentialGeneratorA {
            parameters:
                @display("i=block/routing,red;p=191,240;is=l");
        }
        on: OnOffGeneratorA {
            parameters:
                @display("i=block/routing,green;p=290,240;is=l");
        }
        mm: MMPPGeneratorA {
            parameters:
                @display("i=block/routing,magenta;p=389,240;is=l");
        }
        rec: ReceiverA {
            parameters:
                @display("i=,gold;p=40,66");
        }
        admission_based_on_source: SourceAdmissionControlA {
            @display("p=191,53");
        }

        pss1: PoissonGeneratorA {
            parameters:
                @display("i=block/routing,cyan;p=494,240;is=l");
        }
        expo1: ExponentialGeneratorA {
            parameters:
                @display("i=block/routing,red;p=191,240;is=l");
        }
        on1: OnOffGeneratorA {
            parameters:
                @display("i=block/routing,green;p=290,240;is=l");
        }
        mm1: MMPPGeneratorA {
            parameters:
                @display("i=block/routing,magenta;p=389,240;is=l");
        }
        rec1: ReceiverA {
            parameters:
                @display("i=,gold;p=29,383");
        }
        admission_based_on_priority: PriorityAdmissionControlA {
            @display("p=191,390");
        }

        pss2: PoissonGeneratorA {
            parameters:
                @display("i=block/routing,cyan;p=494,240;is=l");
        }
        expo2: ExponentialGeneratorA {
            parameters:
                @display("i=block/routing,red;p=191,240");
        }
        on2: OnOffGeneratorA {
            parameters:
                @display("i=block/routing,green;p=290,240");
        }
        mm2: MMPPGeneratorA {
            parameters:
                @display("i=block/routing,magenta;p=389,240;is=l");
        }
        rec2: ReceiverA {
            parameters:
                @display("i=,gold;p=670,382");
        }
        admission_based_on_session: SessionAdmissionControlA {
            @display("p=463,382");
        }

        POISSON: PoissonGeneratorA {
            parameters:
                @display("i=block/routing,cyan;p=508,240;is=vl");
        }
        EXPONENTIAL: ExponentialGeneratorA {
            parameters:
                @display("i=block/routing,red;p=184,240;is=vl");
        }
       ON_OFF: OnOffGeneratorA {
            parameters:
                @display("i=block/routing,green;p=290,240;is=vl");
        }
        MMPP: MMPPGeneratorA {
            parameters:
                @display("i=block/routing,magenta;p=395,240;is=vl");
        }
        rec3: ReceiverA {
            parameters:
                @display("i=,gold;p=647,66");
        }
        admission_based_on_avg: MAvgAdmissionControlA {
            @display("p=447,65");
        }

    connections:
        expo.out --> admission_based_on_source.in++;
        pss.out --> admission_based_on_source.in++;
        on.out --> admission_based_on_source.in++;
        mm.out --> admission_based_on_source.in++;
        admission_based_on_source.out --> rec.in;

        expo1.out --> admission_based_on_priority.in++;
        pss1.out --> admission_based_on_priority.in++;
        on1.out --> admission_based_on_priority.in++;
        mm1.out --> admission_based_on_priority.in++;
        admission_based_on_priority.out --> rec1.in;

        expo2.out --> admission_based_on_session.in++;
        pss2.out --> admission_based_on_session.in++;
        on2.out --> admission_based_on_session.in++;
        mm2.out --> admission_based_on_session.in++;
        admission_based_on_session.out --> rec2.in;

        EXPONENTIAL.out --> admission_based_on_avg.in++;
        POISSON.out --> admission_based_on_avg.in++;
        ON_OFF.out --> admission_based_on_avg.in++;
        MMPP.out --> admission_based_on_avg.in++;
        admission_based_on_avg.out --> rec3.in;


}
