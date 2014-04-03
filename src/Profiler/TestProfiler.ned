package pakietowiec.Profiler;

import pakietowiec.Generator.AbstractGenerator;
import pakietowiec.Profiler.LeakyBucket;


simple ExponentialGenerator extends AbstractGenerator
{
    parameters:
        double mean @unit("s") = default(1s);
        @class(ExponentialGenerator);
}

simple PoissonGenerator extends AbstractGenerator
{
    parameters:
        double lambda = default(10);
        @class(PoissonGenerator);
}
simple OnOffGenerator extends AbstractGenerator
{
    parameters:
        double shape = default(2.0);
        double scale = default(2.0);
        double shift = default(2.0);

        @class(OnOffGenerator);
}
simple MMPPGenerator extends AbstractGenerator
{
    parameters:
        int quantState = default(3);
        int maxPack = default(10);
        string transP = default("");
        string poissonLambdaP = default("");
        @class(MMPPGenerator);
}
simple LeakyBucket1 extends Profiler
{
    parameters:
        double byteFlow @unit("B") = default(100B);

        @class(LeakyBucket);
}

simple JitterControl1 extends Profiler
{
    parameters:
        double expectedPacketDelay @unit("s") = default(500ms);

        @signal[AveragePacketDelay](type="double");
        @statistic[packetDelay](title="average packet delay"; source="AveragePacketDelay"; record=vector; interpolationmode="none");
        @class(JitterControl);
}

simple LoadShedding1 extends Profiler
{
    parameters:
        int criticalBandwidth @unit("MB") = default(1MB);

        @class(LoadShedding);
}

simple TokenBucket1 extends Profiler
{
    parameters:
        int tokensMax @unit("MB") = default(1MB);
        int tokenIncrement @unit("KB") = default(64KB);

        @class(TokenBucket);
}
simple Receiver
{
    parameters:
        @display("i=block/process");
        @class(Receiver);
    gates:
        input in;
}

network Profil
{
    @display("bgb=770,623");
    submodules:

        pss: PoissonGenerator {
            parameters:
                @display("i=block/routing,cyan;p=411,200");
        }
        pss1: PoissonGenerator {
            parameters:
                @display("i=block/routing,cyan;p=411,200");
        }
        pss2: PoissonGenerator {
            parameters:
                @display("i=block/routing,cyan;p=403,200");
        }
        POISSON: PoissonGenerator {
            parameters:
                @display("i=block/routing,cyan;p=412,200;is=vl");
        }

        expo: ExponentialGenerator {
            parameters:
                @display("i=block/routing,red;p=499,200");
        }
        expo1: ExponentialGenerator {
            parameters:
                @display("i=block/routing,red;p=499,200");
        }
        expo2: ExponentialGenerator {
            parameters:
                @display("i=block/routing,red;p=499,200");
        }
        EXPONENTIAL: ExponentialGenerator {
            parameters:
                @display("i=block/routing,red;p=529,200;is=vl");
        }

        on: OnOffGenerator {
            parameters:
                @display("i=block/routing,green;p=186,200");
        }
        on1: OnOffGenerator {
            parameters:
                @display("i=block/routing,green;p=186,200");
        }
        on2: OnOffGenerator {
            parameters:
                @display("i=block/routing,green;p=186,200");
        }
        ON_OFF: OnOffGenerator {
            parameters:
                @display("i=block/routing,green;p=201,200;is=vl");
        }


        mm: MMPPGenerator {
            parameters:
                @display("i=block/routing,magenta;p=319,200");
        }
        mm1: MMPPGenerator {
            parameters:
                @display("i=block/routing,magenta;p=319,200");
        }
        mm2: MMPPGenerator {
            parameters:
                @display("i=block/routing,magenta;p=319,200");
        }
        MMPP: MMPPGenerator {
            parameters:
                @display("i=block/routing,magenta;p=307,200;is=vl");
        }

        rec: Receiver {
            parameters:
                @display("i=,gold;p=307,63");
        }
        rec1: Receiver {
            parameters:
                @display("i=,gold;p=432,52");
        }
        rec2: Receiver {
            parameters:
                @display("i=,gold;p=288,395");
        }
        rec3: Receiver {
            parameters:
                @display("i=,gold;p=442,402");
        }


        lb: LeakyBucket1 {
            @display("p=76,32");
        }
        jc: JitterControl1 {
            @display("p=676,52");
        }
        tb: TokenBucket1 {
            @display("p=57,410");
        }
        ls: LoadShedding1 {
            @display("p=685,410");
        }


    connections:

        expo.out --> lb.in++;
        pss.out --> lb.in++;
        on.out --> lb.in++;
        mm.out --> lb.in++;
        lb.out --> rec.in;

        expo1.out --> jc.in++;
        pss1.out --> jc.in++;
        on1.out --> jc.in++;
        mm1.out --> jc.in++;
        jc.out --> rec1.in;

        expo2.out --> tb.in++;
        pss2.out --> tb.in++;
        on2.out --> tb.in++;
        mm2.out --> tb.in++;
        tb.out --> rec2.in;

        EXPONENTIAL.out --> ls.in++;
        POISSON.out --> ls.in++;
        ON_OFF.out --> ls.in++;
       MMPP.out --> ls.in++;
        ls.out --> rec3.in;


}
