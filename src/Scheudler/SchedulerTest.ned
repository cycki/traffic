package pakietowiec.Scheudler;



simple PoissonGenerator extends pakietowiec.Generator.AbstractGenerator
{
    parameters:
        double lambda = default(5);
        @class(PoissonGenerator);
}
simple Receiver
{
    parameters:
        @display("i=block/process");
    gates:
        input in;
}

simple Receiver2
{
    parameters:
        @display("i=block/process");
        @class(Receiver);
    gates:
        input in;
}

network SchedulerTest
{
    @display("bgb=775,1002");
    submodules:

        LIFO: LIFO {
            @display("is=vl;p=273,199");
        }
        FIFO: FIFO {
            @display("is=vl;p=280,80");
        }

        WeightedRoundRobin: WRR {
            @display("is=vl;p=273,327");
        }
        RoundRobin: RR {
            @display("is=vl;p=273,466");
        }
        RoundRobin2: RRScheduler {
            @display("is=vl;p=273,586");
        }
        PriorityScheduler: PriorityScheduler {
            @display("is=vl;p=273,700");
        }

        gen[6]: PoissonGenerator {
            parameters:
                @display("i=block/departure,#FF8000;p=78,199;is=vl");
        }
        gen2[6]: PoissonGenerator {
            parameters:
                @display("i=block/departure,#FF8000;p=78,80;is=vl");
        }
        gen3[6]: PoissonGenerator {
            parameters:
                @display("i=block/departure,#FF8000;p=78,327;is=vl");
        }
        gen4[6]: PoissonGenerator {
            parameters:
                @display("i=block/departure,#FF8000;p=72,466;is=vl");
        }
        gen5[6]: PoissonGenerator {
            parameters:
                @display("i=block/departure,#FF8000;p=72,586;is=vl");
        }
        gen6[6]: PoissonGenerator {
            parameters:
                @display("i=block/departure,#FF8000;p=72,700;is=vl");
        }
        rec1: Receiver {
            parameters:
                @display("i=block/arrival,gold;p=678,199;is=vl");
        }
        rec2: Receiver {
            parameters:
                @display("i=block/arrival,gold;p=678,80;is=vl");
        }
        rec3: Receiver {
            parameters:
                @display("i=block/arrival,gold;p=678,327;is=vl");
        }
        rec4: Receiver {
            parameters:
                @display("i=block/arrival,gold;p=678,466;is=vl");
        }
        rec5: Receiver {
            parameters:
                @display("i=block/arrival,gold;p=678,586;is=vl");
        }
        rec6: Receiver {
            parameters:
                @display("i=block/arrival,gold;p=678,700;is=vl");
        }
    connections:
        gen[0].out --> LIFO.in++;
        gen[1].out --> LIFO.in++;
        gen[2].out --> LIFO.in++;
        gen[3].out --> LIFO.in++;
        gen[4].out --> LIFO.in++;
        gen[5].out --> LIFO.in++;

        gen2[0].out --> FIFO.in++;
        gen2[1].out --> FIFO.in++;
        gen2[2].out --> FIFO.in++;
        gen2[3].out --> FIFO.in++;
        gen2[4].out --> FIFO.in++;
        gen2[5].out --> FIFO.in++;

        gen3[0].out --> WeightedRoundRobin.in++;
        gen3[1].out --> WeightedRoundRobin.in++;
        gen3[2].out --> WeightedRoundRobin.in++;
        gen3[3].out --> WeightedRoundRobin.in++;
        gen3[4].out --> WeightedRoundRobin.in++;
        gen3[5].out --> WeightedRoundRobin.in++;

        gen4[0].out --> RoundRobin.in++;
        gen4[1].out --> RoundRobin.in++;
        gen4[2].out --> RoundRobin.in++;
        gen4[3].out --> RoundRobin.in++;
        gen4[4].out --> RoundRobin.in++;
        gen4[5].out --> RoundRobin.in++;

        gen5[0].out --> RoundRobin2.in++;
        gen5[1].out --> RoundRobin2.in++;
        gen5[2].out --> RoundRobin2.in++;
        gen5[3].out --> RoundRobin2.in++;
        gen5[4].out --> RoundRobin2.in++;
        gen5[5].out --> RoundRobin2.in++;

        gen6[0].out --> PriorityScheduler.in++;
        gen6[1].out --> PriorityScheduler.in++;
        gen6[2].out --> PriorityScheduler.in++;
        gen6[3].out --> PriorityScheduler.in++;
        gen6[4].out --> PriorityScheduler.in++;
        gen6[5].out --> PriorityScheduler.in++;


        LIFO.out --> rec1.in;
        FIFO.out --> rec2.in;
        WeightedRoundRobin.out --> rec3.in;
        RoundRobin.out --> rec4.in;
        RoundRobin2.out --> rec5.in;
        PriorityScheduler.out --> rec6.in;
}
