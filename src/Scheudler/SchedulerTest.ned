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


network SchedulerTest
{
    @display("bgb=775,757");
    submodules:

        LIFO: LIFO {
            @display("is=vl;p=366,199");
        }
        FIFO: FIFO {
            @display("is=vl;p=366,80");
        }

        RoundRobin: RRScheduler {
            @display("is=vl;p=366,327");
        }
        PriorityScheduler: PriorityScheduler {
            @display("is=vl;p=366,466");
        }
        SJFScheduler: SJFScheduler {
            @display("is=vl;p=366,607");
        }
        WWR: WRRScheduler {

            @display("p=360,707");
        }

        gen[6]: PoissonGenerator {
            parameters:
                @display("i=block/departure,#FF8000;p=78,199");
        }
        gen2[6]: PoissonGenerator {
            parameters:
                @display("i=block/departure,#FF8000;p=78,80");
        }
        gen3[6]: PoissonGenerator {
            parameters:
                @display("i=block/departure,#FF8000;p=78,327");
        }
        gen4[6]: PoissonGenerator {
            parameters:
                @display("i=block/departure,#FF8000;p=72,466");
        }
        gen5[6]: PoissonGenerator {
            parameters:
                @display("i=block/departure,#FF8000;p=72,607");
        }
        gen6[6]: PoissonGenerator {

            @display("i=block/departure,#FF8000;p=72,707");
        }

        rec1: Receiver {
            parameters:
                @display("i=block/arrival,gold;p=678,199");
        }
        rec2: Receiver {
            parameters:
                @display("i=block/arrival,gold;p=678,80");
        }
        rec3: Receiver {
            parameters:
                @display("i=block/arrival,gold;p=678,327");
        }
        rec4: Receiver {
            parameters:
                @display("i=block/arrival,gold;p=678,466");
        }
        rec5: Receiver {
            parameters:
                @display("i=block/arrival,gold;p=678,607");
        }
        rec6: Receiver {
            parameters:
                @display("i=block/arrival,gold;p=678,707");
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



        gen3[0].out --> RoundRobin.in++;
        gen3[1].out --> RoundRobin.in++;
        gen3[2].out --> RoundRobin.in++;
        gen3[3].out --> RoundRobin.in++;
        gen3[4].out --> RoundRobin.in++;
        gen3[5].out --> RoundRobin.in++;



        gen4[0].out --> PriorityScheduler.in++;
        gen4[1].out --> PriorityScheduler.in++;
        gen4[2].out --> PriorityScheduler.in++;
        gen4[3].out --> PriorityScheduler.in++;
        gen4[4].out --> PriorityScheduler.in++;
        gen4[5].out --> PriorityScheduler.in++;

        gen5[0].out --> SJFScheduler.in++;
        gen5[1].out --> SJFScheduler.in++;
        gen5[2].out --> SJFScheduler.in++;
        gen5[3].out --> SJFScheduler.in++;
        gen5[4].out --> SJFScheduler.in++;
        gen5[5].out --> SJFScheduler.in++;

		gen6[0].out --> WWR.in++;
		gen6[1].out --> WWR.in++;
		gen6[2].out --> WWR.in++;
		gen6[3].out --> WWR.in++;
		gen6[4].out --> WWR.in++;
		gen6[5].out --> WWR.in++;


        LIFO.out --> rec1.in;
        FIFO.out --> rec2.in;
        RoundRobin.out --> rec3.in;
        PriorityScheduler.out --> rec4.in;
        SJFScheduler.out --> rec5.in;
        WWR.out --> rec6.in;
}
