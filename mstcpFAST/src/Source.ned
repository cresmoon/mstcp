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
simple Source
{
     parameters:
        volatile double sendInterval @unit(s);
        @display("i=block/source");
        @signal[cwnd](type="long");
        @statistic[cwnd](title="window length";record=vector,count,sum,mean,timeavg,max;interpolationmode=sample-hold);

		@signal[seqnum](type="long");
		@statistic[seqnum](title="ack receive";record=vector,count,sum,mean,timeavg,max;interpolationmode=sample-hold);
		
    gates:
        input	in;
        output 	out;
}
