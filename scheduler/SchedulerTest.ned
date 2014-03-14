//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package scheduler;

simple FifoScheduler extends AbstractScheduler
{
    parameters:
        int maxQueueSize = default(1);
        @class(FifoScheduler);
}
simple LifoScheduler extends AbstractScheduler
{
    parameters:
        int maxQueueSize = default(1);
        @class(LifoScheduler);
}
simple PoissonGenerator extends generators.AbstractGenerator
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
    @display("bgb=791,409");
    submodules:
        
        sch1: LifoScheduler {
            @display("is=vl");
        }
        gen[6]: PoissonGenerator {
            parameters:
                @display("i=block/departure,#FF8000;p=93,166;is=vl");
        }
        rec1: Receiver {
            parameters:
                @display("i=block/arrival,gold;p=678,166;is=vl");
        }
    connections:
        gen[0].out --> sch1.in++;
        gen[1].out --> sch1.in++;
        gen[2].out --> sch1.in++;
        gen[3].out --> sch1.in++;
        gen[4].out --> sch1.in++;
        gen[5].out --> sch1.in++;
        sch1.out --> rec1.in;
}
