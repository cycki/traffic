
import pakietowiec.Generator.AbstractGenerator;
import pakietowiec.AdmissionControl.REDAdmissionControl;
import pakietowiec.Profiler.JitterControl;
import pakietowiec.Scheudler.PriorityScheduler;

network Simulations3
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
            @display("p=504,200");
        }
        jitterControl: JitterControl {
            parameters:
                @display("p=329,201");
        }
        PriorityScheduler: PriorityScheduler {
            @display("p=158,201");
        }

    connections:

        expo2.out --> PriorityScheduler.in++;
        pss2.out --> PriorityScheduler.in++;
        on2.out --> PriorityScheduler.in++;
        mm2.out --> PriorityScheduler.in++;
        PriorityScheduler.out --> jitterControl.in++;
        jitterControl.out --> redJestSpoko.in++;
        redJestSpoko.out --> rec2.in;

}
