package pakietowiec.Profiler;

simple Profiler
{
    parameters:
        int maxQueueSize = default(0);
        double bandwidthCalcTick @unit("s") = 1s;
        double endTime @unit("s") = default(0s);
        volatile double processDelay @unit("s") = default(0s);
        
        @signal[Input](type="double");
        @signal[Output](type="double");
        @statistic[inputBandwidth](title="input bandwidth"; source="Input"; record=vector; interpolationmode="none");
        @statistic[outputBandwidth](title="output bandwidth"; source="Output"; record=vector; interpolationmode="none");
        @display("i=block/bucket");
        
    gates:
        input  in[];
        output out;
}