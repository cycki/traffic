package pakietowiec.Profiler;
simple LoadSheddingProfiler extends Profiler
{
    parameters:
        int criticalBandwidth @unit("MB") = default(1MB);
        
        @class(LoadSheddingProfiler);
}
