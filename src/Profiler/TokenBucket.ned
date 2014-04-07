package pakietowiec.Profiler;

simple TokenBucket extends Profiler
{
    parameters:
        int tokensMax @unit("MB") = default(1MB);
        int tokenIncrement @unit("KB") = default(64KB);
        
        @class(TokenBucket);
}