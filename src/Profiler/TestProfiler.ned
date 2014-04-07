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
    @display("bgb=770,453");
    submodules:

        pss: PoissonGenerator {
            parameters:
                @display("i=block/routing,cyan;p=77,338");
        }
        pss1: PoissonGenerator {
            parameters:
                @display("i=block/routing,cyan;p=77,188");
        }
        pss2: PoissonGenerator {
            parameters:
                @display("i=block/routing,cyan;p=77,45");
        }
        expo: ExponentialGenerator {
            parameters:
                @display("i=block/routing,red;p=38,338");
        }
        expo1: ExponentialGenerator {
            parameters:
                @display("i=block/routing,red;p=38,188");
        }
        expo2: ExponentialGenerator {
            parameters:
                @display("i=block/routing,red;p=38,45");
        }
        on: OnOffGenerator {
            parameters:
                @display("i=block/routing,green;p=77,377");
        }
        on1: OnOffGenerator {
            parameters:
                @display("i=block/routing,green;p=77,227");
        }
        on2: OnOffGenerator {
            parameters:
                @display("i=block/routing,green;p=77,84");
        }
        mm: MMPPGenerator {
            parameters:
                @display("i=block/routing,magenta;p=38,377");
        }
        mm1: MMPPGenerator {
            parameters:
                @display("i=block/routing,magenta;p=38,227");
        }
        mm2: MMPPGenerator {
            parameters:
                @display("i=block/routing,magenta;p=38,84");
        }
        rec: Receiver {
            parameters:
                @display("i=,gold;p=531,362");
        }
        rec1: Receiver {
            parameters:
                @display("i=,gold;p=531,208");
        }
        rec2: Receiver {
            parameters:
                @display("i=,gold;p=531,66");
        }
        leakyBucket: LeakyBucket {
            @display("p=249,362");
        }
        jitterControl: JitterControl {
            @display("p=249,208");
        }
        tokenBucket: TokenBucket {
            @display("p=249,66");
        }


    connections:

        expo.out --> leakyBucket.in++;
        pss.out --> leakyBucket.in++;
        on.out --> leakyBucket.in++;
        mm.out --> leakyBucket.in++;
        leakyBucket.out --> rec.in;

        expo1.out --> jitterControl.in++;
        pss1.out --> jitterControl.in++;
        on1.out --> jitterControl.in++;
        mm1.out --> jitterControl.in++;
        jitterControl.out --> rec1.in;

        expo2.out --> tokenBucket.in++;
        pss2.out --> tokenBucket.in++;
        on2.out --> tokenBucket.in++;
        mm2.out --> tokenBucket.in++;
        tokenBucket.out --> rec2.in;


}
