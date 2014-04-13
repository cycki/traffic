package pakietowiec.Scheudler;

simple Scheduler
{
    parameters:
        @signal[delay](type = "double");
        @statistic[packetDelay](title = "Packet delay"; source = "delay"; record = vector, histogram; interpolationmode="none");
        @signal[interval](type="double");
        @statistic[packetInterval](title="packet intervals"; source="interval"; record=vector, histogram; interpolationmode="none");
        @signal[rejected](type="int");
        @statistic[rejectedCount](title="liczba odrzuconych"; source="rejected"; record=count; interpolationmode="none";);
        @signal[bandwidth](type="int");
        @statistic[bandwidthStat](title="przepustowosc";source="bandwidth";record=vector; interpolationmode="none";);
        
        volatile double processDelay @unit("s") = default(0s);

        @display("i=block/join");

    gates:
        input  in[];
        output out;
}