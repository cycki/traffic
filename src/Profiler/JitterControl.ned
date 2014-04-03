package pakietowiec.Profiler;

simple JitterControl extends Profiler
{
    parameters:
        double expectedPacketDelay @unit("s") = default(500ms);        
        @signal[AveragePacketDelay](type="double");
        @statistic[packetDelay](title="average packet delay"; source="AveragePacketDelay"; record=vector; interpolationmode="none");
        @class(JitterControl);
}
