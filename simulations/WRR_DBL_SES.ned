
import pakietowiec.Generator.AbstractGenerator;
import pakietowiec.AdmissionControl.AdmissionControl;
import pakietowiec.Profiler.LeakyBucket;
import pakietowiec.Scheudler.WRRScheduler;

network Simulations4
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
                @display("i=,gold;p=491,201");
        }
        admission_based_on_session: SessionAdmissionControlA {
            @display("p=334,200");
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

            @display("p=178,201");
        }



    connections:

        expo2.out --> WWR.in++;
        pss2.out --> WWR.in++;
        on2.out --> WWR.in++;
        mm2.out --> WWR.in++;
        WWR.out --> leakyBucket1.in++;
        leakyBucket1.out --> leakyBucket2.in++;
        leakyBucket2.out --> admission_based_on_session.in++;
        admission_based_on_session.out --> rec2.in;

}
