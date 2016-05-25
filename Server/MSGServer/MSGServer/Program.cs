using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MSGServer
{
    class Program
    {
        public static int PORT = 9045;

        static void Main(string[] args)
        {
            AsynchronousUDPSocketListener.StartListening();
            AsynchronousTCPSocketListener.StartListening();
        }
    }
}
