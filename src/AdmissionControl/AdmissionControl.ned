

package pakietowiec.AdmissionControl;

simple AdmissionControl
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
//        @signal[timeRequest](type = "double");
//        @statistic[timeRequestStat](title="Requests in time";record=histogram; source="timeRequest";interpolationmode="none";);
        volatile double processDelay @unit("s") = default(0s);
        
        @display("i=device/firewall");
        
    gates:
        input  in[];
        output out;
}