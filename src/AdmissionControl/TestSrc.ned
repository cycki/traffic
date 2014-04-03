package pakietowiec.AdmissionControl;

import pakietowiec.Generator.AbstractGenerator;

simple ExponentialGenerator1 extends AbstractGenerator
{
    parameters:
        double mean @unit("s") = default(1s);
        @class(ExponentialGenerator);
}

simple PoissonGenerator1 extends AbstractGenerator
{
    parameters:
        double lambda = default(10);
        @class(PoissonGenerator);
}
simple OnOffGenerator1 extends AbstractGenerator
{
    parameters:
        double shape = default(2.0);
        double scale = default(2.0);
        double shift = default(2.0);

        @class(OnOffGenerator);
}
simple MMPPGenerator1 extends AbstractGenerator
{
    parameters:
        int quantState = default(3);
        int maxPack = default(10);
        string transP = default("");
        string poissonLambdaP = default("");
        @class(MMPPGenerator);
}
simple SourceAdmissionControl1 extends AdmissionControl
{
    parameters:

        int deny = default(2);

        @class(SourceAdmissionControl);
}

simple Receiver1
{
    parameters:
        @display("i=block/process");
         @class(Receiver);
    gates:
        input in;
}

network SRC
{
    @display("bgb=733,431");
    submodules:
        gen: PoissonGenerator1 {
            parameters:
                @display("i=block/routing,cyan;p=488,240;is=vl");
        }
        gen2: ExponentialGenerator1 {
            parameters:
                @display("i=block/routing,red;p=191,240;is=vl");
        }
        gen3: OnOffGenerator1 {
            parameters:
                @display("i=block/routing,green;p=290,240;is=vl");
        }
        gen4: MMPPGenerator1 {
            parameters:
                @display("i=block/routing,magenta;p=389,240;is=vl");
        }
        rec: Receiver1 {
            parameters:
                @display("i=,gold;p=42,86");
        }


     admission: SourceAdmissionControl1 {
            @display("p=166,391");
        }

    connections:
        gen.out --> admission.in++;
        gen2.out --> admission.in++;
        gen3.out --> admission.in++;
        gen4.out --> admission.in++;
        admission.out --> rec.in;


}
