package pakietowiec.AdmissionControl;

import pakietowiec.Generator.AbstractGenerator;
simple ExponentialGeneratorA extends AbstractGenerator
{
    parameters:
        double mean @unit("s") = default(1s);
        @display("is=s");
        @class(ExponentialGenerator);
}

simple PoissonGeneratorA extends AbstractGenerator
{
    parameters:
        double lambda = default(10);
        @display("is=s");
        @class(PoissonGenerator);
}
simple OnOffGeneratorA extends AbstractGenerator
{
    parameters:
        double shape = default(2.0);
        double scale = default(2.0);
        double shift = default(2.0);

        @display("is=s");
        @class(OnOffGenerator);
}
simple MMPPGeneratorA extends AbstractGenerator
{
    parameters:
        int quantState = default(3);
        int maxPack = default(10);
        string transP = default("");
        string poissonLambdaP = default("");
        @display("is=s");
        @class(MMPPGenerator);
}
simple SourceAdmissionControlA extends AdmissionControl
{
    parameters:


        string BlockedSources = default("");
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
                @display("i=block/routing,cyan;p=24,25");
        }
        expo: ExponentialGeneratorA {
            parameters:
                @display("i=block/routing,red;p=47,25");
        }
        on: OnOffGeneratorA {
            parameters:
                @display("i=block/routing,green;p=47,48");
        }
        mm: MMPPGeneratorA {
            parameters:
                @display("i=block/routing,magenta;p=24,48");
        }
        rec: ReceiverA {
            parameters:
                @display("i=,gold;p=584,41");
        }
        admission_based_on_source: SourceAdmissionControlA {
            @display("p=328,40");
        }

        pss1: PoissonGeneratorA {
            parameters:
                @display("i=block/routing,cyan;p=24,106");
        }
        expo1: ExponentialGeneratorA {
            parameters:
                @display("i=block/routing,red;p=47,106");
        }
        on1: OnOffGeneratorA {
            parameters:
                @display("i=block/routing,green;p=47,129");
        }
        mm1: MMPPGeneratorA {
            parameters:
                @display("i=block/routing,magenta;p=24,129");
        }
        rec1: ReceiverA {
            parameters:
                @display("i=,gold;p=584,122");
        }
        admission_based_on_priority: PriorityAdmissionControlA {
            @display("p=328,121");
        }

        pss2: PoissonGeneratorA {
            parameters:
                @display("i=block/routing,cyan;p=24,185");
        }
        expo2: ExponentialGeneratorA {
            parameters:
                @display("i=block/routing,red;p=47,185");
        }
        on2: OnOffGeneratorA {
            parameters:
                @display("i=block/routing,green;p=47,208");
        }
        mm2: MMPPGeneratorA {
            parameters:
                @display("i=block/routing,magenta;p=24,208");
        }
        rec2: ReceiverA {
            parameters:
                @display("i=,gold;p=584,201");
        }
        admission_based_on_session: SessionAdmissionControlA {
            @display("p=328,200");
        }
        pss4: PoissonGeneratorA {
            parameters:
                @display("i=block/routing,cyan;p=24,351");
        }
        expo4: ExponentialGeneratorA {
            parameters:
                @display("i=block/routing,red;p=47,351");
        }
        on4: OnOffGeneratorA {
            parameters:
                @display("i=block/routing,green;p=47,374");
        }
        mm4: MMPPGeneratorA {
            parameters:
                @display("i=block/routing,magenta;p=24,374");
        }
        rec4: ReceiverA {
            parameters:
                @display("i=,gold;p=584,367");
        }
        pss3: PoissonGeneratorA {
            parameters:
                @display("i=block/routing,cyan;p=24,279");
        }
        expo3: ExponentialGeneratorA {
            parameters:
                @display("i=block/routing,red;p=47,279");
        }
        on3: OnOffGeneratorA {
            parameters:
                @display("i=block/routing,green;p=47,302");
        }
        mm3: MMPPGeneratorA {
            parameters:
                @display("i=block/routing,magenta;p=24,302");
        }
        rec3: ReceiverA {
            parameters:
                @display("i=,gold;p=584,295");
        }
        admission_based_on_avg: MAvgAdmissionControlA {
            @display("p=328,294");
        }

        admission_red: REDAdmissionControl {
            @display("p=328,366");
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

        expo3.out --> admission_based_on_avg.in++;
        pss3.out --> admission_based_on_avg.in++;
        on3.out --> admission_based_on_avg.in++;
        mm3.out --> admission_based_on_avg.in++;
        admission_based_on_avg.out --> rec3.in;


        admission_red.out --> rec4.in;
        pss4.out --> admission_red.in++;
        expo4.out --> admission_red.in++;
        mm4.out --> admission_red.in++;
        on4.out --> admission_red.in++;
}
