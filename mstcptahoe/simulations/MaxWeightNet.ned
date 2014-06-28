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

package mstcp2.simulations;

import mstcp2.Source;
import mstcp2.Sink;
import mstcp2.MaxWeight;
//
// TODO auto-generated type
//
network MaxWeightNet
{
    @display("bgl=2");
    submodules:
        S1: Source {
            @display("p=70,44");
        }
        S2: Source {

            @display("p=70,121");
        }

        S3: Source {
            @display("p=70,233");
        }
        S4: Source {

            @display("p=70,306");
        }
        D1: Sink {
            @display("p=327,44");
        }
        D2: Sink {

            @display("p=327,121");
        }

        D3: Sink {
            @display("p=327,233");
        }
        D4: Sink {
            @display("p=327,306");
        }
        MW1: MaxWeight {

            @display("p=154,181;is=vl");
        }
       
    connections:
        S1.out --> MW1.in++;
        MW1.out++ --> D1.in;
        
        S2.out --> MW1.in++;
        MW1.out++ --> D2.in;

        S3.out --> MW1.in++;
        MW1.out++ --> D3.in;
        
        S4.out --> MW1.in++;
        MW1.out++ --> D4.in;

        S1.in <-- D1.out;
        S2.in <-- D2.out;

        S3.in <-- D3.out;
        S4.in <-- D4.out;

}
