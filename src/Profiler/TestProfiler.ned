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
    @display("bgb=770,623");
    submodules:

        pss: PoissonGenerator {
            parameters:
                @display("i=block/routing,cyan;p=74,463");
        }
        pss1: PoissonGenerator {
            parameters:
                @display("i=block/routing,cyan;p=74,313");
        }
        pss2: PoissonGenerator {
            parameters:
                @display("i=block/routing,cyan;p=74,170");
        }
        pss3: PoissonGenerator {
            parameters:
                @display("i=block/routing,cyan;p=74,33");
        }

        expo: ExponentialGenerator {
            parameters:
                @display("i=block/routing,red;p=35,463");
        }
        expo1: ExponentialGenerator {
            parameters:
                @display("i=block/routing,red;p=35,313");
        }
        expo2: ExponentialGenerator {
            parameters:
                @display("i=block/routing,red;p=35,170");
        }
        expo3: ExponentialGenerator {
            parameters:
                @display("i=block/routing,red;p=35,33");
        }

        on: OnOffGenerator {
            parameters:
                @display("i=block/routing,green;p=74,502");
        }
        on1: OnOffGenerator {
            parameters:
                @display("i=block/routing,green;p=74,352");
        }
        on2: OnOffGenerator {
            parameters:
                @display("i=block/routing,green;p=74,209");
        }
        on3: OnOffGenerator {
            parameters:
                @display("i=block/routing,green;p=74,72");
        }


        mm: MMPPGenerator {
            parameters:
                @display("i=block/routing,magenta;p=35,502");
        }
        mm1: MMPPGenerator {
            parameters:
                @display("i=block/routing,magenta;p=35,352");
        }
        mm2: MMPPGenerator {
            parameters:
                @display("i=block/routing,magenta;p=35,209");
        }
        mm3: MMPPGenerator {
            parameters:
                @display("i=block/routing,magenta;p=35,72");
        }

        rec: Receiver {
            parameters:
                @display("i=,gold;p=528,487");
        }
        rec1: Receiver {
            parameters:
                @display("i=,gold;p=528,333");
        }
        rec2: Receiver {
            parameters:
                @display("i=,gold;p=528,191");
        }
        rec3: Receiver {
            parameters:
                @display("i=,gold;p=528,51");
        }


        leakyBucket: LeakyBucket {
            @display("p=246,487");
        }
        jitterControl: JitterControl {
            @display("p=246,333");
        }
        tokenBucket: TokenBucket {
            @display("p=246,191");
        }
        loadShedding: LoadShedding {
            @display("p=246,51");
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

        expo3.out --> loadShedding.in++;
        pss3.out --> loadShedding.in++;
        on3.out --> loadShedding.in++;
        mm3.out --> loadShedding.in++;
        loadShedding.out --> rec3.in;


}
