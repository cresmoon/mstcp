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

package mstcp2;

//
// TODO auto-generated type
//
import mstcp2.Fifo;
import mstcp2.MaxWTimer;


network MaxWeight
{
    gates:
        input in[];
        output out[];

    submodules:
        Q1: Fifo {
            @display("p=51,68");
        }
        Q2: Fifo {
            @display("p=51,201");
        }

        Q3: Fifo {
            @display("p=200,201");
        }
        Q4: Fifo {

            @display("p=200,68");
        }
        Clk: MaxWTimer {

            @display("p=131,136");
        }
    connections:
        Q1.out --> out++;
        in++ --> Q1.in;
        Q2.out --> out++;
        in++ --> Q2.in;

        Q3.out --> out++;
        in++ --> Q3.in;
        Q4.out --> out++;
        in++ --> Q4.in;


        Clk.gate++ <--> Q1.gate;
        Clk.gate++ <--> Q2.gate;

        Clk.gate++ <--> Q3.gate;
        Clk.gate++ <--> Q4.gate;

}
