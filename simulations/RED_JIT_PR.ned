
import pakietowiec.Generator.AbstractGenerator;
import pakietowiec.AdmissionControl.REDAdmissionControl;
import pakietowiec.Profiler.JitterControl;
import pakietowiec.Scheudler.PriorityScheduler;
simple ExponentialGeneratorC extends AbstractGenerator
{
    parameters:
        double mean @unit("s") = default(1s);
        @display("is=s");
        @class(ExponentialGenerator);
}

simple PoissonGeneratorC extends AbstractGenerator
{
    parameters:
        double lambda = default(10);
        @display("is=s");
        @class(PoissonGenerator);
}
simple OnOffGeneratorC extends AbstractGenerator
{
    parameters:
        double shape = default(2.0);
        double scale = default(2.0);
        double shift = default(2.0);

        @display("is=s");
        @class(OnOffGenerator);
}
simple MMPPGeneratorC extends AbstractGenerator
{
    parameters:
        int quantState = default(3);
        int maxPack = default(10);
        string transP = default("");
        string poissonLambdaP = default("");
        @display("is=s");
        @class(MMPPGenerator);
}



simple ReceiverC
{
    parameters:
        @display("i=block/process");
        @class(Receiver);
    gates:
        input in;
}
network Simulations2
{
    @display("bgb=731,358");
    submodules:

        pss2: PoissonGeneratorC {
            parameters:
                @display("i=block/routing,cyan;p=24,185");
        }
        expo2: ExponentialGeneratorC {
            parameters:
                @display("i=block/routing,red;p=47,185");
        }
        on2: OnOffGeneratorC {
            parameters:
                @display("i=block/routing,green;p=47,208");
        }
        mm2: MMPPGeneratorC {
            parameters:
                @display("i=block/routing,magenta;p=24,208");
        }
        rec2: ReceiverC {
            parameters:
                @display("i=,gold;p=637,201");
        }

        redJestSpoko: REDAdmissionControl {
            @display("p=155,200");
        }
        jitterControl: JitterControl {
            parameters:
                @display("p=264,201");
        }
        PriorityScheduler: PriorityScheduler {
            @display("p=458,201");
        }

    connections:

        expo2.out --> redJestSpoko.in++;
        pss2.out --> redJestSpoko.in++;
        on2.out --> redJestSpoko.in++;
        mm2.out --> redJestSpoko.in++;
        redJestSpoko.out --> jitterControl.in++;
        jitterControl.out --> PriorityScheduler.in++;
        PriorityScheduler.out --> rec2.in;

}
