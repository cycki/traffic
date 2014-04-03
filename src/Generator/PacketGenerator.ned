package pakietowiec.Generator;


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
    gates:
        input in;
}

network PacketGenerator
{
    @display("bgb=330,349");
    submodules:
        POISSON: PoissonGenerator {
            parameters:
                @display("i=block/routing,cyan;p=35,50");
        }
        EXPONENTIAL: ExponentialGenerator {
            parameters:
                @display("i=block/routing,red;p=35,120");
        }
        ON_OFF: OnOffGenerator {
            parameters:
                @display("i=block/routing,green;p=35,190");
        }
        MMPP: MMPPGenerator {
            parameters:
                @display("i=block/routing,magenta;p=35,261");
        }
        rec: Receiver {
            parameters:
                @display("i=,gold;p=200,50");
        }
        rec2: Receiver {
            parameters:
                @display("i=,gold;p=200,120");
        }
        rec3: Receiver {
            parameters:
                @display("i=,gold;p=200,190");
        }
        rec4: Receiver {
            parameters:
                @display("i=,gold;p=200,261");
        }
    connections:
        POISSON.out --> rec.in;
        EXPONENTIAL.out --> rec2.in;
        ON_OFF.out --> rec3.in;
        MMPP.out --> rec4.in;
}
