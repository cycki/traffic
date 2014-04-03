package pakietowiec.Profiler;
simple LeakyBucket extends Profiler
{
    parameters:
        double byteFlow @unit("B") = default(100B);
        
        @class(LeakyBucket);
}