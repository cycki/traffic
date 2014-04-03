package pakietowiec.AdmissionControl;

import pakietowiec.Generator.AbstractGenerator;
import pakietowiec.AdmissionControl.PriorityAdmissionControl;
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

simple PriorityAdmissionControl extends AdmissionControl
{
    parameters:
        int Maximal_priority = default(3);
        int Minimal_priority = default(0);
        @class(PriorityAC);
}

simple Receiver
{
    parameters:
        @display("i=block/process");
    gates:
        input in;
}

network PRIO
{
    @display("bgb=733,431");
    submodules:
        gen: PoissonGenerator {
            parameters:
                @display("i=block/routing,cyan;p=488,240;is=vl");
        }
        gen2: ExponentialGenerator {
            parameters:
                @display("i=block/routing,red;p=191,240;is=vl");
        }
        gen3: OnOffGenerator {
            parameters:
                @display("i=block/routing,green;p=290,240;is=vl");
        }
        gen4: MMPPGenerator {
            parameters:
                @display("i=block/routing,magenta;p=389,240;is=vl");
        }
        rec: Receiver {
            parameters:
                @display("i=,gold;p=42,86");
        }


     admission: PriorityAdmissionControl {
            @display("p=166,391");
        }

    connections:
        gen.out --> admission.in++;
        gen2.out --> admission.in++;
        gen3.out --> admission.in++;
        gen4.out --> admission.in++;
        admission.out --> rec.in;


}

