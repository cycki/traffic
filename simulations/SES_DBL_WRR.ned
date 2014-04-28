
import pakietowiec.Generator.AbstractGenerator;
import pakietowiec.AdmissionControl.AdmissionControl;
import pakietowiec.Profiler.LeakyBucket;
import pakietowiec.Scheudler.WRRScheduler;
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
simple ReceiverA
{
    parameters:
        @display("i=block/process");
        @class(Receiver);
    gates:
        input in;
}
network Simulations
{
    @display("bgb=560,446");
    submodules:

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
                @display("i=,gold;p=490,201");
        }
        admission_based_on_session: SessionAdmissionControlA {
            @display("p=178,200");
        }
        leakyBucket1: LeakyBucket {
            parameters:
                @display("p=178,345");
        }
        leakyBucket2: LeakyBucket {
            parameters:
                @display("p=334,345");
        }
        WWR: WRRScheduler {

            @display("p=334,201");
        }



    connections:

        expo2.out --> admission_based_on_session.in++;
        pss2.out --> admission_based_on_session.in++;
        on2.out --> admission_based_on_session.in++;
        mm2.out --> admission_based_on_session.in++;
        admission_based_on_session.out --> leakyBucket1.in++;
        leakyBucket1.out --> leakyBucket2.in++;
        leakyBucket2.out --> WWR.in++;
        WWR.out --> rec2.in;

}
