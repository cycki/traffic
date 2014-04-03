package pakietowiec.Scheudler;

simple Scheduler
{
    parameters:
        volatile double processDelay @unit("s") = default(0s);

        @display("i=block/join");

    gates:
        input  in[];
        output out;
}