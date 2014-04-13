package pakietowiec.AdmissionControl;

import pakietowiec.Generator.AbstractGenerator;

network REDTEST
{
    @display("bgb=733,431");
    submodules:

        expo: ExponentialGeneratorA {
            parameters:
                @display("i=block/routing,red;p=52,256;is=l");
        }

        rec: ReceiverA {
            parameters:
                @display("i=,gold;p=408,256");
        }
        redJestSpoko: REDAdmissionControl {
            @display("p=229,255");
        }


    connections:
        expo.out --> redJestSpoko.in++;
        redJestSpoko.out --> rec.in;




}
