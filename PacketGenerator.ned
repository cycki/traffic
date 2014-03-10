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

simple ExponentialGenerator extends AbstractGenerator
{
    parameters:
        double mean = default(2);
        @class(ExponentialGenerator);
}
simple PoissonGenerator extends AbstractGenerator
{
    parameters:
        double lambda = default(5);
        @class(PoissonGenerator);
}
simple OnOff extends AbstractGenerator
{
    parameters:
        double lambda = default(15);
        double offTime = default(12);
        double probability = default(0.3);
        @class(OnOff);
}
simple MMPPGenerator extends AbstractGenerator
{
    parameters:
        int states = default(4);
        int max_packets = default(20);
        string upProbability = default("0.2 0.2 0.2 0");
        string downProbability = default("0.0 0.2 0.2 0.2");
        string lambdas = default("100 200 300 400");
        @class(MMPPGenerator);
}

simple Receiver
{
    parameters:
        @display("i=block/process");
    gates:
        input in;
}

network PacketGenerator
{
    @display("bgb=330,349");
    submodules:
        gen: PoissonGenerator {
            parameters:
                @display("i=,cyan;p=35,50");
        }
        gen2: ExponentialGenerator {
            parameters:
                @display("i=,red;p=35,120");
        }
        gen3: OnOff {
            parameters:
                @display("i=,green;p=35,190");
        }
        gen4: MMPPGenerator {
            parameters:
                @display("i=,magenta;p=35,261");
        }
        rec: Receiver {
            parameters:
                @display("i=,gold;p=200,50");
        }
        rec2: Receiver {
            parameters:
                @display("i=,gold;p=200,120");
        }
        rec3: Receiver {
            parameters:
                @display("i=,gold;p=200,190");
        }
        rec4: Receiver {
            parameters:
                @display("i=,gold;p=200,261");
        }
    connections:
        gen.out --> rec.in;
        gen2.out --> rec2.in;
        gen3.out --> rec3.in;
        gen4.out --> rec4.in;
}
