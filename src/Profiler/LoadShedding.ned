package pakietowiec.Profiler;
simple LoadShedding extends Profiler
{
    parameters:
        int criticalBandwidth @unit("MB") = default(1MB);
        
        @class(LoadShedding);
}
